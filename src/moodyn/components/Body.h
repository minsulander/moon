#ifndef MOODYN_BODY_H
#define MOODYN_BODY_H

#include "moodyn/Export.h"
#include <moon/components/Component.h>
#include <osg/Referenced>
#include <osg/CopyOp>
#include <osg/Vec3>
#include <osg/Quat>
#include <osg/Matrix>
#include <ode/ode.h>

namespace moodyn {
	
	/// \brief Rigid body wrapper class
	/// \ingroup components dynamics
	class MOODYN_EXPORT Body : public moon::Component
	{
	public:
		Body();
		Body(const Body& other, const osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Body);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Actually create the ODE body
		void realize();
		/// Delete the ODE body
		void unrealize();
		bool isRealized() { return bodyID != 0; }
		
		/// Set position and rotation from an osg::Matrix
		void setTransformation(const osg::Matrix& M);
		/// Get position and rotation as an osg::Matrix
		osg::Matrix getTransformation();
		/// Set position of the body
		void setPosition(const osg::Vec3& pos);
		/// Get position of the body
		const osg::Vec3 getPosition();
		/// Set rotation of the body from a quaternion
		void setRotation(const osg::Quat& rot);
		/// Get rotation of the body as a quaternion
		const osg::Quat getRotation();
		/// Set linear velocity
		void setVelocity(const osg::Vec3& vel, const bool rel = false);
		/// Get linear velocity
		const osg::Vec3 getVelocity(const bool rel = false);
		/// Set angular velocity
		void setAngularVelocity(const osg::Vec3& avel, const bool rel = false);
		/// Get angular velocity
		const osg::Vec3 getAngularVelocity(const bool rel = false);
		
		void addForce(const osg::Vec3& F, const bool rel = false);
		void addForceAt(const osg::Vec3& F, const bool rel = false, const osg::Vec3& pos = osg::Vec3(0,0,0), const bool relpos = false);
		void addTorque(const osg::Vec3& Q, const bool rel = false);
		void setForce(const osg::Vec3& F, const bool rel = false);
		void setTorque(const osg::Vec3& Q, const bool rel = false);
		const osg::Vec3 getForce(const bool rel = false);
		const osg::Vec3 getTorque(const bool rel = false);
		
		const double getMass();
		void setMass(const double newmass);
		
		const bool isEnabled() const;
		void enable();
		void disable();
		
		/// Returns true if this body is connected to the other through a joint
		bool isConnectedTo(Body *other);
		
		dBodyID id();

	public:
		virtual ~Body();

	private:
		dBodyID bodyID;
		dMass mass;
		bool startdisabled;
	};

}

#endif
