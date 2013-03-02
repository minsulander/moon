#ifndef MOON_LUACONSOLECALLBACK_H
#define MOON_LUACONSOLECALLBACK_H

#include "Export.h"
#include "Interpreter.h"
#include <mdraw/ConsoleWindow.h>
#include <string>

namespace moon {
	
	/// \ingroup script
	class MOON_EXPORT LuaConsoleCallback : public mdraw::ConsoleCallback {
	public:
		LuaConsoleCallback(Interpreter *nlua) : lua(nlua) {}
		virtual void input(mdraw::ConsoleWindow* window, const std::string& line);
	protected:
		Interpreter *lua;
		std::string buf;
	};
}

#endif
