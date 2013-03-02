#include "ShellApplication.h"
#include "PluginManager.h"
#include "Version.h"
#include "Interpreter.h"
#include "TerminalConsole.h"
#include "TaskTimer.h"
#include <mlog/Log.h>
#include <moonet/NetworkManager.h>
#include <mdraw/utils.h>
#include <osg/Version>
#include <osgDB/Registry>
#include <osgDB/FileUtils>
#include <stdexcept>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#ifdef MOON_USE_FLTK
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#endif

using namespace mlog;
using namespace moonet;

namespace moon {
	
	ShellApplication::ShellApplication()
	: Application(),
	arguments(NULL), console(true), initialized(false), terminalConsole(NULL), firstUpdate(true)
	{
#if defined(WIN32) && defined(MOON_USE_FLTK)
		console = false;
#endif
	}
	
	ShellApplication::~ShellApplication()
	{
		if (arguments)
			delete arguments;
		if (terminalConsole)
			delete terminalConsole;
	}

	/**
	 \param argc Pointer to argument count (optional)
	 \param argv Pointer to arguments (optional)
	 \return false if arguments used indicate that the application should terminate
	 */
	bool ShellApplication::init(int *argc, char *argv[])
	{
		if (argc && argv) {
			arguments = new osg::ArgumentParser(argc, argv);
			
			if (arguments->read("-h") || arguments->read("-help") || arguments->read("--help") || arguments->read("/?")) {
				usage(arguments->getApplicationName());
				return false;
			}
			int debuglevel = 0;
			if (arguments->read("-d", debuglevel))
				setDebugLevel(debuglevel);
			if (arguments->read("-dn", debuglevel))
				setDebugLevel(debuglevel, NETWORK);
			if (arguments->read("-ds", debuglevel))
				setDebugLevel(debuglevel, SCRIPT);
			if (arguments->read("-da", debuglevel))
				setDebugLevel(debuglevel, AUDIO);
			
			arguments->read("-scenario", startScenarioName);
			if (arguments->read("-nosleep"))
				setMaxSleepTime(0);
			double d;
			if (arguments->read("-end", d))
				setEndTime(d);
			if (arguments->read("-simstep", d) && d > 1e-5)
				SimulationManager::instance().setTimeStep(d);
			if (arguments->read("-simfreq", d) && d > 1e-5)
				SimulationManager::instance().setTimeStep(1.0/d);
			if (arguments->read("-simscale", d))
				SimulationManager::instance().setTimeScale(d);
			int i;
			if (arguments->read("-simnrt", i))
				setNonRealtimeSimulation(i);
			else if (arguments->read("-simnrt"))
				setNonRealtimeSimulation(1);
			if (arguments->read("-version")) {
				printVersions(0);
				exit(0);
			}
			if (arguments->read("-noconsole"))
				console = false;
				
			if (arguments->read("-testcrash"))
				strcpy(0x0, "i shall crash");
			if (arguments->read("-testexception"))
			  throw std::runtime_error("test exception");
		}
		dout(1) << "Initializing\n";
		printVersions(2);

#ifdef WIN32
		TCHAR szDirectory[MAX_PATH] = "";

		if (::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory)) {

			dout(2) << "Working directory: " << szDirectory << "\n";

		}

#else

		char wd[1024];
		if (getcwd(wd,1024))
			dout(2) << "Working directory: " << wd << "\n";
#endif

		dout(2) << "Initializing paths\n";
		initPaths();
		
		if (arguments) {
			if (arguments->read("-nodisplay"))
				PluginManager::instance().setNoDisplay(true);
			if (arguments->read("-allplugins"))
				PluginManager::instance().loadAll();
			else {
				std::string str;
				while (arguments->read("-plugins", str)) {
					unsigned int i;
					while ((i = str.find_first_of(",;:")) != std::string::npos)
						str.replace(i,1," ");	
					std::stringstream sin(str);
					std::string plugin;
					while (sin >> plugin)
						PluginManager::instance().load(plugin);
				}
			}
		
			if (arguments->read("-list")) {
				// List object factory types
				ObjectFactory::IdentifierList list = ObjectFactory::instance().getIdentifierList();
				for (unsigned int i = 0; i < list.size(); i++)
					dout(0) << list[i] << "\n";
				return false;
			}
		}
		
		if (!PluginManager::instance().getNoDisplay()) {
			dout(2) << "Setting up viewer\n";
			initViewer();
		}
		dout(2) << "Setting up intepreter\n";
		initInterpreter();
		dout(2) << "Initializing network\n";
		initNetwork();		
		if (arguments) {
			std::string playerName;
			std::string gameName;
			std::string peer;
			arguments->read("-player", playerName);
			if (arguments->read("-host", gameName))
				host(gameName, playerName);
			else if (arguments->read("-join", peer))
				join(peer, playerName);
			int statslevel;
			if (arguments->read("-netstats", statslevel))
				NetworkManager::instance().doStatistics(statslevel);
		}
		initPlugins();
		initialized = true;
		
		// Load drag-n-dropped files on OSX
		while (dropFiles.size() > 0) {
			load(dropFiles[0]);
			dropFiles.pop_front();
		}
		
		if (arguments && arguments->read("-tc"))
			terminalConsole = new TerminalConsole(&Interpreter::instance());
		
		return true;		
	}
	
	void ShellApplication::initPaths()
	{
#if defined(WIN32) && !defined(__CYGWIN__)
		char delimitor = ';';
#else
		char delimitor = ':';
#endif
		osgDB::Registry::instance()->initFilePathLists();
		/// Set data path (-path and environment variable OSG_FILE_PATH)
		osgDB::FilePathList& path = osgDB::getDataFilePathList();
		path.push_back("data");
		path.push_back("../data");
		if (arguments) {
			unsigned int index = arguments->getApplicationName().find_last_of("/\\");
			if (index != std::string::npos) {
				path.push_back(arguments->getApplicationName().substr(0,index) + "/data");
				path.push_back(arguments->getApplicationName().substr(0,index) + "/../data");
			}
		}
		
		// Add path list from arguments
		std::string argpath;
		while (arguments && arguments->read("-path",argpath)) {
			int lasti = -1;
			for (unsigned int i = 0; i < argpath.length(); i++) {
				if (argpath[i] == delimitor) {
					path.push_back(argpath.substr(lasti+1,i-lasti-1));
					lasti = i;
				}
			}
			path.push_back(argpath.substr(lasti+1));
		}
		dout(3) << "Data path: ";
		for(osgDB::FilePathList::iterator i=path.begin(); i != path.end(); i++) {
			dout(3) << *i << ":";
		}
		dout(3) << "\n";
		
		/// Set library/plugin path (-libpath and environment variable OSG_LIBRARY_PATH)
		osgDB::FilePathList& libpath = osgDB::getLibraryFilePathList();
		libpath.push_back("moonPlugins");
		libpath.push_back("../moonPlugins");
#ifdef WIN32
#  define LIBDIR "bin"
#else
#  define LIBDIR "lib"
#endif
		libpath.push_back(LIBDIR "/moonPlugins");
		libpath.push_back("../" LIBDIR "/moonPlugins");
#ifdef MOON_DEBUG
		libpath.push_back(LIBDIR "/moonPlugins/Debug");
		libpath.push_back("../" LIBDIR "/moonPlugins/Debug");
#else
		libpath.push_back(LIBDIR "/moonPlugins/Release");
		libpath.push_back("../" LIBDIR "/moonPlugins/Release");
#endif

		if (arguments) {
			unsigned int index = arguments->getApplicationName().find_last_of("/\\");
			if (index != std::string::npos) {
#ifdef WIN32
				libpath.push_back(arguments->getApplicationName().substr(0,index) + "/moonPlugins");
#else
				libpath.push_back(arguments->getApplicationName().substr(0,index) + "/../lib/moonPlugins");
#endif
			}
		}
		// Add path list from arguments
		while (arguments && arguments->read("-libpath",argpath)) {
			int lasti = -1;
			for (unsigned int i = 0; i < argpath.length(); i++) {
				if (argpath[i] == delimitor) {
					libpath.push_back(argpath.substr(lasti+1,i-lasti-1));
					lasti = i;
				}
			}
			libpath.push_back(argpath.substr(lasti+1));
		}
		dout(3) << "Library path: ";
		for(osgDB::FilePathList::iterator i=libpath.begin(); i != libpath.end(); i++) {
			dout(3) << *i << ":";
		}
		dout(3) << "\n";
		
		/// Set project root path (-root)
		std::string rootPath;
		if (arguments && arguments->read("-root", rootPath)) {
			dout(2) << "  Root path: " << rootPath << "\n";
			setRootPath(rootPath);
		}
		
		Application::initPaths();
	}
	
	void ShellApplication::initViewer()
	{
		if (isDone())
			return;
		if (!viewer)
			viewer = new Viewer(new osgViewer::Viewer);
		if (!arguments || !arguments->read("-mtviewer"))
			viewer->getOsgViewer()->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		int x = -1, y = -1, w = -1, h = -1;
		while (arguments && arguments->read("-window", x, y, w, h)) {}
		int screen = -1;
		while (arguments && arguments->read("-screen", screen)) {}
		if (w > 0 && h > 0) {
			if (screen >= 0)
				viewer->getOsgViewer()->setUpViewInWindow(x,y,w,h,screen);
			else
				viewer->getOsgViewer()->setUpViewInWindow(x,y,w,h);
		} else if (screen >= 0)
			viewer->getOsgViewer()->setUpViewOnSingleScreen(screen);
		viewer->getOsgViewer()->realize();
		viewer->frame();
                viewer->setDefaultControlBindings();
		if (arguments && arguments->read("-c") && viewer->getHUD() && viewer->getConsoleWindow())
			viewer->getHUD()->setChildValue(viewer->getConsoleWindow(), true);
		if (arguments && arguments->read("-debugcontrols") && viewer->getHUD())
			viewer->getHUD()->addChild(ControlHandler::instance().getDebugHUD());
	}

	void ShellApplication::loadRemainingArguments()
	{
		if (!arguments || isDone())
			return;
		for (int i = 1; i < arguments->argc(); i++) {
			if (!arguments->isOption(i))
				load((*arguments)[i]);
		}		
	}
	
	void ShellApplication::dropLoad(const std::string& filename)
	{
		if (!initialized) {
			dropFiles.push_back(filename);
			return;
		}
		unsigned int numScenariosPrev = 0;
		if (config.valid())
			numScenariosPrev = config->getNumScenarios();
		try {
			load(filename);
		} catch (std::exception& e) {
#ifdef MOON_USE_FLTK
			fl_alert("%s", e.what());
#endif
			dout(ERROR) << "whiel loading " << filename << ": " << e.what() << "\n";
		}
		if (config.valid() && config->getNumScenarios() > numScenariosPrev)
			loadScenario(config->getScenario(config->getNumScenarios()-1)->name);
	}
	
	void ShellApplication::update(const double dt)
	{
		if (terminalConsole) {
			if (firstUpdate)
				terminalConsole->start();
			terminalConsole->mutex.lock();
		}
		
		Application::update(dt);
		
		if (terminalConsole) {
			terminalConsole->mutex.unlock();
			if (!terminalConsole->isRunning())
				setDone(true);
		}
#ifdef MOON_USE_FLTK
		TaskTimer::instance().beginTask("GUI");
		osg::Timer timer;
		Fl::wait(0);
		TaskTimer::instance().endTask("GUI");
#endif
		firstUpdate = false;
	}
	
	int ShellApplication::run()
	{
		if (arguments && arguments->read("-scenedump")) {
			// Print out the scene graph and quit, for debugging purposes
			if (!scenario)
				dout(ERROR) << "No scenario\n";
			else
				dout(0) << mdraw::getNodeString(scenario->getRootNode());
			return 0;
		}
		// If running in model-view mode, just run it with no further questions asked...
		if (viewer.valid() && viewer->isViewingModel()) {
			viewer->run();
			return 0;
		}
		// Start scenario specified as command-line argument
		if (startScenarioName != "") {
			if (!NetworkManager::instance().isActive() || NetworkManager::instance().isServer())
				loadScenario(startScenarioName);
			else
				dout(WARN) << "Start scenario specified when running as client\n";
		}
		// Start in edit mode if specified on command-line
		if (arguments && arguments->read("-edit") && viewer.valid() && viewer->getEditHandler())
			viewer->getEditHandler()->setEditMode(true);
		if (arguments && arguments->read("-paused"))
			SimulationManager::instance().setPaused(true);
		if (arguments && arguments->read("-debug") && scenario.valid())
			scenario->setDisplayMode(BaseObject::DISPLAY_DEBUG);
		
		return Application::run();
	}

	void ShellApplication::usage(const std::string& appname)
	{
		std::cout << "usage: " << appname << " [arguments] [files]\n"
		<< "  where [files] are scenario/configuration XML files\n"
		<< "\n"
		<< "  Options:\n"
		<< "    -d  <level>       Set log verbosity level for general messages\n"
		<< "    -dn <level>       Set log verbosity level for network category messages\n"
		<< "    -ds <level>       Set log verbosity level for script messages\n"
		<< "    -da <level>       Set log verbosity level for audio messages\n"
		<< "    -version          Print version number and exit\n"
		<< "    -c                Start with console window open\n"
		<< "    -tc               Start with terminal console\n"
		<< "    -path <path>      Data file path (colon-separated list)\n"
		<< "    -libpath <path>   Library/plugin file path\n"
		<< "    -plugins <list>   Load comma-separated list of plugins on startup\n"
		<< "    -allplugins       Load all available plugins on startup\n"
		<< "    -window <x,y,w,h> Set viewer window position/size\n"
		<< "    -screen <num>     Set viewer screen\n"
		<< "    -noconsole        Use GUI for error reporting\n"
		<< "    -player <name>    Set player name to use on the network\n"
		<< "    -host <name>      Host a network game of the specified name\n"
		<< "    -join <peer>      Join a network game on the specified server address\n"
		<< "    -netstats <level> Collect network statistics with the specified level of verbosity\n"
		<< "    -nodisplay        Run without a viewer (useful for a dedicated server)\n"
		<< "    -scenario <name>  Start the specified scenario\n"
		<< "    -end <time>       Quit after specified number of seconds\n"
		<< "    -root <path>      Set root path for data files (mainly for saving)\n"
		<< "    -edit             Start in edit mode\n"
		<< "    -paused           Start paused\n"
		<< "    -debug            Start scenario in debug display mode\n"
		<< "    -debugcontrols    Enable debug HUD for controls\n"
		<< "    -list             List registered factory objects and quit\n"
		<< "    -mtviewer         Run a multi-threaded viewer\n"
		<< "    -nosleep          Don't sleep if above target frame rate\n"
		<< "    -simfreq <freq>   Set simulation frequency (1/time step) [Hz]\n"
		<< "    -simstep <step>   Set simulation time step [seconds]\n"
		<< "    -simscale <scale> Set simulation time scale\n"
		<< "    -simnrt [steps]   Set non-realtime simulation with specified steps per frame\n"
		<< "\n";
	}

	void ShellApplication::printVersions(const int level)
	{
		dout(level) << MOON_VERSION_STRING << "\n";
		dout(level+1) << osgGetLibraryName() << " " << osgGetVersion() << "\n";
	}
	
} // namespace
