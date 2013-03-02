#include "VisualObject.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include <mdraw/utils.h>
#include <mlog/Log.h>
#include <osgText/FadeText>
#include <osg/ShapeDrawable>
#include <osg/Billboard>

namespace moon {
	
	REGISTER_Object_Alias(moon, VisualObject, Visual);
	
	VisualObject::VisualObject()
	:	BaseObject(),
                labelShowsName(true),
                radius(1.f)
	{
	}
	
	VisualObject::VisualObject(const VisualObject& source, const osg::CopyOp& copyop)
	:	BaseObject(source, copyop),
                labelShowsName(source.labelShowsName),
                radius(source.radius)
	{
		if (source.labelText.valid()) {
			labelText = dynamic_cast<osgText::Text*> (source.labelText->clone(osg::CopyOp::SHALLOW_COPY));
                        osg::Billboard *bb = new osg::Billboard;
                        bb->setMode(osg::Billboard::POINT_ROT_EYE);
                        labelGeode = bb;
			labelGeode->addDrawable(labelText.get());
			getModelSwitch()->addChild(labelGeode.get());
			getModelSwitch()->setChildValue(labelGeode.get(), source.modelswitch->getChildValue(source.labelGeode.get()));
		}
	}
	
	void VisualObject::parseXML(const TiXmlElement *element)
	{
		//=== VisualObject
		//=* alias: Visual
		//=* component: VisualModel
		//=See superclass BaseObject for more parameters.
		BaseObject::parseXML(element);
                //=* attribute: radius=(number)
                //=. Radius of fallback model to use if model loading failed
                element->QueryValueAttribute("radius", &radius);
                //=* attribute: model="(filename)"
		//=. Quick way to add a visual model.
		std::string str;
		if (XMLParser::parseStringAttribute(str, element, "model")) {
			osg::Matrix M = osg::Matrix::identity();
			//=* attribute: yup="true|false"
			//=. Rotate model from x-left, y-up, z-back coordinate system.
			if (XMLParser::parseBooleanAttribute(element, "yup", true, false)) {
				M = osg::Matrix::rotate(M_PI/2.0,osg::Vec3(1,0,0))
				* osg::Matrix::rotate(M_PI,osg::Vec3(0,0,1));
			}
			osg::ref_ptr<VisualModel> model = new VisualModel(str, M);
			//=* attribute: extract="true|false"
			//=. If set, tagged nodes of visual model are replaced with other eyecandy
			if (XMLParser::parseBooleanAttribute(element, "extract", true, false))
				model->extractSpecialNodes();
			addComponent(model.get());
		}
		//=* attribute: label="name|hidden|(string)"
		if (XMLParser::parseStringAttribute(str, element, "label")) {
			if (str == "name") {
				labelShowsName = true;
				createLabel();
			} else if (str == "hidden")
				hideLabel();
			else
				setLabel(str);
		}

		if (labelText.valid() && labelShowsName)
			labelText->setText(getName());
	}
	
	void VisualObject::addComponent(Component *component)
	{
		if (VisualModel *model = dynamic_cast<VisualModel*> (component)) {
			if (model->getNode()) {
				getModelSwitch(); // make sure it's there...
				modelswitch->addChild(model->getNode());
				if (model->isInitiallyHidden())
					modelswitch->setChildValue(model->getNode(), false);
				else
					checkVisibility();
			}
			models.push_back(model);
		}
		BaseObject::addComponent(component);	
	}

        void VisualObject::realize()
        {
            BaseObject::realize();
            checkVisibility();
            if (models.size() == 0)
                mlog::dout(mlog::WARN) << "No model for visible object '" << getName() << "'\n";
        }
	
	unsigned int VisualObject::getNumModels() const { return models.size(); }
	
	VisualModel* VisualObject::getModel(const unsigned int index)
	{
		if (index < models.size())
			return models[index].get();
		return NULL;
	}
	
	void VisualObject::showModel(const unsigned int index)
	{
		if (modelswitch.valid()) {
			hideAllModels();
			switchModel(models[index].get(), true);
		}
		checkVisibility();
	}

	void VisualObject::setModelVisibility(const unsigned int index, const bool value)
	{
		switchModel(models[index].get(), true);
		checkVisibility();
	}
	
	void VisualObject::showModel(const std::string& name)
	{
		if (modelswitch.valid()) {
			hideAllModels();
			for (unsigned int i = 0; i < models.size(); i++) {
				if (models[i]->getName() == name)
					switchModel(models[i].get(), true);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::setModelVisibility(const std::string& name, const bool value)
	{
		if (modelswitch.valid()) {
			for (unsigned int i = 0; i < models.size(); i++) {
				if (models[i]->getName() == name)
					switchModel(models[i].get(), value);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::showModelsWithTag(const std::string& tag)
	{
		if (modelswitch.valid()) {
			hideAllModels();
			for (unsigned int i = 0; i < models.size(); i++) {
				if (models[i]->hasTag(tag))
					switchModel(models[i].get(), true);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::setModelVisibilityWithTag(const std::string& tag, const bool value)
	{
		if (modelswitch.valid()) {
			for (unsigned int i = 0; i < models.size(); i++) {
				if (models[i]->hasTag(tag))
					switchModel(models[i].get(), value);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::showModelsWithoutTag(const std::string& tag)
	{
		if (modelswitch.valid()) {
			hideAllModels();
			for (unsigned int i = 0; i < models.size(); i++) {
				if (!models[i]->hasTag(tag))
					switchModel(models[i].get(), true);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::setModelVisibilityWithoutTag(const std::string& tag, const bool value)
	{
		if (modelswitch.valid()) {
			for (unsigned int i = 0; i < models.size(); i++) {
				if (!models[i]->hasTag(tag))
					switchModel(models[i].get(), value);
			}
		}
		checkVisibility();
	}
	
	void VisualObject::showAllModels()
	{
		modelswitch->setAllChildrenOn();
		checkVisibility();
	}
	
	void VisualObject::hideAllModels()
	{
		modelswitch->setAllChildrenOff();
	}
	
	void VisualObject::showLabel()
	{
		createLabel();
		modelswitch->setChildValue(labelGeode.get(), true);
	}
	
	void VisualObject::hideLabel()
	{
		modelswitch->setChildValue(labelGeode.get(), false);
	}
	
	void VisualObject::setLabel(const std::string& text)
	{
		createLabel();
		labelText->setText(text);
		labelShowsName = false;
	}
	
	osg::observer_ptr<osgText::Text> VisualObject::labelTextTemplate = NULL;
	
	osg::Switch* VisualObject::getModelSwitch()
	{
		if (!modelswitch.valid()) {
			modelswitch = new osg::Switch;
			modelswitch->setName(getName() + " modelswitch");
			addNode(modelswitch.get());
		}
		return modelswitch.get();
	}
	
	void VisualObject::switchModel(VisualModel *model, const bool value)
	{
		if (!modelswitch || !model)
			return;
		modelswitch->setChildValue(model->getNode(), value);
	}
	
	void VisualObject::createLabel()
	{
		if (!labelText && labelTextTemplate.valid())
			labelText = dynamic_cast<osgText::Text*> (labelTextTemplate->clone(osg::CopyOp::SHALLOW_COPY));
		if (!labelText) {
			labelText = new osgText::FadeText;
			labelText->setCharacterSize(16);
			labelText->setFont("fonts/arial.ttf");
			labelText->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
                        labelText->setAutoRotateToScreen(true);
			labelText->setAlignment(osgText::TextBase::CENTER_BOTTOM);
                        osg::StateSet *stateset = labelText->getOrCreateStateSet();
                        stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
                        //stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
                }
		if (labelShowsName)
			labelText->setText(getName());
		if (!labelGeode) {
                        osg::Billboard *bb = new osg::Billboard;
                        bb->setMode(osg::Billboard::POINT_ROT_EYE);
                        labelGeode = bb;
                        labelGeode->addDrawable(labelText.get());
			getModelSwitch()->addChild(labelGeode.get());
		}
                if (isRealized())
                    checkVisibility();
	}
	
        void VisualObject::checkVisibility()
        {
            /*
                unsigned int numshown = 0;
                if (modelswitch.valid()) {
                        for (unsigned int i = 0; i < modelswitch->getNumChildren(); i++) {
                                if (modelswitch->getValue(i) && modelswitch->getChild(i) != labelGeode.get())
                                        numshown++;
                        }
                }
                */
            if (isRealized()) {
                if (models.size() == 0 && isNormallyVisible() && !getDebugNode()) {
                    if (!fallbackNode && radius > 1e-5) {
                        mlog::dout(0) << "ze sphere " << getName() << " " << radius << "\n";
                        osg::Sphere *sphere = new osg::Sphere(osg::Vec3(0,0,0), radius);
                        osg::ShapeDrawable *sd = new osg::ShapeDrawable(sphere);
                        sd->setColor(osg::Vec4(1,0.3,0.3,0.5));
                        osg::StateSet *stateset = sd->getOrCreateStateSet();
                        stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
                        stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
                        osg::Geode *geode = new osg::Geode;
                        geode->addDrawable(sd);
                        getModelSwitch()->addChild(geode);
                        fallbackNode = geode;
                    }
                } else if (fallbackNode.valid())
                    getModelSwitch()->removeChild(fallbackNode.get());
            }
            if (labelText.valid()) {
                osg::BoundingBox bbox = mdraw::getBoundingBox(modelswitch.get());
                if (!getModelSwitch()->containsNode(labelGeode.get()))
                    getModelSwitch()->addChild(labelGeode.get());
                labelText->setPosition(bbox.center()+osg::Vec3(0,0,bbox.zMax()-bbox.center().z())*1.05f);
            }
        }
	
	void VisualObject::reset()
	{
		if (modelswitch.valid() && resetModelList.size() > 0)
			modelswitch->setValueList(resetModelList);
		BaseObject::reset();
	}
	
	void VisualObject::setResetState()
	{
		if (modelswitch.valid())
			resetModelList = modelswitch->getValueList();
		BaseObject::setResetState();
	}
	
} // namespace
