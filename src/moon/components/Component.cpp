#include "Component.h"
#include "mlog/Log.h"
#include "moon/XMLParser.h"
#include "moon/ObjectFactory.h"
#include <osg/observer_ptr>

using namespace mlog;

namespace moon {

	Component::Component()
	:	FactoryProduct(),
		initialized(false),
		realized(false),
		container(NULL),
		realizeMode(WITH_CONTAINER),
		updateMode(WITH_CONTAINER),
		resetRealized(0)
	{
	}

	Component::Component(const Component& source, const osg::CopyOp& copyop)
	:	FactoryProduct(source, copyop),
		initialized(false),
		realized(false),
		tags(source.tags),
		container(NULL),
		realizeMode(source.realizeMode),
		updateMode(source.updateMode),
		resetRealized(0)
	{
	}

	void Component::parseXML(const TiXmlElement *element)
	{
		//=== Component
		std::string name;
		if (XMLParser::parseStringAttribute(name, element, "name"))
			setName(name);
		//=* attribute: tag="(string list)"
		//=. Tag this object for specific function(s) (usually used for children of complex objects to define behavior)
		std::vector<std::string> taglist = XMLParser::parseStringListAttribute(element, "tag");
		if (taglist.size() > 0) {
			dout(4) << "    tags:";
			for (unsigned int i = 0; i < taglist.size(); i++) {
				setTag(taglist[i]);
				dout(4) << " " << taglist[i];
			}
			dout(4) << "\n";
		}
	}

	void Component::initialize() { initialized = true; }

	void Component::realize()
	{
		if (!initialized)
			initialize();
		realized = true;
	}

	void Component::unrealize() { realized = false; }

	void Component::writeXML(TiXmlElement *element) const
	{
		std::ostringstream oss;
		for (TagMap::const_iterator it = tags.begin(); it != tags.end(); it++) {
			oss << it->first << " ";
		}
		if (oss.str().length() > 0)
			element->SetAttribute("tag", oss.str());
	}

	void Component::reset()
	{
		if (resetRealized == 1 && !isRealized())
			realize();
		else if (resetRealized == -1 && isRealized())
			unrealize();
	}

	void Component::setResetState()
	{
		if (isRealized())
			resetRealized = 1;
		else
			resetRealized = -1;
	}

	void Component::setTag(const std::string& tag, const bool value) { tags[tag] = value; }

	bool Component::hasTag(const std::string& tag) const
	{
		TagMap::const_iterator it = tags.find(tag);
		if (it != tags.end())
			return true;
		return false;
	}

	ComponentContainer::ComponentContainer()
	:	Component()
	{
	}

	ComponentContainer::~ComponentContainer()
	{
		for (unsigned int i = 0; i < components.size(); i++)
			components[i]->container = NULL;
	}

	ComponentContainer::ComponentContainer(const ComponentContainer& source, const osg::CopyOp& copyop)
	:	Component(source, copyop)
	{
		// Copy components into a pending list, so that they can be initialized later
		for (unsigned int i = 0; i < source.components.size(); i++) {
			pendingComponents.push_back((Component*) source.components[i]->clone(copyop));
		}
		for (unsigned int i = 0; i < source.pendingComponents.size(); i++) {
			pendingComponents.push_back((Component*) source.pendingComponents[i]->clone(copyop));
		}
	}

	void ComponentContainer::parseXML(const TiXmlElement *element)
	{
		Component::parseXML(element);
		ObjectFactory::ObjectList objects = ObjectFactory::instance().parseObjects(element, false);
		for (ObjectFactory::ObjectList::iterator it = objects.begin(); it != objects.end(); it++) {
			if (Component *component = dynamic_cast<moon::Component*> (it->get()))
				pendingComponents.push_back(component);
			/*
			else
				dout(WARN) << "Don't know how to handle object '" << (*it)->getName() << "'"
				<< " (" << (*it)->libraryName() << "::" << (*it)->className() << ")\n";
			*/
		}
	}

	void ComponentContainer::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		ObjectFactory::ObjectList objects;
		for (unsigned int i = 0; i < components.size(); i++)
			objects.push_back(components[i].get());
		for (unsigned int i = 0; i < pendingComponents.size(); i++)
			objects.push_back(pendingComponents[i].get());
		ObjectFactory::instance().writeObjects(objects, element, false);
	}

	void ComponentContainer::initialize()
	{
		while (pendingComponents.size() > 0) {
			osg::observer_ptr<Component> component = pendingComponents[0].get();
			dout(3) << "Adding component " << component->getName() << " to " << getName() << " refcount " << component->referenceCount() << "\n";
			addComponent(component.get());
			pendingComponents.erase(pendingComponents.begin());
		}
		for (unsigned int i = 0; i < components.size(); i++) {
			components[i]->initialize();
			dout(3) << "After initialize() " << components[i]->getName() << " has refcount " << components[i]->referenceCount()
			<< " and " << getName() << " has refcount " << referenceCount() << "\n";
		}
		Component::initialize();
	}

	void ComponentContainer::realize()
	{
		Component::realize();
		std::cout << "realize components " << getName() << " " << components.size() << "\n";
		for (unsigned int i = 0; i < components.size(); i++) {
			if (components[i]->getRealizeMode() == Component::WITH_CONTAINER)
				components[i]->realize();
		}
	}

	void ComponentContainer::unrealize()
	{
		for (unsigned int i = 0; i < components.size(); i++)
			if (components[i]->getRealizeMode() == Component::WITH_CONTAINER)
				components[i]->unrealize();
		Component::unrealize();
	}

	void ComponentContainer::update(const double dt)
	{
		for (unsigned int i = 0; i < components.size(); i++)
			if (components[i]->getUpdateMode() == Component::WITH_CONTAINER)
				components[i]->update(dt);
		Component::update(dt);
	}

	void ComponentContainer::reset()
	{
		Component::reset();
		for (unsigned int i = 0; i < components.size(); i++)
			components[i]->reset();
	}

	void ComponentContainer::setResetState()
	{
		Component::setResetState();
		std::cout << "setResetState components " << getName() << " " << components.size() << "\n";
		for (unsigned int i = 0; i < components.size(); i++)
			components[i]->setResetState();
	}

	bool ComponentContainer::containsComponent(Component *component) const
	{
		if (!component) return false;
		for (unsigned int i = 0; i < components.size(); i++) {
			if (components[i] == component)
				return true;
		}
		for (unsigned int i = 0; i < pendingComponents.size(); i++) {
			if (pendingComponents[i] == component)
				return true;
		}
		return false;
	}

	void ComponentContainer::icMessage(const unsigned int id, void *data)
	{
		Component::icMessage(id, data);
		for (unsigned int i = 0; i < components.size(); i++)
			components[i]->icMessage(id, data);
	}

	void ComponentContainer::addComponent(Component *component)
	{
		components.push_back(component);
		component->container = this;
		if (isInitialized())
			component->initialize();
		if (isRealized() && component->getRealizeMode() == Component::WITH_CONTAINER)
			component->realize();
	}

	void ComponentContainer::removeComponent(Component *component)
	{
		for (ComponentList::iterator it = components.begin(); it != components.end(); it++) {
			if (it->get() == component) {
				//dout(3) << "Removing component " << (*it)->getName() << " from " << getName() << " refcount " << (*it)->referenceCount() << "\n";
				components.erase(it);
				break;
			}
		}
	}

	Component* ComponentContainer::getComponentByTag(const std::string& tag) const
	{
		//ComponentContainer::initialize(); // ensure no pending components
		for (ComponentList::const_iterator it = components.begin(); it != components.end(); it++) {
			if ((*it)->hasTag(tag))
				return it->get();
		}
		return NULL;
	}

} // namespace
