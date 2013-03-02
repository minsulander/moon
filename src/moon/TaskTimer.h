#ifndef MOON_TASKTIMER_H
#define MOON_TASKTIMER_H

#include "Export.h"
#include <osg/Timer>
#include <map>
#include <iostream>

namespace moon {

	/// \brief Utility singleton class for timing tasks (poor man's profiling)
	/// \ingroup util
	class MOON_EXPORT TaskTimer {
	public:
		/// Start a task
		inline void beginTask(const char* name) { beginTime[name] = timer.time_s(); }
		/// End a task
		inline void endTask(const char* name) { totalTime[name] += timer.time_s() - beginTime[name]; }
		/// Get total time spent on a task
		inline double getTotalTime(const char* name) { return totalTime[name]; }
		
		/// Write out total times for all tasks
		void report(std::ostream& stream, const unsigned int indent = 0);
	
		static TaskTimer& instance();
		
		class ScopedTask {
		public:
			ScopedTask(const char *nname) { name = nname; TaskTimer::instance().beginTask(name); }
			virtual ~ScopedTask() { TaskTimer::instance().endTask(name); }
		private:
			const char *name;
		};
		
	private:
		void printReport(std::ostream& stream, const unsigned int indent, const char* name, double subTotal);
		
		TaskTimer();
		static TaskTimer *instancePtr;
		
		typedef std::map<const char*, double> TaskTimeMap;
		TaskTimeMap beginTime, totalTime;
		
		typedef std::multimap<double, const char*> ReverseMap;
		ReverseMap revmap;

		typedef std::map<const char*, bool> ReportedMap;
		ReportedMap reported;

		double accumulatedTotal;
		osg::Timer timer;
	};

}

#endif
