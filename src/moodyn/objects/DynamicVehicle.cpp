#include "DynamicVehicle.h"
#include <moon/ObjectFactory.h>
#include <moon/Scenario.h>
#include <moon/Interpreter.h>
#include <moon/NodeMask.h>

using namespace moon;
using namespace mlog;

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, DynamicVehicle, Vehicle);
	
	DynamicVehicle::DynamicVehicle()
	:	DynamicPhysicalObject(), Vehicle()
	{
		transform->setNodeMask(transform->getNodeMask() | NodeMask::INTERACTIVE);
	}
	
	DynamicVehicle::DynamicVehicle(const DynamicVehicle& vehicle, const osg::CopyOp& copyop)
	:	DynamicPhysicalObject(vehicle, copyop)
	{
		transform->setNodeMask(transform->getNodeMask() | NodeMask::INTERACTIVE);
	}
	
	void DynamicVehicle::realize()
	{
		if (!trackcam.valid())
			trackcam = dynamic_cast<Camera*> (getChildByTag("track"));
		if (trackcam.valid()) {
			trackcam->setTemporary(true);
			trackcam->track(this, Camera::CHASE); // this sets up track parameters and connects modifiers
			separateChild(trackcam.get());
			trackcam->track(NULL, Camera::NONE);
		}
		DynamicPhysicalObject::realize();
	}
	
	void DynamicVehicle::unrealize()
	{
		if (currentVehicle == this)
			exit();
		if (Scenario::current())
			Scenario::current()->removeComponent(trackcam.get());
		DynamicPhysicalObject::unrealize();
	}
	
	void DynamicVehicle::enter()
	{
		if (!drivercam.valid()) {
			drivercam = dynamic_cast<Camera*> (findRelatedByTag("driver"));
			if (!drivercam.valid()) {
				dout(ERROR) << "No driver camera found in vehicle '" << getName() << "'\n";
				return;
			}
		}
		entrycam = CameraManipulator::instance().getActiveCamera();
		if (entrycam.valid())
			entrypos = osg::Matrix::inverse(getWorldTransformMatrix()).getRotate() * (entrycam->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans());
		drivercam->activate();
		
		if (!exitControl.valid())
			exitControl = new ListenerControl("Exit", Control::MOMENTARY, this);
		if (!cameraModeControl.valid())
			cameraModeControl = new ListenerControl("CameraMode", Control::MOMENTARY, this);
		bindControls();
		if (isRemote() && getOwner())
			dout(WARN) << "Entered remote vehicle " << getName() << " owned by " << (getOwner() ? getOwner()->toString() : "server") << "\n";
		setOwner(moonet::Client::me());
		// Export current vehicle to Lua interpreter
		Interpreter::instance().pushGlobal("objects");
		Interpreter::instance().setTable("vehicle", this, "moon::KinematicObject");
		// Set model visbility interior/extiror
		setModelVisibilityWithTag("interior", true);
		setModelVisibilityWithTag("exterior", false);

		Vehicle::enter();
	}
	
	void DynamicVehicle::exit()
	{
		unbindControls();
		if (entrycam.valid()) {
			entrycam->setPosition( getWorldTransformMatrix().getTrans() + getWorldTransformMatrix().getRotate() * entrypos);
			entrycam->track(NULL);
			entrycam->pointAt(this);
			entrycam->activate();
		} else
			CameraManipulator::instance().setNoActiveCamera();
		if (trackcam.valid())
			trackcam->track(NULL);
		if (Scenario::current())
			Scenario::current()->removeComponent(trackcam.get());
		// Export current vehicle to Lua interpreter
		Interpreter::instance().pushGlobal("objects");
		Interpreter::instance().setTable("vehicle", NULL, "nil");
		// Set model visbility interior/extiror
		setModelVisibilityWithTag("interior", false);
		setModelVisibilityWithTag("exterior", true);

		setOwner(NULL);
		
		Vehicle::exit();
	}
	
	void DynamicVehicle::interaction(const InteractionType type)
	{
		if (type == ACTION && !currentVehicle)
			enter();
	}
	
	void DynamicVehicle::controlUpdate(Control *control)
	{
		if (control == exitControl.get() && control->getValue() > 0.5)
			exit();
		if (control == cameraModeControl.get() && control->getValue() > 0.5)
			cycleCameraMode();
	}
	
	void DynamicVehicle::cycleCameraMode()
	{
		if (!trackcam.valid()) {
			trackcam = new Camera(getName() + " TrackCam");
			trackcam->setTrackParameters(20,0,-M_PI/12.0);
		}
		bool interior = false;
		switch (trackcam->getTrackMode()) {
			case Camera::NONE:
				if (Scenario::current())
					Scenario::current()->addComponent(trackcam.get());
				trackcam->track(this, Camera::CHASE_HORIZONTAL_VELOCITY);
				trackcam->activate();
				break;
			case Camera::CHASE_HORIZONTAL_VELOCITY:
				trackcam->track(this, Camera::CHASE_VELOCITY);
				break;
			case Camera::CHASE_VELOCITY:
				trackcam->track(this, Camera::FOLLOW);
				break;
			case Camera::FOLLOW:
				trackcam->track(this,Camera::POINT);
				break;
			default:
				trackcam->track(NULL, Camera::NONE);
				drivercam->activate();
				if (Scenario::current())
					Scenario::current()->removeComponent(trackcam.get());
				interior = true;
		}
		setModelVisibilityWithTag("interior", interior);
		setModelVisibilityWithTag("exterior", !interior);
	}
	
	DynamicVehicle::~DynamicVehicle()
	{
		if (currentVehicle == this) {
			unbindControls();
			if (entrycam.valid()) {
				entrycam->setPosition( getWorldTransformMatrix().getTrans() + getWorldTransformMatrix().getRotate() * entrypos);
				entrycam->track(NULL);
				entrycam->pointAt(this);
				entrycam->activate();
			} else
				CameraManipulator::instance().setNoActiveCamera();
			if (trackcam.valid())
				trackcam->track(NULL);
			if (Scenario::current())
				Scenario::current()->removeComponent(trackcam.get());
		}
	}
	
	
} // namespace
