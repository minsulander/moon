
#include "Log.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#	pragma warning(disable:4996) // 'getenv' unsafe warning
#endif

namespace mlog {
	
	static std::map<LogCategory, int> debug_level;
	static bool initialized = false;
	static bool use_colors = false;
	static std::ostream *logstream = NULL;
	
#if defined(WIN32) && !(defined(__CYGWIN__) || defined(__MINGW32__))
	static const char* snull = "nul";
#else
	static const char* snull = "/dev/null";
#endif
	
	void initializeLog() {
		char *envs = getenv("MOON_LOG_LEVEL");
		if (envs)
			debug_level[GENERAL] = atoi(envs);
		envs = getenv("MOON_NETWORK_LOG_LEVEL");
		if (envs)
			debug_level[NETWORK] = atoi(envs);
		envs = getenv("MOON_AUDIO_LOG_LEVEL");
		if (envs)
			debug_level[AUDIO] = atoi(envs);
		envs = getenv("MOON_SCRIPT_LOG_LEVEL");
		if (envs)
			debug_level[SCRIPT] = atoi(envs);
		if (getenv("MOON_LOG_COLORS"))
			use_colors = true;
		initialized = true;
	}
	
	void setDebugLevel(int level, const LogCategory category) {
		if (!initialized)
			initializeLog();
		debug_level[category] = level;
	}
	
	int getDebugLevel(LogCategory category) {
		return debug_level[category];
	}
	
	void useLogColors(const bool value) {
		use_colors = value;
	}
	
	bool usingLogColors() {
		return use_colors;
	}
	
	/**
	 This function is the heart of the logging functionality. Debug levels above the \c INFO level
	 can be used freely, although levels above, say 10, seems rather meaningless.
	 \param level The debug level of the message to be passed on to the stream.
	 \sa setDebugLevel(), DebugLevels
	 \return \c std::cerr for \c ERROR and \c WARN levels, \c std::cout for levels below the currently set debuglevel,
	 \c /dev/null (or \c NUL on Win32) for levels above the current debuglevel (discards output).
	 
	 As an all-in-one example, consider:
	 \code
	 setDebugLevel(1); // level DEBUG == 1
	 dout(ERROR) << "The upper starboard magic flux generator has somehow disconnected" << std::endl;
	 dout(WARN)  << "Cross-dimensional gate has spontaneously opened itself" << std::endl;
	 dout(3)     << "  gate angle is " << gate->getAngle() << "\n";
	 dout(INFO)  << "Enabling creature passthrough countermeasures\n"; // level INFO == 0
	 dout(1)     << "  animated gatekeeper curse key=" << std::hex << gatekeeper.key << "\n";
	 \endcode
	 The above code would generate the following output:
	 \verbatim
	 Error: The upper starboard magic flux generator has somehow disconnected
	 Warning: Cross-dimensional gate has spontaneously opened itself
	 Enabling creature passthrough countermeasures
	 animated gatekeeper curse key=0x1f7a
	 \endverbatim
	 
	 Note that the message at debug level 3 was skipped. Also, the \c ERROR and \c WARN messages
	 had \c "Error:" and \c "Warning:" prepended to them.  The first two lines
	 (\c ERROR and \c WARN levels) are written to \c std::cerr, the rest to \c std::cout.
	 
	 Debug level can be set by the application using the setDebugLevel() function, but it can also
	 be controlled through the \c MOON_LOG_LEVEL environment variable (checked upon the first call to dout()).
	 
	 Default debug level is 0.
	 */
	std::ostream& dout(const int level, const LogCategory category) {
		// Initialize if needed
		static std::ofstream nullout(snull);
		if (!initialized)
			initializeLog();
		static int last_level = 0;
		// Return either stderr, stdout or /dev/null as appropriate
		if (debug_level[category] < level)
			return nullout;
		else if (level < 0) {
			if (logstream) {
				if (level != last_level && level == WARN)
					*logstream << "Warning: ";
				else if (level != last_level && level == ERROR)
					*logstream << "Error: ";
				last_level = level;
				return *logstream;
				
			} else {
#ifdef WIN32
				// Use only stdout on Windows
				if (level != last_level && level == WARN)
					std::cout << "Warning: ";
				else if (level != last_level && level == ERROR)
					std::cout << "Error: ";
				last_level = level;
				return std::cout;
#else
				if (level != last_level && level == WARN) {
					if (use_colors)
						std::cerr << (unsigned char)27 << "[33m";
					std::cerr << "Warning: ";
				} else if (level != last_level && level == ERROR) {
					if (use_colors)
						std::cerr << (unsigned char)27 << "[31m";
					std::cerr << "Error: ";
				}
				last_level = level;
				return std::cerr;
#endif
			}
		}
		if (level != last_level) {
			if (use_colors && (last_level == ERROR || last_level == WARN) && !logstream)
				std::cerr << (unsigned char)27 << "[0m";
		}
		last_level = level;
		if (logstream)
			return *logstream;
		else
			return std::cout;
	}
	
	void dout(const int level, const std::string& message, const LogCategory category) {
		if (debug_level[category] < level)
			return;
		dout(level, category) << message;
	}
	
	void setLogStream(std::ostream *stream) {
		logstream = stream;
		use_colors = false;
	}
	
	void setLogFile(const std::string& filename) {
		logstream = new std::ofstream(filename.c_str());
	}
	
	std::ostream* getLogStream() {
		return logstream;
	}
	
	void closeLog() {
		if (use_colors &&  !logstream) {
			std::cerr << (unsigned char)27 << "[0m";
			std::cout << (unsigned char)27 << "[0m";
		}
		//if (logstream)
		//	logstream->close();
	}
	
} // namespace
