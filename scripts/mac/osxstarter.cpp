#include <FL/x.H>
#include <FL/Fl.H>
#include <sstream>
#include <libgen.h>
#include <stdlib.h>

std::stringstream command;

void open_callback(const char *filename)
{
	command << " \"" << filename << "\"";
}

int main(int argc, char **argv)
{
	command << dirname(argv[0]) << "/../Resources/start.sh";
	fl_open_callback(&open_callback);
	Fl::wait(0.1);
	
	system(command.str().c_str());
}