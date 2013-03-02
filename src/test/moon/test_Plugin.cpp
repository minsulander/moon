#include <unittest++/UnitTest++.h>
#include <moon/PluginManager.h>
#include <moon/ObjectFactory.h>
#include <osgDB/FileUtils>
#include "TestPlugin.h"

using namespace moon;
using namespace moontest;

PluginManager& plugman = PluginManager::instance();

/*
TEST (RegisterPlugin)
{
	CHECK(plugman.get("test") == NULL);
	
	TestPlugin *testplug = new TestPlugin;
	plugman.registerPlugin(testplug);
	CHECK(testplug->registered);
	CHECK(plugman.get("test") != NULL);

	// Registering duplicate plugins should cause exception
	TestPlugin *testplug2 = new TestPlugin;
	CHECK_THROW(plugman.registerPlugin(testplug2), PluginException);

	plugman.unregisterPlugin(testplug);
	CHECK(testplug->unregistered);
	
	CHECK(plugman.get("test") == NULL);

	delete testplug2, testplug;
}
*/

TEST (LoadPlugin)
{
#ifdef MOONTEST_PLUGIN_PATH
	osgDB::getLibraryFilePathList().push_back(MOONTEST_PLUGIN_PATH);
#  ifdef MOON_DEBUG
	osgDB::getLibraryFilePathList().push_back(MOONTEST_PLUGIN_PATH "/Debug");
#  else
	osgDB::getLibraryFilePathList().push_back(MOONTEST_PLUGIN_PATH "/Release");
#  endif
#endif
	// None of the TestPlugin related objects should exist before we start the test
	CHECK(plugman.get("test") == NULL);
	CHECK(ObjectFactory::instance().create("moontest_TestProduct") == NULL);	
	
	Plugin* testplug = plugman.load("test");
	CHECK(testplug != NULL);
	CHECK(plugman.get("test") != NULL);
	CHECK(testplug == plugman.get("test"));
	
	// Loading duplicate plugins should cause exception
	CHECK_THROW(plugman.load("test"), PluginException);
	
	// The test plugin registers a FactoryProduct - check its existence
	{
		FactoryProduct *product = ObjectFactory::instance().create("moontest_TestProduct");
		CHECK(product != NULL);
		if (product)
			delete product;
	}
	
	plugman.unload();
	CHECK(plugman.get("test") == NULL);
	CHECK(ObjectFactory::instance().create("moontest_TestProduct") == NULL);	
}
