#ifndef MOON_TERMINALCONSOLE_H
#define MOON_TERMINALCONSOLE_H

#include <OpenThreads/Thread>
#include <OpenThreads/Mutex>
#include "Interpreter.h"

namespace moon {
	
	/// \ingroup script
	/// \brief A Lua console running on the terminal
	class MOON_EXPORT TerminalConsole : public OpenThreads::Thread {
	public:
		TerminalConsole(Interpreter *lua);
		
		virtual void run();
		
		OpenThreads::Mutex mutex;
	private:
		Interpreter *lua;
	};
	
}

#endif
