#ifndef MOODYN_CONTINUOUSFORCE_H
#define MOODYN_CONTINUOUSFORCE_H

#include "moodyn/Export.h"
#include "Body.h"
#include <moon/components/Component.h>
#include <osg/observer_ptr>
#include <osg/Geode>

namespace moodyn {
	
	/// \brief A force system imposing a continuous force on a Body
	/// \ingroup components dynamics
	class MOODYN_EXPORT ContinuousForce : public moon::Component {
	public:
		ContinuousForce();
		ContinuousForce(const ContinuousForce& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, ContinuousForce);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		
		void setForce(const osg::Vec3& F);
		void setForce(const osg::Vec3& F, const bool rel);
		osg::Vec3 getForce(const bool rel = false);
		void getForce(osg::Vec3& F, bool& rel);
		void setForceOffset(const osg::Vec3& pos);
		void setForceOffset(const osg::Vec3& pos, const bool rel);
		osg::Vec3 getForceOffset(const bool rel = false);
		void getForceOffset(osg::Vec3& pos, bool& rel);
		void setForceAt(const osg::Vec3& F, const bool rel = false, const osg::Vec3& pos = osg::Vec3(0,0,0), const bool relpos = false);
		void setTorque(const osg::Vec3& Q);
		void setTorque(const osg::Vec3& Q, const bool rel);
		osg::Vec3 getTorque(const bool rel = false);
		void getTorque(osg::Vec3& Q, bool& rel);
		
		Body *getBody() { return body.get(); }
		virtual void icMessage(const unsigned int id, void *data = NULL);
		
	private:
		osg::Vec3 force, torque;
		bool forceIsRel, torqueIsRel;
		osg::Vec3 forcePos;
		bool forcePosIsRel;
		
		osg::observer_ptr<Body> body;
		osg::ref_ptr<osg::Geode> debugGeode;
		osg::Vec3Array *vecsF, *vecsQ;
		float debugScale;
	};
}

#endif
