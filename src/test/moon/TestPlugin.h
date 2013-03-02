#ifndef MOONTEST_TESTPLUGIN_H
#define MOONTEST_TESTPLUGIN_H

#include <moon/Plugin.h>
#include <moon/FactoryProduct.h>

namespace moontest {
	
	class MOON_PLUGIN_EXPORT TestPlugin : public moon::Plugin {
	public:
		virtual const char *getName() { return "test"; }
		virtual const char *getDescription() { return "Plugin for internal moon engine testing"; }
		virtual const char *getAuthor() { return "Martin Insulander <martin@insulander.com>"; }
		virtual float getVersion() { return 0.1f; }
		
		virtual void onRegister();
		virtual void onUnregister();
		
		TestPlugin() : registered(false), unregistered(false) {}
		virtual ~TestPlugin() {}
		
		bool registered, unregistered;
	};
	
	class MOON_PLUGIN_EXPORT TestProduct : public moon::FactoryProduct {
	public:
		TestProduct()
			: count(0) {}
		TestProduct(const TestProduct& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
			: count(source.count) {}
		META_Object(moontest, TestProduct);
		virtual void parseXML(const TiXmlElement *element) {}
		virtual void writeXML(TiXmlElement *element) const {}
		
		void dostuff() { count++; }
		int count;
	};

}

#endif
