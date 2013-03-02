#ifndef MOON_APPLICATION_H
#define MOON_APPLICATION_H

#include "Viewer.h"
#include "Scenario.h"
#include "ScriptEventNetworkListener.h"
#include "NetworkGame.h"
#include "Configuration.h"
#include "Scheduler.h"
#include "Environment.h"
#include <string>
#include <map>

namespace moon {
	
	#define FPS_AVG_NUM 10
	#define FPS_NUM_STEPS 10
	
	/// \addtogroup core
	/// @{
	
	/// Base class for moon engine applications
	class MOON_EXPORT Application : public NetworkGameListener, public moonet::NetworkListener {
	public:
		Application();
		virtual ~Application();
		
		/// Standard initialization
		virtual void init();
		/// Initialize file paths
		virtual void initPaths();
		/// Initialize the viewer
		virtual void initViewer();
		/// Initialize Lua interpreter
		virtual void initInterpreter();
		/// Initialize the network
		virtual void initNetwork();
		/// Initialize plugins
		virtual void initPlugins();
		
		/// Host a network game
		void host(const std::string& gameName, const std::string& playerName = "");
		/// Join a network game
		void join(const std::string& peer, const std::string& playerName);
		/// Disconnect from a network game
		void disconnect();
		
		/// Update simulation, network etc
		virtual void update(const double dt);
		virtual void preRunLoop();
		/// Enter into the main loop and run the application
		virtual int run();
		virtual void postRunLoop();
		
		/// Setup a custom viewer - to be called before init()
		void setViewer(Viewer *viewer);
		
		/// Set application name - used for settings file path etc
		void setName(const std::string& newname) { name = newname; }
		const std::string& getName() const { return name; }
		/// Set root path - used for saving scenarios etc
		void setRootPath(const std::string& path);
		const std::string& getRootPath() const { return rootPath; }
		void setDone(const bool flag) { done = flag; }
		bool isDone() const { return done; }
		/// Set simulation time when the run loop will end
		void setEndTime(const double time) { endTime = time; }
		double getEndTime() const { return endTime; }
		/// Set non-realtime simulation and number of steps per viewer frame
		void setNonRealtimeSimulation(const int num = 1) { nonRealtimeSteps = num; }
		int getNonRealtimeSimulation() const { return nonRealtimeSteps; }

		/// Set target frame rate ("frame" includes simulation updates etc)
		void setTargetFrameRate(const float fps) { targetFrameRate = fps; }
		float getTargetFrameRate() const { return targetFrameRate; }
		/// Set current average frame rate ("frame" includes simulation updates etc)
		float getAverageFrameRate() const { return averageFrameRate; }
		/// Get current sleep time used for achieving target frame rate
		int getSleepTime() const { return sleepTime; }
		/// Set maximum sleep time to use for achieving target frame rate
		void setMaxSleepTime(const int time) { maxSleepTime = time; }
		int getMaxSleepTime() const { return maxSleepTime; }

		void setExitCode(const int value) { exitCode = value; }
		int getExitCode() const { return exitCode; }
				
		/// Load a configuration file
		void load(const std::string& filename, const std::string& specname = "", const std::string& spectype = "");
		/// Set the scenario and pass it to the viewer if applicable
		void setScenario(Scenario *scenario);
		/// Get the current scenario
		Scenario* getScenario() { return scenario.get(); }
		/// Load a scenario from the scenario group
		bool loadScenario(const std::string& name);
		/// Save scenario data to the specified file
		void saveScenario(const std::string& filename);		
		
		NetworkGame* getNetworkGame() { return netgame.get(); }
		Viewer* getViewer() { return viewer.get(); }
		osg::FrameStamp* getFrameStamp() { return framestamp.get(); }
		
		/// Called when a NetworkGame update is received
		virtual void updateNetworkGame(NetworkGame *game, const bool fullUpdate);
		
	protected:
		/// Get a suitable location to store user configuration files
		std::string getSettingsPath();
		
		osg::ref_ptr<Viewer> viewer;
		osg::ref_ptr<osg::FrameStamp> framestamp;
		osg::ref_ptr<Scenario> scenario;
		osg::ref_ptr<NetworkGame> netgame;
		osg::ref_ptr<Configuration> config;
		osg::ref_ptr<Environment> environment;

		ScenarioNetworkObjectListener scenarioListener;
		ScriptEventNetworkListener scriptEventNetworkListener;
		Scheduler scheduler;
		
	private:
		std::string name, rootPath;
		bool done;
		double time, lastTime, realTime, endTime;
		int nonRealtimeSteps;
		float framerates[FPS_AVG_NUM];
		int framerateCounter;
		float targetFrameRate;
		float averageFrameRate;
		int sleepTime, maxSleepTime;
		int exitCode;
		bool customViewer;
		
	};
	
	/// @}
}

#endif
