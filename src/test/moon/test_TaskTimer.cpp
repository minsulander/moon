#include <unittest++/UnitTest++.h>
#include <moon/TaskTimer.h>
#include <OpenThreads/Thread>

using namespace moon;

TEST (TaskTimer) {
	TaskTimer::instance().beginTask("test");
	OpenThreads::Thread::microSleep(100000);
	TaskTimer::instance().endTask("test");
	CHECK_CLOSE(0.1, TaskTimer::instance().getTotalTime("test"), 0.05);

	{
	  TaskTimer::ScopedTask task("test");
	  OpenThreads::Thread::microSleep(50000);
	}

	CHECK_CLOSE(0.15, TaskTimer::instance().getTotalTime("test"), 0.05);
}
