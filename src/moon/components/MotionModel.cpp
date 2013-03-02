#include "MotionModel.h"
#include <mdraw/utils.h>

namespace moon {

	MotionModel::MotionModel()
	: Component(),
	targetLinearVelIsRel(false),
	targetAngularVelIsRel(false),
	positionSet(false),
	rotationSet(false),
	linearVelSet(false),
	angularVelSet(false)
	{
	}
	
	MotionModel::MotionModel(const MotionModel& source, const osg::CopyOp& copyop)
	: Component(source, copyop),
	targetPosition(source.targetPosition),
	targetRotation(source.targetRotation),
	targetLinearVel(source.targetLinearVel),
	targetAngularVel(source.targetAngularVel),
	targetLinearVelIsRel(source.targetLinearVelIsRel),
	targetAngularVelIsRel(source.targetAngularVelIsRel),
	positionSet(source.positionSet),
	rotationSet(source.rotationSet),
	linearVelSet(source.linearVelSet),
	angularVelSet(source.angularVelSet)
	{
	}
	
	void MotionModel::parseXML(const TiXmlElement *element)
	{
		//=== MotionModel
		Component::parseXML(element);
	}
	
	void MotionModel::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
	}
	
	void MotionModel::setTargetPosition(const osg::Vec3& pos)
	{
		targetPosition = pos;
		positionSet = true;
	}
	
	const osg::Vec3& MotionModel::getTargetPosition() const
	{
		return targetPosition;
	}
	
	void MotionModel::setTargetRotation(const osg::Quat& quat)
	{
		targetRotation = quat;
		rotationSet = true;
	}
	
	const osg::Quat& MotionModel::getTargetRotation() const
	{
		return targetRotation;
	}
	
	void MotionModel::setTargetAttitude(const osg::Vec3& att)
	{
		setTargetRotation(mdraw::getQuatFromEulerAngles(att));
	}
	
	osg::Vec3 MotionModel::getTargetAttitude() const
	{
		return mdraw::getEulerAnglesFromQuat(getTargetRotation());
	}
	
	void MotionModel::setTargetVelocity(const osg::Vec3& vel, const bool relative)
	{
		targetLinearVel = vel;
		targetLinearVelIsRel = relative;
		linearVelSet = true;
	}
	
	osg::Vec3 MotionModel::getTargetVelocity(const bool relative) const
	{
		if (relative == targetLinearVelIsRel)
			return targetLinearVel;
		else if (relative)
			return getTargetRotation().inverse()*targetLinearVel;
		else
			return getTargetRotation()*targetLinearVel;
	}

	void MotionModel::setTargetAngularVelocity(const osg::Vec3& vel, const bool relative)
	{
		targetAngularVel = vel;
		targetAngularVelIsRel = relative;
		angularVelSet = true;
	}
	
	osg::Vec3 MotionModel::getTargetAngularVelocity(const bool relative) const
	{
		if (relative == targetAngularVelIsRel)
			return targetAngularVel;
		else if (relative)
			return getTargetRotation().inverse()*targetAngularVel;
		else
			return getTargetRotation()*targetAngularVel;
	}

}
