#include "TaskTimer.h"
#include <string>
#include <iomanip>
#include <cmath>
#include <cstring>

namespace moon {

	void TaskTimer::report(std::ostream& stream, const unsigned int indent)
	{
		revmap.clear();
		reported.clear();
		
		// Fill out reverse map - sorting by time
		TaskTimeMap::iterator it;
		for (it = totalTime.begin(); it != totalTime.end(); it++)
			revmap.insert(std::make_pair(it->second, it->first));
			
		accumulatedTotal = 0.0;
		for (ReverseMap::iterator jt = revmap.begin(); jt != revmap.end(); jt++) {
			if (strchr(jt->second, '/'))
				continue;
			accumulatedTotal += jt->first;
		}
		
		for (ReverseMap::iterator jt = revmap.begin(); jt != revmap.end(); jt++) {
			if (reported[jt->second] || strchr(jt->second, '/'))
				continue;
			printReport(stream, indent, jt->second, accumulatedTotal);
		}
	}
	
	void TaskTimer::printReport(std::ostream& stream, const unsigned int indent, const char *name, double subTotal)
	{
		TaskTimeMap::iterator it = totalTime.find(name);
		if (it == totalTime.end())
			return;
		for (unsigned int i = 0; i < indent; i++)
			stream << ' ';
		std::string namestr(name);
		size_t subidx = namestr.find_last_of("/");
		if (subidx != std::string::npos)
			namestr = namestr.substr(subidx+1);
		stream << namestr;
		for (unsigned int i = indent+namestr.length(); i < 30; i++)
			stream << ' ';
		stream << it->second << "\t" << (int) ceil(it->second/accumulatedTotal*100) << "%";
		if (accumulatedTotal != subTotal)
			stream << "\t" << (int) ceil(it->second/subTotal*100) << "%";
		stream << "\n";
		
		// Recursively call printReport() for sub-tasks, also sorted by time 
		for (ReverseMap::iterator jt = revmap.begin(); jt != revmap.end(); jt++) {
			if (reported[jt->second])
				continue;
			std::string str(jt->second);
			size_t subidx = str.find_last_of("/");
			if (subidx == std::string::npos)
				continue;
			if (str.substr(0,subidx) == name)
				printReport(stream, indent+2, jt->second, it->second);
		}
		reported[name] = true;
	}
	
	TaskTimer& TaskTimer::instance()
	{
		if (!instancePtr)
			instancePtr = new TaskTimer;
		return *instancePtr;
	}
	
	TaskTimer::TaskTimer()
	{
	}
	
	TaskTimer* TaskTimer::instancePtr = NULL;

/** \class TaskTimer

	Tasks can be grouped into hierarchies by using slashes, so for example,
	the task \c Simulation/ODE will be a subtask of \c Simulation.
*/

}

