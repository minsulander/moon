#include "ObjectFactory.h"
#include "XMLParser.h"
#include "mlog/Log.h"
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>

using namespace mlog;

namespace moon {
	
#ifdef WIN32
	const char* DIR_SEPARATOR = "\\";
#else
	const char* DIR_SEPARATOR = "/";
#endif
	
	std::string dirname(const std::string& path)
	{
		if (path.length() == 0)
			return ".";
		std::string::size_type index = path.rfind(DIR_SEPARATOR, path.length()-1);
		if (index == std::string::npos)
			return ".";
		std::string dir;
		dir = path.substr(0,index);
		if (dir.length() == 0)
			return "/";
		return dir;
	}
	
	/// @param picky If set, NoSuchObjectException will be thrown if unknown object types encountered
	/// @param globalTemplates Put templates in global templates list 
	/// @param specname Load specific object with this name (if not empty)
	/// @param spectype Load specific objects of this type (if not empty)
	/// @throw NoSuchObjectException if \a picky is set and unknown object types encountered
	ObjectFactory::ObjectList ObjectFactory::parseObjects(const TiXmlElement *element, const bool picky, const bool globalTemplates, const std::string& specname, const std::string& spectype)
	{
		ObjectList localTemplates;
		ObjectList objects;
		element = element->FirstChildElement();
		while (element) {
			std::string type = element->Value();
			std::string name = "";
			if (element->Attribute("name"))
				name = element->Attribute("name");
			// parse special element names
			FactoryProduct *object = NULL;
			if (type == "include") {
				if (fileStack.size() == 0)
					throw FactoryIOException("Cannot include file from non-file");
				// Include another file
				std::string path;
				std::string dir = dirname(fileStack.top());
				if (dir.length() > 0)
					path = dir + "/";
				path += element->Attribute("file");
				dout(4) << "Include file " << path << "\n";
				ObjectList incobjects = loadObjects(path, picky, globalTemplates, rootStack.top(), specname, spectype);
				dout(4) << "Back to " << fileStack.top() << "\n";
				for (ObjectList::iterator it = incobjects.begin(); it != incobjects.end(); it++)
					objects.push_back(it->get());
			} else if ((spectype.length() > 0 && std::string(element->Value()) != spectype) ||
					   (specname.length() > 0 && (!element->Attribute("name") || std::string(element->Attribute("name")) != specname))) {
				element = element->NextSiblingElement();
				continue;
			} else if (type == "templates") {
				// List of templates
				ObjectList templateObjects = parseObjects(element);
				for (ObjectList::iterator it = templateObjects.begin(); it != templateObjects.end(); it++) {
					addTemplate(it->get());
					if (globalTemplates)
						dout(4) << "Global template " << (*it)->getName() << "\n";
					else {
						dout(4) << "Local template " << (*it)->getName() << "\n";
						localTemplates.push_back(it->get());
					}
				}
			} else if (const FactoryProduct *temp = getTemplate(type)) {
				// Template instance
				object = createInstance(temp);
				if (name.length() > 0)
					object->setName(name);
				dout(4) << "Instance of " << type;
				if (name.length() > 0)
					dout(4) <<  " '" << name << "'";
				dout(4) << "\n";
			} else {
				object = create(type);
				// Assume namespace moon if object type was not found
				if (!object)
					object = create(std::string("moon_") + type);
				if (!object) {
					if (picky)
						throw NoSuchObjectException(type);
				} else {
					createcount[element->Value()]++;
					
					if (name.length() > 0) {
						object->setName(name);
					} else {
						std::stringstream namess;
						namess << type << "_" << createcount[type];
						object->setName(namess.str());
					}
					dout(4) << type << " '" << object->getName() << "'\n";
				}
			}
			if (object) {
				if (callback.valid())
					callback->onParseObject(object);
				object->parseXML(element);
				objects.push_back(object);
			}
			element = element->NextSiblingElement();
		}
		for (ObjectList::iterator it = localTemplates.begin(); it != localTemplates.end(); it++)
			removeTemplate(it->get());
		return objects;
	}
	
	/// @param picky If set, NoSuchObjectException will be thrown if unknown object types encountered
	/// @param globalTemplates Put templates in global templates list 
	/// @param rootnode Expect this XML root tag
	/// @param specname Load specific object with this name (if not empty)
	/// @param spectype Load specific objects of this type (if not empty)
	/// @throw NoSuchObjectException if \a picky is set and unknown object types encountered
	/// @throw ParseNoElementException if the \a rootnode is not correct
	ObjectFactory::ObjectList ObjectFactory::parseObjects(const std::string& xmlstring, const bool picky, const bool globalTemplates, const std::string& rootnode, const std::string& specname, const std::string& spectype)
	{
		TiXmlDocument doc;
		doc.Parse(xmlstring.c_str());
		TiXmlHandle hdoc(&doc);
		TiXmlElement *root = hdoc.FirstChildElement().Element();
		if (!root)
			throw ParseNoElementException("No root node");
		if (root->Value() != rootnode)
			throw ParseNoElementException(std::string("Root node is '") + root->Value() + "', expected '" + rootnode + "'", root);
		return parseObjects(root, picky, globalTemplates, specname, spectype);
	}
	
	/// @param picky If set, NoSuchObjectException will be thrown if unknown object types encountered
	/// @param globalTemplates Put templates in global templates list 
	/// @param rootnode Expect this XML root tag
	/// @param specname Load specific object with this name (if not empty)
	/// @param spectype Load specific objects of this type (if not empty)
	/// @throw NoSuchObjectException if \a picky is set and unknown object types encountered
	/// @throw ParseNoElementException if the \a rootnode is not correct
	ObjectFactory::ObjectList ObjectFactory::loadObjects(const std::string& filename, const bool picky, const bool globalTemplates, const std::string& rootnode, const std::string& specname, const std::string& spectype) {
		fileStack.push(filename);
		rootStack.push(rootnode);
		std::string datadir = osgDB::getFilePath(filename);
		osgDB::FilePathList& pathlist = osgDB::getDataFilePathList();
		pathlist.push_back(datadir);
		if (callback.valid())
			callback->onLoadStart(fileStack.top());
		XMLParser::currentFile = fileStack.top();

		TiXmlDocument doc;
		if (!doc.LoadFile(filename)) {
			std::stringstream ss;
			ss << filename << ":" << doc.ErrorRow() << ": " << doc.ErrorDesc();
			throw FactoryIOException(ss.str());
		}
		TiXmlHandle hdoc(&doc);
		TiXmlElement *root = hdoc.FirstChildElement().Element();
		if (!root)
			throw ParseNoElementException("No root node");
		if (root->Value() != rootnode)
			throw ParseNoElementException(std::string("Root node is '") + root->Value() + "', expected '" + rootnode + "'", root);
		ObjectList objects = parseObjects(root, picky, globalTemplates, specname, spectype);

		if (callback.valid())
			callback->onLoadFinish(fileStack.top());
		for (osgDB::FilePathList::iterator it = pathlist.begin(); it != pathlist.end(); it++) {
			if (*it == datadir) {
				pathlist.erase(it);
				break;
			}
		}
		fileStack.pop();
		rootStack.pop();
		if (fileStack.size() > 0)
			XMLParser::currentFile = fileStack.top();
		else
			XMLParser::currentFile = "";
		return objects;
	}
	
	void ObjectFactory::writeTemplates(TiXmlElement *root)
	{
		ObjectList objects;
		for (TemplateMap::iterator it = templates.begin(); it != templates.end(); it++)
			objects.push_back(it->second);
		writeObjects(objects, root, false);
	}
	
	/// @param objects Objects to save to file
	/// @param root XML element to "write" to
	/// @param withTemplates If specified, templates will be written to the \c templates sub-element
	void ObjectFactory::writeObjects(const ObjectList& objects, TiXmlElement *root, const bool withTemplates)
	{
		std::map<const FactoryProduct*, bool> writtenLocalTemplates;
		TiXmlElement *templatesElement = new TiXmlElement("templates");
		root->LinkEndChild(templatesElement);
		if (withTemplates && templates.size() > 0) {
			writeTemplates(templatesElement);
		}
		for (ObjectList::const_iterator it = objects.begin(); it != objects.end(); it++) {
			const FactoryProduct *object = it->get();
			if (!object || object->isTemporary())
				continue;
			TiXmlElement *element;
			if (object->getTemplate()) {
				const FactoryProduct *temp = object->getTemplate();
				element = new TiXmlElement(temp->getName());
				if (!writtenLocalTemplates[temp] && !getTemplate(temp->getName())) {
					dout(4) << "Local template '" << temp->getName() << "' added to save file\n";
					// Local template - add it...
					TiXmlElement *tempElement;
					if (std::string(temp->libraryName()) == "moon")
						tempElement = new TiXmlElement(temp->className());
					else
						tempElement = new TiXmlElement(std::string(temp->libraryName()) + "_" + temp->className());
					tempElement->SetAttribute("name", temp->getName());
					temp->writeXML(tempElement);
					templatesElement->LinkEndChild(tempElement);
					writtenLocalTemplates[temp] = true;
				}
			} else if (std::string(object->libraryName()) == "moon")
				element = new TiXmlElement(object->className());
			else
				element = new TiXmlElement(std::string(object->libraryName()) + "_" + object->className());
			// Don't write out name of object if it matches class/template name (+ incremental instance number)
			if (object->getName().length() < element->ValueStr().length() || object->getName().substr(0,element->ValueStr().length()) != element->ValueStr())
				element->SetAttribute("name", object->getName());
			object->writeXML(element);
			root->LinkEndChild(element);
		}
		if (!templatesElement->FirstChildElement())
			root->RemoveChild(templatesElement);
	}
	
	/// @param objects Objects to save to file
	/// @param withTemplates If specified, templates will be written to the \c templates sub-element
	/// @param rootnode Root node for the XML document
	/// @return The XML document as a string
	std::string ObjectFactory::writeObjects(const ObjectList& objects, const bool withTemplates, const std::string& rootnode)
	{
		TiXmlDocument doc;
		TiXmlElement *root = new TiXmlElement(rootnode);
		doc.LinkEndChild(root);
		writeObjects(objects, root);
		std::stringstream ss;
		ss << doc;
		return ss.str();
	}
	
	/// @param objects Objects to save to file
	/// @param filename Name of file to save
	/// @param withTemplates If specified, templates will be written to the \c templates sub-element
	/// @param rootnode Root node for the XML document
	void ObjectFactory::saveObjects(const ObjectList& objects, const std::string& filename, const bool withTemplates, const std::string& rootnode)
	{
		fileStack.push(filename);
		rootStack.push(rootnode);
		XMLParser::currentFile = filename;
		TiXmlDocument doc;
		TiXmlElement *root = new TiXmlElement(rootnode);
		doc.LinkEndChild(root);
		writeObjects(objects, root, withTemplates);
		fileStack.pop();
		rootStack.pop();
		if (fileStack.size() > 0)
			XMLParser::currentFile = fileStack.top();
		else
			XMLParser::currentFile = "";
		if (!doc.SaveFile(filename))
			throw FactoryIOException(std::string("Failed to save '") + filename + "'");
	}
	
	const FactoryProduct* ObjectFactory::getTemplate(const std::string& name) const
	{
		TemplateMap::const_iterator it = templates.find(name);
		if (it == templates.end())
			return NULL;
		return it->second.get();
	}
	
	const FactoryProduct* ObjectFactory::getTemplate(const unsigned int index) const
	{
		if (index >= templates.size())
			return NULL;
		TemplateMap::const_iterator it = templates.begin();
		for (unsigned int i = 0; i < index; i++)
			it++;
		return it->second.get();
	}
	
	unsigned int ObjectFactory::getNumTemplates() const { return templates.size(); }
	
	void ObjectFactory::addTemplate(FactoryProduct *object)
	{
		if (object->getName().length() == 0)
			throw FactoryIOException("Template needs a name");
		if (templates.find(object->getName()) != templates.end())
			throw FactoryIOException("Duplicate template name '" + object->getName() + "'");
		templates[object->getName()] = object;
	}
	
	void ObjectFactory::clearTemplates() { templates.clear(); }
	
	void ObjectFactory::removeTemplate(const std::string& name)
	{
		TemplateMap::iterator it = templates.find(name);
		if (it == templates.end())
			return;
		templates.erase(it);
	}
	
	void ObjectFactory::removeTemplate(const FactoryProduct *templateObject)
	{
		for (TemplateMap::iterator it = templates.begin(); it != templates.end(); it++) {
			if (it->second == templateObject) {
				templates.erase(it);
				break;
			}
		}
	}
	
	unsigned int ObjectFactory::getTemplateUsage(const FactoryProduct *templateObject)
	{
		TemplateCountMap::iterator it = templatecount.find(templateObject);
		if (it == templatecount.end())
			return 0;
		return it->second;
	}
	
	FactoryProduct* ObjectFactory::createInstance(const FactoryProduct *templateObject, const osg::CopyOp& copyop)
	{
		if (!templateObject)
			return NULL;
		while (templateObject->templateObject.valid())
			templateObject = templateObject->templateObject.get();
		FactoryProduct *object = (FactoryProduct*) templateObject->clone(copyop);
		object->templateObject = templateObject; // we're a friend class to private FactoryProduct...
		templatecount[templateObject]++;
		std::stringstream namess;
		namess << templateObject->getName() << "_" << templatecount[templateObject];
		object->setName(namess.str());
		return object;
	}

	FactoryProduct* ObjectFactory::createInstance(const std::string& templateName, const osg::CopyOp& copyop)
	{
		const FactoryProduct *templateObject = getTemplate(templateName);
		if (!templateObject)
			return NULL;
		return createInstance(templateObject, copyop);
	}
	
	moonet::NetworkObject* ObjectFactory::createNetworkObject(const std::string& type)
	{
		FactoryProduct *object = NULL;
		if (getTemplate(type)) {
			object = createInstance(type);
			if (!object) {
				dout(ERROR, NETWORK) << "Failed to create network object with template '" << type << "'\n";
				return NULL;
			}
			dout(4) << "Created instance of " << type <<  " '" << object->getName() << "'\n";
		} else {
			object = create(type);
			// Assume namespace moon if object type was not found
			if (!object)
				object = create(std::string("moon_") + type);
			if (!object) {
				dout(ERROR, NETWORK) << "Failed to create network object of type '" << type << "'\n";
				return NULL;
			}
			createcount[type]++;
		}
		moonet::NetworkObject *netobject = dynamic_cast<moonet::NetworkObject*> (object);
		if (!netobject)
			dout(ERROR, NETWORK) << "Object '" << type << "' is not a network object, although one was created over the network\n";
		return netobject;
	}
	
	std::string ObjectFactory::getCurrentFileName()
	{
		if (fileStack.size() > 0)
			return fileStack.top();
		return "";
	}
	
	ObjectFactory& ObjectFactory::instance()
	{
		if (!instanceptr) {
			instanceptr = new ObjectFactory;
		}
		return *instanceptr;
	}
	
	ObjectFactory* ObjectFactory::instanceptr = NULL;
	
} // namespace
