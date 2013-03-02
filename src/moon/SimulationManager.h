#ifndef MOON_SIMULATIONMANAGER_H
#define MOON_SIMULATIONMANAGER_H

#ifdef _MSC_VER
#	pragma warning(disable:4251)
#endif

#include "Export.h"
#include <vector>
#include <OpenThreads/Mutex>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// A listener for dynamic updates, stepped by the SimulationManager
	class MOON_EXPORT SimulationListener {
	public:
		SimulationListener(const bool doRegister = true);
		virtual ~SimulationListener();
		virtual void update(const double dt) = 0;
	};
	
	/// Singleton manager that handles updating dynamic objects
	class MOON_EXPORT SimulationManager {
	public:
		void registerListener(SimulationListener *listener);
		void unregisterListener(SimulationListener *listener);
		
		void step();
		void update(const double dt);
		
		void setTimeStep(const double step) { timestep = step; }
		double getTimeStep() const { return timestep; }
		void setPaused(const bool value);
		bool isPaused() const { return paused; }
		double getTime() const { return time; }
		void setTime(const double newtime) { time = newtime; }
		/// Get average offset between local time and network game time (the common clock)
		double getGameTimeOffset() const { return averageGameTimeOffset; }
		void setGameTimeOffset(const double newoffset);
		/// Get offset between local time and viewer reference time
		double getViewerTimeOffset() const { return viewerTimeOffset; }
		void setViewerTimeOffset(const double newoffset) { viewerTimeOffset = newoffset; }
		/// Get ratio between simulation time and real time
		double getTimeScale() const { return timeScale; }
		void setTimeScale(const double ratio);
		/// Get number of simulation steps taken
		unsigned long long getNumSteps() const { return numSteps; }
		
		static SimulationManager& instance();
		static OpenThreads::Mutex mutex;
	protected:
		SimulationManager();

		typedef std::vector<SimulationListener*> ListenerList;
		ListenerList listeners;
		double time, difftime, timestep, viewerTimeOffset;
		double averageGameTimeOffset;
		double gameTimeOffsets[10];
		int gameTimeOffsetIndex;
		bool paused;
		double timeScale;
		unsigned long long numSteps;
		
		static SimulationManager *instanceptr;
	};
	
	/// @}
}

#endif
