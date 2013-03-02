#ifdef MOON_USE_FLTK
#	ifdef APPLE
#		include <FL/Fl.H>
#		include <FL/x.H>
#	endif
#	include <FL/fl_ask.H>
#endif

#include "moon/ShellApplication.h"
#include "moon/ObjectFactory.h"
#include "mlog/Log.h"

using namespace moon;
using namespace mlog;

ShellApplication *app = new ShellApplication;

#ifndef WIN32
#include <signal.h>
void sighandler(int sig)
{
	if (sig == SIGINT) {
		if (app)
			app->setDone(true);
	}
}
#endif

void open_callback(const char *filename)
{
	app->dropLoad(filename);
}

int main(int argc, char *argv[])
{
	int exitcode = 0;

#if defined(MOON_USE_FLTK) && defined(APPLE)
	fl_open_callback(&open_callback);
	Fl::wait(0.1);
#endif
	if (!app->init(&argc, argv))
	  return 0;

	try {
		app->loadRemainingArguments();
	} catch (std::exception& e) {
#ifdef MOON_USE_FLTK
		if (!app->hasConsole())
			fl_alert("%s", e.what());
#endif
		dout(ERROR) << e.what() << "\n";
		exitcode = 255;
	}

#ifndef WIN32
	signal(SIGINT, sighandler);
#endif
	if (!exitcode)
	  exitcode = app->run();

	delete app;
	return exitcode;
}
