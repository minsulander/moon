#ifndef MAUDIO_AUDIOPLUGIN_H
#define MAUDIO_AUDIOPLUGIN_H

#include <moon/Plugin.h>
#include <moon/Version.h>

namespace maudio {

	/// \ingroup plugin audio
	class MOON_PLUGIN_EXPORT AudioPlugin : public moon::Plugin {
	public:
		virtual const char *getName() { return "maudio"; }
		virtual const char *getDescription() { return "OpenAL audio plugin"; }
		virtual const char *getAuthor() { return "Martin Insulander <martin@insulander.com>"; }
		virtual float getVersion() { return MOON_VERSION; }
		
		virtual void onRegister();
		virtual void onUnregister();
		virtual void onInitialize();
		virtual bool handleProduct(moon::FactoryProduct *product);
	};
	
}

#endif
