#ifndef MOON_COMPONENT_H
#define MOON_COMPONENT_H

#include "moon/FactoryProduct.h"
#include "moon/Export.h"
#include <vector>
#include <map>

namespace moon {

	/// \addtogroup core
	/// @{
	
	class ComponentContainer;
	
	/// \brief A simulation component
	/// \ingroup components
	class MOON_EXPORT Component : public FactoryProduct {
	public:
		Component();
		Component(const Component& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Component);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Called after copying / parsing
		virtual void initialize();
		inline bool isInitialized() { return initialized; }
		/// Called when scenario is activated - for creating geometry etc
		virtual void realize();
		/// Called when scenario is deactivated - for removing/disabling geometry
		virtual void unrealize();
		/// Returns wether this component is realized
		inline bool isRealized() { return realized; }
		/// Update simulation of this component
		virtual void update(const double dt) {}
		/// Reset simulation state of this component
		virtual void reset();
		/// Set the reset point (record current state which will be returned to by calling reset())
		virtual void setResetState();
		
		/// Callback for an inter-component message
		virtual void icMessage(const unsigned int id, void* data = NULL) {}
		
		/// Set a string tag which can be used to specify what the component is to be used for
		void setTag(const std::string& tag, const bool value = true);
		/// Returns wether the component has a tag set
		bool hasTag(const std::string& tag) const;
		
		/// Get the container that "owns" this component
		inline ComponentContainer* getContainer() { return container; }
		
		enum TraversalMode { WITH_CONTAINER, SPECIFIC };
		void setRealizeMode(const TraversalMode& mode) { realizeMode = mode; }
		TraversalMode getRealizeMode() const { return realizeMode; }
		void setUpdateMode(const TraversalMode& mode) { updateMode = mode; }
		TraversalMode getUpdateMode() const { return updateMode; }
		
	private:
		bool initialized, realized;
		typedef std::map< std::string, bool > TagMap;
		TagMap tags;
		ComponentContainer *container;
		friend class ComponentContainer;
		TraversalMode realizeMode, updateMode;
		int resetRealized;
	};
	
	/// Interface class for an object that holds (and handles) components
	class MOON_EXPORT ComponentContainer : public Component {
	public:				
		ComponentContainer();
		ComponentContainer(const ComponentContainer& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		~ComponentContainer();
		META_Object(moon, ComponentContainer);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		virtual void reset();
		virtual void setResetState();
		/// Add a component - this is typically extended by objects that recognize certain components
		virtual void addComponent(Component *component);
		virtual void removeComponent(Component *component);
		virtual bool containsComponent(Component *component) const;
		virtual void icMessage(const unsigned int id, void *data = NULL);
		
		unsigned int getNumComponents() const { return components.size(); }
		Component* getComponent(const unsigned int index) const { return components[index].get(); }
		Component* getComponentByTag(const std::string& tag) const;
		
	private:		
		typedef std::vector< osg::ref_ptr<Component> > ComponentList;
		ComponentList components;
		ComponentList pendingComponents;
	};
	
	/// Inter-component message IDs used internally in the engine
	/// \see Component::icMessage()
	enum InternalICID { 
		IC_MSG_UPDATE_TRANSFORMATION,
		IC_MSG_DEBUG_DISPLAY_ON,
		IC_MSG_DEBUG_DISPLAY_OFF,
		IC_MSG_USER
	};
	
	/// @}
}

#endif
