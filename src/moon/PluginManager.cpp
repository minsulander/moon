#include "PluginManager.h"
#include <mlog/Log.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <osgDB/FileUtils>

#if defined(WIN32) && !defined(__CYGWIN__)
#include <io.h>
#include <windows.h>
#include <winbase.h>
#else
#include <dlfcn.h>
#endif

#if defined(WIN32)
#  define PLUGIN_EXTENSION ".dll"
#else
#  define PLUGIN_EXTENSION ".so"
#endif

using namespace mlog;

namespace moon {
	
	void PluginManager::registerPlugin(Plugin *plugin)
	{
		// check for duplicates
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++) {
			if (std::string((*it)->getName()) == plugin->getName())
				throw PluginException(std::string("Plugin '") + plugin->getName() + std::string("' already registered"));
		}
		plugins.push_back(plugin);
		dout(2) << "Registering plugin " << plugin->getName() << "\n";
		dout(3) << "  Description: " << plugin->getDescription() << "\n";
		dout(3) << "  Author: " << plugin->getAuthor() << "\n";
		dout(3) << "  Version: " << plugin->getVersion() << "\n";
		plugin->onRegister();
		if (initialized)
			plugin->onInitialize();
		if (running)
			plugin->setRunning(true);
		lastRegisteredPlugin = plugin;
	}
	
	void PluginManager::unregisterPlugin(Plugin *plugin)
	{
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++) {
			if (*it == plugin) {
				dout(2) << "Unregistering plugin " << plugin->getName() << "\n";
				plugin->onUnregister();
				/// \todo delete plugin or use ref pointer?
				plugins.erase(it);
				return;
			}
		}
	}
	
	Plugin* PluginManager::load(const std::string& name)
	{
		lastRegisteredPlugin = NULL;
		if (name.length() == 0)
			throw PluginException("Empty plugin name");
		std::string fname;
		bool checkname = true;
		// Check if it's a complete filename
		if (osgDB::fileType(name) == osgDB::REGULAR_FILE) {
			fname = name;
			checkname = false;
		} else {
			std::string osname;
			osname += "moonplug_" + name;
#if defined(MOON_DEBUG)
			osname += "d";
#endif
			osname += PLUGIN_EXTENSION;
			// find plugin file in library path
			fname = osgDB::findLibraryFile(osname);
			if (fname.length() == 0) {
				std::stringstream ss;
				ss << osname << ": File not found in library path";
				throw PluginException(ss.str());
			}
		}
		
		dout(3) << "Loading plugin library " << fname << "\n";
#if defined(WIN32) && !defined(__CYGWIN__)
		void *handle = LoadLibrary( fname.c_str() );
		if (!handle)
			throw PluginException(fname + ": Failed to load plugin");
#else
		void *handle = dlopen( fname.c_str(), RTLD_NOW | RTLD_GLOBAL);
		if (!handle)
			throw PluginException(fname + ": " + dlerror());
#endif
		void (*loadfunc)();
		loadfunc = NULL;
#if defined(WIN32) && !defined(__CYGWIN__)
		loadfunc = (void (*)())GetProcAddress((HMODULE)handle,"moon_Plugin_Load");
#else
		loadfunc = (void (*)()) dlsym(handle,"moon_Plugin_Load");
#endif
		if (!loadfunc)
			throw PluginException(fname + ": Failed to load plugin. Entry point 'moon_Plugin_Load' not found.");
		(*loadfunc)();
		libraries[name] = handle;
		if (!lastRegisteredPlugin)
			throw PluginException(fname + ": Plugin failed to register.");
		if (checkname && name != lastRegisteredPlugin->getName() && name != std::string(lastRegisteredPlugin->getName()) + "d")
			throw PluginException(fname + ": Plugin name mismatch '" + name + "' vs '" + lastRegisteredPlugin->getName() + "'");
		return lastRegisteredPlugin;
	}
	
	void PluginManager::loadAll()
	{
	  std::string ext(PLUGIN_EXTENSION);
	  dout(2) << "Loading all plugins\n";
	  osgDB::FilePathList& paths = osgDB::getLibraryFilePathList();
	  for (unsigned int pathi = 0; pathi < paths.size(); pathi++) {
	    osgDB::DirectoryContents dir = osgDB::getDirectoryContents(paths[pathi]);
	    for (unsigned int diri = 0; diri < dir.size(); diri++) {
	      if (dir[diri].substr(0,8) == "moonplug" && dir[diri].substr(dir[diri].length()-ext.length()) == ext) {
		std::string name = dir[diri].substr(9);
		name = name.substr(0,name.find_first_of("."));
		if (get(name) || (name.substr(name.length()-1) == "d" && get(name.substr(0,name.length()-1))) )
		  dout(4) << "Plugin '" << name << "' already loaded, skipping " << paths[pathi] << "/" << dir[diri] << "\n";
					else
					  load(paths[pathi] + "/" + dir[diri]);
	      }
	    }
	  }
	}
	
	void PluginManager::unload()
	{
		/// Unregister and delete all plugins
		dout(2) << "Unregistering plugins\n";
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++) {
			(*it)->onUnregister();
			delete *it;
		}
		plugins.clear();
		/// Unload all libraries
		dout(2) << "Unloading plugin libraries\n";
		for (LibraryList::iterator it = libraries.begin(); it != libraries.end(); it++) {
#ifdef WIN32
			int ret = FreeLibrary((HMODULE) it->second);
			if (ret == 0)
				dout(ERROR) << "Unloading " << it->first << ": win32 error code " << GetLastError() << "\n";
#else
			int ret = dlclose(it->second);
			if (ret != 0)
				dout(ERROR) << "Unloading " << it->first << ": " << dlerror() << "\n";
#endif
		}
	}
	
	Plugin* PluginManager::get(const std::string& name)
	{
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++) {
			if (name == (*it)->getName())
				return *it;
		}
		return NULL;
	}
	
	Plugin* PluginManager::getPlugin(const unsigned int index)
	{
		if (index >= plugins.size())
			return NULL;
		return plugins[index];
	}
	
	void PluginManager::initialize()
	{
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++)
			(*it)->onInitialize();
		initialized = true;
	}
	
	void PluginManager::setRunning(const bool value)
	{
		running = value;
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++)
			(*it)->setRunning(value);
	}
	
	bool PluginManager::handleProduct(FactoryProduct *product)
	{
		for (PluginList::iterator it = plugins.begin(); it != plugins.end(); it++) {
			if ((*it)->handleProduct(product))
				return true;
		}
		return false;
	}
	
	PluginManager& PluginManager::instance()
	{
		if (!instancePtr)
			instancePtr = new PluginManager;
		return *instancePtr;
	}
	
	PluginManager::PluginManager()
	: lastRegisteredPlugin(NULL), initialized(false), running(false), nodisplay(false)
	{
	}
	
	PluginManager* PluginManager::instancePtr = NULL;

}
