#ifndef MLOG_LOG_H
#define MLOG_LOG_H

#include "Export.h"
#include <iostream>
#include <fstream>
#include <ios>

namespace mlog {

	/// \addtogroup log
	/// @{
		
	enum DebugLevel {
		ERROR = -2,
		WARN,
		INFO,
		DEBUG
    };
    
    enum LogCategory {
    	GENERAL,
    	NETWORK,
    	AUDIO,
		SCRIPT
    };
	
	/// Initialize logging
	extern MLOG_EXPORT void initializeLog();
    
    /// \brief Set debug level for log output. 
    /// \param level Any output above this level will be discarded.
	/// \param category Message category to apply this level to.
    /// \sa dout()
    extern MLOG_EXPORT void setDebugLevel(int level, const LogCategory category=GENERAL);

    /// Get current debug level.
    extern MLOG_EXPORT int getDebugLevel(LogCategory category=GENERAL);
    
    /// Set wether to use ANSI colors for \c ERROR and \c WARN levels
    extern MLOG_EXPORT void useLogColors(const bool value);
    
    /// Get wether using ANSI colors for \c ERROR and \c WARN levels
    extern MLOG_EXPORT bool usingLogColors();

    /// \brief Return an appropriate output stream for the given debug level.
	/// \param level Severity/debug level
	/// \param category Message category (levels are specified separately for different categories)
	/// \sa setDebugLevel()
    extern MLOG_EXPORT std::ostream& dout(const int level, const LogCategory category=GENERAL);

    /// Alternate form for debug log output, taking a string argument \a message instead of providing a string
    extern MLOG_EXPORT void dout(const int level, const std::string& message, const LogCategory category=GENERAL);
    
    /// Send output to a stream (instead of the default cout/cerr combination)
    extern MLOG_EXPORT void setLogStream(std::ostream *stream);
    
    /// Send output to a logfile
    extern MLOG_EXPORT void setLogFile(const std::string& filename);
    
	/// Get the current log stream
    extern MLOG_EXPORT std::ostream* getLogStream();
    
    /// If using log stream or colors, this should be called before exit
    extern MLOG_EXPORT void closeLog();
	
	/// @}
}
#endif
