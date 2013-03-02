#ifndef MOODYN_DYNAMICVEHICLE_H
#define MOODYN_DYNAMICVEHICLE_H

#include <moon/objects/Interactive.h>
#include <moon/objects/Camera.h>
#include <moon/objects/Vehicle.h>
#include <moon/Control.h>
#include "DynamicPhysicalObject.h"

namespace moodyn {
	
	/// \brief A dynamic vehicle
	/// \ingroup objects dynamics
	class MOODYN_EXPORT DynamicVehicle : public DynamicPhysicalObject, public moon::Interactive, public moon::Vehicle, public moon::ControlListener {
	public:
		DynamicVehicle();
		DynamicVehicle(const DynamicVehicle& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, DynamicVehicle);
		
		virtual void realize();
		virtual void unrealize();
		
		virtual void enter();
		virtual void exit();
		
		virtual void interaction(const moon::InteractionType type);
		virtual void controlUpdate(moon::Control *control);
		
		void cycleCameraMode();
		
	protected:
		~DynamicVehicle();
		
	private:
		osg::ref_ptr<moon::Camera> drivercam;
		osg::ref_ptr<moon::Camera> entrycam;
		osg::ref_ptr<moon::Camera> trackcam;

		osg::Vec3 entrypos;
		osg::ref_ptr<moon::ListenerControl> exitControl, cameraModeControl;
	};
	
}

#endif
