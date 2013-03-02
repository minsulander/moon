#ifndef MOON_SIMPLEMOTION_H
#define MOON_SIMPLEMOTION_H

#include "MotionModel.h"
#include "moon/objects/KinematicObject.h"

namespace moon {

	class MOON_EXPORT SimpleMotion : public MotionModel {
	public:
		SimpleMotion();
		SimpleMotion(const SimpleMotion& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, SimpleMotion);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void realize();		
		virtual void update(const double dt);
	private:
		osg::observer_ptr<KinematicObject> object;
		float linearAcc, angularAcc, speed, rotationSpeed;
	};

}

#endif
