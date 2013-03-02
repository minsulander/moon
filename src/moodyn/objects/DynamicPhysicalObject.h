#ifndef MOON_DYNAMICPHYSICALOBJECT_H
#define MOON_DYNAMICPHYSICALOBJECT_H

#include "PhysicalObject.h"
#include "moodyn/components/Body.h"
#include "moodyn/components/Joint.h"
#include <osg/Group>
#include <vector>

namespace moodyn {
	
	/// \brief Object with rigid body motion model, supports moodyn::Body and moodyn::Joint components
	/// \ingroup objects dynamics
	class MOODYN_EXPORT DynamicPhysicalObject : public PhysicalObject {
	public:
		DynamicPhysicalObject();
		DynamicPhysicalObject(const DynamicPhysicalObject& object, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn,DynamicPhysicalObject);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void addComponent(Component *component);
		
		virtual void setVelocity(const osg::Vec3& vel, const bool relative = false);
		inline void setVelocity(const double x, const double y, const double z, const bool relative = false) { setVelocity(osg::Vec3(x,y,z), relative); }
		virtual void setAngularVelocity(const osg::Vec3& angvel, const bool relative = false);
		inline void setAngularVelocity(const double x, const double y, const double z, const bool relative = false) { setAngularVelocity(osg::Vec3(x,y,z), relative); }
		virtual osg::Vec3 getVelocity(const bool relative = false) const;
		virtual osg::Vec3 getAngularVelocity(const bool relative = false) const;
		virtual osg::Vec3 getWorldVelocity() const;
		virtual osg::Vec3 getWorldAngularVelocity() const;
		
		virtual void initialize();
		virtual void reset();
		virtual void realize();
		virtual void unrealize();
		virtual void setGeometry(moodyn::Geometry *geometry);
		virtual void separateChild(BaseObject *child);
				
		virtual void update(const double dt = 0);		
		virtual void setDisplayMode(const unsigned int mode);
		
		/// Get the rigid body
		moodyn::Body* getBody() { return body.get(); }
		const moodyn::Body* getBody() const { return body.get(); }
		
		/// Add a joint and attach it
		void addJoint(moodyn::Joint *joint, DynamicPhysicalObject *connection = NULL);
		/// Add a new joint of the specified type and attach it
		void addJoint(const moodyn::Joint::JointType type, BaseObject *connection = NULL);
		unsigned int getNumJoints();
		moodyn::Joint* getJoint(const unsigned int index);
		void removeJoint(moodyn::Joint *joint, const bool otherSide = true);
		void removeJoints(const unsigned int index, const unsigned int num);
		void removeJoint(const unsigned int index) { removeJoints(index,1); }
		DynamicPhysicalObject* getJointConnection(const unsigned int index);

		virtual void setTransformMatrix(const osg::Matrix& M);
		virtual osg::Matrix getTransformMatrix() const;
		virtual void preUpdateTransformation(const bool parentUpdate = false);
		virtual void updateTransformation(const bool parentUpdate = false);
		virtual void stop(const bool recursive = true);
		
		virtual bool serialize(const bool full);
		virtual void deserialize(const bool full, const double timediff);
		virtual void onOwnerChange();
		
		enum RemoteMode { STATIC, DYNAMIC };
		void setRemoteMode(const RemoteMode& mode, const bool recursive = true);
		RemoteMode getRemoteMode() const { return remoteMode; }
		
		virtual bool isDynamic();
		virtual void setStatic(const bool value);
		
	protected:
		virtual ~DynamicPhysicalObject();
		virtual bool onNear(PhysicalObject *other);
		
	private:
		void setBodyForGeometries(PhysicalObject *object, DynamicPhysicalObject *root);
		void connectJoint(moodyn::Joint *joint, DynamicPhysicalObject *connection = NULL);
		
		osg::observer_ptr<moodyn::Body> body;
		typedef std::vector< osg::observer_ptr<moodyn::Joint> > JointList;
		JointList joints;
		typedef std::map<const moodyn::Joint*, DynamicPhysicalObject*> JointConnectionMap;
		JointConnectionMap joint_connections; // used in copy constructor
		osg::Matrix lastM, parentOffsetM;
		bool orphanTransform;
		osg::Vec3 worldVel, worldAngularVel;
		RemoteMode remoteMode;
		bool remoteModeRecursive, remoteModeSwitch, switchingMode;
		typedef std::map<const moodyn::Joint*, osg::observer_ptr<osg::Node> > JointDebugNodeMap;
		JointDebugNodeMap jointDebugNodes;
	};

}

#endif
