#ifndef MOON_BACKTRACE_H
#define MOON_BACKTRACE_H

#ifndef WIN32

#include <execinfo.h>

namespace moon {

extern void print_callstack(void **callstack, int num);	
 
#define PRINT_BACKTRACE() \
 void* callstack[128]; \
 int i, frames = backtrace(callstack, 128); \
 print_callstack(callstack, frames);
 
}

#endif //WIN32

#endif
