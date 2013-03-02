#ifndef MOON_MOTIONMODEL_H
#define MOON_MOTIONMODEL_H

#include "Component.h"
#include <osg/Vec3>
#include <osg/Quat>

namespace moon {

	class MOON_EXPORT MotionModel : public Component {
	public:
		MotionModel();
		MotionModel(const MotionModel& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, MotionModel);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		void setTargetPosition(const osg::Vec3& pos);
		const osg::Vec3& getTargetPosition() const;
		bool isTargetPositionSet() const { return positionSet; }
		
		void setTargetRotation(const osg::Quat& quat);
		const osg::Quat& getTargetRotation() const;
		bool isTargetRotationSet() const { return rotationSet; }
		
		void setTargetAttitude(const osg::Vec3& att);
		osg::Vec3 getTargetAttitude() const;
		
		bool isNavigating() const { return positionSet || rotationSet; }
		
		void setTargetVelocity(const osg::Vec3& vel, const bool relative = false);
		osg::Vec3 getTargetVelocity(const bool relative = false) const;
		bool isTargetVelocitySet() const { return linearVelSet; }

		void setTargetAngularVelocity(const osg::Vec3& vel, const bool relative = false);
		osg::Vec3 getTargetAngularVelocity(const bool relative = false) const;
		bool isTargetAngularVelocitySet() const { return angularVelSet; }
		
		bool isAccelerating() const { return linearVelSet || angularVelSet; }
		
	protected:
		osg::Vec3 targetPosition;
		osg::Quat targetRotation;
		osg::Vec3 targetLinearVel, targetAngularVel;
		bool targetLinearVelIsRel, targetAngularVelIsRel;
		bool positionSet, rotationSet, linearVelSet, angularVelSet;
	};

}

#endif
