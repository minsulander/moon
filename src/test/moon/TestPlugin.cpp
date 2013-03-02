#include "TestPlugin.h"
#include <moon/PluginManager.h>
#include <moon/ObjectFactory.h>

namespace moontest {
	REGISTER_PLUGIN(moontest::TestPlugin);
	
	void TestPlugin::onRegister()
	{
		registered = true;
		REGISTER_Object(moontest, TestProduct);
	}
	
	void TestPlugin::onUnregister()
	{
		UNREGISTER_Object(moontest, TestProduct);
		unregistered = true;
	}

}
