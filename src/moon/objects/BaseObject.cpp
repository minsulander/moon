#include "BaseObject.h"
#include "KinematicObject.h"
#include "moon/ObjectFactory.h"
#include "mlog/Log.h"
#include "moon/XMLParser.h"
#include "moon/SimulationManager.h"
#include "moon/Scenario.h"
#include "moon/Interpreter.h"
#include "moon/components/Script.h"
#include "moon/NodeMask.h"
#include <moonet/SerializeMacros.h>
#include <moonet/NetworkManager.h>
#include <mdraw/utils.h>
#include <osgFX/Scribe>
#include <osg/io_utils>

using namespace mlog;

namespace moon {

	REGISTER_Object(moon, BaseObject);

	BaseObject::BaseObject()
	:	TransformObject(),
		PositionedNetworkObject(),
		ComponentContainer(),
		ParameterContainer(),
		resetHidden(false),
		serializeChildren(false),
		serializeAsChild(false),
		parent(NULL),
		dirtyInverseWorldMatrix(true),
		normallyVisible(true),
		hidden(false),
		displayMode(DISPLAY_NORMAL),
		wasRealizedInRange(false),
		wasHiddenInRange(false),
		realizeRange(0.f),
		realizeAzimuth(0.f),
		realizeElevation(0.f),
		realizeExemptRange(0.f),
		scriptUpdateInterval(0.0),
		scriptTimeStamp(0.0),
		removeTime(-1)
	{
		headingParam = new Parameter("att_heading", this);
		pitchParam = new Parameter("att_pitch", this);
		rollParam = new Parameter("att_roll", this);
		if (transform.valid()) {
			transform->setUserData(this);
			transform->setNodeMask(moon::NodeMask::DEFAULT);
			unref_nodelete();
		}
	}

	BaseObject::BaseObject(const BaseObject& object, const osg::CopyOp& copyop)
	:	TransformObject(object, copyop),
		PositionedNetworkObject(object),
		ComponentContainer(object, copyop),
		ParameterContainer(object, copyop),
		resetMatrix(object.resetMatrix),
		resetHidden(false),
		serializeChildren(object.serializeChildren),
		serializeAsChild(object.serializeAsChild),
		parent(NULL),
		dirtyInverseWorldMatrix(true),
		normallyVisible(object.normallyVisible),
		hidden(object.hidden),
		displayMode(DISPLAY_NORMAL),
		wasRealizedInRange(false),
		wasHiddenInRange(false),
		realizeRange(object.realizeRange),
		realizeAzimuth(object.realizeAzimuth),
		realizeElevation(object.realizeElevation),
		realizeExemptRange(object.realizeExemptRange),
		scriptUpdateInterval(object.scriptUpdateInterval),
		scriptTimeStamp(0.0),
		removeTime(object.removeTime),
		scriptParams(object.scriptParams)
	{
		// Note: MS VC++ compiler doesn't like using "this" in initializer list
		headingParam = new Parameter("att_heading", this);
		pitchParam = new Parameter("att_pitch", this);
		rollParam = new Parameter("att_roll", this);
		if (transform.valid()) {
			transform->setUserData(this);
			transform->setNodeMask(object.transform->getNodeMask());
			unref_nodelete();
		}
	}

	const std::string BaseObject::networkObjectName() const
	{
		if (getTemplate())
			return getTemplate()->getName();
		else {
			return std::string(libraryName()) + "_" + className();
		}
	}

	unsigned int BaseObject::getNumChildren() const { return children.size(); }

	void BaseObject::addChild(BaseObject *child)
	{
		if (!child)
			return;
		addComponent(child);
	}

	void BaseObject::removeChild(BaseObject *child)
	{
		removeChildren(getChildIndex(child), 1);
	}

	void BaseObject::removeChildren(const unsigned int index, const unsigned int num)
	{
		unsigned int range = index+num;
		if (range > children.size())
			range = children.size();
		for (ChildList::iterator it = children.begin()+index; it != children.begin()+range; it++) {
			BaseObject *child = it->get();
			transform->removeChild(child->getTransform());
			child->parent = NULL;
			removeComponent(child);
		}
		children.erase(children.begin()+index, children.begin()+range);
	}

	void BaseObject::separateChild(BaseObject *child)
	{
		osg::Matrix M = child->getWorldTransformMatrix();
		child->ref();
		removeChild(child);
		child->setTransformMatrix(M);
		if (Scenario::current())
			Scenario::current()->addComponent(child);
		child->unref();
	}

	BaseObject* BaseObject::getChild(const unsigned int index)
	{
		if (index >= children.size())
			return NULL;
		return children[index].get();
	}

	unsigned int BaseObject::getChildIndex(const BaseObject *child) const
	{
		unsigned int index = 0;
		for (ChildList::const_iterator it = children.begin(); it != children.end(); it++) {
			if (it->get() == child)
				return index;
			index++;
		}
		return children.size();
	}

	BaseObject* BaseObject::getParent() const { return parent; }

	BaseObject* BaseObject::getRoot()
	{
		BaseObject *object = this;
		while (object->parent)
			object = object->parent;
		return object;
	}

	BaseObject* BaseObject::findRelated(const std::string& name, const bool childrenOnly)
	{
		if (name == getName())
			return this;

		if (!childrenOnly && parent) {
			BaseObject *obj = parent;
			while (obj->parent)
				obj = obj->parent;
			return obj->findRelated(name, true);
		}

		for (ChildList::iterator it = children.begin(); it != children.end(); it++) {
			if (name == (*it)->getName())
				return it->get();
			BaseObject *obj = (*it)->findRelated(name, true);
			if (obj)
				return obj;
		}
		return NULL;
	}

	BaseObject* BaseObject::findRelatedByTemplate(const BaseObject *templateObject, const bool childrenOnly)
	{
		if (templateObject == getTemplate())
			return this;

		if (!childrenOnly && parent) {
			BaseObject *obj = parent;
			while (obj->parent)
				obj = obj->parent;
			return obj->findRelatedByTemplate(templateObject, true);
		}

		for (ChildList::iterator it = children.begin(); it != children.end(); it++) {
			if (templateObject == (*it)->getTemplate())
				return it->get();
			BaseObject *obj = (*it)->findRelatedByTemplate(templateObject, true);
			if (obj)
				return obj;
		}
		return NULL;
	}

	BaseObject* BaseObject::findRelatedByTag(const std::string& tag, const bool childrenOnly)
	{
		if (hasTag(tag))
			return this;

		if (!childrenOnly && parent) {
			BaseObject *obj = parent;
			while (obj->parent)
				obj = obj->parent;
			return obj->findRelatedByTag(tag, true);
		}

		for (ChildList::iterator it = children.begin(); it != children.end(); it++) {
			if ((*it)->hasTag(tag))
				return it->get();
			BaseObject *obj = (*it)->findRelatedByTag(tag, true);
			if (obj)
				return obj;
		}
		return NULL;
	}


	void BaseObject::parseXML(const TiXmlElement *element)
	{
		// Call load event function (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushNamed("event.loadObject")) {
			Interpreter::instance().pushUserType(this, "moon::BaseObject");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
		//=== BaseObject
		//=The base of all scenario objects.

		TransformObject::parseXML(element);
		ComponentContainer::parseXML(element);
		transform->setName(getName() + " transform");

                //=* attribute: shadow="receive|cast|both|none"
		std::string str;
		if (XMLParser::parseStringAttribute(str, element, "shadow")) {
			if (str == "receive")
				transform->setNodeMask((transform->getNodeMask() | NodeMask::RECEIVE_SHADOW) & ~NodeMask::CAST_SHADOW);
			else if (str == "cast")
				transform->setNodeMask((transform->getNodeMask() | NodeMask::CAST_SHADOW) & ~NodeMask::RECEIVE_SHADOW);
			else if (str == "both")
				transform->setNodeMask(transform->getNodeMask() | NodeMask::RECEIVE_SHADOW | NodeMask::CAST_SHADOW);
			else if (str == "none")
				transform->setNodeMask(transform->getNodeMask() & ~(NodeMask::RECEIVE_SHADOW | NodeMask::CAST_SHADOW));
			else
				throw ParseException("Invalid 'shadow' specification", element);
		}
		//=* attribute: intersect="true|false" (default true)
		if (!XMLParser::parseBooleanAttribute(element, "intersect", true, true)) {
			transform->setNodeMask(transform->getNodeMask() & ~NodeMask::INTERSECT);
		}
		//=* attribute: visible="true|false" (default true)
		if (!XMLParser::parseBooleanAttribute(element, "visible", true, true)) {
		    setNormallyVisible(false);
		}
		//=* element: remote inc="(number)" full="(number)" [second]
		//=. Network serialization interval (incremental - only dynamic data content sent, and full - all data sent).
		setSerializationInterval(XMLParser::parseDouble(element, "remote", "second", true, getSerializationInterval(), "inc"),
								 XMLParser::parseDouble(element, "remote", "second", true, getFullSerializationInterval(), "full"));
		//=** attribute: range="(number)" [meter]
		//=. Visible range (decides when to send it over the network), disabled by default
		double range;
		if (XMLParser::parseDouble(range, element, "remote", "meter", "range"))
			setVisibleRange(range);
		//=** attribute: children="true|false"
		//=. Sets wether to send child objects over the network
		XMLParser::parseBoolean(serializeChildren, element, "remote", "children");

		//=* element: realize range="(number)" [meter] azimuth="(number)" [degrees] elevation="(number)" [degrees] exempt="(number)" [meter]
		//=. Range from active camera within which the object will be realized
		if (XMLParser::parseDouble(range, element, "realize", "meter", "range"))
			realizeRange = range;
		if (XMLParser::parseDouble(range, element, "realize", "degrees", "azimuth"))
			realizeAzimuth = range*M_PI/180.0;
		if (XMLParser::parseDouble(range, element, "realize", "degrees", "elevation"))
			realizeElevation = range*M_PI/180.0;
		if (XMLParser::parseDouble(range, element, "realize", "meter", "exempt"))
			realizeExemptRange = range;

		//=* repeatable element: param name="(string)" value="(string)"
		//=. Paramaters to set as variables in object's Lua table
		for (const TiXmlElement *varElement = element->FirstChildElement("param"); varElement; varElement = varElement->NextSiblingElement("param")) {
			if (varElement->Attribute("name") && varElement->Attribute("value")) {
				scriptParams[varElement->Attribute("name")] = varElement->Attribute("value");
			} else
				throw ParseException("Missing 'name' or 'value' attribute", varElement);
		}

                        /* TODO add code for setting TransformObject::ellipsoidModel
                        if (baseobject->hasTag("coordinatesystem")) {
                            if (csNode.valid()) {
                                dout(WARN) << "Coordinate system node already defined - skipping the one found in object '" << baseobject->getName() << "'\n";
                            } else {
                                /// \todo find node using visitor instead
                                csNode = dynamic_cast<const osg::CoordinateSystemNode*> (baseobject->getNode());
                                if (!csNode && baseobject->getNode() && baseobject->getNode()->asGroup()) {
                                    const osg::Group *group = baseobject->getNode()->asGroup();
                                    if (group->getChild(0) && group->getChild(0)->getName().find("modelswitch") != std::string::npos)
                                        group = group->getChild(0)->asGroup();
                                    for (int i = 0; i < group->getNumChildren(); i++) {
                                        csNode = dynamic_cast<const osg::CoordinateSystemNode*> (group->getChild(i));
                                        if (csNode.valid())
                                            break;
                                    }
                                }
                                if (csNode.valid())
                                    dout(6) << "  coordinate system node\n";
                            }
                        }
*/

                updateTransformation();
		setResetState();
	}

	void BaseObject::writeXML(TiXmlElement *element) const
	{
		// Write components only if it's a template
		if (getTemplate())
			Component::writeXML(element);
		else
			ComponentContainer::writeXML(element);

		TransformObject::writeXML(element, dynamic_cast<const TransformObject*> (getTemplate()));
		BaseObject *templateObject = (BaseObject*) getTemplate();
		float f = getSerializationInterval();
		if ((!templateObject && f - moonet::NetworkManager::instance().getDefaultSerializationInterval() > 1e-5) || (templateObject && f != templateObject->getSerializationInterval()))
			XMLParser::setDouble(element, "remote", f, "inc");
		f = getFullSerializationInterval();
		if ((!templateObject && f - moonet::NetworkManager::instance().getDefaultFullSerializationInterval() > 1e-5) || (templateObject && f != templateObject->getFullSerializationInterval()))
			XMLParser::setDouble(element, "remote", f, "full");
		f = getVisibleRange();
		if ((!templateObject && f > 0) || (templateObject && f != templateObject->getVisibleRange()))
			XMLParser::setDouble(element, "remote", f, "range");
                if ((!templateObject && serializeChildren) || (templateObject && serializeChildren != templateObject->serializeChildren))
			XMLParser::setBoolean(element, "remote", serializeChildren, "children");
		if ((!templateObject && realizeRange > 1e-5) || (templateObject && realizeRange != templateObject->realizeRange))
			XMLParser::setDouble(element, "realize", realizeRange, "range");
		if ((!templateObject && realizeAzimuth > 1e-5) || (templateObject && realizeAzimuth != templateObject->realizeAzimuth))
			XMLParser::setDouble(element, "realize", realizeAzimuth*180.0/M_PI, "range");
		if ((!templateObject && realizeElevation > 1e-5) || (templateObject && realizeElevation != templateObject->realizeElevation))
			XMLParser::setDouble(element, "realize", realizeElevation*180.0/M_PI, "range");
		if ((!templateObject && realizeExemptRange > 1e-5) || (templateObject && realizeExemptRange != templateObject->realizeExemptRange))
			XMLParser::setDouble(element, "realize", realizeExemptRange, "exempt");
	}

	/// This method may be used to add child objects, sounds, geometry etc.
	/// It can be overridden by derived classes to implement usage of any type of component.
	void BaseObject::addComponent(Component *component)
	{
		if (BaseObject *child = dynamic_cast<BaseObject*> (component)) {
			if (child->parent == this)
				return;
			if (child->parent)
				child->parent->removeChild(child);
			children.push_back(child);
			child->parent = this;
			child->setOwner(getOwner());
			transform->addChild(child->getTransform());
		} else if (Script *script = dynamic_cast<Script*> (component)) {
			script->setSelf(this, "moon::BaseObject");
		}
		ComponentContainer::addComponent(component);
	}

	void BaseObject::initialize()
	{
		dout(6) << "Initializing object " << getName() << "\n";
		ComponentContainer::initialize();
		if (Interpreter::initialized) {
			// Call lua callback (if it exists)
			if (Interpreter::instance().pushMethod(this, "moon::BaseObject", "onInitialize")) {
				Interpreter::instance().pushUserType(this, "moon::BaseObject");
				if (Interpreter::instance().pCall(1,0) != 0)
					dout(ERROR, SCRIPT) << "onInitialize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
			}
			for (ScriptParamMap::iterator it = scriptParams.begin(); it != scriptParams.end(); it++) {
				Interpreter::instance().pushUserType(this, "moon::BaseObject");
				Interpreter::instance().setTable(it->first, it->second);
				Interpreter::instance().pop(1);
			}
		}
	}

	void BaseObject::reset()
	{
		dout(6) << "Resetting object " << getName() << "\n";
		ComponentContainer::reset();
		setTransformMatrix(resetMatrix);
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::BaseObject", "onReset")) {
			Interpreter::instance().pushUserType(this, "moon::BaseObject");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onReset script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
		if (hidden && !resetHidden)
			show();
		else if (!hidden && resetHidden)
			hide();
	}

	void BaseObject::setResetState()
	{
		resetMatrix = getTransformMatrix();
		resetHidden = hidden;
		ComponentContainer::setResetState();
	}

	/// This is called by the Scenario when it is realized. This way, geometry, bodies
	/// etc are not created until the object is part of the active scenario.
	void BaseObject::realize()
	{
		if (isRealized())
			return;
		dout(6) << "Realizing object " << getName() << "\n";

		ComponentContainer::realize();

		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::BaseObject", "onRealize")) {
			Interpreter::instance().pushUserType(this, "moon::BaseObject");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onRealize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
	}

	/// \see realize()
	void BaseObject::unrealize()
	{
		if (!isRealized())
			return;
		dout(6) << "Unrealizing object " << getName() << "\n";
		ComponentContainer::unrealize();
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::BaseObject", "onUnrealize")) {
			Interpreter::instance().pushUserType(this, "moon::BaseObject");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onUnrealize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
	}

	void BaseObject::show()
	{
		transform->removeChild(nodeGroup.get());
		transform->removeChild(debugGroup.get());
		transform->removeChild(highlightnode.get());
		osg::Group *group = NULL;
		// Setup highlighting if necessary
		if (highlightnode.valid()) {
			if (highlightnode->asGroup()) {
				group = highlightnode->asGroup();
				group->removeChildren(0, group->getNumChildren());
				transform->addChild(group);
			} else {
				transform->addChild(highlightnode.get());
				group = transform.get();
			}
		} else
			group = transform.get();
		// Add nodes in the displayed modes
		if (nodeGroup.valid() && displayMode & DISPLAY_NORMAL)
			group->addChild(nodeGroup.get());
		if (debugGroup.valid() && (displayMode & DISPLAY_DEBUG || (isNormallyVisible() && (!nodeGroup.valid() || nodeGroup->getNumChildren() == 0))))
			group->addChild(debugGroup.get());
		for (ChildList::iterator it = children.begin(); it != children.end(); it++) {
			(*it)->show();
		}
		hidden = false;
	}

	void BaseObject::hide()
	{
		dout(6) << "Hide " << getName() << "\n";
		transform->removeChild(nodeGroup.get());
		transform->removeChild(debugGroup.get());
		transform->removeChild(highlightnode.get());
		hidden = true;
		for (ChildList::iterator it = children.begin(); it != children.end(); it++)
			(*it)->hide();
	}

	void BaseObject::addNode(osg::Node *newnode)
	{
		if (!newnode)
			return;
		if (!nodeGroup.valid()) {
			nodeGroup = new osg::Group;
			nodeGroup->setName(getName() + " nodes");
		}
		nodeGroup->addChild(newnode);
		if (!hidden)
			show();
	}

	void BaseObject::removeNode(osg::Node *remnode)
	{
		if (!remnode || !nodeGroup)
			return;
		nodeGroup->removeChild(remnode);
		if (nodeGroup->getNumChildren() == 0) {
			transform->removeChild(nodeGroup.get());
			nodeGroup = NULL;
		}
		if (!hidden)
			show();
	}

	void BaseObject::addDebugNode(osg::Node *newnode)
	{
		if (!newnode)
			return;
		if (!debugGroup.valid()) {
			debugGroup = new osg::Group;
			debugGroup->setName(getName() + " debug nodes");
			debugGroup->setNodeMask(NodeMask::DEFAULT_DEBUG);
			if (transform->getNodeMask() & NodeMask::INTERACTIVE)
				debugGroup->setNodeMask(debugGroup->getNodeMask() | NodeMask::INTERACTIVE);
			if (!(transform->getNodeMask() & NodeMask::INTERSECT))
				debugGroup->setNodeMask(debugGroup->getNodeMask() & ~NodeMask::INTERSECT);
		}
		debugGroup->addChild(newnode);
		if (!hidden)
			show();
	}

	void BaseObject::removeDebugNode(osg::Node *remnode)
	{
		if (!remnode || !debugGroup)
			return;
		debugGroup->removeChild(remnode);
		if (debugGroup->getNumChildren() == 0) {
			transform->removeChild(debugGroup.get());
			debugGroup = NULL;
		}
		if (!hidden)
			show();
	}

	osg::Node* BaseObject::getNode() const { return nodeGroup.get(); }

	osg::Node* BaseObject::getDebugNode() const { return debugGroup.get(); }

	void BaseObject::highlight(const bool on, const HighLightMode mode, const osg::Vec4& color, const bool recursive)
	{
		if (osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*> (highlightnode.get())) {
			transform->addChild(scribe->getChild(0));
			transform->removeChild(scribe);
		} else if (highlightnode.valid())
			transform->removeChild(highlightnode.get());
		highlightnode = NULL;
		if (on && transform->getNumChildren() > 0) {
			switch (mode) {
				case THICK_BBOX:
				case TRANSPARENT_BBOX:
				case BBOX:
					if (!highlightnode.valid()) {
						mdraw::DebugDrawMode drawMode = mdraw::WIREFRAME;
						if (mode == THICK_BBOX)
							drawMode = mdraw::THICK_WIREFRAME;
						else if (mode == TRANSPARENT_BBOX)
							drawMode = mdraw::TRANSPARENT;
						osg::Node *node = NULL;
						if (displayMode & DISPLAY_NORMAL && getNode())
							node = getNode();
						else
							node = getDebugNode();
						osg::Node *bboxNode = mdraw::getBoundingBoxNode(node, drawMode, 1.0, color);
						if (!bboxNode) {
							dout(ERROR) << "Failed to create bounding box node for " << getName() << "\n";
							return;
						}
						bboxNode->setName("highlight bbox");
						transform->addChild(bboxNode);
						highlightnode = bboxNode;
						/*
						osg::Group *group = new osg::Group(*transform.get());
						group->addChild(bboxNode);
						highlightnode = group;
						 */
					}
					break;
				case THICK_SCRIBE:
				case SCRIBE:
					osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*> (transform->getChild(0));
					if (on && scribe)
						return;
					else {
						scribe = new osgFX::Scribe;
						scribe->setName("highlight scribe");
						if (mode == THICK_SCRIBE)
							scribe->setWireframeLineWidth(2);
						scribe->setWireframeColor(color);
						scribe->addChild(transform->getChild(0));
						highlightnode = scribe;
					}
					break;
			}
		}
		if (recursive) {
			for (ChildList::iterator it = children.begin(); it != children.end(); it++)
				(*it)->highlight(on, mode, color);
		}
		if (!hidden)
			show();
		else
			hide();
	}

	osg::Matrix BaseObject::getWorldTransformMatrix() const
	{
		if (parent)
			return getTransformMatrix() * parent->getWorldTransformMatrix();
		else
			return getTransformMatrix();
	}

	osg::Matrix BaseObject::getInverseWorldTransformMatrix()
	{
		if (!dirtyInverseWorldMatrix)
			return inverseWorldMatrix;

		if (parent)
			inverseWorldMatrix = osg::Matrix::inverse(getTransformMatrix()) * parent->getInverseWorldTransformMatrix();
		else
			inverseWorldMatrix = osg::Matrix::inverse(getTransformMatrix());
		dirtyInverseWorldMatrix = false;
		return inverseWorldMatrix;
	}

	void BaseObject::pointAt(const osg::Vec3& pos)
	{
		osg::Vec3 r = pos - getWorldTransformMatrix().getTrans();
		r.normalize();
		osg::Vec3 o = getEulerAnglesFromMatrix(getWorldTransformMatrix());
		double elevation = asin(r.z());
		double azimuth = atan2(r.x(),r.y());
		setAttitude(getAttitude() + osg::Vec3(0, elevation - o.y(), azimuth - o.z()));
	}

	void BaseObject::pointAt(BaseObject *object)
	{
		if (!object)
			return;
		osg::Vec3 r = object->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		r.normalize();
		osg::Vec3 watt = getEulerAnglesFromMatrix(getWorldTransformMatrix());
		double elevation = asin(r.z());
		double azimuth = atan2(r.x(),r.y());
		osg::Vec3 latt = getAttitude();
		setAttitude(osg::Vec3(latt.x() + azimuth - watt.x(), latt.y() + elevation - watt.y(), latt.z()));
	}

	float BaseObject::getRange(const BaseObject *object)
	{
		if (!object)
			return 0;
		return (object->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans()).length();
	}

	/** \param rel if specified, return difference to current heading
		\return azimuth angle to \a object in world coordinates
	 */
	float BaseObject::getAzimuth(const BaseObject *object, const bool rel)
	{
		if (!object)
			return 0;
		osg::Vec3 r = object->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		r.normalize();
		float azimuth = atan2f(r.x(),r.y());
		if (rel)
			azimuth -= getEulerAnglesFromMatrix(getWorldTransformMatrix()).x();
		while (azimuth < -M_PI) azimuth += 2.0*M_PI;
		while (azimuth > M_PI) azimuth -= 2.0*M_PI;
		return azimuth;
	}

	/** \param rel if specified, return difference to current pitch attitude
	 \return elevation angle to \a object in world coordinates
	 */
	float BaseObject::getElevation(const BaseObject *object, const bool rel)
	{
		if (!object)
			return 0;
		osg::Vec3 r = object->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		r.normalize();
		float elevation = asinf(r.z());
		if (rel)
			elevation -= getEulerAnglesFromMatrix(getWorldTransformMatrix()).y();
		while (elevation < -M_PI) elevation += 2.0*M_PI;
		while (elevation > M_PI) elevation -= 2.0*M_PI;
		return elevation;
	}

	void BaseObject::getSpherical(float& range, float& azimuth, float& elevation, const BaseObject *object, const bool rel)
	{
		if (!object)
			return;
		osg::Vec3 r = object->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		range = r.length();
		r.normalize();
		osg::Vec3 att = getEulerAnglesFromMatrix(getWorldTransformMatrix());
		azimuth = atan2f(r.x(),r.y());
		if (rel)
			azimuth -= att.x();
		elevation = asinf(r.z());
		if (rel)
			elevation -= att.y();
		while (azimuth < -M_PI) azimuth += 2.0*M_PI;
		while (azimuth > M_PI) azimuth -= 2.0*M_PI;
		while (elevation < -M_PI) elevation += 2.0*M_PI;
		while (elevation > M_PI) elevation -= 2.0*M_PI;
	}

	bool BaseObject::getHeightAboveTerrain(float& height, const bool boundscenter, const double below, const double above, const osg::Node::NodeMask mask)
	{
		/// \todo rembered HAT and dirty flag to avoid intersections in subsequent calls
		osg::Vec3 offset;
		if (boundscenter)
			offset += getBottomCenter();
		osg::Vec3 start = getPosition() + offset + osg::Vec3(0,0,above);
		// Run intersector
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(start,start - osg::Vec3(0,0,above+below));
		osgUtil::IntersectionVisitor iv(intersector.get());
		iv.setTraversalMask(mask);
		osg::Node::NodeMask saveMask = getTransform()->getNodeMask();
		getTransform()->setNodeMask(0);
		osg::Node *root = getTransform()->getParent(0);
		if (root) {
			while (root->getNumParents() > 0)
				root = root->getParent(0);
			root->accept(iv);
			// Go through intersections
			osgUtil::LineSegmentIntersector::Intersections& ixns = intersector->getIntersections();
			if (ixns.size() > 0) {
				osgUtil::LineSegmentIntersector::Intersection ix = *ixns.begin();
				// Move to intersection point
				osg::Vec3 p = ix.getWorldIntersectPoint();
				getTransform()->setNodeMask(saveMask);
				height = (getPosition() - p + offset).z();
				return true;
			}
		}
		getTransform()->setNodeMask(saveMask);
		return false;
	}

	bool BaseObject::clampToTerrain(const bool boundscenter, const double below, const double above, const osg::Node::NodeMask mask)
	{
		osg::Vec3 offset;
		if (boundscenter)
			offset += osg::Vec3(0,0,getBottomCenter().z());
		osg::Vec3 start = getPosition() + offset + osg::Vec3(0,0,above);
		// Run intersector
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(start,start - osg::Vec3(0,0,above+below));
		osgUtil::IntersectionVisitor iv(intersector.get());
		iv.setTraversalMask(mask);
		osg::Node::NodeMask saveMask = getTransform()->getNodeMask();
		getTransform()->setNodeMask(0);
		osg::Node *root = getTransform()->getParent(0);
		if (root) {
			while (root->getNumParents() > 0)
				root = root->getParent(0);
			root->accept(iv);
			// Go through intersections
			osgUtil::LineSegmentIntersector::Intersections& ixns = intersector->getIntersections();
			if (ixns.size() > 0) {
				osgUtil::LineSegmentIntersector::Intersection ix = *ixns.begin();
				// Move to intersection point
				osg::Vec3 p = ix.getWorldIntersectPoint();
				setPosition(p - offset);
				getTransform()->setNodeMask(saveMask);
				return true;
			}
		}
		getTransform()->setNodeMask(saveMask);
		return false;
	}

	bool BaseObject::alignToTerrain(const bool boundscenter, const double below, const double above, const osg::Node::NodeMask mask)
	{
		osg::Vec3 start = getPosition() + osg::Vec3(0,0,above);
		if (boundscenter)
			start += getBottomCenter();
		// Run intersector
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(start,start - osg::Vec3(0,0,above+below));
		osgUtil::IntersectionVisitor iv(intersector.get());
		iv.setTraversalMask(mask);
		osg::Node::NodeMask saveMask = getTransform()->getNodeMask();
		getTransform()->setNodeMask(0);
		osg::Node *root = getTransform()->getParent(0);
		if (root) {
			while (root->getNumParents() > 0)
				root = root->getParent(0);
			root->accept(iv);
			// Go through intersections
			osgUtil::LineSegmentIntersector::Intersections& ixns = intersector->getIntersections();
			if (ixns.size() > 0) {
				osgUtil::LineSegmentIntersector::Intersection ix = *ixns.begin();
				// Move to intersection point (both selection and dragger)
				osg::Vec3 n = ix.getWorldIntersectNormal();
				osg::Matrix rotM = osg::Matrix::rotate(getAttitude().x(), osg::Vec3(0,0,-1))
					* osg::Matrix::rotate(osg::Vec3(0,0,1), n);
				osg::Vec3 att = TransformObject::getEulerAnglesFromMatrix(rotM);
				setAttitude(att);
				getTransform()->setNodeMask(saveMask);
				return true;
			}
		}
		getTransform()->setNodeMask(saveMask);
		return false;
	}

	/// This method is used by getHeightAboveTerrain(), clampToTerrain() and alignToTerrain(), as well as the editor
	osg::Vec3 BaseObject::getBottomCenter()
	{
		// Get bottom center
		osg::ref_ptr<osg::Group> node = new osg::Group(*transform->asGroup());
		osg::BoundingBox bbox = mdraw::getBoundingBox(node.get());
		return osg::Vec3(0, 0, bbox.zMin()) - bbox.center();
	}

	void BaseObject::setDisplayMode(const unsigned int mode)
	{
		if (mode == displayMode)
			return;
		displayMode = mode;
		if (mode & DISPLAY_DEBUG && !debugGroup && nodeGroup)
			addDebugNode(mdraw::getBoundingBoxNode(nodeGroup.get(), mdraw::WIREFRAME));
		if (mode & DISPLAY_DEBUG)
			icMessage(IC_MSG_DEBUG_DISPLAY_ON);
		else
			icMessage(IC_MSG_DEBUG_DISPLAY_OFF);
		for (ChildList::iterator it = children.begin(); it != children.end(); it++)
			(*it)->setDisplayMode(mode);
		if (!hidden)
			show();
	}

	void BaseObject::onConstruction()
	{
		dout(3, NETWORK) << "Constructed " << libraryName() << "::" << className()
			<< " '" << getName() << "'\n";
		for (unsigned int i = 0; i < getNumChildren(); i++)
			getChild(i)->setOwner(getOwner());
	}

	void BaseObject::onOwnerChange()
	{
		for (unsigned int i = 0; i < getNumChildren(); i++)
			getChild(i)->setOwner(getOwner());
	}

	bool BaseObject::serialize(const bool full)
	{
		if (full) {
			SERIALIZE_String(getName());
			/// \todo serialize reset matrix, some other quasi-static properties...
		}
		SERIALIZE_Bit(hidden);
		osg::Quat rot = getRotation();
		if (!full && rot == lastRot)
			SERIALIZE_0();
		else {
			SERIALIZE_1();
			SERIALIZE_NQuat(rot);
		}
		lastRot = rot;
		bool result = PositionedNetworkObject::serialize(full);

		if (serializeChildren && getTemplate() && children.size() > 0) {
			for (unsigned int i = 0; i < getNumChildren(); i++) {
				BaseObject *child = getChild(i);
				if (child->serializeAsChild) {
					SERIALIZE(i);
					child->bitstream = bitstream;
					child->serialize(full);
				}
			}
		}
		SERIALIZE(-1);
		return result;
	}

	void BaseObject::deserialize(const bool full, const double timediff)
	{
		if (!isInitialized())
			initialize();
		if (full) {
			std::string str;
			DESERIALIZE_String(str, 128);
			setName(str);
		}
		if (DESERIALIZE_Bit()) {
			if (!hidden)
				hide();
		} else {
			if (hidden)
				show();
		}
		if (SimulationManager::instance().isPaused())
			return;
		if (DESERIALIZE_Bit()) {
			osg::Quat rot;
			DESERIALIZE_NQuat(rot);
			setRotation(rot);
		}

		PositionedNetworkObject::deserialize(full, timediff);

		int i;
		DESERIALIZE(i);
		while (i >= 0) {
			if ((unsigned int)i > getNumChildren()) {
				dout(ERROR, NETWORK) << "Deserialized data for invalid child index " << i << "\n";
				return;
			}
			BaseObject *child = getChild(i);
			child->bitstream = bitstream;
			child->deserialize(full, timediff);
			DESERIALIZE(i);
		}
	}

	bool BaseObject::setOwner(moonet::Client *newOwner)
	{
		bool result = NetworkObject::setOwner(newOwner);
		for (ChildList::iterator it = children.begin(); it != children.end(); it++)
			(*it)->setOwner(newOwner);
		return result;
	}

	void BaseObject::setVisibility(const bool visible)
	{
		dout(6) << "setVisibility " << getName() << " " << visible << " range " << getVisibleRange() << "\n";
		if (getVisibleRange() < 1e-5)
			return;
		if (visible) {
			if (wasRealizedInRange && !isRealized())
				realize();
			if (hidden)
				show();
		} else if (!isCloaked()) {
			wasRealizedInRange = isRealized();
			wasHiddenInRange = isHidden();
			if (isRealized())
				unrealize();
			if (!hidden)
				hide();
		}
	}

	KinematicObject* BaseObject::asKinematic() { return NULL; }

	void BaseObject::preUpdateTransformation(const bool parentUpdate)
	{
		for (ChildList::iterator it = children.begin(); it != children.end(); it++)
			(*it)->preUpdateTransformation(true);
	}

	void BaseObject::updateTransformation(const bool parentUpdate)
	{
		dirtyInverseWorldMatrix = true;
		for (ChildList::iterator it = children.begin(); it != children.end(); it++)
			(*it)->updateTransformation(true);
		icMessage(IC_MSG_UPDATE_TRANSFORMATION);
	}

	BaseObject* BaseObject::getChildByTag(const std::string& tag)
	{
		for (ChildList::iterator it = children.begin(); it != children.end(); it++) {
			if ((*it)->hasTag(tag))
				return it->get();
		}
		return NULL;
	}

	osg::Matrix BaseObject::getWorldResetMatrix() const
	{
		if (parent)
			return getResetMatrix() * parent->getWorldResetMatrix();
		else
			return getResetMatrix();
	}

	void BaseObject::remove(const double timeFromNow)
	{
		setRemoveTime(SimulationManager::instance().getTime() + timeFromNow);
	}

	void BaseObject::update(const double dt)
	{
		Camera *cam = CameraManipulator::instance().getActiveCamera();
		// Update realize ranges
		/// \todo need sorting on range somehow...
		if (cam && (realizeRange > 1e-5 || realizeAzimuth > 1e-5 || realizeElevation > 1e-5)) {
			bool inrange = true, inazimuth = true, inelevation = true, exempt = false;
			float r, phi, theta;
			cam->getSpherical(r, phi, theta, this, true);
			if (realizeRange > 1e-5 && r > realizeRange)
				inrange = false;
			if (realizeAzimuth > 1e-5 && fabs(phi) > realizeAzimuth)
				inazimuth = false;
			if (realizeElevation > 1e-5 && fabs(theta) > realizeElevation)
				inelevation = false;
			if (realizeExemptRange > 1e-5 && r < realizeExemptRange)
				exempt = true;
			if ((!inrange || !inazimuth || !inelevation) && !exempt && isRealized())
				unrealize();
			else if (((inrange && inazimuth && inelevation) || exempt) && !isRealized())
				realize();
		}
		// Update script
		if (scriptUpdateInterval > 1e-5 && Interpreter::initialized) {
			scriptTimeStamp += dt;
			while (scriptTimeStamp > scriptUpdateInterval) {
				scriptTimeStamp -= scriptUpdateInterval;
				if (Interpreter::instance().pushMethod(this, "moon::BaseObject", "onUpdate")) {
					Interpreter::instance().pushUserType(this, "moon::BaseObject");
					Interpreter::instance().pushDouble(scriptUpdateInterval);
					if (Interpreter::instance().pCall(2,0) != 0) {
						dout(ERROR, SCRIPT) << "onUpdate script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
						scriptUpdateInterval = 0.0;
						break;
					}
				} else {
					dout(ERROR, SCRIPT) << "No onUpdate() callback for " << getName() << "\n";
					scriptUpdateInterval = 0.0;
					break;
				}
			}
		}
		// Update parameters
		if (headingParam->isConnected() || pitchParam->isConnected() || rollParam->isConnected()) {
			osg::Vec3 att = getAttitude();
			headingParam->set(att.x());
			pitchParam->set(att.y());
			rollParam->set(att.z());
		}
		// Update components and children
		ComponentContainer::update(dt);

		// Remove children that are scheduled for removal
		for (std::size_t i = 0; i < children.size(); i++) {
			BaseObject *child = children[i].get();
			if (child->getRemoveTime() >= 0 && SimulationManager::instance().getTime() > child->getRemoveTime()) {
				removeChild(child);
				i--;
			}
		}
	}

	Parameter* BaseObject::findParameter(const std::string& name)
	{
		std::string objectname, param = name;
		std::size_t sepindex = param.find_first_of(" :.,");
		if (sepindex != std::string::npos) {
			objectname = param.substr(0, sepindex);
			param = param.substr(sepindex+1);
		}
		/// \todo Find parameters in components derived from ParameterContainer.
		if (objectname.length() > 0) {
			/// If \a name is separated into object and parameter, look for parameters in components derived from ParameterContainer.
			for (unsigned int i = 0; i < getNumComponents(); i++) {
				if (getComponent(i)->getName() == objectname) {
					if (ParameterContainer* paramco = dynamic_cast<ParameterContainer*> (getComponent(i))) {
						if (Parameter *coparam = paramco->getParameter(param))
							return coparam;
					}
				}
			}
			/// Then (also if separated) look for parameters in related objects using findRelated
			BaseObject *object = NULL;
			if (objectname == "root")
				object = getRoot();
			else
				object = getRoot()->findRelated(objectname);
			if (object)
				return object->findParameter(param);
			return NULL;

		}
		Parameter *myparam = ParameterContainer::getParameter(param);
		if (myparam)
			return myparam;
		/// If parameter is not found, try parent object if it exists.
		if (getParent())
			return getParent()->findParameter(param);
		return NULL;
	}

	BaseObject::~BaseObject()
	{
		//dout(3) << "~BaseObject " << getName() << "\n";
		if (transform->getUserData() == this) {
			// Work-around for the cyclic reference created by setting user data to this...
			ref(); ref();
			transform->setUserData(NULL);
			unref_nodelete();
		}
	}

} // namespace
