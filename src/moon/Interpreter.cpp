#include "Interpreter.h"
#include <sstream>

namespace moon {
	
	Interpreter::Interpreter() {
		luastate = lua_open();
		lua_atpanic(luastate, lua_panic_function);
	}
	
	Interpreter::~Interpreter() {
		if(luastate)
			lua_close(luastate);
	}
	
	/// @see the Lua manual
	void Interpreter::loadLibs(const luaL_reg *lib) {
		for (; lib->func; lib++) {
			loadedLibs.push_back(lib->name);
			lib->func(luastate);  /* open library */
			lua_settop(luastate, 0);  /* discard any results */
		}
	}
	
	/// @see the Lua manual
	void Interpreter::loadStandardLibs() {
		luaL_openlibs(luastate);
		loadedLibs.push_back(LUA_LOADLIBNAME);
		loadedLibs.push_back(LUA_TABLIBNAME);
		loadedLibs.push_back(LUA_IOLIBNAME);
		loadedLibs.push_back(LUA_OSLIBNAME);
		loadedLibs.push_back(LUA_STRLIBNAME);
		loadedLibs.push_back(LUA_MATHLIBNAME);
		loadedLibs.push_back(LUA_DBLIBNAME);
	}
	
	/// @see the Lua manual
	/// @return non-zero on errors, and a description is (hopefully) available through getError()
	int Interpreter::loadLib(const std::string& name, lua_CFunction func) {
		errstr = "";
		if (!func) {
			errstr = "NULL function passed to loadLib()";
			return 1;
		}
		status = func(luastate);
		if (status != 0 && getTop() > 0) {
			if (lua_tostring(luastate, -1))
				errstr = lua_tostring(luastate, -1);
			else {
				std::stringstream ss;
				ss << "loadLib returned " << status << " and top of stack is not string, stack:\n" << getStack();
				throw LuaException(ss.str());
			}
			lua_pop(luastate,1);
		} else
			loadedLibs.push_back(name);
		return status;
	}
	
	bool Interpreter::hasLoadedLib(const std::string& name) {
		for (size_t i = 0; i < loadedLibs.size(); i++) {
			if (loadedLibs[i] == name)
				return true;
		}
		return false;
	}
	
	/// @return non-zero on errors, and a description is available through getError()
	int Interpreter::doFile(const std::string& filename) {
		errstr = "";
		// Load the data
		status = luaL_loadfile(luastate, filename.c_str());
		if (status != 0 && getTop() > 0) {
			if (lua_tostring(luastate, -1))
				errstr = lua_tostring(luastate, -1);
			else {
				std::stringstream ss;
				ss << "doFile returned " << status << " and top of stack is not string, stack:\n" << getStack();
				throw LuaException(ss.str());
			}
			lua_pop(luastate,1);
			return status;
		}
		// Run it
		return pCall(0,1,0,1);
	}
	
	/// @return non-zero on errors, and a description is available through getError()
	int Interpreter::doString(const std::string& str, const std::string& identifier) {
		errstr = "";
		status = luaL_loadbuffer(luastate, str.c_str(), str.length(), identifier.c_str());
		if (status != 0 && getTop() > 0) {
			if (lua_tostring(luastate, -1))
				errstr = lua_tostring(luastate, -1);
			else {
				std::stringstream ss;
				ss << "doString returned " << status << " and top of stack is not string, stack:\n" << getStack();
				throw LuaException(ss.str());
			}
			lua_pop(luastate,1);
			return status;
		}
		// Run it
		return pCall(0,1,0,1);
	}

// Intrepreter::pCall
/**
 This method is typically used to call a Lua function from C++ code.
 @return non-zero on errors, and a description is available through getError().
 @see the Lua manual for more information.
 
 As an example, if the following Lua function has been defined:
@verbatim
function foo(a, b)
	c = a + 4700
	d = b - 11
	return c, d
end
@endverbatim
 
 The following C++ code would do the trick:
@code
moon::Interpreter lua;
// Push the function
lua.pushGlobal("foo");
// Push the arguments
lua.pushInt(11);
lua.pushInt(47);
// Call the function with correct number of arguments and return values
lua.pCall(2, 2);
// Pop return values in reverse order
int d = lua.popInt(); // = 36
int c = lua.popInt(); // = 4711
@endcode
 */
	
	int Interpreter::pCall(int nargs, int nresult, int errfunc, int pops) {
		errstr = "";
		status = lua_pcall(luastate,nargs,nresult,errfunc);
		if (status != 0 && getTop() > 0) {
			if (lua_isfunction(luastate, -1))
				lua_pcall(luastate, 0, 0, 0);
			else if (lua_tostring(luastate, -1))
				errstr = lua_tostring(luastate, -1);
			else {
				std::stringstream ss;
				ss << "lua_pcall returned " << status << " and top of stack is not string, stack:\n" << getStack();
				throw LuaException(ss.str());
			}
			lua_pop(luastate,1);
		}
		lua_pop(luastate,pops);
		return status;
	}
		
	/// @return an empty string on errors
	std::string Interpreter::getString(const std::string& varname) {
		if (!pushNamed(varname))
			return "";
		std::string str;
		const char *s = lua_tostring(luastate, -1);
		if (s)
			str = s;
		lua_pop(luastate, 1);
		return str;
	}
	
	/// @return zero on errors
	int Interpreter::getInt(const std::string& varname) {
		if (!pushNamed(varname))
			return 0;
		int i = lua_tointeger(luastate, -1);
		lua_pop(luastate, 1);
		return i;
	}
	
	/// @return zero on errors
	double Interpreter::getDouble(const std::string& varname) {
		if (!pushNamed(varname))
			return 0.0;
		double d = lua_tonumber(luastate, -1);
		lua_pop(luastate, 1);
		return d;
	}
	
	/// @return NULL on errors
	const void* Interpreter::getUserData(const std::string& varname) {
		if (!pushNamed(varname))
			return NULL;
		const void *p = lua_topointer(luastate, -1);
		lua_pop(luastate, 1);
		return p;
	}
	
	
	void Interpreter::setGlobal(const std::string& varname, const double d) {
		lua_pushstring(luastate, varname.c_str());
		lua_pushnumber(luastate, d);
		lua_settable(luastate, LUA_GLOBALSINDEX);
	}
	
	void Interpreter::setGlobal(const std::string& varname, const std::string& val) {
		lua_pushstring(luastate, varname.c_str());
		lua_pushstring(luastate, val.c_str());
		lua_settable(luastate, LUA_GLOBALSINDEX);
	}
	
	void Interpreter::setGlobal(const std::string& varname, void* data, const std::string& type) {
		lua_pushstring(luastate, varname.c_str());
		if (data)
			pushUserType(data,type);
		else
			lua_pushnil(luastate);
		lua_settable(luastate, LUA_GLOBALSINDEX);
	}
	
	void Interpreter::setTable(const std::string& key, const std::string& val, int index) {
		lua_pushstring(luastate,key.c_str());
		lua_pushstring(luastate,val.c_str());
		lua_settable(luastate,index);
	}
	
	void Interpreter::setTable(const std::string& key, const double val, int index) {
		lua_pushstring(luastate,key.c_str());
		lua_pushnumber(luastate,val);
		lua_settable(luastate,index);
	}
	
	void Interpreter::setTable(const std::string& key, void* data, const std::string& type, int index) {
		lua_pushstring(luastate,key.c_str());
		if (data)
			pushUserType(data,type);
		else
			lua_pushnil(luastate);
		lua_settable(luastate,index);
	}
	
	void Interpreter::setTable(const double key, const std::string& val, int index) {
		lua_pushnumber(luastate,key);
		lua_pushstring(luastate,val.c_str());
		lua_settable(luastate,index);
	}
	
	void Interpreter::setTable(const double key, const double val, int index) {
		lua_pushnumber(luastate,key);
		lua_pushnumber(luastate,val);
		lua_settable(luastate,index);
	}
	
	void Interpreter::setTable(const double key, void* data, const std::string& type, int index) {
		lua_pushnumber(luastate,key);
		pushUserType(data,type);
		lua_settable(luastate,index);
	}
	
	void Interpreter::newTable(const std::string& name) {
		if (name != std::string(""))
			lua_pushstring(luastate, name.c_str()); 
		lua_newtable(luastate); 
	}
	
	void Interpreter::pushUserType(void *data, const std::string& type)
	{
		int top = getTop();
		tolua_pushusertype(luastate,data,type.c_str());
		if (getTop() == top)
			throw LuaException(std::string("Failed to push user type ") + type);
	}
	/** Traverses through tables separated by '.' to find the appropriate
	 *  function , and pushes it onto the stack.
	 *  @return false if the named variable was not found
	 */
	bool Interpreter::pushNamed(const std::string& str) {
		int lasti = 0;
		int i = str.find('.');
		// don't look into tables if there's no '.' in the std::string
		if (i < 0) {
			pushGlobal(str);
			return true;
		}
		int count = 1;
		while (i >= 0) {
			std::string sub = str.substr(lasti,i-lasti);
			lasti = i+1;
			i = str.find('.',lasti);
			// get next table
			lua_pushstring(luastate,sub.c_str());
			if (count > 1)
				lua_gettable(luastate,-2);
			else
				lua_gettable(luastate,LUA_GLOBALSINDEX);
			if (lua_gettop(luastate) == 0)
				return false;
			if (lua_isnil(luastate, -1)) {
				pop(count);
				return false;
			}
			count++;
		}
		// get value
		lua_pushstring(luastate,str.substr(lasti).c_str());
		lua_gettable(luastate, -2);
		if (lua_isnil(luastate, -1)) {
			pop(count);
			return false;
		}
		// remove tables from stack
		while (lua_gettop(luastate) > 1 && lua_istable(luastate, -2)) {
			lua_remove(luastate, -2);
		}
		return true;
	}

	/**
	 * Used for Lua callbacks and extended functionality.
	 * @param data the object
	 * @param type tolua type of the object
	 * @param the method name
	 * @return true if the corresponding table key was found and it is a function
	 */
	bool Interpreter::pushMethod(void *data, const std::string& type, const std::string& name)
	{
		pushUserType(data, type);
		if (lua_gettop(luastate) == 0)
			return false;
		pushString(name);
		lua_gettable(luastate, -2);
		if (lua_gettop(luastate) >= 2 && (lua_isuserdata(luastate, -2) || lua_istable(luastate, -2)))
			lua_remove(luastate, -2);
		if (lua_isfunction(luastate, -1))
			return true;
		lua_pop(luastate, 1);
		return false;
	}

	void Interpreter::pop(const int num)
	{
		if (num > getTop()) {
			std::cout << "woah... num " << num << " top " << getTop() << ", stack:\n" << getStack();
			throw LuaException("Attempt to pop more than what is on the stack\n" + getStack());
		}
		lua_pop(luastate, num);
	}
	
	std::string Interpreter::getStack() {
		std::stringstream ss;
		int top = lua_gettop(luastate);
		for (int i = -1; i >= -top; i--) {
			ss << i << " " << lua_typename(luastate,lua_type(luastate,i)) << "\n";
		}
		return ss.str();
	}
	
	void Interpreter::collect() {
		lua_gc(luastate, LUA_GCCOLLECT, 0);
	}
	
	int Interpreter::getMemoryUsage() {
		return lua_gc(luastate, LUA_GCCOUNT, 0);
	}
	
	void Interpreter::causePanic() {
		lua_pushstring(luastate, "");
		lua_gettable(luastate, -1);
	}
	
	/** @note Singleton usage is optional, in order to allow a "global" interpreter
		and several other script interpreters. */
	Interpreter& Interpreter::instance() {
		if (!instanceptr)
			instanceptr = new Interpreter;
		return *instanceptr;
	}
	
	bool Interpreter::initialized = false;
	
	Interpreter *Interpreter::instanceptr = NULL;
	
	int lua_panic_function(lua_State *L) {
		const char *error = lua_tostring(L, -1);
		throw LuaException(error);
		return 0;
	}
		
} // namespace
