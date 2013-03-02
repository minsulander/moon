#include "SimpleMotion.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include <mlog/Log.h>
#include <osg/io_utils>

using namespace mlog;

namespace moon {

	REGISTER_Object(moon, SimpleMotion);

	SimpleMotion::SimpleMotion()
	: MotionModel(),
	linearAcc(0.f),
	angularAcc(0.f),
	speed(0.f),
	rotationSpeed(0.f)
	{
	}
	
	SimpleMotion::SimpleMotion(const SimpleMotion& source, const osg::CopyOp& copyop)
	: MotionModel(source, copyop),
	linearAcc(source.linearAcc),
	angularAcc(source.angularAcc),
	speed(source.speed),
	rotationSpeed(source.rotationSpeed)
	{
	}
	
	void SimpleMotion::parseXML(const TiXmlElement *element)
	{
		//=== SimpleMotion
		//=* superclass: MotionModel
		double value;
		//=* attribute: acc="(number)"
		//=. Linear acceleration
		if (XMLParser::parseDoubleAttribute(value, element, "acc"))
			linearAcc = value;
		//=* attribute: angacc="(number)" [degrees/second^2]
		//=. Angular acceleration
		if (XMLParser::parseDoubleAttribute(value, element, "angacc"))
			angularAcc = value*M_PI/180.0;
		//=* attribute: speed="(number)"
		//=. Maximum speed used to reach requested position
		if (XMLParser::parseDoubleAttribute(value, element, "speed"))
			speed = value;
		//=* attribute: rotspeed="(number)" [degrees/second]
		//=. Maximum rotational speed used to reach requested rotation/attitude
		if (XMLParser::parseDoubleAttribute(value, element, "rotspeed"))
			rotationSpeed = value*M_PI/180.0;
		MotionModel::parseXML(element);
	}
	
	void SimpleMotion::writeXML(TiXmlElement *element) const
	{
		MotionModel::writeXML(element);
	}
	
	void SimpleMotion::realize()
	{
		object = dynamic_cast<moon::KinematicObject*> (getContainer());
		if (!object) {
			dout(ERROR) << className() << " '" << getName() << "' is a component of non-kinematic object\n";
			return;
		}
	}
	
	void SimpleMotion::update(const double dt)
	{
		if (object.valid()) {
			if (positionSet) {
				osg::Vec3 actualPos = object->getPosition();
				osg::Vec3 actualVel = object->getVelocity();
				osg::Vec3 error = actualPos - targetPosition;
				if (speed < 1e-5 || error.length() <= actualVel.length()*dt) {
					object->setPosition(targetPosition);
					object->setVelocity(osg::Vec3(0,0,0));
					linearVelSet = false;
					positionSet = false;
				} else {
					if (linearAcc > 1e-5 && error.length() <= actualVel.length2()/(linearAcc*2.f))
						setTargetVelocity(osg::Vec3(0,0,0));
					else {
						osg::Vec3 errorn = error;
						errorn.normalize();
						setTargetVelocity(-errorn*speed);
					}
				}
			}
			if (rotationSet) {
				osg::Quat actualRot = object->getRotation();
				osg::Vec3 actualVel = object->getAngularVelocity();
				osg::Quat error = targetRotation.inverse()*actualRot;
				double angle;
				osg::Vec3 vec;
				error.getRotate(angle, vec);
				if (angle > M_PI) {
					angle = angle-2.0*M_PI;
					vec = -vec;
				}
				vec.normalize();
				if (rotationSpeed < 1e-5 || fabs(angle) <= actualVel.length()*dt*2.0) {
					object->setRotation(targetRotation);
					object->setAngularVelocity(osg::Vec3(0,0,0));
					angularVelSet = false;
					rotationSet = false;
				} else {
					if (angularAcc > 1e-5 && fabs(angle) <= actualVel.length2()/(angularAcc*2.f))
						setTargetAngularVelocity(osg::Vec3(0,0,0));
					else {
						setTargetAngularVelocity(-vec*rotationSpeed);
					}
				}
			}
			if (linearVelSet) {
				osg::Vec3 actualVel = object->getVelocity(targetLinearVelIsRel);
				osg::Vec3 error = actualVel-targetLinearVel;
				if (linearAcc < 1e-5 || error.length() < linearAcc*dt) {
					object->setVelocity(targetLinearVel, targetLinearVelIsRel);
					linearVelSet = false;
				} else {
					osg::Vec3 errorn = error;
					errorn.normalize();
					actualVel -= errorn*linearAcc*dt;
					object->setVelocity(actualVel, targetLinearVelIsRel);
				}
			}
			if (angularVelSet) {
				osg::Vec3 actualVel = object->getAngularVelocity(targetAngularVelIsRel);
				osg::Vec3 error = actualVel-targetAngularVel;
				if (angularAcc < 1e-5 || error.length() < angularAcc*dt) {
					object->setAngularVelocity(targetAngularVel, targetAngularVelIsRel);
					angularVelSet = false;
				} else {
					osg::Vec3 errorn = error;
					errorn.normalize();
					actualVel -= errorn*angularAcc*dt;
					object->setAngularVelocity(actualVel, targetAngularVelIsRel);
				}
			}
		}
		MotionModel::update(dt);
	}

} // namespace
