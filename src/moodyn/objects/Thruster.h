#ifndef MOON_THRUSTER_H
#define MOON_THRUSTER_H

#include "DynamicVehicle.h"
#include "moodyn/components/ContinuousForce.h"
#include "moodyn/components/PIDController.h"
#include <vector>

namespace moodyn {
	
	/// \brief Test thruster vehicle
	/// \ingroup objects dynamics
	class MOODYN_EXPORT Thruster : public DynamicVehicle {
	public:
		Thruster();
		Thruster(const Thruster& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Thruster);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void addComponent(Component *component);
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		virtual void controlUpdate(moon::Control *control);
		
		bool isOnGround() const { return groundContact; }
		bool isControlsFlipped() const { return flippedControls; }
		bool isRecoveringFCS() const { return fcsRecovery; }
				
	private:
		float headingSet, pitchSet, rollSet;
		float pitchLimitHi, pitchLimitLo, rollLimitHi, rollLimitLo;
		bool groundContact, flippedControls, fcsRecovery;
		std::vector< osg::observer_ptr<Geometry> > gears;
		osg::ref_ptr<moon::ListenerControl> riseControl, pitchControl, yawControl, rollControl, moveControl, strafeControl;
		osg::ref_ptr<moon::ListenerControl> autoHoverControl, autoAttitudeControl, flipControl;
		osg::observer_ptr<PIDController> ratePitchPID, rateRollPID, rateYawPID, attPitchPID, attRollPID, vspeedPID, movePID, strafePID, straightPID, headingPID;
		osg::ref_ptr<moon::Parameter> riseParam, pitchParam, yawParam, rollParam, moveParam, strafeParam;
	};
	
}

#endif
