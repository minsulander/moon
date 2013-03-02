#ifndef MOON_BUGGY_H
#define MOON_BUGGY_H

#include "DynamicVehicle.h"
#include <moon/Modifier.h>
#include <vector>
#include <map>

namespace moodyn {
	
	/// \brief Test buggy vehicle
	/// \ingroup objects dynamics
	class MOODYN_EXPORT Buggy : public DynamicVehicle, public moon::ModifierContainer {
	public:
		Buggy();
		Buggy(const Buggy& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Buggy);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		virtual void controlUpdate(moon::Control *control);
		
	private:
		osg::ref_ptr<moon::ListenerControl> turnControl, driveControl, brakeControl, fireControl, flipControl;
		float maxturnspeed, maxturndeflection, turngain, maxrollspeed;
		float swayForce, maxSwayForce, brakeTorque, maxDriveTorque, dragTorque, aeroLoad;
		float wheeltrack, wheelbase;
		osg::ref_ptr<moon::Parameter> driveParam, driveTorqueParam, driveRotSpeedParam;
		
		typedef std::vector< osg::observer_ptr<moodyn::Joint> > JointList;
		JointList wheelJoints, driveJoints, brakeJoints, steerJoints, rearSteerJoints;
		std::map<moodyn::Joint*, moodyn::Joint*> oppositeJoint;
		
		osg::observer_ptr<moon::Modifier> driveTorqueModifier, steerAngleModifier, rearSteerAngleModifier;
		enum ModifierTarget {
			NO_TARGET,
			DRIVE_TORQUE,
			STEER_ANGLE,
			REAR_STEER_ANGLE
		};
	};
	
}

#endif
