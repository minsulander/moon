#include "AudioPlugin.h"
#include "../AudioManager.h"
#include <mlog/Log.h>
#include <moon/PluginManager.h>
#include <moon/Interpreter.h>
#include "../bindings/tolua_maudio.h"

namespace maudio {
	
	REGISTER_PLUGIN(maudio::AudioPlugin);
	
	void AudioPlugin::onRegister()
	{
		if (!moon::PluginManager::instance().getNoDisplay())
			AudioManager::instance().init();
		else
			mlog::dout(1, mlog::AUDIO) << "Skipping audio initialization because of no display\n";
	}
	
	void AudioPlugin::onUnregister()
	{
		if (AudioManager::instance().isInitialized())
			AudioManager::instance().shutdown();
	}
	
	void AudioPlugin::onInitialize()
	{
		// Setup interpreter bindings
		moon::Interpreter& lua = moon::Interpreter::instance();
		if (lua.loadLib("maudio", tolua_maudio_open)) {
			lua.setGlobal("audio", &AudioManager::instance(), "maudio::AudioManager");
		} else
			mlog::dout(mlog::ERROR) << "Loading maudio bindings: " << lua.getError() << "\n";
	}
	
	bool AudioPlugin::handleProduct(moon::FactoryProduct *product)
	{
		if (Sound *sound = dynamic_cast<Sound*> (product)) {
			AudioManager::instance().addSound(sound);
			return true;
		}
		return false;
	}
	
}
