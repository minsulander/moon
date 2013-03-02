#include "Scheduler.h"
#include "Interpreter.h"
#include "SimulationManager.h"
#include <mlog/Log.h>

using namespace mlog;

namespace moon {
	
	Scheduler::Scheduler()
	:	nowtime(0.0)
	{
	}
	
	void Scheduler::schedule(const std::string& scriptFunctionName, const double deltaTime, const bool repeat)
	{
		ScheduleEntry entry;
		entry.functionName = scriptFunctionName;
		entry.interval = deltaTime;
		entry.repeat = repeat;
		schedule(entry);
	}
	
	void Scheduler::scheduleAt(const std::string& scriptFunctionName, const double time, const bool repeat, const double interval)
	{
		ScheduleEntry entry;
		entry.functionName = scriptFunctionName;
		entry.time = time;
		entry.repeat = repeat;
		entry.interval = interval;
		schedule(entry);
	}
	
	void Scheduler::scheduleAtGameTime(const std::string& scriptFunctionName, const double time, const bool repeat, const double interval)
	{
		ScheduleEntry entry;
		entry.functionName = scriptFunctionName;
		entry.time = time - SimulationManager::instance().getGameTimeOffset();
		entry.repeat = repeat;
		entry.interval = interval;
		schedule(entry);
	}
	
	void Scheduler::unschedule(const std::string& scriptFunctionName)
	{
		for (Schedule::iterator it = sched.begin(); it != sched.end(); it++) {
			if (it->functionName == scriptFunctionName) {
				sched.erase(it);
				break;
			}
		}
	}
	
	void Scheduler::clear() { sched.clear(); }
	
	void Scheduler::update(const double dt)
	{
		/// \todo get time from SimulationManager
		nowtime += dt;
		while (sched.size() > 0 && sched[0].time <= nowtime) {
			// erase and reschedule if needed
			ScheduleEntry entry = sched[0];
			sched.erase(sched.begin());
			// run the script function
			dout(5, SCRIPT) << "Scheduler calling '" << entry.functionName << "' at " << nowtime << "\n";
			Interpreter::instance().pushNamed(entry.functionName);
			Interpreter::instance().pushDouble(entry.interval);
			int ret = Interpreter::instance().pCall(1,0);
			if (ret != 0) {
				dout(ERROR, SCRIPT) << "Schedule script '" << entry.functionName << "': " << Interpreter::instance().getError() << "\n";
			}
			// reschedule if needed
			if (entry.repeat && ret == 0) {
				entry.time = 0;
				schedule(entry);
			}
		}
	}
			
	
	void Scheduler::schedule(ScheduleEntry& entry) {
		if (entry.time <= 0)
			entry.time = nowtime + entry.interval;
		for (Schedule::iterator it = sched.begin(); it != sched.end(); it++) {
			if (entry.time < it->time) {
				sched.insert(it, entry);
				return;
			}
		}
		sched.push_back(entry);
	}
			

} // namespace
