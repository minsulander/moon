#ifndef WIN32

 #include "backtrace.h"
 #include <cxxabi.h>
 #include <libgen.h>
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <dlfcn.h>
 
 namespace moon {
 
 void print_callstack(void **callstack, int num)
 {
 	Dl_info info;
 	for (int i = 0; i < num; i++) {
 		int ret = dladdr(callstack[i], &info);
 		// basename of file
 		size_t len = 128;
		char filename[len];
		strcpy(filename, info.dli_fname);
		// demangle the name (found on Apple forums)
		char demangled_name[len];
		abi::__cxa_demangle(info.dli_sname, demangled_name, &len, &ret);
		if (ret == 0) {
			demangled_name[len] = 0;
			printf("%3d %30s %s\n", i, basename(filename), demangled_name);
		} else
	 		printf("%3d %30s %s\n", i, basename(filename), info.dli_sname);
	}
 }
 
 }

#endif //WIN32
