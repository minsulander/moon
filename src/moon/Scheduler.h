#ifndef MOON_SCHEDULER_H
#define MOON_SCHEDULER_H

#include <vector>
#include <string>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// A utility class for running script functions at regular intervals
	class Scheduler {
	public:
		Scheduler();
		
		void schedule(const std::string& scriptFunctionName, const double deltaTime, const bool repeat = false);
		void scheduleAt(const std::string& scriptFunctionName, const double time, const bool repeat = false, const double interval = 0.0);
		void scheduleAtGameTime(const std::string& scriptFunctionName, const double time, const bool repeat = false, const double interval = 0.0);
		void unschedule(const std::string& scriptFunctionName);
		void clear();
		
		void update(const double dt);
		
	private:
		double nowtime;
		
		struct ScheduleEntry {
			std::string functionName;
			double time;
			bool repeat;
			double interval;
			ScheduleEntry() : functionName(""), time(0.0), repeat(false), interval(0.0) {}
		};
		void schedule(ScheduleEntry& entry);
		
		typedef std::vector<ScheduleEntry> Schedule;
		Schedule sched;
	};

	/// @}
}

#endif
