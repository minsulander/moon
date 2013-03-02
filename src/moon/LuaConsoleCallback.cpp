#include "LuaConsoleCallback.h"

#define DEFAULT_HELP "\
This is a Lua interpreter. See the manual at http://www.lua.org/ for an introduction.\n\
The help text here can be customized by defining a global help() function."

namespace moon {
	
	void LuaConsoleCallback::input(mdraw::ConsoleWindow* window, const std::string& line)
	{
		if (!lua)
			return;
		if (line.length() <= 0)
			return;
		int status = 0;
		buf += line;
		if (line == "help" || line == "?") {
			lua->pushGlobal("help");
			status = lua->pCall(0,0);
			if (status != 0)
				window->print(DEFAULT_HELP);
			status = 0;
		} else if (buf[0] == '=')
			status = lua->doString("_RET"+buf, "=console");
		else
			status = lua->doString(buf, "=console");

		if (status == 0) {
			window->setPrompt(lua->getString("_PROMPT"));
			if (buf[0] == '=') {
				lua->doString("print(_RET)");
				//std::string result = lua->getString("_RET");
				//window->print(result);
			}
			buf = "";
		} else {
			if (status == LUA_ERRSYNTAX && lua->getError().substr(lua->getError().length()-7) == "'<eof>'") {
				window->setPrompt(lua->getString("_PROMPT2"));
				buf += "\n";
			} else {
				window->setPrompt(lua->getString("_PROMPT"));
				std::stringstream ss;
				ss << "(" << status << ") " << lua->getError();
				if (ss.str().at(ss.str().length()-1) == '\n')
					window->print(ss.str().substr(0,ss.str().length()-1));
				else
					window->print(ss.str());
				buf = "";
			}
		}
	}
	
} // namespace
