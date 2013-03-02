#include "Instrument.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include "moon/objects/BaseObject.h"
#include <mdraw/Bar.h>
#include <mdraw/TextValuator.h>
#include <mdraw/TransformValuator.h>
#include <osgDB/ReadFile>

using namespace mlog;

namespace moon {
	
	REGISTER_Object_Alias(moon, Instrument, Instrument);

	Instrument::Instrument()
	: VisualModel(), ModifierContainer()
	{
		group = new osg::Group;
	}
	
	Instrument::Instrument(const Instrument& source, const osg::CopyOp& copyop)
	: VisualModel(source, copyop), ModifierContainer(source, copyop)
	{
		group = new osg::Group(*source.group.get(), osg::CopyOp::DEEP_COPY_ALL);
		for (unsigned int i = 0; i < group->getNumChildren(); i++) {
			if (group->getChild(i)->getName() == "labels")
				labelGeode = group->getChild(i)->asGeode();
		}
		if (transform.valid()) {
			transform->removeChildren(0, transform->getNumChildren());
			transform->addChild(group.get());
		}
		model = group;
	}
	
	void Instrument::parseXML(const TiXmlElement *element)
	{
		//=== Instrument
		//=See superclass VisualModel
		VisualModel::parseXML(element);
		// Parse common instrument elements...
		// ... labels
		//=* repeatable element: label (see separate section below)
		//=. Static text label
		for (const TiXmlElement *textElement = element->FirstChildElement("label"); textElement; textElement = textElement->NextSiblingElement("label")) {
			osgText::Text *text = parseText(textElement);
			if (text) {
				if (!labelGeode) {
					labelGeode = new osg::Geode;
					labelGeode->setName("labels");
					group->addChild(labelGeode.get());
				}
				labelGeode->addDrawable(text);
			}
		}
		//=* repeatable element: text (see separate section below)
		//=. Text valuator
		// ... text valuators
		mdraw::TextValuator *textVal = NULL;
		for (const TiXmlElement *textElement = element->FirstChildElement("text"); textElement; textElement = textElement->NextSiblingElement("text")) {
			osgText::Text *text = parseText(textElement);
			if (text) {
				if (!textVal) {
					textVal = new mdraw::TextValuator;
					textVal->setName("texts");
					group->addChild(textVal);
				}
				textVal->addText(text);
			}
		}
		
		for (const TiXmlElement *transformElement = element->FirstChildElement("transform"); transformElement; transformElement = transformElement->NextSiblingElement("transform")) {
			osg::Node *node = osgDB::readNodeFile(XMLParser::parseStringAttribute(transformElement, "model"));
			if (node) {
				mdraw::TransformValuator *transformVal = new mdraw::TransformValuator;
				transformVal->setName(XMLParser::parseStringAttribute(transformElement, "name"));
				transformVal->addChild(node);
				group->addChild(transformVal);
			}
		}
		// Parse modifiers
		//=* modifier targets: (valuator), (element names)
		ModifierContainer::parseXML(element);
		// Setup nodes
		if (model.valid() && model != group && !group->containsNode(model.get())) {
			group->addChild(model.get());
			if (transform.valid()) {
				transform->removeChildren(0, transform->getNumChildren());
				transform->addChild(group.get());
			}
			model = group;
		}
	}
	
	void Instrument::writeXML(TiXmlElement *element) const
	{
		VisualModel::writeXML(element);
		ModifierContainer::writeXML(element);
	}
	
	void Instrument::initialize()
	{
		VisualModel::initialize();
		group->setName(getName() + " instrument group");
		// Setup valuator
		for (unsigned int i = 0; i < group->getNumChildren(); i++) {
			if (mdraw::Valuator *val = dynamic_cast<mdraw::Valuator*> (group->getChild(i)))
				valuators.push_back(val);
		}
		// Setup modifiers
		if (getNumModifiers() > 0) {
			BaseObject* object = dynamic_cast<BaseObject*> (getContainer());
			if (!object) {
				dout(ERROR) << "Container for instrument '" << getName() << "' is not a BaseObject\n";
				return;
			}
			for (unsigned int i = 0; i < getNumModifiers(); i++) {
				Modifier *mod = getModifier(i);
				if (Parameter *param = object->findParameter(mod->getName())) {
					mod->setParameter(param);
					dout(5) << "Instrument modifer " << object->getName() << ":" << mod->getName() << " connected\n";
				}
				std::string target1, target2 = mod->getTargetName();
				std::size_t sepindex = target2.find_first_of(" :.,");
				if (sepindex != std::string::npos) {
					target1 = target2.substr(0, sepindex);
					target2 = target2.substr(sepindex+1);
				}
				for (unsigned int i = 0; i < valuators.size(); i++) {
					osg::Node *node = valuators[i]->asNode();
					if (!node)
						continue;
					if (target1.length() > 0 && target1 != node->getName())
						continue;
					// Find value index from valuator name..
					int index = valuators[i]->getIndex(target2);
					// ...or drawable name
					if (index < 0 && target2.length() > 0 && node->asGeode()) {
						for (unsigned int j = 0; j < node->asGeode()->getNumDrawables(); j++) {
							if (target2 == node->asGeode()->getDrawable(j)->getName()) {
								index = j;
							}
						}
					}
					if (index >= 0) {
						mod->setTargetIndex((i << 16) | (index & 0xFF));
						dout(5) << "Modifier target " << target1 << " " << target2 << " valuator " << i << " index " << index << "\n";
					}
				}
			}
		}
	}
	
	void Instrument::update(const double dt)
	{
		VisualModel::update(dt);
		if (valuators.size() == 0)
			return;
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			const Modifier *mod = getModifier(i);
			unsigned int valindex = (mod->getTargetIndex() & (~0xFF)) >> 16;
			unsigned int index = (mod->getTargetIndex() & 0xFF);
			if (valindex < valuators.size())
				valuators[valindex]->setValue(mod->get(), index);
		}
	}
	
	osgText::Text* Instrument::getLabel(const std::string& name)
	{
		if (!labelGeode)
			return NULL;
		for (unsigned int i = 0; i < labelGeode->getNumDrawables(); i++) {
			osg::Drawable *draw = labelGeode->getDrawable(i);
			if (draw->getName() == name)
				return dynamic_cast<osgText::Text*> (draw);
		}
		return NULL;
	}
	
	osgText::Text* Instrument::parseText(const TiXmlElement *textElement)
	{
		std::string str;
		if (textElement->GetText())
			str = textElement->GetText();
		//==== Text
		//=* attribute: text="(string)"
		//=. Text to be displayed. Can also be specified with text within the XML element.
		XMLParser::parseStringAttribute(str, textElement, "text");
		if (str.length() == 0)
			return NULL;
		osgText::Text *text = new osgText::Text; 
		text->setText(str);
		//=* attribute: name="(string)"
		if (XMLParser::parseStringAttribute(str, textElement, "name"))
			text->setName(str);
		//=* attribute: size="(number)" aspect="(number)"
		double size = XMLParser::parseDoubleAttribute(textElement, "size", true, 0.05);
		double aspect = XMLParser::parseDoubleAttribute(textElement, "aspect", true, 1.5);
		text->setCharacterSize(size, aspect);
		//=* attribute: font="(filename)"
		text->setFont(XMLParser::parseStringAttribute(textElement, "font", true, "fonts/arial.ttf"));
		//=* attribute: pos="(vector3)"
		text->setPosition(XMLParser::parseVector3Attribute(textElement, "pos", true, osg::Vec3(0,0,0)));
		//=* attribute: layout="left|right|vertical"
		if (XMLParser::parseStringAttribute(str, textElement, "layout")) {
			if (str == "left")
				text->setLayout(osgText::Text::LEFT_TO_RIGHT);
			else if (str == "right")
				text->setLayout(osgText::Text::RIGHT_TO_LEFT);
			else if (str == "vertical")
				text->setLayout(osgText::Text::VERTICAL);
			else
				throw ParseException("Invalid layout", textElement);
		}
		//=* attribute: align="a number of different options"
		if (XMLParser::parseStringAttribute(str, textElement, "align")) {
			if (str == "left_center|right_bottom|...")
				text->setAlignment(osgText::Text::LEFT_TOP);
			else if (str == "left_center")
				text->setAlignment(osgText::Text::LEFT_CENTER);
			else if (str == "left_center")
				text->setAlignment(osgText::Text::LEFT_CENTER);
			else if (str == "center_top")
				text->setAlignment(osgText::Text::CENTER_TOP);
			else if (str == "center_center")
				text->setAlignment(osgText::Text::CENTER_CENTER);
			else if (str == "center_bottom")
				text->setAlignment(osgText::Text::CENTER_BOTTOM);
			else if (str == "right_top")
				text->setAlignment(osgText::Text::RIGHT_TOP);
			else if (str == "right_center")
				text->setAlignment(osgText::Text::RIGHT_CENTER);
			else if (str == "right_bottom")
				text->setAlignment(osgText::Text::RIGHT_BOTTOM);
			else if (str == "left_base_line")
				text->setAlignment(osgText::Text::LEFT_BASE_LINE);
			else if (str == "center_base_line")
				text->setAlignment(osgText::Text::CENTER_BASE_LINE);
			else if (str == "right_base_line")
				text->setAlignment(osgText::Text::RIGHT_BASE_LINE);
			else if (str == "left_bottom_base_line")
				text->setAlignment(osgText::Text::LEFT_BOTTOM_BASE_LINE);
			else if (str == "center_bottom_base_line")
				text->setAlignment(osgText::Text::CENTER_BOTTOM_BASE_LINE);
			else if (str == "right_bottom_base_line")
				text->setAlignment(osgText::Text::RIGHT_BOTTOM_BASE_LINE);
			else if (str == "base_line")
				text->setAlignment(osgText::Text::BASE_LINE);
			else
				throw ParseException("Invalid alignment", textElement);
		}
		//=* attribute: color="(vector4)"
		osg::Vec4 v4;
		if (XMLParser::parseVector4Attribute(v4, textElement, "color"))
			text->setColor(v4);
		//=* attribute: backdrop="outline|shadow..."
		if (XMLParser::parseStringAttribute(str, textElement, "backdrop")) {
			if (str == "shadow_bottom_right")
				text->setBackdropType(osgText::Text::DROP_SHADOW_BOTTOM_RIGHT);
			else if (str == "shadow_center_right")
				text->setBackdropType(osgText::Text::DROP_SHADOW_CENTER_RIGHT);
			else if (str == "shadow_top_right")
				text->setBackdropType(osgText::Text::DROP_SHADOW_TOP_RIGHT);
			else if (str == "shadow_bottom_center")
				text->setBackdropType(osgText::Text::DROP_SHADOW_BOTTOM_CENTER);
			else if (str == "shadow_top_center")
				text->setBackdropType(osgText::Text::DROP_SHADOW_TOP_CENTER);
			else if (str == "shadow_bottom_left")
				text->setBackdropType(osgText::Text::DROP_SHADOW_BOTTOM_LEFT);
			else if (str == "shadow_center_left")
				text->setBackdropType(osgText::Text::DROP_SHADOW_CENTER_LEFT);
			else if (str == "shadow_top_left")
				text->setBackdropType(osgText::Text::DROP_SHADOW_TOP_LEFT);
			else if (str == "outline")
				text->setBackdropType(osgText::Text::OUTLINE);
			else
				throw ParseException("Invalid backdrop", textElement);
		}
		//=* attribute: backdropcolor="(vector4)"
		if (XMLParser::parseVector4Attribute(v4, textElement, "backdropcolor"))
			text->setBackdropColor(v4);
		double value;
		//=* attribute: backdropoffset="(number)"
		if (XMLParser::parseDoubleAttribute(value, textElement, "backdropoffset"))
			text->setBackdropOffset(value);
		int i;
		//=* attribute: resolution="(integer)"
		if (XMLParser::parseIntAttribute(i, textElement, "resolution"))
			text->setFontResolution(i,i);
		return text;
	}
	
	REGISTER_Object(moon, BarGraph);
	
	void BarGraph::parseXML(const TiXmlElement *element)
	{
		//=== BarGraph
		//=See superclass Instrument
		//=* repeatable element: bar (see separate section below)
		//=. If only one bar is wanted, it can be specified directly in the 'BarGraph' element.
		bool barsparsed = false;
		for (const TiXmlElement *barElement = element->FirstChildElement("bar"); barElement; barElement = barElement->NextSiblingElement("bar")) {
			mdraw::Bar *bar = parseBar(barElement);
			group->addChild(bar);
			barsparsed = true;
		}
		if (!barsparsed && !getTemplate()) {
			mdraw::Bar *bar = parseBar(element);
			bar->setCenter(osg::Vec3(0,0,0)); // set by instrument position instead
			group->addChild(bar);
		}

		Instrument::parseXML(element);
	}
	
	void BarGraph::writeXML(TiXmlElement *element) const
	{
		Instrument::writeXML(element);
	}
	
	mdraw::Bar* BarGraph::parseBar(const TiXmlElement *element)
	{
		//==== Bar
		mdraw::Bar *bar = new mdraw::Bar;
		std::string str;
		//=* attribute: name="(string)"
		if (XMLParser::parseStringAttribute(str, element, "name"))
			bar->setName(str);
		double value;
		//=* attribute: min="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "min"))
			bar->setMin(value);
		//=* attribute: max="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "max"))
			bar->setMax(value);
		//=* attribute: length="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "length"))
			bar->setSize(value, bar->getWidth());
		//=* attribute: width="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "width"))
			bar->setSize(bar->getLength(), value);
		//=* attribute: spacing="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "spacing"))
			bar->setSpacing(value);
		//=* attribute: vertical="true|false"
		if (XMLParser::parseBooleanAttribute(element, "vertical", true, false))
			bar->setOrientation(mdraw::Bar::VERTICAL);
		//=* attribute: pos="(vector3)"
		osg::Vec3 v3;
		if (XMLParser::parseVector3Attribute(v3, element, "pos"))
			bar->setCenter(v3);
		//=* attribute: color="(vector4)"
		osg::Vec4 v4;
		if (XMLParser::parseVector4Attribute(v4, element, "color"))
			bar->setBarColor(v4);
		//=* attribute: bordercolor="(vector4)"
		if (XMLParser::parseVector4Attribute(v4, element, "bordercolor"))
			bar->setBorderColor(v4);
		//=* attribute: markcolor="(vector4)"
		if (XMLParser::parseVector4Attribute(v4, element, "markcolor"))
			bar->setMarkColor(v4);
		//=* attribute: markwidth="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "markwidth"))
			bar->setMarkWidth(value);
		//=* attribute: markthick="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "markthick"))
			bar->setMarkThickness(value);
		return bar;
	}
	
}
