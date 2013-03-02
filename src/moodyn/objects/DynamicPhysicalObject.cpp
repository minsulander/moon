#include "DynamicPhysicalObject.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>
#include <moonet/Client.h>
#include <moonet/NetworkManager.h>
#include <moonet/SerializeMacros.h>
#include <mdraw/utils.h>
#include <osg/io_utils>

using namespace moon;
using namespace mlog;

namespace moodyn {

	REGISTER_Object_Alias(moodyn, DynamicPhysicalObject, Dynamic);

	DynamicPhysicalObject::DynamicPhysicalObject()
	:	PhysicalObject(),
		orphanTransform(false),
		remoteMode(STATIC),
		remoteModeRecursive(true),
		remoteModeSwitch(true),
		switchingMode(false)
	{
		serializeAsChild = true;
	}

	DynamicPhysicalObject::DynamicPhysicalObject(const DynamicPhysicalObject& other, const osg::CopyOp& copyop)
	:	PhysicalObject(other, copyop),
		orphanTransform(false),
		remoteMode(other.remoteMode),
		remoteModeRecursive(other.remoteModeRecursive),
		remoteModeSwitch(other.remoteModeSwitch),
		switchingMode(false)
	{
	}

	void DynamicPhysicalObject::parseXML(const TiXmlElement *element)
	{
		//=== DynamicPhysicalObject
		//=* alias: Dynamic
		//=* component: Body
		//=See superclass PhysicalObject for more parameters.

		PhysicalObject::parseXML(element);

		//=* element: remote mode="static|dynamic" recursive="true|false"
		std::string remoteModeStr;
		if (XMLParser::parseString(remoteModeStr, element, "remote", "mode")) {
			if (remoteModeStr == "static")
				remoteMode = STATIC;
			else if (remoteModeStr == "dynamic")
				remoteMode = DYNAMIC;
			else
				throw ParseException("Invalid remote mode specified", element);
		}
		XMLParser::parseBoolean(remoteModeSwitch, element, "remote", "modeswitch");
		XMLParser::parseBoolean(remoteModeRecursive, element, "remote", "recursive");
	}

	void DynamicPhysicalObject::writeXML(TiXmlElement *element) const
	{
		PhysicalObject::writeXML(element);
		DynamicPhysicalObject *templateObject = (DynamicPhysicalObject*) getTemplate();
		if (!templateObject || getRemoteMode() != templateObject->getRemoteMode()) {
			std::string remoteModeStr;
			switch (getRemoteMode()) {
				case STATIC: remoteModeStr = "static"; break;
				case DYNAMIC: remoteModeStr = "dynamic"; break;
			}
			if (remoteModeStr.length() > 0)
				XMLParser::setString(element, "remote", remoteModeStr, "mode");
			XMLParser::setBoolean(element, "remote", remoteModeRecursive, "recursive");
			XMLParser::setBoolean(element, "remote", remoteModeSwitch, "modeswitch");
		}
	}

	void DynamicPhysicalObject::addComponent(Component *component)
	{
		if (Joint *joint = dynamic_cast<Joint*> (component)) {
			addJoint(joint);
			return;
		} else if (Body *newbody = dynamic_cast<Body*> (component)) {
			if (body.valid())
				dout(WARN) << "Multiple bodies specified for '" << getName() << "' - overriding\n";
			body = newbody;
			body->setUserData(this);
			if (isRealized())
				body->realize();
		}
		PhysicalObject::addComponent(component);
	}

	void DynamicPhysicalObject::setVelocity(const osg::Vec3& vel, const bool relative)
	{
		if (!body)
			return PhysicalObject::setVelocity(vel, relative);
		if (orphanTransform && getParent() && !relative) {
			if (getParent()->asKinematic())
				body->setVelocity((getParent()->getWorldTransformMatrix().getRotate() * vel) + getParent()->asKinematic()->getVelocity(false));
			else
				body->setVelocity((getParent()->getWorldTransformMatrix().getRotate() * vel));
			PhysicalObject::setVelocity(vel);
		} else {
			body->setVelocity(vel, relative);
			PhysicalObject::setVelocity(vel, relative);
		}
		/// \todo Distribute velocity change to children DynamicPhysicalObjects or KinematicObjects?
	}

	void DynamicPhysicalObject::setAngularVelocity(const osg::Vec3& angvel, const bool relative)
	{
		if (!body)
			return PhysicalObject::setAngularVelocity(angvel, relative);
		if (orphanTransform && getParent() && !relative) {
			if (getParent()->asKinematic())
				body->setAngularVelocity((getParent()->getWorldTransformMatrix().getRotate() * angvel) + getParent()->asKinematic()->getAngularVelocity(true) ^ getPosition());
			else
				body->setAngularVelocity(getParent()->getWorldTransformMatrix().getRotate() * angvel);
			PhysicalObject::setAngularVelocity(getParent()->getWorldTransformMatrix().getRotate() * angvel);
		} else {
			body->setAngularVelocity(angvel, relative);
			PhysicalObject::setAngularVelocity(angvel, relative);
		}
		/// \todo Distribute velocity change to children DynamicPhysicalObjects?
	}

	osg::Vec3 DynamicPhysicalObject::getVelocity(const bool relative) const
	{
		if (body.valid() && orphanTransform && getParent()) {
			if (getParent()->asKinematic() && !relative)
				return getParent()->getWorldTransformMatrix().getRotate().inverse() * body->getVelocity(false) - getParent()->asKinematic()->getWorldVelocity();
			else
				return body->getVelocity(true);
		}
		return PhysicalObject::getVelocity(relative);
	}

	osg::Vec3 DynamicPhysicalObject::getAngularVelocity(const bool relative) const
	{
		if (body.valid() && orphanTransform && getParent()) {
			if (getParent()->asKinematic() && !relative)
				return getParent()->getWorldTransformMatrix().getRotate().inverse() * body->getAngularVelocity(false) - getParent()->asKinematic()->getWorldAngularVelocity();
			else
				return body->getAngularVelocity(true);
		}
		return PhysicalObject::getAngularVelocity(relative);
	}

	osg::Vec3 DynamicPhysicalObject::getWorldVelocity() const
	{
		if (body.valid() && body->isRealized())
			return body->getVelocity(false);
		return PhysicalObject::getWorldVelocity();
	}

	osg::Vec3 DynamicPhysicalObject::getWorldAngularVelocity() const
	{
		if (body.valid() && body->isRealized())
			return body->getAngularVelocity(false);
		return PhysicalObject::getWorldAngularVelocity();
	}

	void DynamicPhysicalObject::initialize()
	{
		PhysicalObject::initialize();
		setRemoteMode(remoteMode, remoteModeRecursive);
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			Joint *joint = it->get();
			connectJoint(joint);
		}
	}

	void DynamicPhysicalObject::reset()
	{
		PhysicalObject::reset();
		// Re-attach broken joints
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			moodyn::Joint *joint = it->get();
			if (joint_connections[joint] && joint->getBody1() == getBody())
				joint->attach(getBody(), joint_connections[joint]->getBody());
		}
	}

	void DynamicPhysicalObject::realize()
	{
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		if (isRealized())
			return;

		if (!body.valid() || body->getRealizeMode() != WITH_CONTAINER)
			return PhysicalObject::realize();

		if (getRoot()->isRemote()) {
			// Don't realize the body (or joints) on remote network objects in static mode
			if (remoteMode == STATIC) {
				PhysicalObject::realize();
				return;
			}
			// If this is a remote child in dynamic mode, but parent doesn't serialize children,
			// add geometry to the parent
			if (remoteMode == DYNAMIC && getParent() && !getRoot()->serializesChildren()) {
				DynamicPhysicalObject *root = dynamic_cast<DynamicPhysicalObject*> (getRoot());
				if (root && getGeometry())
					getGeometry()->setBody(root->getBody(), getWorldTransformMatrix() * root->getInverseWorldTransformMatrix());
				PhysicalObject::realize();
				return;
			}
		}

		// Get world velocities before we do the orphan transform trickery
		worldVel = getWorldVelocity();
		worldAngularVel = getWorldAngularVelocity();

		// We can't have a parent transform, since we update ours with ODE positions/rotations,
		// which are always in world coordinates, so let's reshuffle the transforms here..
		BaseObject *parent = getParent();
		if (parent) {
			// Transform our matrix to world coordinates
			parentOffsetM = transform->getMatrix();
			osg::Matrix M = parent->getWorldTransformMatrix();
			transform->setMatrix(M * transform->getMatrix());
			// Add our transform to scenario root directly and remove from parent transform
			parent->getTransform()->removeChild(transform.get());
			while (parent->getParent())
				parent = parent->getParent();
			if (parent->getTransform()->getNumParents() > 0)
				parent->getTransform()->getParent(0)->addChild(transform.get());
			else
				dout(ERROR) << "DynamicPhysicalObject '" << getName() << "' has no parent's parent node\n";
			orphanTransform = true;
		}

		// In case position/velocities have been set before the body is realized
		body->realize();
		body->setTransformation(transform->getMatrix());
		body->setVelocity(worldVel);
		body->setAngularVelocity(worldAngularVel);

		if (getGeometry()) {
			getGeometry()->setBody(body.get());
			initNearCallback();
		}
		// Set body for child physical objects
		setBodyForGeometries(this,this);

		PhysicalObject::realize();
		updateTransformation();
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			Joint *joint = it->get();
			joint->updateAnchorsAndAxes();
		}
	}

	void DynamicPhysicalObject::unrealize()
	{
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		if (!isRealized())
			return;
		if (!body.valid())
			return PhysicalObject::unrealize();

		// Unrealize joints
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++)
			(*it)->unrealize();

		if (getGeometry())
			getGeometry()->setBody(NULL);

		body->unrealize();

		// Undo our transform reshuffling from realize()
		BaseObject *parent = getParent();
		if (orphanTransform && parent) {
			// Re-transform our matrix
			osg::Matrix invM = parent->getInverseWorldTransformMatrix();
			transform->setMatrix(transform->getMatrix() * invM);
			// Re-transform our velocities
			PhysicalObject::setVelocity(invM.getRotate() * PhysicalObject::getVelocity());
			PhysicalObject::setAngularVelocity(invM.getRotate() * PhysicalObject::getAngularVelocity());
			// Put our transform back below parent transform
			while (parent->getParent())
				parent = parent->getParent();
			if (parent->getTransform()->getNumParents() > 0)
				parent->getTransform()->getParent(0)->removeChild(transform.get());
			getParent()->getTransform()->addChild(transform.get());
		}
		orphanTransform = false;

		PhysicalObject::unrealize();
	}

	void DynamicPhysicalObject::setGeometry(moodyn::Geometry *newgeometry)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		PhysicalObject::setGeometry(newgeometry);
		if (body.valid())
			newgeometry->setBody(body.get());
	}

	void DynamicPhysicalObject::separateChild(BaseObject *child)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			if (joint_connections[it->get()] == child)
				(*it)->detach();
		}
		PhysicalObject::separateChild(child);
	}

	void DynamicPhysicalObject::update(const double dt)
	{
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);

		if (isRealized() && body.valid() && body->isRealized() && !getRoot()->isRemote()) {
			// Avoid ODE from crashing us but warn...
			if (body->getTransformation().isNaN()) {
				dout(ERROR) << "NaN transformation from ODE: object " << getName() << "\n";
				body->setVelocity(osg::Vec3(0,0,0));
				body->setAngularVelocity(osg::Vec3(0,0,0));
				body->setForce(osg::Vec3(0,0,0));
				body->setTorque(osg::Vec3(0,0,0));
				updateTransformation();
				return;
			}
			// Update position and velocity
			if (getParent() && !orphanTransform) {
				transform->setMatrix(body->getTransformation() * getParent()->getInverseWorldTransformMatrix());
				KinematicObject::setVelocity(body->getVelocity(true), true);
				KinematicObject::setAngularVelocity(body->getAngularVelocity(true), true);
				worldVel = body->getVelocity(false);
				worldAngularVel = body->getAngularVelocity(false);
			} else {
				transform->setMatrix(body->getTransformation());
				worldVel = body->getVelocity(false);
				worldAngularVel = body->getAngularVelocity(false);
				KinematicObject::setVelocity(worldVel, false);
				KinematicObject::setAngularVelocity(worldAngularVel, false);
			}
			setDirtyInverseWorldMatrix();
			setFrameInterpolation(false);
		} else
			setFrameInterpolation(true);

		if (switchingMode) {
			setRemoteMode(DYNAMIC, false);
			// Collision seems to get a little f-ed up if not all objects are dynamic...
			// so we switch to dynamic for the entire object hierarchy
			if (DynamicPhysicalObject *rbRoot = dynamic_cast<DynamicPhysicalObject*> (getRoot())) {
				if (rbRoot->getRemoteMode() != DYNAMIC) {
					rbRoot->setRemoteMode(DYNAMIC);
					dout(5) << "Switching " << rbRoot->getName() << " to dynamic remote mode\n";
				}
			}
			//if (getOwner() != moonet::Client::me())
			if (!getOwner())
				setOwner(moonet::Client::me());
			switchingMode = false;
		}

		PhysicalObject::update(dt);

	}

	void DynamicPhysicalObject::addJoint(Joint *joint, DynamicPhysicalObject *conn)
	{
		joints.push_back(joint);
		ComponentContainer::addComponent(joint);
		connectJoint(joint, conn);
	}

	void DynamicPhysicalObject::addJoint(const moodyn::Joint::JointType type, BaseObject *connection)
	{
		osg::ref_ptr<Joint> joint = new Joint(type);
		joint->attach(getBody());
		DynamicPhysicalObject *rbobject = dynamic_cast<DynamicPhysicalObject*> (connection);
		osg::Vec3 r;
		if (connection)
			r = connection->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		if (rbobject) {
			/// If the object specified in \a connection is a DynamicPhysicalObject, set joint anchor in between the two objects.
			joint->setAnchor(getWorldTransformMatrix().getTrans()+r*0.5, false);
			osg::Vec3 v = r;
			v.normalize();
			osg::Vec3 v2 = v ^ osg::Vec3(0,0,1);
			joint->setAxis(v2, false);
			joint->setAxis2(v ^ v2, false);
			addJoint(joint.get(), rbobject);
		} else {
			/// Otherwise, if \a connection is specified, set joint anchor on the other object.
			/// If no \a connection is specified, anchor/axis has to be set programatically after the call to this method
			if (connection) {
				joint->setAnchor(getWorldTransformMatrix().getTrans()+r, false);
				osg::Vec3 v = connection->getPosition() - getPosition();
				v.normalize();
				osg::Vec3 v2 = v ^ osg::Vec3(0,0,1);
				joint->setAxis(v2, false);
				joint->setAxis2(v ^ v2, false);
			}
			addJoint(joint.get());
		}
	}

	unsigned int DynamicPhysicalObject::getNumJoints() { return joints.size(); }

	Joint* DynamicPhysicalObject::getJoint(const unsigned int index)
	{
		if (index >= joints.size())
			return NULL;
		return joints[index].get();
	}

	void DynamicPhysicalObject::removeJoint(Joint *joint, bool otherSide)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			if (*it == joint) {
				/// \todo Should joint also be removed from connected DynamicPhysicalObject?
				// I think yes...
				if (otherSide && joint_connections[joint]) {
					for (JointList::iterator ito = joint_connections[joint]->joints.begin(); ito != joint_connections[joint]->joints.end(); ito++) {
						if (*ito == joint) {
							joint_connections[joint]->removeJoint(joint, false);
							break;
						}
					}
				}
				/// \todo Remove debug visualization
				// Remove joint
				joint->detach();
				joints.erase(it);
				return;
			}
		}
	}

	void DynamicPhysicalObject::removeJoints(const unsigned int index, const unsigned int num)
	{
		for (unsigned int i = 0; i < num; i++)
			removeJoint(joints[index].get());
	}

	DynamicPhysicalObject* DynamicPhysicalObject::getJointConnection(const unsigned int index)
	{
		if (index >= joints.size())
			return NULL;
		return joint_connections[joints[index].get()];
	}

	void DynamicPhysicalObject::setTransformMatrix(const osg::Matrix& M)
	{
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
		if (orphanTransform && getParent())
			PhysicalObject::setTransformMatrix(M * getParent()->getWorldTransformMatrix());
		else
			PhysicalObject::setTransformMatrix(M);
	}

	osg::Matrix DynamicPhysicalObject::getTransformMatrix() const
	{
		// Return matrix relative to parent, so that DynamicPhysicalObjects that are children to other objects behave the same
		if (orphanTransform && getParent())
			return transform->getMatrix() * osg::Matrix::inverse(getParent()->getWorldTransformMatrix());
		return transform->getMatrix();
	}

	void DynamicPhysicalObject::preUpdateTransformation(const bool parentUpdate)
	{
		if (orphanTransform && getParent() && parentUpdate)
			parentOffsetM =  getWorldTransformMatrix() * osg::Matrix::inverse(getParent()->getWorldTransformMatrix());
		PhysicalObject::preUpdateTransformation(parentUpdate);
	}

	void DynamicPhysicalObject::updateTransformation(const bool parentUpdate)
	{
		if (orphanTransform && getParent() && parentUpdate)
			transform->setMatrix(parentOffsetM * getParent()->getWorldTransformMatrix());

		PhysicalObject::updateTransformation(parentUpdate);

		if (!body.valid())
			return;

		body->setTransformation(getWorldTransformMatrix());
		body->enable();
		for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
			Joint *joint = it->get();
			// Update joint anchors/axes if the moved object is a child or connects to static
			if (joint->getBody1() == getBody() && (getParent() || !joint->getBody2())) {
				joint->updateAnchorsAndAxes();
				if (joint_connections[joint]) {
					joint_connections[joint]->removeDebugNode(joint_connections[joint]->jointDebugNodes[joint].get());
					joint_connections[joint]->setDisplayMode(joint_connections[joint]->getDisplayMode());
				}
			}
			if (!parentUpdate) {
				removeDebugNode(jointDebugNodes[joint].get());
			}
		}
		// Update debug visualization if needed
		setDisplayMode(getDisplayMode());
	}

	void DynamicPhysicalObject::stop(const bool recursive)
	{
		KinematicObject::stop(recursive);
		if (body.valid()) {
			body->setForce(osg::Vec3(0,0,0));
			body->setTorque(osg::Vec3(0,0,0));
			body->disable();
		}
	}

	void DynamicPhysicalObject::setDisplayMode(const unsigned int mode)
	{
		// Joint visualization needs to be done when realized, so that orientation to bodies can be figured out
		if (isRealized() && body.valid() && body->isRealized() && mode & DISPLAY_DEBUG && joints.size() > 0) {
			for (JointList::iterator it = joints.begin(); it != joints.end(); it++) {
				Joint *joint = it->get();
				if (jointDebugNodes[joint].valid())
					continue;
				if (joint->getBody1() == body.get()) {
					osg::Node *node = joint->createDebugNode(1);
					node->setUserData(it->get());
					addDebugNode(node);
					jointDebugNodes[joint] = node;
				} else if (joint->getBody2() == body.get() && joint->getBody2()->getUserData() == this) {
					osg::Node *node = joint->createDebugNode(2);
					node->setUserData(joint);
					addDebugNode(node);
					jointDebugNodes[joint] = node;
				}
			}
		}
		PhysicalObject::setDisplayMode(mode);
	}

	bool DynamicPhysicalObject::serialize(const bool full)
	{
		if (!body.valid()) {
			SERIALIZE_Bit(0);
			return PhysicalObject::serialize(full);
		}
		SERIALIZE_Bit(1);

		bool enabled = (body->isEnabled() || !body->isRealized());
		SERIALIZE_Bit(enabled);
		if (!full && !enabled)
			return true;
		SERIALIZE_Vec3(worldVel);
		if (getSerializeAngularVel()) {
			SERIALIZE_1();
			SERIALIZE_Vec3(worldAngularVel);
		} else
			SERIALIZE_0();
		return PhysicalObject::serialize(full);
	}

	void DynamicPhysicalObject::deserialize(const bool full, const double timediff)
	{
		if (!DESERIALIZE_Bit())
			return PhysicalObject::deserialize(full, timediff);
		bool enabled = DESERIALIZE_Bit();
		if (!enabled && !full) {
			body->disable();
			return;
		}
		DESERIALIZE_Vec3(worldVel);
		if (DESERIALIZE_Bit())
			DESERIALIZE_Vec3(worldAngularVel);
		PhysicalObject::deserialize(full, timediff);

		// Velocity coordinate frames will mismatch if a child is static
		// (linearVel and angularVel are in world coordinates copied directly from ODE)
		if (getParent() && remoteMode == STATIC) {
			osg::Vec3 vel = getParent()->getWorldTransformMatrix().getRotate().inverse() * worldVel;
			if (getParent()->asKinematic())
				vel -= getParent()->asKinematic()->getVelocity(true);
			KinematicObject::setVelocity(vel, false);
			KinematicObject::setAngularVelocity(osg::Vec3(0,0,0), false);
		}

		if (!enabled && body.valid())
			body->disable();
		else if (body.valid()) {
			body->setVelocity(worldVel);
			body->setAngularVelocity(worldAngularVel);
			if (orphanTransform) {
				KinematicObject::setVelocity(worldVel, false);
				KinematicObject::setAngularVelocity(worldAngularVel, false);
			}
		}
	}

	void DynamicPhysicalObject::onOwnerChange()
	{
		bool reRealize = isRealized();
		if (reRealize)
			unrealize();
		PhysicalObject::onOwnerChange();
		if (reRealize)
			realize();
	}

	/// \param recursive If set, the change is applied for children as well
	void DynamicPhysicalObject::setRemoteMode(const RemoteMode& mode, const bool recursive)
	{
		// Don't allow dynamic children of statics - set dynamic mode recursively for parent
		if (mode == DYNAMIC) {
			if (DynamicPhysicalObject *rbParent = dynamic_cast<DynamicPhysicalObject*> (getParent())) {
				if (rbParent->getRemoteMode() != DYNAMIC) {
					rbParent->setRemoteMode(DYNAMIC, true);
					return;
				}
			}
		}

		remoteMode = mode;

		bool reRealize = (isRealized());// && isRemote());
		if (reRealize)
			unrealize();
		if (recursive) {
			for (unsigned int i = 0; i < getNumChildren(); i++) {
				if (DynamicPhysicalObject *rbChild = dynamic_cast<DynamicPhysicalObject*> (getChild(i)))
					rbChild->setRemoteMode(mode, true);
			}
		}
		if (reRealize)
			realize();
	}

	bool DynamicPhysicalObject::isDynamic()
	{
		if (body.valid())
			return true;
		return PhysicalObject::isDynamic();
	}

	void DynamicPhysicalObject::setStatic(const bool value)
	{
		bool reRealize = isRealized();
		if (reRealize)
			unrealize();
		if (body.valid()) {
			if (value)
				body->setRealizeMode(SPECIFIC);
			else
				body->setRealizeMode(WITH_CONTAINER);
		}
		for (unsigned int i = 0; i < getNumChildren(); i++) {
			if (DynamicPhysicalObject *rbChild = dynamic_cast<DynamicPhysicalObject*> (getChild(i)))
				rbChild->setStatic(value);
		}
		if (reRealize)
			realize();
	}

	DynamicPhysicalObject::~DynamicPhysicalObject()
	{
		if (orphanTransform && getTransform()->getNumParents() > 0) {
			getTransform()->getParent(0)->removeChild(getTransform());
		}
		// Work-around for the cyclic reference created by setting user data to this...
		/*
		if (body.valid()) {
			ref(); ref();
			body->setUserData(NULL);
			unref_nodelete();
		}
		*/
	}

	bool DynamicPhysicalObject::onNear(PhysicalObject *other)
	{
		if (!getRoot()->isRemote()) {
			if (DynamicPhysicalObject *rbother = dynamic_cast<DynamicPhysicalObject*> (other)) {
				if (rbother->remoteModeSwitch && rbother->isRemote() && rbother->getRemoteMode() != DYNAMIC)
					rbother->switchingMode = true;
			}
		}
		return PhysicalObject::onNear(other);
	}

	void DynamicPhysicalObject::setBodyForGeometries(PhysicalObject *object, DynamicPhysicalObject *root)
	{
		for (unsigned int i = 0; i < object->getNumChildren(); i++) {
			PhysicalObject *child = dynamic_cast<PhysicalObject*> (object->getChild(i));
			if (child && !dynamic_cast<DynamicPhysicalObject*> (child) && child->getGeometry()) {
				child->getGeometry()->setBody(root->getBody(), child->getTransformMatrix());
				setBodyForGeometries(child, root);
			}
		}
	}

	void DynamicPhysicalObject::connectJoint(Joint *joint, DynamicPhysicalObject *conn)
	{
		if (joint->getBody1())
			return;
		DynamicPhysicalObject *connection = conn;
		// Use parsed joint connection if not specified
		if (!connection) {
			std::string name = joint->getConnectName();
			if (name.length() > 0) {
				BaseObject *obj = findRelated(name);
				if (!obj)
					dout(ERROR) << "Object '" << name << "' not found for connecting joint '" << joint->getName() << "' from '" << getName() << "'\n";
				else {
					connection = dynamic_cast<DynamicPhysicalObject*> (obj);
					if (!connection)
						dout(ERROR) << "Joint connection to wrong object type " << obj->libraryName() << "::" << obj->className() << " '" << name << "' cannot be made\n";
				}
			}
		}
		if (connection == this)
			return;
		if (connection) {
			connection->joints.push_back(joint);
			if (connection->getBody())
				joint->attach(getBody(), connection->getBody());
			joint_connections[joint] = connection;
		} else {
			// Connection not specified - connect to parent or static world
			DynamicPhysicalObject *dparent = dynamic_cast<DynamicPhysicalObject*> (getParent());
			if (dparent) {
				dparent->joints.push_back(joint);
				joint->attach(getBody(), dparent->getBody());
				joint_connections[joint] = dparent;
				dparent->joint_connections[joint] = this;
			} else
				joint->attach(getBody());
		}
		if (isRealized() && body.valid() && body->isRealized()) {
			joint->updateAnchorsAndAxes();
			joint->realize();
		}
	}

} // namespace
