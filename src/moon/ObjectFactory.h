#ifndef MOON_OBJECTFACTORY_H
#define MOON_OBJECTFACTORY_H

#include "Export.h"
#include "Factory.h"
#include "FactoryProduct.h"
#include "moonet/ObjectFactory.h"
#include <string>
#include <exception>
#include <stack>

namespace moon
{
	
	/// \addtogroup core
	/// @{
	
	/// Callback for some factory events like loading files, parsing objects etc.
	class MOON_EXPORT FactoryCallback : public osg::Referenced {
	public:
		virtual void onParseObject(const FactoryProduct *object) {}
		virtual void onLoadStart(const std::string& filename) {}
		virtual void onLoadFinish(const std::string& filename) {}
	};
	
	
	/// The object factory creates/loads/saves objects and manages templates/instances
	class MOON_EXPORT ObjectFactory : public Factory<std::string, FactoryProduct>, public moonet::ObjectFactory {
	public:
		typedef std::vector< osg::ref_ptr<FactoryProduct> > ObjectList;
		/// Parse objects from an XML element
		ObjectList parseObjects(const TiXmlElement *element, const bool picky = true, const bool globalTemplates = false, const std::string& specname = "", const std::string& spectype = "");
		/// Parse objects from an XML string
		ObjectList parseObjects(const std::string& xmlstring, const bool picky = true, const bool globalTemplates = false, const std::string& rootnode = "moon", const std::string& specname = "", const std::string& spectype = "");
		/// Load objects from an XML file
		ObjectList loadObjects(const std::string& filename, const bool picky = true, const bool globalTemplates = false, const std::string& rootnode = "moon", const std::string& specname = "", const std::string& spectype = "");
		/// Write template objects to an XML element
		void writeTemplates(TiXmlElement *element);
		/// Write objects to an XML element
		void writeObjects(const ObjectList& objects, TiXmlElement *element, const bool withTemplates = true);
		/// Write objects to an XML string
		std::string writeObjects(const ObjectList& objects, const bool withTemplates = true, const std::string& rootnode = "moon");
		/// Save objects to an XML file
		void saveObjects(const ObjectList& objects, const std::string& filename, const bool withTemplates = true, const std::string& rootnode = "moon");
		
		/// Get a template by name
		const FactoryProduct* getTemplate(const std::string& name) const;
		/// Get a template by its index in the template map
		const FactoryProduct* getTemplate(const unsigned int index) const;
		/// Get number of templates available
		unsigned int getNumTemplates() const;
		/// Add a template
		void addTemplate(FactoryProduct* templateObject);
		/// Remove all templates
		void clearTemplates();
		/// Remove a template by its name
		void removeTemplate(const std::string& name);
		/// Remove a template
		void removeTemplate(const FactoryProduct* templateObject);
		/// Get number of times a template has been instantiated
		unsigned int getTemplateUsage(const FactoryProduct* templateObject);
		/// Create an object from a template
		FactoryProduct* createInstance(const FactoryProduct *templateObject, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		/// Create an object from a template by name
		FactoryProduct* createInstance(const std::string& templateName, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		
		moonet::NetworkObject *createNetworkObject(const std::string& objectName);
		
		void setCallback(FactoryCallback* newcallback) { callback = newcallback; }
		FactoryCallback* getCallback() { return callback.get(); }
		std::string getCurrentFileName();
		
		static ObjectFactory& instance();
		
		virtual ~ObjectFactory() {}

	protected:
		typedef std::map< std::string, unsigned int> CreateCountMap;
		CreateCountMap createcount;
		
		typedef std::map< std::string, osg::ref_ptr<FactoryProduct> > TemplateMap;
		TemplateMap templates;
		
		typedef std::map< const FactoryProduct*, unsigned int> TemplateCountMap;
		TemplateCountMap templatecount;
		
		std::stack<std::string> fileStack;
		std::stack<std::string> rootStack;
		
		osg::ref_ptr<FactoryCallback> callback;
		
		static ObjectFactory* instanceptr;
	};
	
	template <class ObjectT>
	class ObjectAdder {
	public:
		ObjectAdder(const std::string& identifier) { 
			moon::ObjectFactory::instance().registerObject(identifier, new Creator<ObjectT, moon::FactoryProduct>);
		}
	};
	
	class ObjectRemover {
	public:
		ObjectRemover(const std::string& identifier) { 
			moon::ObjectFactory::instance().unregisterObject(identifier);
		}
	};
	
	#define REGISTER_Object(library, name) \
		moon::ObjectAdder<name> adder##library##name(#library "_" #name)
	#define REGISTER_Object_Alias(library, name, identifier) \
		moon::ObjectAdder<name> adder##library##name(#library "_" #name); \
		moon::ObjectAdder<name> adder##identifier(#identifier)
	#define UNREGISTER_Object(library, name) \
		moon::ObjectRemover remover##library##name(#library "_" #name)
	#define UNREGISTER_Object_Alias(library, name, identifier) \
		moon::ObjectRemover remover##library##name(#library "_" #name); \
		moon::ObjectRemover remover##identifier(#identifier)
	
	#define REGISTER_Object_Func(library, name) \
		moon::ObjectFactory::instance().registerObject(#library "_" #name, new Creator<name, moon::FactoryProduct>)
	#define REGISTER_Object_Func_Alias(library, name, identifier) \
	moon::ObjectFactory::instance().registerObject(#library "_" #name, new Creator<name, moon::FactoryProduct>); \
		moon::ObjectFactory::instance().registerObject(#identifier,new Creator<name, moon::FactoryProduct>)
	#define UNREGISTER_Object_Func(library, name) \
		moon::ObjectFactory::instance().unregisterObject(#library "_" #name)
	#define UNREGISTER_Object_Func_Alias(library, name, identifier) \
		moon::ObjectFactory::instance().unregisterObject(#library "_" #name); \
		moon::ObjectFactory::instance().unregisterObject(#identifier)
	
	class NoSuchObjectException : public std::exception {
	public:
		NoSuchObjectException(const std::string& identifier) : message("No such object '" + identifier + "'") {}
		virtual ~NoSuchObjectException() throw() {}
		virtual const char* what() const throw() { return message.c_str(); }
		std::string message;
	};

	class NoSuchTemplateException : public std::exception {
	public:
		NoSuchTemplateException(const std::string& identifier) : message("No such template '" + identifier + "'") {}
		virtual ~NoSuchTemplateException() throw() {}
		virtual const char* what() const throw() { return message.c_str(); }
		std::string message;
	};
	
	class FactoryIOException : public std::exception {
	public:
		FactoryIOException(const std::string& nmessage) : message(nmessage) {}
		virtual ~FactoryIOException() throw() {}
		virtual const char* what() const throw() { return message.c_str(); }
		std::string message;
	};

	/// @}
}

#endif
