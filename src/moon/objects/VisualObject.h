#ifndef MOON_VISUALOBJECT_H
#define MOON_VISUALOBJECT_H

#include "BaseObject.h"
#include "moon/components/VisualModel.h"
#include <osg/Switch>
#include <osgText/Text>
#include <osg/Geode>

namespace moon {
	
	/// \ingroup core objects
	/// @{
	
	/// Object capable of displaying visual models
	class MOON_EXPORT VisualObject : public BaseObject {
	public:
		VisualObject();
		VisualObject(const VisualObject& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, VisualObject);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void addComponent(Component* component);

                virtual void realize();
		
		unsigned int getNumModels() const;
		VisualModel* getModel(const unsigned int index);
		/// Show the specified model index, hide all others
		void showModel(const unsigned int index);
		/// Set visibility of a model index
		void setModelVisibility(const unsigned int index, const bool value);
		/// Show model(s) matching name, hide all others
		void showModel(const std::string& name);
		/// Set visibility of model(s) matching name
		void setModelVisibility(const std::string& name, const bool value);
		/// Show models matching tag, hide all others
		void showModelsWithTag(const std::string& tag);
		/// Set visibility of models matching tag
		void setModelVisibilityWithTag(const std::string& tag, const bool value);
		/// Show models matching tag, hide all others
		void showModelsWithoutTag(const std::string& tag);
		/// Set visibility of models matching tag
		void setModelVisibilityWithoutTag(const std::string& tag, const bool value);
		/// Show all models
		virtual void showAllModels();
		/// Hide all models
		virtual void hideAllModels();
		
		virtual void showLabel();
		virtual void hideLabel();
		virtual void setLabel(const std::string& text);
		static osg::observer_ptr<osgText::Text> labelTextTemplate;
		
		virtual void reset();
		virtual void setResetState();
		
	protected:
		osg::Switch* getModelSwitch();
		virtual void switchModel(VisualModel* model, const bool value);
		virtual void createLabel();
		
	private:
		void checkVisibility();
		
		typedef std::vector< osg::observer_ptr<VisualModel> > ModelList;
		ModelList models;
		
		osg::ref_ptr<osg::Switch> modelswitch;
		osg::Switch::ValueList resetModelList;
		osg::ref_ptr<osg::Geode> labelGeode;
		osg::observer_ptr<osgText::Text> labelText;
		bool labelShowsName;
                float radius;
                osg::observer_ptr<osg::Node> fallbackNode;
	};
	
	/// @}
	
}

#endif
