#include "SimulationManager.h"
#include "Interpreter.h"
#include "mlog/Log.h"
#include <OpenThreads/ScopedLock>

using namespace mlog;

namespace moon {
	
	SimulationListener::SimulationListener(const bool doRegister)
	{
		if (doRegister)
			SimulationManager::instance().registerListener(this);
	}
	
	SimulationListener::~SimulationListener()
	{
		SimulationManager::instance().unregisterListener(this);
	}

	
	void SimulationManager::registerListener(SimulationListener *listener)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
		listeners.push_back(listener);
	}
	
	void SimulationManager::unregisterListener(SimulationListener *listener)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
		for (ListenerList::iterator it = listeners.begin(); it != listeners.end(); it++) {
			if (*it == listener) {
				listeners.erase(it);
				break;
			}
		}
	}
	
	void SimulationManager::step()
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
		for (ListenerList::iterator it = listeners.begin(); it != listeners.end(); it++) {
			(*it)->update(timestep);
		}
		time += timestep;
		numSteps++;
	}
	
	/// \param dt Real time increment since last call
	void SimulationManager::update(const double dt)
	{
		if (!paused) {
			difftime += dt*timeScale;
			while (difftime > timestep) {
				step();
				/// \todo Restrict updates in order to avoid freeze-up if realtime performance drops
				difftime -= timestep;
			}
		}
	}
	
	void SimulationManager::setPaused(const bool value)
	{
		paused = value;
		// Call event function (if it exists)
		if (Interpreter::instance().pushNamed("event.pause")) {
			Interpreter::instance().pushBool(paused);
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void SimulationManager::setGameTimeOffset(const double offset)
	{
		if (gameTimeOffsetIndex == 0 && gameTimeOffsets[0] == 0) {
			for (unsigned int i = 0; i < 10; i++)
				gameTimeOffsets[i] = offset;
			averageGameTimeOffset = offset;
			return;
		}
		gameTimeOffsetIndex++;
		if (gameTimeOffsetIndex >= 10)
			gameTimeOffsetIndex = 0;
		gameTimeOffsets[gameTimeOffsetIndex] = offset;
		double sum = 0;
		for (unsigned int i = 0; i < 10; i++)
			sum += gameTimeOffsets[i];
		averageGameTimeOffset = sum/10.0;
	}
	
	void SimulationManager::setTimeScale(const double ratio)
	{
		if (ratio < 0)
			return;
		if (ratio == 0)
			setPaused(true);
		timeScale = ratio;
	}
	
	SimulationManager& SimulationManager::instance()
	{
		if (!instanceptr)
			instanceptr = new SimulationManager;
		return *instanceptr;
	}
	
	SimulationManager::SimulationManager()
	:	time(0.0),
		difftime(0.0),
		timestep(1.0/60.0),
		viewerTimeOffset(0.0),
		averageGameTimeOffset(0.0),
		gameTimeOffsetIndex(0),
		paused(false),
		timeScale(1.0),
		numSteps(0)
	{
		gameTimeOffsets[0] = 0;
	}
	
	OpenThreads::Mutex SimulationManager::mutex;
	SimulationManager *SimulationManager::instanceptr = NULL;
}
