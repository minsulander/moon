#ifndef MOODYN_DRAG_H
#define MOODYN_DRAG_H

#include "ContinuousForce.h"
#include <moon/objects/KinematicObject.h>

namespace moodyn {
	
	/// \brief Aerodynamic drag force system
	/// \ingroup components dynamics
	class MOODYN_EXPORT Drag : public ContinuousForce {
	public:
		Drag();
		Drag(const Drag& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Drag);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void realize();
		virtual void update(const double dt);
		
	private:
		float cd;
		osg::Vec3 A;
		osg::observer_ptr<moon::KinematicObject> object;
		
		enum AreaSource { NONE, BSPHERE, BBOX };
		AreaSource areaSource;
	};
}

#endif
