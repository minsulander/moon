#ifndef MOON_SHELLAPPLICATION_H
#define MOON_SHELLAPPLICATION_H

#include "Application.h"
#include "TerminalConsole.h"
#include <osg/ArgumentParser>
#include <deque>
#include <string>

namespace moon {

	/// \addtogroup core
	///@{
	
	/// More elaborate application class
	class MOON_EXPORT ShellApplication : public Application {
	public:
		ShellApplication();
		virtual ~ShellApplication();
		
		bool init(int *argc = NULL, char *argv[] = NULL);
		virtual void initPaths();
		virtual void initViewer();
		/// Treat remaining command-line arguments as files to load
		virtual void loadRemainingArguments();
		/// Load file drag-n-dropped on OSX
		void dropLoad(const std::string& filename);

		virtual void update(const double dt);
		virtual int run();
		
		/// Print command-line usage information
		virtual void usage(const std::string& appname);
		virtual void printVersions(const int level);
		
		bool hasConsole() const { return console; }
		
	protected:
		osg::ArgumentParser* arguments;
		
	private:
		std::string startScenarioName;
		bool console, initialized;
		std::deque<std::string> dropFiles;
		TerminalConsole *terminalConsole;
		bool firstUpdate;
	};
	
	///@}
	
}

#endif
