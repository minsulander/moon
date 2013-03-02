#include "Buggy.h"
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <osg/io_utils>

using namespace moon;
using namespace mlog;

namespace moodyn {

	REGISTER_Object_Alias(moodyn, Buggy, Buggy);
	
	Buggy::Buggy()
	:	DynamicVehicle(),
		ModifierContainer(),
		maxturnspeed(1.0),
		maxturndeflection(0.3),
                turngain(10),
		maxrollspeed(25),
		swayForce(0),
		maxSwayForce(0),
		brakeTorque(0),
		maxDriveTorque(0),
		dragTorque(0),
		aeroLoad(0),
		wheeltrack(2),
		wheelbase(3)
	{
		driveParam = new Parameter("drive", this);
		driveTorqueParam = new Parameter("drivetorque", this);
		driveRotSpeedParam = new Parameter("driverotspeed", this);
		turnControl = new ListenerControl("Strafe",Control::AXIS,this);
		driveControl = new ListenerControl("Move",Control::AXIS,this);
		brakeControl = new ListenerControl("Brake",Control::MOMENTARY,this);
		fireControl = new ListenerControl("Fire",Control::MOMENTARY,this);
		flipControl = new ListenerControl("Reset",Control::MOMENTARY,this);
	}
	
	Buggy::Buggy(const Buggy& other, const osg::CopyOp& copyop)
	:	DynamicVehicle(other, copyop),
		ModifierContainer(other, copyop),
		maxturnspeed(other.maxturnspeed),
		maxturndeflection(other.maxturndeflection),
		turngain(other.turngain),
		maxrollspeed(other.maxrollspeed),
		swayForce(other.swayForce),
		maxSwayForce(other.maxSwayForce),
		brakeTorque(other.brakeTorque),
		maxDriveTorque(other.maxDriveTorque),
		dragTorque(other.dragTorque),
		aeroLoad(other.aeroLoad),
		wheeltrack(other.wheeltrack),
		wheelbase(other.wheelbase)
	{
		driveParam = new Parameter("drive", this);
		driveTorqueParam = new Parameter("drivetorque", this);
		driveRotSpeedParam = new Parameter("driverotspeed", this);
		turnControl = new ListenerControl("Strafe",Control::AXIS,this);
		driveControl = new ListenerControl("Move",Control::AXIS,this);
		brakeControl = new ListenerControl("Brake",Control::MOMENTARY,this);
		fireControl = new ListenerControl("Fire",Control::MOMENTARY,this);
		flipControl = new ListenerControl("Reset",Control::MOMENTARY,this);
	}
	
	void Buggy::parseXML(const TiXmlElement* element)
	{
		DynamicVehicle::parseXML(element);
		maxturnspeed = XMLParser::parseDouble(element,"turnspeed","radian/second",true,maxturnspeed);
		maxturndeflection = XMLParser::parseDouble(element,"turnmax","radian",true,maxturndeflection);
		turngain = XMLParser::parseDouble(element,"turngain","",true,turngain);
		maxrollspeed = XMLParser::parseDouble(element,"rollmax","radian/second",true,maxrollspeed);
		swayForce = XMLParser::parseDouble(element,"swayforce","N/m",true,swayForce);
		maxSwayForce = XMLParser::parseDouble(element,"maxswayforce","N",true,maxSwayForce);
		brakeTorque = XMLParser::parseDouble(element,"brake","N m",true,brakeTorque);
		maxDriveTorque = XMLParser::parseDouble(element,"drive","N m",true,maxDriveTorque);
		dragTorque = XMLParser::parseDouble(element,"drag","N m",true,dragTorque);
		aeroLoad = XMLParser::parseDouble(element,"aeroload","N s",true,aeroLoad);
		
		// Parse modifiers
		//=* modifier targets: drivetorque (vs rotspeed) [N m], steerangle (vs speed) [deg], rearsteerangle (vs speed) [deg]
		ModifierContainer::parseXML(element);
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			std::string target = mod->getTargetName();
			if (target == "drivetorque")
				mod->setTargetIndex(DRIVE_TORQUE);
			else if (target == "steerangle")
				mod->setTargetIndex(STEER_ANGLE);
			else if (target == "rsteerangle")
				mod->setTargetIndex(REAR_STEER_ANGLE);
		}
	}
	
	void Buggy::writeXML(TiXmlElement *element) const
	{
		DynamicVehicle::writeXML(element);
		/// \todo Implement
	}
	
	void Buggy::initialize()
	{
		DynamicVehicle::initialize();
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			switch(mod->getTargetIndex()) {
				case DRIVE_TORQUE: driveTorqueModifier = mod; break;
				case STEER_ANGLE: steerAngleModifier = mod; break;
				case REAR_STEER_ANGLE: rearSteerAngleModifier = mod; break;
			}
		/*
			if (Parameter *param = object->findParameter(mod->getName())) {
				mod->setParameter(param);
				dout(5) << "Buggy modifer " << object->getName() << ":" << mod->getName() << " connected\n";
			} else
				dout(5) << "No connection for buggy modifier " << object->getName() << ":" << mod->getName() << "\n";
		*/
		}
		osg::BoundingBox wheelsbbox;
		for (unsigned int i = 0; i < getNumJoints(); i++) {
			moodyn::Joint* joint = getJoint(i);
			DynamicPhysicalObject *other = getJointConnection(i);
			if (!other)
				continue;
			dout(4) << "Initializing " << getName() << "\n";
			// Find wheels
			if (other->hasTag("wheel")) {
				wheelJoints.push_back(joint);
				if (other->hasTag("drive")) {
					driveJoints.push_back(joint);
					joint->initFeedback();
				}
				if (other->hasTag("brake"))
					brakeJoints.push_back(joint);
				if (other->hasTag("steer"))
					steerJoints.push_back(joint);
				if (other->hasTag("rsteer"))
					rearSteerJoints.push_back(joint);
				wheelsbbox.expandBy(other->getPosition());
			}
			dout(4) << "  " << wheelJoints.size() << " wheels\n";
			osg::Vec3 anchor = joint->getAnchor();
			// Find opposite joints used for anti-sway forces
			for (unsigned int j = 0; j < getNumJoints(); j++) {
				if (i == j)
					continue;
				osg::Vec3 anchor2 = getJoint(j)->getAnchor();
				if (fabs(anchor.x() + anchor2.x()) < 1e-5 && fabs(anchor.y() - anchor2.y()) < 1e-5) {
					dout(5) << getJointConnection(i)->getName() << " is opposite of "
						<< getJointConnection(j)->getName() << "\n";
					oppositeJoint[joint] = getJoint(j);
				}
			}
		}
		wheeltrack = wheelsbbox.xMax()-wheelsbbox.xMin();
		wheelbase = wheelsbbox.yMax()-wheelsbbox.yMin();
		dout(4) << "  track " << wheeltrack << " base " << wheelbase << "\n";
	}
	
	void Buggy::realize()
	{
		DynamicVehicle::realize();
		DynamicPhysicalObject *ammo = dynamic_cast<DynamicPhysicalObject*> (getChildByTag("ammo"));
		if (ammo) {
			ammo->unrealize();
			ammo->hide();
		}
		driveParam->set(0);
	}
	
	void Buggy::unrealize()
	{
		DynamicVehicle::unrealize();
	}
	
	void Buggy::update(const double dt)
	{
		if (!isRemote()) {
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
			
			osg::Vec3 vel = getVelocity(true);

			float rotspeed = 0;
			float driveTorque = 0;
			
			// Turning

			float turnsign = (turnControl->getValue() > 0 ? 1.0 : -1.0);
			float turninner = fabs(turnControl->getValue())*maxturndeflection;
			float turninnerRear = turninner;

			if (steerAngleModifier.valid())
				turninner = turninnerRear = fabs(turnControl->getValue()) * steerAngleModifier->calculate(vel.y())*M_PI/180.0;
			float turnouter = atan(1.0/(wheeltrack/wheelbase+1.0/tan(turninner)));
			if (rearSteerAngleModifier.valid())
				turninnerRear = fabs(turnControl->getValue()) * rearSteerAngleModifier->calculate(vel.y())*M_PI/180.0;
			float turnouterRear = atan(1.0/(wheeltrack/wheelbase+1.0/tan(turninnerRear)));

			for (JointList::iterator it = steerJoints.begin(); it != steerJoints.end(); it++) {
				moodyn::Joint *joint = it->get();
				if (!joint) continue;
				// outer wheel has smaller angle - the ackerman steering condition
				float turn = turnsign*turninner;
				if ((turn > 0 && joint->getBody2()->getPosition().x() < 0) || (turn < 0 && joint->getBody2()->getPosition().x() > 0))
					turn = turnsign*turnouter;
				float turnerr = turn - joint->getDeflection();
				if (turnerr > 0) {
					joint->setParameter(moodyn::Joint::HISTOP, turn);
					joint->setParameter(moodyn::Joint::LOSTOP, turn);
				} else {
					joint->setParameter(moodyn::Joint::LOSTOP, turn);
					joint->setParameter(moodyn::Joint::HISTOP, turn);
				}
			}
			
			for (JointList::iterator it = rearSteerJoints.begin(); it != rearSteerJoints.end(); it++) {
				moodyn::Joint *joint = it->get();
				if (!joint) continue;
				float turn = -turnsign*turninnerRear;
				if ((turn > 0 && joint->getBody2()->getPosition().x() < 0) || (turn < 0 && joint->getBody2()->getPosition().x() > 0))
					turn = -turnsign*turnouterRear;
				float turnerr = turn - joint->getDeflection();
				if (turnerr > 0) {
					joint->setParameter(moodyn::Joint::HISTOP, turn);
					joint->setParameter(moodyn::Joint::LOSTOP, turn);
				} else {
					joint->setParameter(moodyn::Joint::LOSTOP, turn);
					joint->setParameter(moodyn::Joint::HISTOP, turn);
				}
			}

			// Drive
			
			for (JointList::iterator it = driveJoints.begin(); it != driveJoints.end(); it++) {
				moodyn::Joint *joint = it->get();
				if (!joint) continue;
				float omega = -joint->getBody2()->getAngularVelocity(true).x();
				float maxtorque = maxDriveTorque;
				if (driveTorqueModifier.valid())
					maxtorque = driveTorqueModifier->calculate(omega);
				if (maxtorque > 1e-5) {
					if (omega < maxrollspeed) {
						float Q = driveControl->getValue()*maxtorque;
						joint->addForce(0,Q);
						driveTorque += -Q;
					}
					joint->setParameter(moodyn::Joint::MAXFORCE2, dragTorque);
				} else {
					driveTorque += -joint->getTorque2()*joint->getAxis2();
					joint->setParameter(moodyn::Joint::VELOCITY2,driveControl->getValue()*maxrollspeed);
				}
				rotspeed += omega;
			}
			
			driveTorqueParam->set(driveTorque);
			if (driveJoints.size() > 0)
				driveRotSpeedParam->set(rotspeed/(float)driveJoints.size());
				
			// Brake

			for (JointList::iterator it = brakeJoints.begin(); it != brakeJoints.end(); it++) {
				moodyn::Joint *joint = it->get();
				if (!joint) continue;
				joint->setParameter(moodyn::Joint::MAXFORCE2, brakeControl->getValue()*brakeTorque);
				joint->setParameter(moodyn::Joint::VELOCITY2, 0);
			}
				

			// Aero-load
			if (fabs(aeroLoad) > 1e-5) {
				float v2 = vel.y()*vel.y();
				getBody()->addForce(osg::Vec3(0, 0, aeroLoad*v2));
			}
			
			// Anti-sway
			if (swayForce > 1e-5 && maxSwayForce > 1e-5) {
				for (JointList::iterator it = wheelJoints.begin(); it != wheelJoints.end(); it++) {
					moodyn::Joint *joint = it->get();
					moodyn::Joint *opposite = oppositeJoint[joint];
					if (!joint || !opposite) continue;
					osg::Vec3 anchor2 = joint->getAnchor2World();
					osg::Vec3 anchor = joint->getAnchorWorld();
					osg::Vec3 axis = joint->getAxis(false);
					float displacement = (anchor-anchor2) * axis;
					if (displacement > 0) {
						float F = displacement * swayForce;
						if (maxSwayForce > 1e-5 && F > maxSwayForce)
							F = maxSwayForce;
						joint->getBody2()->addForce(-axis*F);
						joint->getBody1()->addForceAt(axis*F, false, joint->getBody2()->getPosition(), false);
						opposite->getBody2()->addForce(axis*F);
						opposite->getBody1()->addForceAt(-axis*F, false, opposite->getBody2()->getPosition(), false);
					}
				}
			}
			
		}
		DynamicVehicle::update(dt);
	}
	
	void Buggy::controlUpdate(Control *control)
	{
		DynamicVehicle::controlUpdate(control);
		if (getBody())
			getBody()->enable();
		if (control == fireControl.get() && control->getValue()) {
			DynamicPhysicalObject *ammo = dynamic_cast<DynamicPhysicalObject*> (getChildByTag("ammo"));
			if (ammo) {
				ammo->reset();
				ammo->setVelocity(osg::Vec3(0,40,-2),true);
				ammo->setAngularVelocity(osg::Vec3(0,0,0));
				ammo->show();
				ammo->realize();
			} else
				dout(ERROR) << "Buggy '" << getName() << "' has no ammo\n";
		}
		if (control == flipControl.get() && control->getValue()) {
			setVelocity(0,0,0,false);
			setAngularVelocity(0,0,0,false);
			alignToTerrain();
			clampToTerrain();
			for (unsigned int i = 0; i < getNumChildren(); i++)
				getChild(i)->reset();
			//move(0,0,1);
		}
		driveParam->set(driveControl->getValue());
	}
	
} // namespace
