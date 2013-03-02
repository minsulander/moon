#ifndef MOODYN_DYNAMICSPLUGIN_H
#define MOODYN_DYNAMICSPLUGIN_H

#include <moon/Plugin.h>
#include <moon/Version.h>

namespace moodyn {
	
	/// \ingroup plugin dynamics
	class MOON_PLUGIN_EXPORT DynamicsPlugin : public moon::Plugin {
	public:
		virtual const char *getName() { return "moodyn"; }
		virtual const char *getDescription() { return "ODE dynamics plugin"; }
		virtual const char *getAuthor() { return "Martin Insulander <martin@insulander.com>"; }
		virtual float getVersion() { return MOON_VERSION; }
		
		virtual void onRegister();
		virtual void onUnregister();
		virtual void onInitialize();
		virtual bool handleProduct(moon::FactoryProduct *product);
	};
	
}

#endif
