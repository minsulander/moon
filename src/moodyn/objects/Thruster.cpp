#include "Thruster.h"
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <mlog/Log.h>

using namespace moon;

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, Thruster, Thruster);
	
	Thruster::Thruster()
	: DynamicVehicle(),
	pitchLimitHi(M_PI), pitchLimitLo(-M_PI),
	rollLimitHi(M_PI), rollLimitLo(-M_PI),
	groundContact(false),
	flippedControls(false),
	fcsRecovery(false)
	{
		riseParam = new Parameter("rise", this);
		pitchParam = new Parameter("pitch", this);
		yawParam = new Parameter("yaw", this);
		rollParam = new Parameter("roll", this);
		moveParam = new Parameter("move", this);
		strafeParam = new Parameter("strafe", this);
		riseControl = new ListenerControl("Rise", Control::AXIS, this);
		pitchControl = new ListenerControl("Pitch", Control::AXIS, this);
		yawControl = new ListenerControl("Yaw", Control::AXIS, this);
		rollControl = new ListenerControl("Roll", Control::AXIS, this);
		moveControl = new ListenerControl("Move", Control::AXIS, this);
		strafeControl = new ListenerControl("Strafe", Control::AXIS, this);
		autoHoverControl = new ListenerControl("AutoHover", Control::TOGGLE, this);
		autoAttitudeControl = new ListenerControl("AutoAttitude", Control::TOGGLE, this);
		flipControl = new ListenerControl("FlipControl", Control::MOMENTARY, this);
	}
	
	Thruster::Thruster(const Thruster& source, const osg::CopyOp& copyop)
	: DynamicVehicle(source, copyop),
	pitchLimitHi(source.pitchLimitHi),
	pitchLimitLo(source.pitchLimitLo),
	rollLimitHi(source.rollLimitHi),
	rollLimitLo(source.rollLimitLo),
	groundContact(false),
	flippedControls(false),
	fcsRecovery(false)
	{
		riseParam = new Parameter("rise", this);
		pitchParam = new Parameter("pitch", this);
		yawParam = new Parameter("yaw", this);
		rollParam = new Parameter("roll", this);
		moveParam = new Parameter("move", this);
		strafeParam = new Parameter("strafe", this);
		riseControl = new ListenerControl("Rise", Control::AXIS, this);
		pitchControl = new ListenerControl("Pitch", Control::AXIS, this);
		yawControl = new ListenerControl("Yaw", Control::AXIS, this);
		rollControl = new ListenerControl("Roll", Control::AXIS, this);
		moveControl = new ListenerControl("Move", Control::AXIS, this);
		strafeControl = new ListenerControl("Strafe", Control::AXIS, this);
		autoHoverControl = new ListenerControl("AutoHover", Control::TOGGLE, this);
		autoAttitudeControl = new ListenerControl("AutoAttitude", Control::TOGGLE, this);
		flipControl = new ListenerControl("FlipControl", Control::MOMENTARY, this);
	}
	
	void Thruster::parseXML(const TiXmlElement* element)
	{
		DynamicVehicle::parseXML(element);
		double value;
		if (XMLParser::parseDouble(value, element, "pitchlimit", "degrees", "hi"))
			pitchLimitHi = value*M_PI/180.0;
		if (XMLParser::parseDouble(value, element, "pitchlimit", "degrees", "lo"))
			pitchLimitLo = value*M_PI/180.0;
		if (XMLParser::parseDouble(value, element, "rolllimit", "degrees", "hi"))
			rollLimitHi = value*M_PI/180.0;
		if (XMLParser::parseDouble(value, element, "rolllimit", "degrees", "lo"))
			rollLimitLo = value*M_PI/180.0;
	}
	
	void Thruster::writeXML(TiXmlElement *element) const
	{
		DynamicVehicle::writeXML(element);
	}
	
	void Thruster::addComponent(Component *component)
	{
		if (PIDController *pid = dynamic_cast<PIDController*> (component)) {
			pid->setUpdateMode(Component::SPECIFIC);
			if (pid->hasTag("rate_pitch"))
				ratePitchPID = pid;
			else if (pid->hasTag("rate_roll"))
				rateRollPID = pid;
			else if (pid->hasTag("rate_yaw"))
				rateYawPID = pid;
			else if (pid->hasTag("att_pitch")) 
				attPitchPID = pid;
			else if (pid->hasTag("att_roll"))
				attRollPID = pid;
			else if (pid->hasTag("vspeed"))
				vspeedPID = pid;
			else if (pid->hasTag("move"))
				movePID = pid;
			else if (pid->hasTag("strafe"))
				strafePID = pid;
			else if (pid->hasTag("straight"))
				straightPID = pid;
			else if (pid->hasTag("heading"))
				headingPID = pid;
			else
				pid->setUpdateMode(Component::WITH_CONTAINER);
		}
		DynamicVehicle::addComponent(component);
	}
	
	void Thruster::initialize()
	{
		DynamicVehicle::initialize();
		// Get a list of landing gear geometries
		for (unsigned int i = 0; i < getNumChildren(); i++) {
			if (getChild(i)->hasTag("gear")) {
				if (PhysicalObject *physical = dynamic_cast<PhysicalObject*> (getChild(i))) {
					gears.push_back(physical->getGeometry());
				}
			}
		}
		autoHoverControl->setValue(1);
		autoAttitudeControl->setValue(1);
	}
	
	void Thruster::realize()
	{
		DynamicVehicle::realize();
		osg::Vec3 att = getAttitude();
		headingSet = att.x();
		pitchSet = att.y();
		rollSet = att.z();
	}
	
	void Thruster::unrealize()
	{
		DynamicVehicle::unrealize();
	}
	
	void Thruster::update(const double dt)
	{
		if (!isOccupied()) {
			DynamicVehicle::update(dt);
			return;
		}
		
		osg::Vec3 pos = getWorldTransformMatrix().getTrans();
		osg::Vec3 vel = getVelocity(true);
		osg::Vec3 wvel = getVelocity(false);
		osg::Vec3 angvel = getAngularVelocity(true);
		osg::Vec3 att = getAttitude();
		float rise = riseControl->getValue();
		float pitch = pitchControl->getValue();
		if (flippedControls)
			pitch = -pitch;
		float yaw = yawControl->getValue();
		float roll = rollControl->getValue();
		float move = moveControl->getValue();
		float strafe = strafeControl->getValue();
		
		groundContact = false;
		for (size_t i = 0; i < gears.size(); i++) {
			if (gears[i].valid() && gears[i]->getContactForce().length() > 1e-5)
				groundContact = true;
		}
		if (vspeedPID.valid()) {
			if (!groundContact || rise > 0) {
				// Ground collision prevention - reduce vertical speed close to ground
				if (autoHoverControl->getValue() > 1e-5) {
					while (getHeight()+rise*vspeedPID->getRefScale()*3.f < -1.f && getHeight() > 0)
						rise += 0.01;
				}
				if (fabs(att.z()) < M_PI/2.0) 
					rise += vspeedPID->calculate(wvel.z(), rise, dt);
				else
					rise -= vspeedPID->calculate(wvel.z(), rise, dt);
				
			} else
				vspeedPID->reset();
		}

		// Disable most controllers on ground
		if (groundContact) {
			headingSet = att.x();
			pitchSet = att.y();
			rollSet = att.z();
		} else {
			if (autoHoverControl->getValue() && !fcsRecovery) {
				if (!flippedControls)
					rollSet = 0;
				if (movePID.valid()) {	
					if (moveParam->isConnected())
						move += movePID->calculate(vel.y(), move, dt);
					else
						pitchSet -= movePID->calculate(vel.y(), move, dt);
				}
				if (strafePID.valid()) {
					if (strafeParam->isConnected())
						strafe += strafePID->calculate(vel.x(), strafe, dt);
					else
						rollSet += strafePID->calculate(vel.x(), strafe, dt);
				}
			} else {
				if (movePID.valid())
					movePID->reset();
				if (strafePID.valid())
					strafePID->reset();
			}
			
			// Attitude controllers
			if (autoAttitudeControl->getValue() < 1e-5) {
				headingSet = att.x();
				pitchSet = att.y();
				rollSet = att.z();
				autoHoverControl->setValue(0);
			} else {
				if (!fcsRecovery && !autoHoverControl->getValue() && straightPID.valid()) {
					rollSet = straightPID->calculate(vel.x(), strafe, dt);
				}
				if (attPitchPID.valid()) {
					if (fabs(pitch) > 0.01)
						pitchSet = att.y();
					if (pitchSet > pitchLimitHi) pitchSet = pitchLimitHi;
					if (pitchSet < pitchLimitLo) pitchSet = pitchLimitLo;
					float err = att.y()-pitchSet;
					if (err <= -M_PI) err += 2.0*M_PI;
					if (err >= M_PI) err -= 2.0*M_PI;
					pitch += attPitchPID->calculate(err, 0, dt);
				}
				if (attRollPID.valid()) {
					if (fabs(roll) > 0.01)
						rollSet = att.z();
					if (rollSet > rollLimitHi) rollSet = rollLimitHi;
					if (rollSet < rollLimitLo) rollSet = rollLimitLo;
					float err = att.z()-rollSet;
					if (err <= -M_PI) err += 2.0*M_PI;
					if (err >= M_PI) err -= 2.0*M_PI;
					roll += attRollPID->calculate(err, 0, dt);
				}
				if (!fcsRecovery && headingPID.valid()) {
					if (fabs(yaw) > 0.01)
						headingSet = att.x();
					float err = att.x()-headingSet;
					if (err <= -M_PI) err += 2.0*M_PI;
					if (err >= M_PI) err -= 2.0*M_PI;
					yaw += headingPID->calculate(err, 0, dt);
				}
			}
			
			// Simple rate suppression controllers
			if (ratePitchPID.valid())
				pitch += ratePitchPID->calculate(angvel.x(), 0, dt);
			if (rateRollPID.valid())
				roll += rateRollPID->calculate(angvel.y(), 0, dt);
			if (rateYawPID.valid())
				yaw += rateYawPID->calculate(-angvel.z(), 0, dt);
		}
		
		// Attitude recovery mode
		if (fcsRecovery) {
			yaw = move = strafe = 0;
			headingSet = att.x();
			pitchSet = rollSet = 0;
			autoAttitudeControl->setValue(1.0f);
			if (att.y() < pitchLimitHi && att.y() > pitchLimitLo && att.z() < rollLimitHi && att.z() > rollLimitLo && fabs(angvel.y()) < M_PI/6.0 && fabs(angvel.x()) < M_PI/6.0) {
				fcsRecovery = false;
				autoHoverControl->setValue(1.0f);
			}
		} else if (fabs(att.z()) > M_PI/2.0 || fabs(angvel.y()) > M_PI || fabs(angvel.x()) > M_PI) {
			fcsRecovery = true;
		}
		
		riseParam->set(rise);
		pitchParam->set(pitch);
		yawParam->set(yaw);
		rollParam->set(roll);
		moveParam->set(move);
		strafeParam->set(strafe);
		
		/// \todo right now PID controllers get updated twice...
		DynamicVehicle::update(dt);

	}
	
	void Thruster::controlUpdate(Control *control)
	{
		// Flip control flips move/strafe with pitch/roll controls
		if (control == flipControl.get() && control->getValue()) {
			unbindControls();
			if (moveControl->getName() == "Move") {
				moveControl->setName("Pitch");
				strafeControl->setName("Roll");
				pitchControl->setName("Move");
				rollControl->setName("Strafe");
			} else {
				moveControl->setName("Move");
				strafeControl->setName("Strafe");
				pitchControl->setName("Pitch");
				rollControl->setName("Roll");
			}
			bindControls();
			flippedControls = !flippedControls;
		} else if (control == autoHoverControl.get() && control->getValue() > 1e-5) {
			// Reset roll attitude setpoint
			if (autoAttitudeControl->getValue() > 1e-5 && straightPID.valid())
				rollSet = 0;
			autoAttitudeControl->setValue(1);
		}
		DynamicVehicle::controlUpdate(control);
	}
	
} // namespace
