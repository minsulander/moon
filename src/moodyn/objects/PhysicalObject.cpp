#include "PhysicalObject.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <moon/Interpreter.h>
#include <moon/SimulationManager.h>
#include <mlog/Log.h>
#include <mdraw/utils.h>
#include <osgDB/ReadFile>

using namespace moon;
using namespace mlog;

namespace moodyn {

	REGISTER_Object_Alias(moodyn, PhysicalObject, Static);

	PhysicalObject::PhysicalObject()
	:	KinematicObject(),
		Destructible(),
		resetHealth(100.f),
		luaContactCallback(false),
		luaContactFeedbackCallback(false),
		destructionTime(-1.0),
		destructionHideTime(-1.0),
		destructionUnrealizeTime(-1.0),
		destructionRemoveTime(-1.0)
	{
		contactParam = new Parameter("contact", this);
		contactTorqueParam = new Parameter("contact_torque", this);
	}

	PhysicalObject::PhysicalObject(const PhysicalObject& source, const osg::CopyOp& copyop)
	:	KinematicObject(source, copyop),
		Destructible(source),
		resetHealth(source.resetHealth),
		luaContactCallback(false),
		luaContactFeedbackCallback(false),
		destructionTime(-1.0),
		destructionHideTime(source.destructionHideTime),
		destructionUnrealizeTime(source.destructionUnrealizeTime),
		destructionRemoveTime(source.destructionRemoveTime)
	{
		contactParam = new Parameter("contact", this);
		contactTorqueParam = new Parameter("contact_torque", this);
	}

	void PhysicalObject::parseXML(const TiXmlElement *element)
	{
		//=== PhysicalObject
		//=* alias: Static
		//=* component: Geometry
		//=See superclass KinematicObject for more parameters.
		KinematicObject::parseXML(element);
		Destructible::parseXML(element);
		//=* attribute: geomodel="(filename)"
		//=. Model file to use for geometry. If unspecified, visual model is used.
		std::string str;
		osg::ref_ptr<osg::Node> geonode = getNode();
		if (XMLParser::parseStringAttribute(str, element, "geomodel")) {
			geonode = osgDB::readNodeFile(str);
			if (XMLParser::parseBooleanAttribute(element, "yup", true, false)) {
				osg::MatrixTransform *xform = new osg::MatrixTransform;
				xform->setMatrix(osg::Matrix::rotate(M_PI/2.0,osg::Vec3(1,0,0)) * osg::Matrix::rotate(M_PI,osg::Vec3(0,0,1)));
				xform->addChild(geonode.get());
				geonode = xform;
			}
		}
		//=* attribute: geometry="bsphere|bbox|bounds|mesh"
		//=. Quick way to define Geometry by bounding sphere/box, bounds traversal or mesh based on visual model.
		if (XMLParser::parseStringAttribute(str, element, "geometry")) {
			initialize();
			if (!geometry)
				setGeometry(new moodyn::Geometry);
			if (!geonode)
				dout(ERROR) << "No node to generate geometry for '" << getName() << "'\n";
			else if (str == "bsphere")
				geometry->addBoundingSphere(geonode->getBound());
			else if (str == "bbox")
				geometry->addBoundingBox(mdraw::getBoundingBox(geonode.get()));
			else if (str == "bounds")
				geometry->addShapesFromBounds(geonode.get());
			else if (str == "mesh")
				geometry->addMesh(geonode.get());
			else
				throw ParseException(std::string("Invalid geometry specifiation '") + str + "'", element);
		} else if (geonode.valid() && geonode != getNode()) {
			//=. If 'geomodel' is set but 'geometry' is unspecified, 'geometry=bounds' is assumed.
			initialize();
			if (!geometry)
				setGeometry(new moodyn::Geometry);
			geometry->addShapesFromBounds(geonode.get());
		}
		XMLParser::parseDouble(destructionHideTime, element, "destruction", "second", "hide");
		XMLParser::parseDouble(destructionUnrealizeTime, element, "destruction", "second", "unrealize");
		XMLParser::parseDouble(destructionRemoveTime, element, "destruction", "second", "remove");
	}

	void PhysicalObject::writeXML(TiXmlElement *element) const
	{
		KinematicObject::writeXML(element);
		Destructible::writeXML(element, dynamic_cast<const Destructible*> (getTemplate()));
	}

	void PhysicalObject::initialize()
	{
		KinematicObject::initialize();
	}

	void PhysicalObject::reset()
	{
		KinematicObject::reset();
		setHealth(resetHealth);
		destructionTime = -1.0;
		if (geometry.valid())
			geometry->setColorMultiplier((100.f-getHealth())/100.f);
	}

	void PhysicalObject::setResetState()
	{
		KinematicObject::setResetState();
		resetHealth = getHealth();
	}

	void PhysicalObject::addComponent(Component *component)
	{
		if (moodyn::Geometry *geo = dynamic_cast<moodyn::Geometry*> (component)) {
			if (isRealized() && geometry.valid())
				geometry->unrealize(); // unrealize old
			if (!geometry.valid()) {
				geometry = geo;
				geometry->setUserData(this);
			} else {
				dout(3) << "Merging geometry '" << geo->getName() << "' with existing geometry\n";
				geometry->merge(geo);
			}
			if (geometryDebugNode.valid())
				removeDebugNode(geometryDebugNode.get());
			geometryDebugNode = geometry->createDebugNode();
			addDebugNode(geometryDebugNode.get());
			if (isRealized())
				geometry->realize(); // re-realize
		}
		KinematicObject::addComponent(component);
	}

	void PhysicalObject::realize()
	{
		KinematicObject::realize();
		if (geometry.valid() && geometry->needsMesh()) {
			if (!getNode())
				dout(ERROR) << "No node to generate geometry mesh for '" << getName() << "'\n";
			else {
				geometry->addMesh(getNode());
				geometry->realize();
			}
		}
		if (geometry.valid())
			geometry->setTransformation(getWorldTransformMatrix());
		if (geometry.valid()) {
			// Initialize contact feedback if needed for audio or damage
			if (contactParam->isConnected() || contactTorqueParam->isConnected() || getDamageRatio(Destructible::CONTACT) || getDamageRatio(Destructible::CONTACT_TORQUE))
				initContactFeedbackCallback();
			// .. or for script callback
			if (Interpreter::initialized) {
				Interpreter& lua = Interpreter::instance();
				// Check for onContact callback
				if (lua.pushMethod(this, "moodyn::PhysicalObject", "onContact")) {
					luaContactCallback = true;
					initContactCallback();
					lua.pop(1);
				}
				// Check for onContactFeedback callback
				if (lua.pushMethod(this, "moodyn::PhysicalObject", "onContactFeedback")) {
					luaContactFeedbackCallback = true;
					initContactFeedbackCallback();
					lua.pop(1);
				}
			}
		}
	}

	void PhysicalObject::unrealize()
	{
		KinematicObject::unrealize();
	}

	void PhysicalObject::setDisplayMode(const unsigned int mode)
	{
		if (mode & DISPLAY_DEBUG && geometry.valid() && !geometryDebugNode) {
			geometryDebugNode = geometry->createDebugNode();
			addDebugNode(geometryDebugNode.get());
		}
		KinematicObject::setDisplayMode(mode);
	}

	void PhysicalObject::updateTransformation(const bool parentUpdate)
	{
		osg::Matrix WM = getWorldTransformMatrix();
		if (geometry.valid() && geometry->isEnabled())
			geometry->setTransformation(WM);
		KinematicObject::updateTransformation(parentUpdate);
	}

	void PhysicalObject::setGeometry(moodyn::Geometry *newgeometry)
	{
		addComponent(newgeometry);
	}

	moodyn::Geometry* PhysicalObject::getGeometry() { return geometry.get(); }

	void PhysicalObject::destroy()
	{
		destructionTime = 0.0;
		if (destructionRemoveTime > 0.0)
			remove(destructionRemoveTime);
		showModelsWithTag("destroyed");
		Destructible::destroy();
		for (unsigned int i = 0; i < getNumChildren(); i++) {
			if (Destructible *destructible = dynamic_cast<Destructible*> (getChild(i)))
				destructible->destroy();
		}
	}

	void PhysicalObject::update(const double dt)
	{
		KinematicObject::update(dt);
		if (geometry.valid() && !geometry->getBody() && isDynamic()) {
			osg::Matrix WM = getWorldTransformMatrix();
			if (geometry.valid() && geometry->isEnabled())
				geometry->setTransformation(WM);
		}
		if (destructionTime >= 0.0) {
			destructionTime += dt;
			if (destructionHideTime >= 0.0 && destructionTime > destructionHideTime && !isHidden())
				hide();
			if (destructionUnrealizeTime >= 0.0 && destructionTime > destructionUnrealizeTime && isRealized())
				unrealize();
		}
	}

	bool PhysicalObject::ContactCallback::operator()(moodyn::Geometry *own, moodyn::Geometry *other)
	{
		if (!own || !other)
			return false;
		PhysicalObject *ownObject = static_cast<PhysicalObject*> (own->getUserData());
		PhysicalObject *otherObject = static_cast<PhysicalObject*> (other->getUserData());
		if (ownObject && otherObject)
			return ownObject->onContact(otherObject);
		return true;
	}

	bool PhysicalObject::ContactFeedbackCallback::operator()(moodyn::Geometry *own, moodyn::Geometry *other)
	{
		if (!own)
			return false;
		PhysicalObject *ownObject = static_cast<PhysicalObject*> (own->getUserData());
		PhysicalObject *otherObject = NULL;
		if (other)
			otherObject = static_cast<PhysicalObject*> (other->getUserData());
		if (ownObject)
			return ownObject->onContactFeedback(otherObject);
		return true;
	}

	bool PhysicalObject::NearCallback::operator()(moodyn::Geometry *own, moodyn::Geometry *other)
	{
		if (!own || !other)
			return false;
		PhysicalObject *ownObject = static_cast<PhysicalObject*> (own->getUserData());
		PhysicalObject *otherObject = static_cast<PhysicalObject*> (other->getUserData());
		if (ownObject && otherObject)
			return ownObject->onNear(otherObject);
		return true;
	}

	PhysicalObject::~PhysicalObject() {
		// Work-around for the cyclic reference created by setting user data to this...
		/*
		if (geometry.valid()) {
			ref(); ref();
			geometry->setUserData(NULL);
			unref_nodelete();
		}
		*/
	}

	bool PhysicalObject::onContact(PhysicalObject *other)
	{
		if (luaContactCallback) {
			Interpreter& lua = Interpreter::instance();
			lua.pushMethod(this, "moodyn::PhysicalObject", "onContact");
			lua.pushUserType(this, "moodyn::PhysicalObject");
			lua.pushUserType(other, "moodyn::PhysicalObject");
			if (lua.pCall(2,1) != 0) {
				dout(ERROR, SCRIPT) << "onContact script for " << getName() << ": " << lua.getError() << "\n";
				luaContactCallback = false;
			} else if (!lua_isnil(lua.getState(),-1))
					return lua.popBool();
		}
		return true;
	}

	bool PhysicalObject::onContactFeedback(PhysicalObject *other)
	{
		float Fi = geometry->getContactForce().length()*SimulationManager::instance().getTimeStep();
		float Qi = geometry->getContactTorque().length()*SimulationManager::instance().getTimeStep();
		contactParam->set(Fi);
		contactTorqueParam->set(Qi);
		damage(Fi, Destructible::CONTACT);
		damage(Qi, Destructible::CONTACT_TORQUE);
		geometry->setColorMultiplier((100.f-getHealth())/100.f);
		if (luaContactFeedbackCallback) {
			/// \todo bindings for geometry so that we can get contact force/torque from script
			Interpreter& lua = Interpreter::instance();
			lua.pushMethod(this, "moodyn::PhysicalObject", "onContactFeedback");
			lua.pushUserType(this, "moodyn::PhysicalObject");
			lua.pushUserType(other, "moodyn::PhysicalObject");
			if (lua.pCall(2,1) != 0) {
				dout(ERROR, SCRIPT) << "onContactFeedback script for " << getName() << ": " << lua.getError() << "\n";
				luaContactFeedbackCallback = false;
			} else if (!lua_isnil(lua.getState(),-1))
				return lua.popBool();
		}
		return true;
	}

	bool PhysicalObject::onNear(PhysicalObject *other)
	{
		return true;
	}

	void PhysicalObject::initContactCallback()
	{
		if (!geometry.valid() || geometry->getContactCallback())
			return;
		geometry->setContactCallback(new ContactCallback);
	}

	void PhysicalObject::initContactFeedbackCallback()
	{
		if (!geometry.valid() || geometry->getContactFeedbackCallback())
			return;
		geometry->setContactFeedback(true);
		geometry->setContactFeedbackCallback(new ContactFeedbackCallback);
	}

	void PhysicalObject::initNearCallback()
	{
		if (!geometry.valid() || geometry->getNearCallback())
			return;
		geometry->setNearCallback(new NearCallback);
	}

} // namespace
