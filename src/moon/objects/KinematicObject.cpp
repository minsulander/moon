#include "KinematicObject.h"
#include "moon/ObjectFactory.h"
#include "moon/SimulationManager.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include <moonet/SerializeMacros.h>
#include <osg/io_utils>

using namespace mlog;

namespace moon {
	
	REGISTER_Object_Alias(moon, KinematicObject, Kinematic);
	
	KinematicObject::KinematicObject()
	:	VisualObject(),
		linearVelIsRel(false),
		angularVelIsRel(false),
		resetLinearVelIsRel(false),
		resetAngularVelIsRel(false),
		serializeAngularVel(true),
		frameInterpolation(true),
		corrTime(0),
		animTime(0),
		animPaused(false),
		updateControlPoint(NULL),
		timestamp(0),
		lastHeightUpdate(0),
		heightUpdateStep(0.1),
		speedParam(new Parameter("speed")),
		rotspeedParam(new Parameter("rotspeed")),
		heightParam(new Parameter("height")),
		speedxParam(new Parameter("speed_x")),
		speedyParam(new Parameter("speed_y")),
		speedzParam(new Parameter("speed_z")),
		rotspeedxParam(new Parameter("rotspeed_x")),
		rotspeedyParam(new Parameter("rotspeed_y")),
		rotspeedzParam(new Parameter("rotspeed_z"))
	{
		addParameter(speedParam.get());
		addParameter(rotspeedParam.get());		
		addParameter(heightParam.get());
		addParameter(speedxParam.get());
		addParameter(speedyParam.get());
		addParameter(speedzParam.get());
		addParameter(rotspeedxParam.get());
		addParameter(rotspeedyParam.get());
		addParameter(rotspeedzParam.get());
	}
	
	KinematicObject::KinematicObject(const KinematicObject& object, const osg::CopyOp& copyop)
	:	VisualObject(object),
		linearVel(object.linearVel),
		angularVel(object.angularVel),
		linearVelIsRel(object.linearVelIsRel),
		angularVelIsRel(object.angularVelIsRel),
		resetLinearVel(object.linearVel),
		resetAngularVel(object.resetAngularVel),
		resetLinearVelIsRel(object.resetLinearVelIsRel),
		resetAngularVelIsRel(object.resetAngularVelIsRel),
		serializeAngularVel(object.serializeAngularVel),
		frameInterpolation(true),
		corrTime(0),
		animationPath(object.animationPath),
		animTime(object.animTime),
		animPaused(object.animPaused),
		updateControlPoint(NULL),
		timestamp(object.timestamp),
		lastHeightUpdate(0),
		heightUpdateStep(object.heightUpdateStep),
		speedParam(new Parameter(*object.speedParam.get())),
		rotspeedParam(new Parameter(*object.rotspeedParam.get())),
		heightParam(new Parameter(*object.heightParam.get())),
		speedxParam(new Parameter(*object.speedxParam.get())),
		speedyParam(new Parameter(*object.speedyParam.get())),
		speedzParam(new Parameter(*object.speedzParam.get())),
		rotspeedxParam(new Parameter(*object.rotspeedxParam.get())),
		rotspeedyParam(new Parameter(*object.rotspeedyParam.get())),
		rotspeedzParam(new Parameter(*object.rotspeedzParam.get()))
	{
		checkUpdateCallback();
		addParameter(speedParam.get());
		addParameter(rotspeedParam.get());
		addParameter(heightParam.get());
		addParameter(speedxParam.get());
		addParameter(speedyParam.get());
		addParameter(speedzParam.get());
		addParameter(rotspeedxParam.get());
		addParameter(rotspeedyParam.get());
		addParameter(rotspeedzParam.get());
	}
	
	void KinematicObject::parseXML(const TiXmlElement *element)
	{
		VisualObject::parseXML(element);
		//=== KinematicObject
		//=* alias: Kinematic
		//=* component: MotionModel
		//=See superclass VisualObject for more parameters.
		//=* element: vel value="(vector3)" rel="true|false" [meter/second]
		//=. Linear velocity, in relative/body coordinates (rel=true) or world coordinates (rel=false).
		setVelocity(XMLParser::parseVector3(element, "vel", "meter/second", true, linearVel),
						  XMLParser::parseBoolean(element, "vel", true, linearVelIsRel, "rel"));
		//=* element: angvel value="(vector3)" rel="true|false" [radian/second]
		//=. Angular velocity, in relative/body coordinates (rel=true) or world coordinates (rel=false).
		setAngularVelocity(XMLParser::parseVector3(element, "angvel", "radian/second", true, angularVel),
						   XMLParser::parseBoolean(element, "angvel", true, angularVelIsRel, "rel"));
		//=* element: remote angvel="true|false" (and other attribute, see VisualObject)
		XMLParser::parseBoolean(serializeAngularVel, element, "remote", "angvel");
		// Parse animation path
		//=* element: animation
		//=. Animation path. Specifies movement relative to a "home" position set the same way as for static objects.
		if (const TiXmlElement *animationElement = element->FirstChildElement("animation")) {
			animationPath = new osg::AnimationPath;
			//=** attribute: loopmode value="swing|loop|none"
			std::string loopmode = XMLParser::parseStringAttribute(animationElement, "loopmode", true, "loop");
			if (loopmode == "swing")
				animationPath->setLoopMode(osg::AnimationPath::SWING);
			else if (loopmode == "none")
				animationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
			//=** repeatable element: at t="(number)" [seconds, required] pos="(vector3)" [meter, required] att="(vector3)" [degree]
			//=. An animation control point. Several of these make up an animation. 
			for (const TiXmlElement *atElement = animationElement->FirstChildElement("at"); atElement; atElement = atElement->NextSiblingElement("at")) {
				double t = XMLParser::parseDoubleAttribute(atElement, "t");
				osg::Vec3 pos = XMLParser::parseVector3Attribute(atElement, "pos");
				osg::Vec3 att = XMLParser::parseVector3Attribute(atElement, "att", true, osg::Vec3(0,0,0));
				// attitude is specified in degrees
				if (att.length() > 1e-5)
					att *= (float)M_PI/180.f;
				osg::Quat rot = getMatrixFromEulerAngles(att).getRotate();
				animationPath->insert(t, osg::AnimationPath::ControlPoint(pos, rot));
			}
			//=** text: animation path as parsed by <tt>osg::AnimationPath::read()</tt>
			if (animationElement->GetText()) {
				std::stringstream ss(animationElement->GetText());
				animationPath->read(ss);
			}
			animationOriginMatrix = transform->getMatrix();
			dout(4) << "    animation\n";
		}
		checkUpdateCallback();
	}
	
	void KinematicObject::writeXML(TiXmlElement *element) const
	{
		osg::Matrix saveMatrix;
		if (animationPath.valid()) {
			saveMatrix = transform->getMatrix();
			transform->setMatrix(animationOriginMatrix);
		}
		VisualObject::writeXML(element);
		const KinematicObject *temp = dynamic_cast<const KinematicObject*> (getTemplate());
		
		// Write velocities
		if (!animationPath.valid()) {
			if (linearVel.length() > linear_threshold) {
				XMLParser::setVector3(element, "vel", linearVel);
				XMLParser::setBoolean(element, "vel", linearVelIsRel, "rel");
			}
			if (angularVel.length() > angular_threshold) {
				XMLParser::setVector3(element, "angvel", angularVel);
				XMLParser::setBoolean(element, "angvel", angularVelIsRel, "rel");
			}
		}
		
		if ((!temp && !serializeAngularVel) || (temp && serializeAngularVel != temp->serializeAngularVel))
			XMLParser::setBoolean(element, "remote", serializeAngularVel, "angvel");
		
		// Write animation
		if (animationPath.valid() && (!temp || animationPath != temp->animationPath)) {
			TiXmlElement *animationElement = new TiXmlElement("animation");
			switch (animationPath->getLoopMode()) {
				case osg::AnimationPath::SWING:
					animationElement->SetAttribute("loopmode","swing");
					break;
				case osg::AnimationPath::NO_LOOPING:
					animationElement->SetAttribute("loopmode","none");
					break;
				default: break;
			}
			/*
			std::stringstream ss;
			animationPath->write(ss);
			TiXmlText *text = new TiXmlText(ss.str());
			animationElement->LinkEndChild(text);
			 */
			const osg::AnimationPath::TimeControlPointMap& cpmap = animationPath->getTimeControlPointMap();
			for (osg::AnimationPath::TimeControlPointMap::const_iterator it = cpmap.begin(); it != cpmap.end(); it++) {
				TiXmlElement *atElement = new TiXmlElement("at");
				atElement->SetDoubleAttribute("t", it->first);
				std::stringstream ss;
				ss << it->second.getPosition();
				atElement->SetAttribute("pos", ss.str());
				ss.str("");
				ss << TransformObject::getEulerAnglesFromMatrix(osg::Matrix::rotate(it->second.getRotation()))*180.f/(float)M_PI;
				atElement->SetAttribute("att", ss.str());
				animationElement->LinkEndChild(atElement);
			}
			element->LinkEndChild(animationElement);
		}
		
		if (animationPath.valid())			
			transform->setMatrix(saveMatrix);
	}
	
	void KinematicObject::addComponent(Component *component)
	{
		if (MotionModel *mmodel = dynamic_cast<MotionModel*> (component))
			motionModel = mmodel;
		VisualObject::addComponent(component);
	}
	
	void KinematicObject::setAnimationPath(osg::AnimationPath *anim)
	{ 
		animationPath = anim;
		checkUpdateCallback();
	}
	osg::AnimationPath* KinematicObject::getAnimationPath() { return animationPath.get(); }
	
	/// @param controlPointIndex Index of control point to set transform matrix to
	void KinematicObject::setAnimationPaused(const bool paused, const int controlPointIndex)
	{
		animPaused = paused;
		if (animPaused && controlPointIndex >= 0) {
			osg::AnimationPath::TimeControlPointMap& cpmap = animationPath->getTimeControlPointMap();
			if (controlPointIndex < (int)cpmap.size()) {
				osg::AnimationPath::TimeControlPointMap::iterator it = cpmap.begin();
				for (int i = 0; i < controlPointIndex; i++)
					it++;
				animTime = it->first;
			}
			osg::Matrix M;
			animationPath->getMatrix(animTime, M);
			M *= animationOriginMatrix;
			transform->setMatrix(M);
			onTransformCallbackUpdate();
			linearVel = osg::Vec3(0,0,0);
			linearVelIsRel = false;
		}
	}
	
	/// @param controlPointIndex Index of control point to update, set to -1 to disable
	void KinematicObject::setTransformationUpdatesControlPoint(const int controlPointIndex)
	{
		const KinematicObject *temp = dynamic_cast<const KinematicObject*> (getTemplate());
		if (getTemplate() && temp->animationPath.valid() && animationPath == temp->animationPath)
			animationPath = new osg::AnimationPath(*temp->animationPath.get());
		if (controlPointIndex >= 0) {
			osg::AnimationPath::TimeControlPointMap& cpmap = animationPath->getTimeControlPointMap();
			if (controlPointIndex < (int)cpmap.size()) {
				osg::AnimationPath::TimeControlPointMap::iterator it = cpmap.begin();
				for (int i = 0; i < controlPointIndex; i++)
					it++;
				updateControlPoint = &(it->second);
			}
		} else
			updateControlPoint = NULL;
	}
	
	void KinematicObject::setVelocity(const osg::Vec3& vel, const bool relative)
	{
		linearVel = vel;
		linearVelIsRel = relative;
		
		// Set parameters
		speedParam->set(vel.length());
		if (speedxParam->isConnected() || speedyParam->isConnected() || speedzParam->isConnected()) {
			osg::Vec3 relvel = getVelocity(true);
			speedxParam->set(relvel.x());
			speedyParam->set(relvel.y());
			speedzParam->set(relvel.z());
		}
		
		checkUpdateCallback();
	}
	
	void KinematicObject::setAngularVelocity(const osg::Vec3& vel, const bool relative)
	{
		angularVel = vel;
		angularVelIsRel = relative;
		
		// Set parameters
		rotspeedParam->set(vel.length());
		if (rotspeedxParam->isConnected() || rotspeedyParam->isConnected() || rotspeedzParam->isConnected()) {
			osg::Vec3 relvel = getAngularVelocity(true);
			rotspeedxParam->set(relvel.x());
			rotspeedyParam->set(relvel.y());
			rotspeedzParam->set(relvel.z());
		}
		
		checkUpdateCallback();
	}
	
	osg::Vec3 KinematicObject::getVelocity(const bool relative) const
	{
		if (relative == linearVelIsRel)
			return linearVel;
		else if (relative)
			return getRotation().inverse()*linearVel;
		else
			return getRotation()*linearVel;
	}
	
	void KinematicObject::getVelocity(double& x, double& y, double& z, const bool relative) const
	{
		osg::Vec3 v = getVelocity(relative);
		x = v.x();
		y = v.y();
		z = v.z();
	}
	
	void KinematicObject::getVelocity(osg::Vec3& vel, bool& rel) const
	{
		vel = linearVel;
		rel = linearVelIsRel;
	}
	
	osg::Vec3 KinematicObject::getWorldVelocity() const
	{
		if (getParent() && getParent()->asKinematic())
			return getParent()->getWorldTransformMatrix().getRotate() * getVelocity(false)
			+ getParent()->asKinematic()->getWorldVelocity()
			+ getParent()->getWorldTransformMatrix().getRotate()*(getParent()->asKinematic()->getAngularVelocity(true) ^ getPosition());
		return getVelocity(false);
	}
	
	void KinematicObject::getWorldVelocity(double& x, double& y, double& z) const
	{
		osg::Vec3 v = getWorldVelocity();
		x = v.x();
		y = v.y();
		z = v.z();
	}
	
	osg::Vec3 KinematicObject::getAngularVelocity(const bool relative) const
	{
		if (relative == angularVelIsRel)
			return angularVel;
		else if (relative)
			return getRotation().inverse()*angularVel;
		else
			return getRotation()*angularVel;
	}
	
	void KinematicObject::getAngularVelocity(double& x, double& y, double& z, const bool relative) const
	{
		osg::Vec3 v = getAngularVelocity(relative);
		x = v.x();
		y = v.y();
		z = v.z();
	}
	
	void KinematicObject::getAngularVelocity(osg::Vec3& angvel, bool& rel) const
	{
		angvel = angularVel;
		rel = angularVelIsRel;
	}
	
	osg::Vec3 KinematicObject::getWorldAngularVelocity() const
	{
		if (getParent() && getParent()->asKinematic())
			return getParent()->asKinematic()->getWorldAngularVelocity() + getParent()->getWorldTransformMatrix().getRotate() * getAngularVelocity(false);
		return getAngularVelocity(false);
	}
	
	void KinematicObject::getWorldAngularVelocity(double& x, double& y, double& z) const
	{
		osg::Vec3 v = getWorldAngularVelocity();
		x = v.x();
		y = v.y();
		z = v.z();
	}
	
	void KinematicObject::requestPosition(const osg::Vec3& pos)
	{
		if (motionModel.valid())
			motionModel->setTargetPosition(pos);
		else
			setPosition(pos);
	}
	
	void KinematicObject::requestRotation(const osg::Quat& rot)
	{
		if (motionModel.valid())
			motionModel->setTargetRotation(rot);
		else
			setRotation(rot);
	}
	
	void KinematicObject::requestAttitude(const osg::Vec3& att)
	{
		if (motionModel.valid())
			motionModel->setTargetAttitude(att);
		else
			setAttitude(att);
	}
	
	void KinematicObject::requestVelocity(const osg::Vec3& vel, const bool relative)
	{
		if (motionModel.valid())
			motionModel->setTargetVelocity(vel, relative);
		else
			setVelocity(vel, relative);
	}
	
	void KinematicObject::requestAngularVelocity(const osg::Vec3& vel, const bool relative)
	{
		if (motionModel.valid())
			motionModel->setTargetAngularVelocity(vel, relative);
		else
			setAngularVelocity(vel, relative);
	}
	
	void KinematicObject::stop(const bool recursive)
	{
		setVelocity(0,0,0);
		setAngularVelocity(0,0,0);
		if (recursive) {
			for (unsigned int i = 0; i < getNumChildren(); i++)
				if (getChild(i)->asKinematic())
					getChild(i)->asKinematic()->stop(true);
		}
	}
	
	bool KinematicObject::isDynamic()
	{
		if (linearVel.length() > linear_threshold || angularVel.length() > angular_threshold || animationPath.valid())
			return true;
		return false;
	}
	
	void KinematicObject::reset()
	{
		setVelocity(resetLinearVel, resetLinearVelIsRel);
		setAngularVelocity(resetAngularVel, resetAngularVelIsRel);
		VisualObject::reset();
		animationOriginMatrix = transform->getMatrix();
		animTime = 0;
	}
	
	void KinematicObject::setResetState()
	{
		resetLinearVel = linearVel;
		resetLinearVelIsRel = linearVelIsRel;
		resetAngularVel = angularVel;
		resetAngularVelIsRel = angularVelIsRel;
		VisualObject::setResetState();
	}
	
	bool KinematicObject::serialize(const bool full)
	{
		// If we have a template with the an equal animation path, the client should have it too, so
		// we don't need to continuosly send position updates...
		if (getTemplate() && animationPath.valid() && animationPath == ((KinematicObject*)getTemplate())->animationPath) {
			SERIALIZE_1();
			// Send animation origin position/rotation instead of current position/rotation
			SERIALIZE_Vec3(animationOriginMatrix.getTrans());
			SERIALIZE_NQuat(animationOriginMatrix.getRotate());
			if (full)
				return VisualObject::serialize(full);
			else
				return true;
		} else
			SERIALIZE_0();
		if (linearVel.length() > linear_threshold) {
			SERIALIZE_1();
			SERIALIZE_Vec3(linearVel);
			SERIALIZE(linearVelIsRel);
		} else
			SERIALIZE_0();
		if (angularVel.length() > angular_threshold && serializeAngularVel) {
			SERIALIZE_1();
			SERIALIZE_Vec3(angularVel);
			SERIALIZE(angularVelIsRel);
		} else
			SERIALIZE_0();
		return VisualObject::serialize(full);
	}
	
	void KinematicObject::deserialize(const bool full, const double timediff)
	{
		bool animated = DESERIALIZE_Bit();
		if (animated) {
			osg::Vec3 pos;
			DESERIALIZE_Vec3(pos);
			osg::Quat rot;
			DESERIALIZE_NQuat(rot);
			if (full)
				VisualObject::deserialize(full, timediff);
			animationOriginMatrix.setTrans(pos);
			animationOriginMatrix.setRotate(rot);
			return;
		}
		if (DESERIALIZE_Bit()) {
			DESERIALIZE_Vec3(linearVel);
			DESERIALIZE(linearVelIsRel);
		} else
			linearVel = osg::Vec3(0,0,0);
		if (DESERIALIZE_Bit()) {
			DESERIALIZE_Vec3(angularVel);
			DESERIALIZE(angularVelIsRel);
		} else
			angularVel = osg::Vec3(0,0,0);

		// Save current position/rotation
		osg::Vec3 posBefore = transform->getMatrix().getTrans();
		osg::Quat rotBefore = transform->getMatrix().getRotate();
		// Get new position/rotation etc
		VisualObject::deserialize(full, timediff);
		
		// If this package arrived really late, reset correction and try again next time
		if (timediff > getAverageTimeDiff()*2.0) {
			corrTime = 0;
			return;
		}
		if (corrTime == 0 || timestamp - corrTime < getSerializationInterval()/2.0) {
			// No correction if receiving net updates very often
			corrLinearVel.set(0,0,0);
			corrNextRot.set(0,0,0,1);
		} else {
			// Setup position correction
			if (/*linearVel.length() > linear_threshold &&*/ (transform->getMatrix().getTrans() - posBefore).length() > linear_threshold) {
				osg::Vec3 posError = transform->getMatrix().getTrans() - posBefore;
				if (linearVelIsRel)
					posError += transform->getMatrix().getRotate() * linearVel * getAverageTimeDiff();
				else
					posError += linearVel * getAverageTimeDiff();
				corrLinearVel = posError / corrTimeStep;
				osg::Matrix M = transform->getMatrix();
				M.setTrans(posBefore);
				transform->setMatrix(M);
			} else
				corrLinearVel.set(0,0,0);
			// Setup rotation interpolation
			if (corrTime != 0)
				corrLastRot = corrNextRot;
			corrNextRot = transform->getMatrix().getRotate();
			osg::Matrix M = transform->getMatrix();
			M.setRotate(rotBefore);
			transform->setMatrix(M);
			// Apply angular velocity
			if (angularVel.length() > angular_threshold) {
				const osg::Vec3& a = angularVel;
				double dt = timestamp-corrTime+getAverageTimeDiff();
				if (angularVelIsRel) {
					osg::Quat rot;
					rot.makeRotate(a.x()*dt, osg::Vec3(1,0,0),
								   a.y()*dt, osg::Vec3(0,1,0),
								   a.z()*dt, osg::Vec3(0,0,1));
					corrNextRot = rot * corrNextRot;
				} else {
					osg::Quat rot;
					rot.makeRotate(a.x()*dt, osg::Vec3(1,0,0),
								   a.y()*dt, osg::Vec3(0,1,0),
								   a.z()*dt, osg::Vec3(0,0,1));
					corrNextRot = corrNextRot * rot;
				}
			}
		}
		corrTimeStep = timestamp - corrTime;
		corrTime = timestamp;

		checkUpdateCallback();
	}
	
	double KinematicObject::linear_threshold = 0.001;
	double KinematicObject::angular_threshold = 0.001;
	double KinematicObject::anim_velocity_timestep = 0.01;
	
	void KinematicObject::preUpdateTransformation(const bool parentUpdate)
	{
		VisualObject::preUpdateTransformation(parentUpdate);
	}
	
	void KinematicObject::updateTransformation(const bool parentUpdate)
	{
		VisualObject::updateTransformation(parentUpdate);
		if (!animationPath.valid())
			return;
		
		if (!parentUpdate && updateControlPoint) {
			osg::Matrix M = transform->getMatrix() * osg::Matrix::inverse(animationOriginMatrix);
			updateControlPoint->setPosition(M.getTrans());
			updateControlPoint->setRotation(M.getRotate());
		} else if (!parentUpdate && animationPath.valid()) {
			osg::Matrix M;
			animationPath->getMatrix(animTime, M);
			animationOriginMatrix = osg::Matrix::inverse(M) * transform->getMatrix();
		}
		//animationOriginMatrix = transform->getMatrix();
	}
	
	void KinematicObject::update(const double dt)
	{
		VisualObject::update(dt);
		if (heightParam->isConnected() && (lastHeightUpdate < 1e-5 || (isDynamic() && timestamp > 1e-5 &&  timestamp - lastHeightUpdate > heightUpdateStep))) {
			float hat;
			if (getHeightAboveTerrain(hat, false, 10000, 0.1)) {
				heightParam->set(hat);
				lastHeightUpdate = timestamp;
			}
		}
	}
	
	/// \return a very large positive number if height could not be obtained
	float KinematicObject::getHeight()
	{
		/// Re-uses value updated continuosly for height parameter if it is connected.
		if (heightParam->isConnected() && lastHeightUpdate > 1e-5)
			return heightParam->get();
		/// Otherwise calls BaseObject::getHeightAboveTerrain() with default parameters.
		float height;
		if (BaseObject::getHeightAboveTerrain(height, false, 10000, 0.1))
			return height;
		return 1e38;
	}
	
	void KinematicObject::checkUpdateCallback()
	{
		if (isDynamic()) {
			if (!transform->getUpdateCallback())
				transform->setUpdateCallback(new TransformCallback(this));
		} else {
			timestamp = 0;
			transform->setUpdateCallback(NULL);
		}
	}
	
	/** This callback extrapolates linear and angular velocity and updates the position and rotation
		of the transform matrix accordingly. If the KinematicObject has an animation path, it is used
		for position/rotation updates instead. */
	void KinematicObject::TransformCallback::operator() (osg::Node *node, osg::NodeVisitor *nv)
	{
		if (!object)
			return;
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(object->updateMutex);
		
		// Check that it is a proper visitor
		if (nv->getVisitorType() != osg::NodeVisitor::UPDATE_VISITOR || !nv->getFrameStamp()
			|| !node->asTransform() || !node->asTransform()->asMatrixTransform())
			return;
		
		// Don't move if we're paused
		if (SimulationManager::instance().isPaused()) {
			if (!object->animationPath.valid())
				object->timestamp = 0;
			return;
		}

		double nowtime = nv->getFrameStamp()->getSimulationTime();
		osg::MatrixTransform *xform = (osg::MatrixTransform*) node;
		
		bool updated = false;
		
		if (object->animationPath.valid()) {
			if (!object->animPaused) {
				osg::Matrix M;
				object->animTime = nowtime + SimulationManager::instance().getGameTimeOffset() - SimulationManager::instance().getViewerTimeOffset();
				object->animationPath->getMatrix(object->animTime, M);
				osg::Matrix oldM;
				object->animationPath->getMatrix(object->animTime - anim_velocity_timestep, oldM);
				M *= object->animationOriginMatrix;
				oldM *= object->animationOriginMatrix;
				xform->setMatrix(M);
				// Set linear velocity to smoothen things out if server has animation but client does not
				object->linearVel = (M.getTrans()-oldM.getTrans()) / anim_velocity_timestep;
				object->linearVelIsRel = false;
				// Set angular velocity
				osg::Quat drot = oldM.getRotate().inverse()*M.getRotate();
				double a;
				osg::Vec3 v;
				drot.getRotate(a,v);
				object->angularVel = v * a / anim_velocity_timestep;
				object->angularVelIsRel = false;
				updated = true;
			}
		} else if (object->timestamp > 0) {
			double dt = nowtime - object->timestamp;
			if (firstUpdate) {
				// Assume somewhat same delta time from last timestep for first update
				dt *= 2.0;
				firstUpdate = false;
			}
			osg::Vec3 v = object->linearVel * SimulationManager::instance().getTimeScale();
			double vl = v.length();
			osg::Vec3 a = object->angularVel * SimulationManager::instance().getTimeScale();
			double al = a.length();
			
			osg::Matrix M = xform->getMatrix();
			// Apply velocities
			if (object->frameInterpolation && (vl > linear_threshold || al > angular_threshold)) {
				// Apply linear velocity
				if (vl > linear_threshold) {
					if (object->linearVelIsRel) 
						M.preMult(osg::Matrix::translate(v*dt));
					else
						M.setTrans(M.getTrans() + v*dt);
					updated = true;
				}
				// Apply angular velocity
				if (object->corrNextRot.zeroRotation() && al > angular_threshold) {
					if (object->angularVelIsRel) {
						M.preMult(osg::Matrix::rotate(a.x()*dt, osg::Vec3(1,0,0),
													  a.y()*dt, osg::Vec3(0,1,0),
													  a.z()*dt, osg::Vec3(0,0,1)));
					} else {
						osg::Quat rot;
						rot.makeRotate(a.x()*dt, osg::Vec3(1,0,0),
									   a.y()*dt, osg::Vec3(0,1,0),
									   a.z()*dt, osg::Vec3(0,0,1));
						M.setRotate(M.getRotate() * rot);
					}
					updated = true;
				}
			}
			// Apply corrections (for network updates)
			if (object->corrTime != 0) {
				if ((nowtime - object->corrTime) > 3.0*object->corrTimeStep) {
					// Time-out corrections if we haven't received updates for a while
					object->corrNextRot.set(0,0,0,1);
					object->corrLinearVel.set(0,0,0);
					object->corrTime = 0;
					object->linearVel.set(0,0,0);
					object->angularVel.set(0,0,0);
				} else {
					if (object->corrLinearVel.length() > linear_threshold) {
						M.setTrans(M.getTrans() + object->corrLinearVel*dt);
					}
					if (!object->corrNextRot.zeroRotation()) {
						if (object->corrLastRot.zeroRotation())
							M.setRotate(object->corrNextRot);
						else {
							osg::Quat rot;
							rot.slerp((nowtime - object->corrTime) / object->corrTimeStep, object->corrLastRot, object->corrNextRot);
							M.setRotate(rot);
						}
					}
					updated = true;
				}
			}
			if (updated)
				xform->setMatrix(M);
		} else if (object->timestamp <= 0) {
			// First update - save it for next timestep
			firstUpdate = true;
		}
		object->timestamp = nowtime;
		if (updated)
			object->onTransformCallbackUpdate();
		nv->traverse(*node);
	}

} // moon
