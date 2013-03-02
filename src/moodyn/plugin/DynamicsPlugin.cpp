#include "DynamicsPlugin.h"
#include <mlog/Log.h>
#include <moon/PluginManager.h>
#include <moon/Interpreter.h>
#include "../bindings/tolua_moodyn.h"
#include "../World.h"

namespace moodyn {
	
	REGISTER_PLUGIN(moodyn::DynamicsPlugin);
	
	void DynamicsPlugin::onRegister()
	{
		World::instance();
	}
	
	void DynamicsPlugin::onUnregister()
	{
	}
	
	void DynamicsPlugin::onInitialize()
	{
		// Setup interpreter bindings
		moon::Interpreter& lua = moon::Interpreter::instance();
		if (!lua.loadLib("moodyn", tolua_moodyn_open))
			mlog::dout(mlog::ERROR) << "Loading moodyn bindings: " << lua.getError() << "\n";
	}
	
	bool DynamicsPlugin::handleProduct(moon::FactoryProduct *product)
	{
		if (DynamicsConfiguration *config = dynamic_cast<DynamicsConfiguration*> (product))
			// DynamicsConfiguration sets World parameters at parse time - so it can be ignored here
			return true;
		return false;
	}
	
}
