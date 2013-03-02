#ifndef MOON_INTERPRETER_H
#define MOON_INTERPRETER_H

#include "Export.h"

#include <iostream>
#include <vector>
#include <exception>
#include <string>

// Couldn't figure out a way to make Lua use C++ and exceptions on Win32 and Linux...
#if defined(WIN32) && !defined(__MINGW32__)
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <tolua++.h>

#if defined(WIN32) && !defined(__MINGW32__)
}
#endif

#ifdef _MSC_VER
#	pragma warning(disable:4251)
#endif

namespace moon {
	
	/// \ingroup script
	/// @{
	
	/// Wrapper class for a Lua script interpreter
    class MOON_EXPORT Interpreter {
		
	public:
		
		Interpreter();
		~Interpreter();
		
		/// Load libraries using the Lua auxiliary library convention
		void loadLibs(const luaL_reg *libs);
		/// Load the standard Lua libraries
		void loadStandardLibs();
		/// Load a library through a lua C function 
		int loadLib(const std::string& name, lua_CFunction func);
		/// Returns true if the specified library name is loaded
		bool hasLoadedLib(const std::string& name);
		/// Interpret the contents of a file
		int doFile(const std::string& filename);
		/// Interpret the contents of a string
		int doString(const std::string& str, const std::string& identifier = "=string");
		/// Do a protected call
		int pCall(int nargs, int nresult, int errfunc = 0, int pops = 0);
		
		/// Get the lua state for further manipulation with Lua functions.
		/** @see the Lua manual.
			@note Handle with care! */
		lua_State* getState() { return luastate; }
		/// Get status code of last doFile(), doString() or pCall()
		int getStatus() { return status; }
		/// Get error description of last doFile(), doString() or pCall()
		const std::string& getError() { return errstr; }
		
		/// Get a string variable from the lua state
		std::string getString(const std::string& varname);
		/// Get an integer from the lua state
		int getInt(const std::string& varname);
		/// Get a double from the lua state
		double getDouble(const std::string& varname);
		/// Get a user data pointer from the lua state
		const void* getUserData(const std::string& varname);

		/// Set the contents of a global variable
		void setGlobal(const std::string& varname, const double d);
		/// Set the contents of a global variable
		void setGlobal(const std::string& varname, const std::string& val);
		/// Set the contents of a global variable
		void setGlobal(const std::string& varname, void* data, const std::string& type);
		/// Set the contents of a field in a table
		void setTable(const std::string& key, const std::string& val, int index = -3);
		/// Set the contents of a field in a table
		void setTable(const std::string& key, const double val, int index = -3);
		/// Set the contents of a field in a table
		void setTable(const std::string& key, void* data, const std::string& type, int index = -3);
		/// Set the contents of a field in a table
		void setTable(const double key, const std::string& val, int index = -3);
		/// Set the contents of a field in a table
		void setTable(const double key, const double val, int index = -3);
		/// Set the contents of a field in a table
		void setTable(const double key, void*  data, const std::string& type, int index = -3);
		/// Create a new table
		void newTable(const std::string& name = "");
		/// Commit a newly created table
		void commitTable(int index = LUA_GLOBALSINDEX) {lua_settable(luastate, index);}
		
		// Stack manipulation wrapper methods
		
		/// Push a boolean onto the stack
		void pushBool(const bool b)								{ lua_pushboolean(luastate, b); }
		/// Push a string onto the stack
		void pushString(const std::string& s)					{ lua_pushstring(luastate, s.c_str()); }
		/// Push an integer onto the stack
		void pushInt(const int i)								{ lua_pushinteger(luastate, i); }
		/// Push a double onto the stack
		void pushDouble(const double d)							{ lua_pushnumber(luastate, d); }
		/// Push a userdata pointer onto the stack
		void pushUserData(void* data)							{ lua_pushlightuserdata(luastate, data); }
		/// Push userdata with a stringed type (tolua fashion) onto the stack
		void pushUserType(void* data, const std::string& type);
		/// Push a nil onto the stack
		void pushNil()											{ lua_pushnil(luastate); }
		/// Push a global variable onto the stack
		void pushGlobal(const std::string& s)					{ lua_pushstring(luastate, s.c_str()); lua_gettable(luastate, LUA_GLOBALSINDEX); }
		/// Push a variable onto the stack
		bool pushNamed(const std::string& str);
		/// Push a "method" for a given object
		bool pushMethod(void* data, const std::string& type, const std::string& name);
		/// Pop the stack
		void pop(const int num);
		/// Pop a boolean from the stack
		bool popBool()											{ bool b = (lua_toboolean(luastate, -1) != 0); lua_pop(luastate,1); return b; }
		/// Pop a string from the stack
		std::string popString()									{ std::string s(lua_tostring(luastate,-1)); lua_pop(luastate,1); return s; }
		/// Pop an integer from the stack
		int popInt()											{ int n = lua_tointeger(luastate, -1); lua_pop(luastate,1); return n; }
		/// Pop a double from the stack
		double popDouble()										{ double n = lua_tonumber(luastate,-1); lua_pop(luastate,1); return n; }
		/// Pop a userdata pointer from the stack
		const void *popUserData()								{ const void *p = lua_topointer(luastate, -1); lua_pop(luastate,1); return p; }
		/// Get top of stack index (equals the number of items on the stack)
		int getTop() { return lua_gettop(luastate); }
		/// Get a string description of the stack
		std::string getStack();
		
		// Garbage collector wrappers
		/// Collect garbage
		void collect();
		/// Get memory usage (in kilobytes) from the garbage collector
		int getMemoryUsage();
	    
		/// Cause a Lua panic (for testing only, no other purpose)
		/// @throw LuaException
		void causePanic();
		
		/// Singleton accessor
		static Interpreter& instance();
		/// May be used to guard against certain operations until properly initialized
		static bool initialized;
		
	private:
		
		lua_State *luastate;
		int status;
		std::string errstr;
		typedef std::vector<std::string> LibsList;
		LibsList loadedLibs;
		
		static Interpreter *instanceptr;
    };

	class LuaException : public std::exception {
	public:
		LuaException(const std::string& error)
		{
			message = "LuaException: ";
			message += error;
		}
		virtual ~LuaException() throw() {}
		virtual const char* what() const throw() { return message.c_str(); }
		std::string message;
	};
	
	extern int lua_panic_function(lua_State *L);
	
	/// @}
}

#endif

