#ifndef MOON_PLUGIN_H
#define MOON_PLUGIN_H

#include "Export.h"
#include "FactoryProduct.h"
#include <exception>
#include <string>

namespace moon {
	
	/// \brief Interface class for all plugins.
	/// \ingroup plugin
	class MOON_EXPORT Plugin {
	public:
		/// Get name of the plugin
		virtual const char* getName() = 0;
		/// Get a short one-line description of the plugin
		virtual const char* getDescription() = 0;
		/// Get author of the plugin. Should include contact information.
		virtual const char* getAuthor() = 0;
		/// Get release version of the plugin.
		virtual float getVersion() { return -1; }
		
		/// Called by the PluginManager when the plugin library has been loaded.
		virtual void onRegister() {}
		/// Called by the PluginManager before the plugin library is unloaded.
		virtual void onUnregister() {}
		/// Called by the PluginManager when application initialization is done
		virtual void onInitialize() {}
		/// Called by the PluginManager when application run state is changed
		virtual void setRunning(const bool running) {}
		/// Handle an application-level FactoryProduct from a data file
		virtual bool handleProduct(FactoryProduct *product) { return false; }
		
		virtual ~Plugin() {}
	};

	/// \brief Exception thrown on plugin loading/registering errors
	/// \ingroup plugin
	class MOON_EXPORT PluginException : public std::exception {
	public:
		PluginException(const std::string& error, Plugin* plugin = NULL) { 
			this->plugin = plugin; this->error = error;
		}
		virtual ~PluginException() throw() {}
		virtual const char* what() const throw()
		{
			return error.c_str();
		}
		std::string error;
		Plugin *plugin;
	};
}

#define REGISTER_PLUGIN(name) \
extern "C" { \
	void MOON_PLUGIN_EXPORT moon_Plugin_Load() { \
		moon::PluginManager::instance().registerPlugin(new name); \
	} \
}

#endif
