#include "Application.h"
#include "SimulationManager.h"
#include "XMLParser.h"
#include "ObjectFactory.h"
#include "Interpreter.h"
#include "LuaConsoleCallback.h"
#include "ScriptEventFactoryCallback.h"
#include "components/Script.h"
#include "PluginManager.h"
#include "bindings/tolua_moon.h"
#include "moonet/NetworkManager.h"
#include "NetworkMessages.h"
#include "TaskTimer.h"
#include <mlog/Log.h>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osg/Timer>
#include <osgUtil/UpdateVisitor>
#include <osg/io_utils>
#include <sys/stat.h>
#include <errno.h>

#ifdef WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace moonet;
using namespace mlog;

namespace moon {
	
	Application::Application()
	:	name("moon"),
		done(false),
		lastTime(0),
		endTime(0),
		nonRealtimeSteps(0),
		targetFrameRate(30),
		averageFrameRate(0),
		sleepTime(0),
		maxSleepTime(100000),
		exitCode(0),
		customViewer(false)
	{
		for (unsigned int i = 0; i < FPS_AVG_NUM; i++)
			framerates[i] = 0;
		framerateCounter = 0;
	}
	
	Application::~Application()
	{
		dout(1) << "\nShutting down\n";
		if (scenario.valid())
			scenario->removeRemoteObjects();
		NetworkManager::instance().removeListener(&scenarioListener);
		if (NetworkManager::instance().isDoingStatistics())
			NetworkManager::instance().printStatistics();
		if (!NetworkManager::instance().isServer())
			NetworkManager::instance().shutdown();
		config = NULL;
		netgame = NULL;
		setScenario(NULL);
		if (viewer.valid() && viewer->getConsoleWindow())
		{
			viewer->getConsoleWindow()->saveHistory(getSettingsPath() + "/console_history.txt");
		}
		if (NetworkManager::instance().isServer())
			NetworkManager::instance().shutdown();
		ObjectFactory::instance().clearTemplates();
		PluginManager::instance().unload();
	}
	
	void Application::init()
	{
		initPaths();
		initViewer();
		initInterpreter();
		initNetwork();
		initPlugins();
	}
	
	void Application::initPaths()
	{
		/// Find units data file (units.dat)
		std::string ufile = osgDB::findDataFile("units.dat");
		if (ufile.length() > 0)
			XMLParser::initUnits(ufile);
		else
			dout(WARN) << "Units data file 'units.dat' not found\n";
	}
	
	void Application::initViewer()
	{
		if (!viewer)
			viewer = new Viewer(new osgViewer::Viewer);
		viewer->getOsgViewer()->realize();
	}
	
	void Application::initInterpreter()
	{
		// Setup Lua interpreter
		Interpreter& lua = Interpreter::instance();
		lua.loadStandardLibs();
		if (!lua.loadLib("moon", tolua_moon_open))
			dout(ERROR) << "Loading moon bindings: " << lua.getError() << "\n";
		lua.setGlobal("app", this, "moon::Application");
		lua.setGlobal("scheduler", &scheduler, "moon::Scheduler");
		lua.setGlobal("sim", &SimulationManager::instance(), "moon::SimulationManager");
		lua.setGlobal("plugin", &PluginManager::instance(), "moon::PluginManager");
		lua.setGlobal("net", &NetworkManager::instance(), "moonet::NetworkManager");
		lua.newTable("objects");	lua.commitTable();
		ObjectFactory::instance().setCallback(new ScriptEventFactoryCallback);
		Interpreter::initialized = true;
		
		if (viewer.valid()) {
			// Export viewer to interpreter
			Interpreter::instance().setGlobal("viewer", viewer.get(), "moon::Viewer");
			Interpreter::instance().setGlobal("editor", viewer->getEditHandler(), "moon::EditHandler");
			// Setup console connection
			if (viewer->getConsoleWindow()) {
				viewer->getConsoleWindow()->setCallback(new LuaConsoleCallback(&Interpreter::instance()));
				Interpreter::instance().setGlobal("console", viewer->getConsoleWindow(), "mdraw::ConsoleWindow");
				viewer->getConsoleWindow()->loadHistory(getSettingsPath() + "/console_history.txt");
			}
		}
	}
	
	void Application::initNetwork()
	{
		NetworkManager::instance().setObjectFactory(&ObjectFactory::instance());
		NetworkManager::instance().addListener(this);
		NetworkManager::instance().addListener(&scenarioListener);		
		NetworkManager::instance().addListener(&scriptEventNetworkListener);		
	}
	
	void Application::initPlugins()
	{
		PluginManager::instance().initialize();
	}
	
	/// \param gameName Name of the network game
	/// \param playerName Name of player - may be omitted (in which case a dedicated server is created)
	void Application::host(const std::string& gameName, const std::string& playerName)
	{
		if (netgame.valid())
			disconnect();
		std::string theGameName = gameName;
		if (gameName.length() == 0)
			theGameName = "NetGame";
		Player *player = NULL;
		if (playerName.length() > 0) {
			player = new Player(playerName);
			dout(0) << "Hosting network game '" << theGameName << "' as '" << playerName << "'\n";
		} else
			dout(0) << "Dedicated server for network game '" << theGameName << "'\n";
		NetworkManager::instance().init(true, player);
		netgame = new NetworkGame;
		NetworkManager::instance().setObjectPriority(netgame.get(), 100);
		netgame->setName(theGameName);
		if (scenario.valid())
			netgame->setScenarioName(scenario->getName());
		netgame->construct();
		NetworkGame::registerListener(this);
	}
	
	/// \param peer Server address
	/// \param playerName Name of player - may be omitted (in which case the game is joined as observer)
	void Application::join(const std::string& peer, const std::string& playerName)
	{
		if (netgame.valid())
			disconnect();
		Player *player = NULL;
		if (playerName.length() > 0) {
			player = new Player(playerName);
			dout(0) << "Joining network game at " << peer << " as '" << playerName << "'\n";
		} else
			dout(0) << "Joining network game at " << peer << " as observer\n";
		NetworkManager::instance().init(false, player, peer);
		NetworkGame::registerListener(this);
	}
	
	void Application::disconnect()
	{
		netgame = NULL;
		if (scenario.valid())
			scenario->removeRemoteObjects();
		NetworkManager::instance().shutdown();
		NetworkGame::unregisterListener(this);
	}
	
	void Application::update(const double dt)
	{
		// Update script function scheduler
		TaskTimer::instance().beginTask("Scheduler");
		if (nonRealtimeSteps == 0)
			scheduler.update(dt * SimulationManager::instance().getTimeScale());
		else
			for (int i = 0; i < nonRealtimeSteps; i++)
				scheduler.update(SimulationManager::instance().getTimeStep());
		TaskTimer::instance().endTask("Scheduler");
		
		// Update control handler
		TaskTimer::instance().beginTask("Controls");
		if (nonRealtimeSteps == 0)
			ControlHandler::instance().update(dt * SimulationManager::instance().getTimeScale());
		else
			for (int i = 0; i < nonRealtimeSteps; i++)
				ControlHandler::instance().update(SimulationManager::instance().getTimeStep());
		TaskTimer::instance().endTask("Controls");
		
		// Update simulation and network
		if (NetworkManager::instance().isServer()) {
			TaskTimer::instance().beginTask("Simulation");
			if (nonRealtimeSteps == 0)
				SimulationManager::instance().update(dt);
			else
				for (int i = 0; i < nonRealtimeSteps; i++)
					SimulationManager::instance().step();
			TaskTimer::instance().endTask("Simulation");
					
			TaskTimer::instance().beginTask("Network");
			if (netgame.valid())
				netgame->setGameTime(SimulationManager::instance().getTime());
			NetworkManager::instance().update(dt);
			TaskTimer::instance().endTask("Network");
		} else {
			TaskTimer::instance().beginTask("Network");
			NetworkManager::instance().update(dt);
			TaskTimer::instance().endTask("Network");

			TaskTimer::instance().beginTask("Simulation");
			if (nonRealtimeSteps == 0)
				SimulationManager::instance().update(dt);
			else
				for (int i = 0; i < nonRealtimeSteps; i++)
					SimulationManager::instance().step();
			TaskTimer::instance().endTask("Simulation");
		}
		// Update scene graph and (optionally) render graphics
		if (viewer.valid()) {
			if (!customViewer) {
				TaskTimer::instance().beginTask("Graphics");
				// Render graphics
				viewer->frame();
				TaskTimer::instance().endTask("Graphics");
			}
			if (viewer->getOsgViewer()->done())
				done = true;
			SimulationManager::instance().setViewerTimeOffset(viewer->getOsgViewer()->getViewerFrameStamp()->getSimulationTime() - SimulationManager::instance().getTime());
		} else if (scenario.valid() && scenario->getRootNode()) {
			if (!framestamp)
				framestamp = new osg::FrameStamp;
			// Do update traversal but no rendering
			/*
			if (nonRealtimeSteps == 0) {
				framestamp->setReferenceTime(framestamp->getReferenceTime() + dt * SimulationManager::instance().getTimeScale());
				framestamp->setSimulationTime(framestamp->getSimulationTime() + dt * SimulationManager::instance().getTimeScale());
			} else {
				for (int i = 0; i < nonRealtimeSteps; i++) {
					framestamp->setReferenceTime(framestamp->getReferenceTime() + SimulationManager::instance().getTimeStep());
					framestamp->setSimulationTime(framestamp->getSimulationTime() + SimulationManager::instance().getTimeStep());
				}
			}
			 */
			framestamp->setReferenceTime(SimulationManager::instance().getTime());
			framestamp->setSimulationTime(SimulationManager::instance().getTime());
			SimulationManager::instance().setViewerTimeOffset(0);
			framestamp->setFrameNumber(framestamp->getFrameNumber()+1);
			osgUtil::UpdateVisitor updateVisitor;
			updateVisitor.setFrameStamp(framestamp.get());
			scenario->getRootNode()->accept(updateVisitor);
		}
		if (endTime && SimulationManager::instance().getTime() > endTime)
			done = true;
	}
	
	void Application::preRunLoop()
	{
		dout(5, SCRIPT) << "Pre run loop stack top: " << Interpreter::instance().getTop() << "\n";
		
		// Run main loop
		dout(1) << "Starting run loop\n";
		if (viewer.valid())
			viewer->setRunning(true);
		PluginManager::instance().setRunning(true);
		// Call event function (if it exists)
		if (Interpreter::instance().pushNamed("event.run")) {
			if (Interpreter::instance().pCall(0,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
		
	}
	
	int Application::run()
	{
		if (done)
			return exitCode;
			
		preRunLoop();
		
		osg::Timer timer;
		double realTime = 0.0;
		double fps_realtime_sum = 0.0;
		unsigned int fps_numsteps = 0;
		sleepTime = 0;
		while (!done) {
			// Update time
			double start = timer.time_s();
			time = timer.time_s();
			// Update simulation
			double dt = time - lastTime;
			update(dt);
			lastTime = time;
			// Calculate average frame rate
			if (fps_numsteps > FPS_NUM_STEPS) {
				framerateCounter++;
				if (framerateCounter >= FPS_AVG_NUM)
					framerateCounter = 0;
				float frameRate = fps_numsteps/fps_realtime_sum;
				framerates[framerateCounter] = frameRate;
				fps_numsteps = 0;
				fps_realtime_sum = 0;
				averageFrameRate = 0;
				for (unsigned int i = 0; i < FPS_AVG_NUM; i++)
					averageFrameRate += framerates[i];
				averageFrameRate /= FPS_AVG_NUM;
				// Adjust sleep time based on average frame rate
				if (averageFrameRate > targetFrameRate*1.2)
					sleepTime += (int) (averageFrameRate-targetFrameRate);
				else if (frameRate < targetFrameRate*0.7)
					sleepTime = 0;
				else if (frameRate < targetFrameRate*0.8)
					sleepTime -= (int) (targetFrameRate-averageFrameRate)*100;
				else if (frameRate < targetFrameRate*0.9)
					sleepTime -= (int) (targetFrameRate-averageFrameRate)*10;
				if (sleepTime < 0)
					sleepTime = 0;
				if (sleepTime > maxSleepTime)
					sleepTime = maxSleepTime;
				//dout(7) << "Average frame rate " << averageFrameRate << " sleepTime " << sleepTime << "\n";
			}
			if (sleepTime > 0 && nonRealtimeSteps == 0)
#ifdef WIN32
				Sleep(sleepTime/1000);
#else
				usleep(sleepTime);
#endif
			// Update realtime
			double real_dt = timer.time_s() - start;
			realTime += real_dt;
			fps_realtime_sum += real_dt;
			fps_numsteps++;
		}

		return exitCode;
	}
	
	void Application::postRunLoop()
	{
		if (viewer.valid())
		  viewer->setRunning(false);
		PluginManager::instance().setRunning(false);

		dout(1) << "Run loop finished at sim time " << SimulationManager::instance().getTime() << ", real time " << realTime << "\n";
		dout(2) << SimulationManager::instance().getNumSteps() << " steps, average frame rate " << averageFrameRate;
		if (maxSleepTime)
			dout(3) << ", sleep time " << sleepTime << "\n";
		dout(2) << "\n";
		dout(3) << "Task times:\n";
		TaskTimer::instance().report(dout(3), 2);

		dout(5, SCRIPT) << "Post run loop stack top: " << Interpreter::instance().getTop() << "\n";
		// Call event function (if it exists)
		if (Interpreter::instance().pushNamed("event.exit")) {
			if (Interpreter::instance().pCall(0,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void Application::setViewer(Viewer *newViewer)
	{
		viewer = newViewer;
		customViewer = true;
	}
	
	void Application::setRootPath(const std::string& path)
	{
		rootPath = path;
		osgDB::getDataFilePathList().push_back(rootPath);
	}
	
	void Application::load(const std::string& filename, const std::string& specname, const std::string& spectype)
	{
		if (filename.substr(0,4) != "init" && viewer.valid()) viewer->setStatusText("Loading " + filename);
		std::string path = osgDB::findDataFile(filename);
		if (path.length() == 0)
			throw FactoryIOException(filename + ": file not found");
		std::stringstream messagess;
		messagess << "Loading";
		if (spectype.length() > 0)
			messagess << " " << spectype;
		if (specname.length() > 0)
			messagess << " '" << specname << "' from";
		messagess << " " << path;
		dout(1) << messagess.str() << "\n";
		
		// If it's a directory, load init.xml and run init.lua in that directory
		osgDB::DirectoryContents dir = osgDB::getDirectoryContents(path);
		if (dir.size() > 0) {
			// Set to root path if not specified earlier
			if (rootPath.length() == 0) {
				rootPath = path;
				dout(2) << "  Root path = " << rootPath << "\n";
			}
			// Add dir to path
			osgDB::getDataFilePathList().push_front(path);
			// Load files in the directory
			for (osgDB::DirectoryContents::iterator it = dir.begin(); it != dir.end(); it++) {
				std::string& file = *it;
				if (file == "init.lua" || file == "init.lub" || file == "init.moonlua" || file == "init.moonlub") {
					if (Interpreter::instance().doFile(path + "/" + file) != 0)
						dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
				} else if (file == "init.xml" || file == "init.moonxml" || file == "init.moon")
					load(file);
			}
			return;
		}
		
		dout(5, SCRIPT) << "Pre load stack top: " << Interpreter::instance().getTop() << "\n";

		// Continue with normal configuration file parsing
		std::string extension = osgDB::getFileExtension(filename);
		if (extension == "xml" || extension == "moonxml" || extension == "moon") {
			osg::Timer timer;
			ObjectFactory::ObjectList objects = ObjectFactory::instance().loadObjects(path, true, true, "moon", specname, spectype);
			dout(3) << "Load time " << timer.time_s() << "\n";
			timer.setStartTick();
			for (ObjectFactory::ObjectList::iterator it = objects.begin(); it != objects.end(); it++) {
				FactoryProduct *product = it->get();
				if (Scenario *scen = dynamic_cast<Scenario*> (product)) {
					if (!scenario)
						setScenario(scen);
					if (!config)
						config = new Configuration;
					if (ScenarioData *existingdata = config->getScenario(scen->getName())) {
						existingdata->ptr = scen;
						dout(4) << "Setting existing scenario group member\n";
					} else {
						ScenarioData data;
						data.name = scen->getName();
						data.filename = filename;
						data.ptr = scen;
						config->addScenario(data);
						dout(4) << "Adding scenario '" << scen->getName() << "' to group\n";
					}
				} else if (dynamic_cast<Configuration*> (product)) {
					config = (Configuration*) product;
					for (unsigned int i = 0; i < config->getNumScenarios(); i++) {
						if (config->getScenario(i)->preload)
							load(config->getScenario(i)->filename, config->getScenario(i)->name);
					}
				} else if (ControlBindingSet *set = dynamic_cast<ControlBindingSet*> (product)) {
					ControlHandler::instance().bind(set);
				} else if (Script *script = dynamic_cast<Script*> (product)) {
					// support no other 'when' than 'parse'
					if (script->getWhen() != Script::PARSE)
						dout(ERROR) << "Application-level script needs to have 'when' set to 'parse'\n";
				} else if (Environment *env = dynamic_cast<Environment*> (product)) {
					environment = env;
				} else if (PluginManager::instance().handleProduct(product)) {
					// taken care of by plugin
				} else {
					dout(ERROR) << "Don't know how to handle application object " << product->libraryName() 
					<< "::" << product->className() << " '" << product->getName() << "'\n";
				}
			}
			if (objects.size() == 0)
				dout(WARN) << "No objects found in " << filename << "\n";
			dout(3) << "Process time " << timer.time_s() << "\n";
			dout(5, SCRIPT) << "Post load stack top: " << Interpreter::instance().getTop() << "\n";
		} else if (extension == "lua" || extension == "lub" || extension == "moonlua" || extension == "moonlub") {
			osg::Timer timer;
			if (Interpreter::instance().doFile(path) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
			dout(3) << "Script run time " << timer.time_s() << "\n";
		} else {
			// Maybe it's a model file and we can view it...
			if (viewer.valid()) viewer->viewModelFile(filename);
		}
		if (viewer.valid()) viewer->setStatusText("");
	}
	
	void Application::setScenario(Scenario *newscenario)
	{
		if (scenario.valid()) {
			scenario->unrealize();
			// If scenario data is not set to preload, unload it now
			if (config.valid()) {
				ScenarioData *data = config->getScenario(scenario->getName());
				if (data && !data->preload)
					data->ptr = NULL;
			}
		}
		
		scenario = newscenario;
		SimulationManager::instance().setTime(0);
		if (scenario.valid()) {
			if (viewer.valid()) viewer->setStatusText("Initializing scenario");
			scenario->initialize();
		}
		if (environment.valid() && scenario.valid() && !scenario->getEnvironment())
			scenario->setEnvironment(environment.get());
		if (viewer.valid())
			viewer->setScenario(scenario.get());
		if (NetworkManager::instance().isServer() && netgame.valid()) {
			if (!scenario)
				netgame->setScenarioName("");
			else
				netgame->setScenarioName(scenario->getName());
			netgame->broadcastFullSerialize();
		}
		if (scenario.valid()) {
			scenarioListener.setScenario(scenario.get());
			if (viewer.valid()) viewer->setStatusText("Realizing scenario");
			scenario->realize();
			scenario->setResetState();
			if (!NetworkManager::instance().isActive() || NetworkManager::instance().isServer())
				scenario->spawn(Player::me());
			else if (NetworkManager::instance().isClient() && NetworkManager::instance().isConnected()) {
				NetworkID playerID = Player::me()->GetNetworkID();
				NetworkManager::instance().sendMessage(MSG_REQUEST_SPAWN, (const char*) &playerID, sizeof(NetworkID));
			}
			if (viewer.valid()) viewer->setStatusText("");
		}
		// Set a global variable 'scenario'
		Interpreter::instance().setGlobal("scenario", scenario.get(), "moon::Scenario");
		// Call event function (if it exists)
		if (Interpreter::instance().pushNamed("event.newScenario")) {
			Interpreter::instance().pushUserType(scenario.get(), "moon::Scenario");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}

	
	bool Application::loadScenario(const std::string& name)
	{
		if (netgame.valid() && NetworkManager::instance().isClient() 
				&& NetworkManager::instance().isConnected() && name != netgame->getScenarioName()) {
			dout(ERROR) << "Refusing to load scenario '" << name << "' while network game is on scenario '"
						<< netgame->getScenarioName() << "'\n";
			return false;
		}
		setScenario(NULL);
		if (!config) {
			dout(ERROR) << "No configuration\n";
			if (viewer.valid())
				viewer->setStatusText("No configuration");
			return false;
		}
		ScenarioData *data = config->getScenario(name);
		if (!data) {
			dout(ERROR) << "Scenario '" << name << "' not found in configuration\n";
			if (viewer.valid())
				viewer->setStatusText("Unknown scenario '" + name + "'");
			return false;
		}
		if (data->ptr.valid()) {
			dout(1) << "Scenario " << name << " (preloaded)\n";
			setScenario(data->ptr.get());
		} else {
			dout(1) << "Load scenario " << name << " from " << data->filename << "\n";
			load(data->filename, name);
			if (scenario.valid() && scenario->getName() != name)
				dout(ERROR) << "Scenario name '" << scenario->getName() << "' does not match group member name '" << name << "'\n";
		}
		return scenario.valid();
	}
	
	void Application::saveScenario(const std::string& filename)
	{
		if (filename.length() == 0)
			return;
		// Exit edit mode temporarily if needed - dont' wanna include edit camera etc
		bool wasEditing = false;
		if (viewer->getEditHandler()->isEditing()) {
			wasEditing = true;
			viewer->getEditHandler()->setEditMode(false);
		}
		std::string path;
		if (filename[0] == '/' || (filename[1] == ':' && filename[2] == '\\'))
			path = filename;
		else {
			if (rootPath.length() > 0)
				path = rootPath + "/" + filename;
			else {
				char cwd[100];
				dout(WARN) << "No root path defined - saving to current directory '" <<  getcwd(cwd,100) << "'\n";
				path = filename;
			}
		}
		ObjectFactory::ObjectList objects;
		objects.push_back(scenario.get());
		ObjectFactory::instance().saveObjects(objects, path, false);
		if (wasEditing)
			viewer->getEditHandler()->setEditMode(true);
	}
	
	void Application::updateNetworkGame(NetworkGame *game, const bool fullUpdate)
	{
		if (netgame.valid() && game != netgame.get()) {
			dout(WARN) << "Received new network game while game is in progress!\n";
			netgame = NULL;
			return;
		}
		if (!netgame) {
			if (fullUpdate) {
				netgame = game;
				dout(1) << "Joining network game " << game->getName() << "\n";
				if (Interpreter::instance().pushNamed("event.joinGame")) {
					Interpreter::instance().pushUserType(game, "moon::NetworkGame");
					if (Interpreter::instance().pCall(1,0) != 0)
						dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
				}
			} else
				return; // wait for first full update
		}

		// Sync clock
		/// \todo need to do some more advanced timing here?
		double timeOffset = game->getGameTime()-SimulationManager::instance().getTime();
		SimulationManager::instance().setGameTimeOffset(timeOffset);

		if (fullUpdate) {
			std::string scenarioName = game->getScenarioName();
			if (!scenario || scenario->getName() != scenarioName) {
				if (scenarioName != "") {
					loadScenario(scenarioName);
				} else {
					setScenario(NULL);
					if (viewer.valid())
						viewer->setStatusText("Waiting for scenario...");
				}
			}
		}
	}
	
	std::string Application::getSettingsPath()
	{
		std::stringstream pathss;
#if defined(WIN32)
		pathss << getenv("APPDATA") << "\\" << name;
#elif defined(__APPLE__)
		pathss << getenv("HOME") << "/Library/Application Support/" << name;
#else
		pathss << getenv("HOME") << "/." << name;
#endif
		
#ifdef WIN32
		int ret = _mkdir(pathss.str().c_str());
#else
		int ret = mkdir(pathss.str().c_str(), S_IFDIR | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
#endif
		
		if (ret == 0)
			dout(INFO) << "Created user settings directory " << pathss.str() << "\n";
		else if (errno != EEXIST) {
			dout(ERROR) << "Failed to create user settings directory " << pathss.str() << ": " << strerror(errno) << "\n";
			return "/tmp";
		}
		return pathss.str();
	}
	
} // namespace
