#ifndef MOON_PLUGINMANAGER_H
#define MOON_PLUGINMANAGER_H

#include "Plugin.h"
#include <vector>
#include <map>
#include <string>

namespace moon {

	/// \brief Singleton manager for plugin libraries
	/// \ingroup plugin
	class MOON_EXPORT PluginManager {
	public:
		void registerPlugin(Plugin *plugin);
		void unregisterPlugin(Plugin *plugin);
		Plugin* load(const std::string& name);
		void loadAll();
		void unload();		
		Plugin* get(const std::string& name);
		unsigned int getNumPlugins() const { return plugins.size(); }
		Plugin* getPlugin(const unsigned int index);

		void initialize();
		void setRunning(const bool running);
		bool handleProduct(FactoryProduct *product);
		
		void setNoDisplay(const bool value) { nodisplay = value; }
		bool getNoDisplay() const { return nodisplay; }
		
		static PluginManager& instance();
	private:
		PluginManager(); // pure singleton
		static PluginManager *instancePtr;
		
		typedef std::vector<Plugin*> PluginList;
		PluginList plugins;
		Plugin* lastRegisteredPlugin;
		typedef std::map<std::string, void*> LibraryList;
		LibraryList libraries;
		
		bool initialized, running, nodisplay;
	};
}

#endif
