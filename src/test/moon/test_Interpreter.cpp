#include <unittest++/UnitTest++.h>
#include <moon/Interpreter.h>

TEST (PassingDataToLua) {
	moon::Interpreter lua;
	int ret = lua.doString(" val = 4711; doo = 47.11; foo = \"bar\" ");
	CHECK_EQUAL(0, ret);

	CHECK_EQUAL(4711, lua.getInt("val"));
	CHECK_CLOSE(47.11, lua.getDouble("doo"), 1e-5);
	CHECK_EQUAL("bar", lua.getString("foo"));
	lua.setGlobal("foo", "bazaar");
	CHECK_EQUAL("bazaar", lua.getString("foo"));
	
	// Get a value from a table
	ret = lua.doString("baz = {} ; baz.foo = \"bar\"");
	CHECK_EQUAL(0, ret);
	CHECK_EQUAL("bar", lua.getString("baz.foo"));
	// Make a new table
	lua.newTable("bong");
	lua.setTable("foo", "bazaar");
	lua.commitTable();
	CHECK_EQUAL("bazaar", lua.getString("bong.foo"));
	// Change a value in a table
	lua.pushNamed("baz");
	lua.setTable("foo", "bazong");
	CHECK_EQUAL("bazong", lua.getString("baz.foo"));
	
	// Check that we haven't caused any errors
	CHECK_EQUAL(0, lua.getStatus());
	// Check that the stack is empty
	CHECK_EQUAL(0, lua.getTop());
	
}

TEST (LuaErrors) {
	moon::Interpreter lua;
	int ret;
	// Try to access "foo" which doesn't exist
	ret = lua.doString(" foo.bar = 3 ");
	CHECK(ret != 0);

	ret = lua.doFile("/non/existent/file.lua");
	CHECK(ret != 0);

	// Non-existent variables just return 0 or ""
	CHECK_EQUAL("", lua.getString("blah.flah"));

	/** \todo Figure out a way to get these tests to pass
	// Try something that causes a Lua panic
	CHECK_THROW( lua.causePanic(), moon::LuaException);
	// Try a protected call with no success
	ret = lua.pCall(1,2,3);
	CHECK(ret != 0);
	*/
}

TEST (LuaGC) {
	moon::Interpreter lua;	
	char data[16348];
	for (int i = 0; i < 16348; i++)
		data[i] = 'a';
	
	lua.setGlobal("foo", data);
	CHECK(lua.getMemoryUsage() >= 16);
	lua.doString("foo = nil");
	lua.collect();
	CHECK(lua.getMemoryUsage() < 16);
}

TEST (CallLuaFunction) {
	moon::Interpreter lua;
	CHECK( lua.doString(" function func(a,b) c=a+4700; d=b-11; return c,d; end ") == 0 );
	// Push the function
	lua.pushNamed("func");
	// then its arguments
	lua.pushInt(11);
	lua.pushInt(47);
	// Provide the correct number of arguments and return values..
	CHECK( lua.pCall(2, 2) == 0);
	// Pop return values in reverse order
	CHECK_EQUAL(36, lua.popInt());
	CHECK_EQUAL(4711, lua.popInt());
}

TEST (CleanStack) {
	moon::Interpreter lua;
	// Check that pushNamed() cleans stack
	// when the item is found..
	CHECK( lua.doString("a = {} ; a.b = 4711") == 0 );
	CHECK(lua.pushNamed("a.b"));
	CHECK_EQUAL(1, lua.getTop());
	CHECK_EQUAL(4711, lua.popInt());
	// .. and not
	CHECK(!lua.pushNamed("a.c"));
	CHECK_EQUAL(0, lua.getTop());
	// .. and not again
	CHECK(!lua.pushNamed("b.c"));
	CHECK_EQUAL(0, lua.getTop());
	
	// .. and for subtables as well
	CHECK( lua.doString("a.a = {} ; a.a.b = 4711") == 0 );
	CHECK(lua.pushNamed("a.a.b"));
	CHECK_EQUAL(1, lua.getTop());
	CHECK_EQUAL(4711, lua.popInt());
	CHECK(!lua.pushNamed("a.a.c"));
	std::cout << lua.getStack() << "\n";
	CHECK_EQUAL(0, lua.getTop());
}

