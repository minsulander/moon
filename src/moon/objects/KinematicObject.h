#ifndef MOON_KINEMATICOBJECT_H
#define MOON_KINEMATICOBJECT_H

#include "VisualObject.h"
#include "moon/components/MotionModel.h"
#include <osg/AnimationPath>
#include <osg/NodeCallback>

namespace moon {

	/// \ingroup core objects
	/// @{
	
	/// An object that may have a linear and/or angular velocity, or an animation path
	class MOON_EXPORT KinematicObject : public VisualObject {
	public:
		KinematicObject();
		KinematicObject(const KinematicObject& object, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon,KinematicObject);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void addComponent(Component* component);

		/// Set an animation path that defines this object's movement
		void setAnimationPath(osg::AnimationPath *animationPath);
		/// Get the animation path (if any) that defines this object's movement
		osg::AnimationPath* getAnimationPath();
		osg::Matrix getAnimationOriginMatrix() const { return animationOriginMatrix; }
		/// Pauses the animation, optionally at a specific control point
		void setAnimationPaused(const bool paused, const int controlPointIndex = -1);
		bool getAnimationPaused() const { return animPaused; }
		/// Makes further transformation changes affect the matrix of the specified control point of the animation path
		void setTransformationUpdatesControlPoint(const int controlPointIndex);
		/// Get time along animation path
		double getAnimationTime() const { return animTime; }
		
		/// Set linear velocity
		virtual void setVelocity(const osg::Vec3& vel, const bool relative = false);
		inline void setVelocity(const double x, const double y, const double z, const bool relative = false) { setVelocity(osg::Vec3(x,y,z), relative); }
		/// Set angular velocity (rotational velocity around the x-y-z axis, i.e. NOT heading/pitch/roll)
		virtual void setAngularVelocity(const osg::Vec3& vel, const bool relative = false);
		inline void setAngularVelocity(const double x, const double y, const double z, const bool relative = false) { setAngularVelocity(osg::Vec3(x,y,z), relative); }
		/// Get linear velocity
		virtual osg::Vec3 getVelocity(const bool relative = false) const;
		void getVelocity(double& x, double& y, double& z, const bool relative = false) const;
		void getVelocity(osg::Vec3& vel, bool& rel) const;
		/// Get linear velocity in world coordinates
		virtual osg::Vec3 getWorldVelocity() const;
		void getWorldVelocity(double& x, double& y, double& z) const;
		/// Get angular velocity (rotational velocity around the x-y-z axis, i.e. NOT heading/pitch/roll)
		virtual osg::Vec3 getAngularVelocity(const bool relative = false) const;
		void getAngularVelocity(double& x, double& y, double& z, const bool relative = false) const;
		void getAngularVelocity(osg::Vec3& angvel, bool& rel) const;
		/// Get angular velocity in world coordinates
		virtual osg::Vec3 getWorldAngularVelocity() const;
		void getWorldAngularVelocity(double& x, double& y, double& z) const;
		
		MotionModel* getMotionModel() const { return motionModel.get(); }
		/// Move to specified position using attached MotionModel if available
		virtual void requestPosition(const osg::Vec3& pos);
		/// Rotate to specified attitude using attached MotionModel if available
		virtual void requestRotation(const osg::Quat& rot);
		/// Rotate to specified attitude using attached MotionModel if available
		virtual void requestAttitude(const osg::Vec3& att);
		/// Accelerate/decelerate to specified velocity using attached MotionModel if available
		virtual void requestVelocity(const osg::Vec3& vel, const bool relative = false);
		/// Accelerate/decelerate to specified angular velocity using attached MotionModel if available
		virtual void requestAngularVelocity(const osg::Vec3& vel, const bool relative = false);
		
		virtual void stop(const bool recursive = true);
		
		/// Returns true if either velocity is above threshold or the object has an animation
		virtual bool isDynamic();
		
		virtual void reset();
		virtual void setResetState();
		
		// Overloaded network methods
		virtual bool serialize(const bool full);
		virtual void deserialize(const bool full, const double timediff);

		static double linear_threshold;  ///< Linear velocities below this are considered no movement
		static double angular_threshold; ///< Angular velocities below this are considered no movement
		static double anim_velocity_timestep; ///< Sample interval for determining velocity from an animation path

		virtual KinematicObject* asKinematic() { return this; }
		virtual void preUpdateTransformation(const bool parentUpdate = false);
		virtual void updateTransformation(const bool parentUpdate = false);
		virtual void update(const double dt);
		
		float getHeight();
		
		double getTimeStamp() const { return timestamp; }
		bool getSerializeAngularVel() const { return serializeAngularVel; }
		
		void setFrameInterpolation(const bool value) { frameInterpolation = value; }
		bool getFrameInterpolation() { return frameInterpolation; }
		
	protected:		
		/// Setup TransformCallback appropriately depending on velocity etc
		virtual void checkUpdateCallback();
		/// Callback from TransformCallback when transform and velocities have been updated
		virtual void onTransformCallbackUpdate() {}

		/// Extrapolating update callback
		class TransformCallback : public osg::NodeCallback {
		public:
			TransformCallback(KinematicObject *nobject) : object(nobject), firstUpdate(true) {}
			virtual void operator() (osg::Node *node, osg::NodeVisitor *nv);
		private:
			osg::observer_ptr<KinematicObject> object;
			bool firstUpdate;
		};
		
	private:
		osg::Vec3 linearVel;  ///< Linear velocity in world/parent or body coordinates
		osg::Vec3 angularVel; ///< Linear velocity in world/parent or body coordinates
		bool linearVelIsRel;  ///< True if linear velocity is relative (body coordinates)
		bool angularVelIsRel; ///< True if angular velocity is relative (body coordinates)
		osg::Vec3 resetLinearVel, resetAngularVel;
		bool resetLinearVelIsRel, resetAngularVelIsRel;
		bool serializeAngularVel;
		bool frameInterpolation;
		
		osg::Vec3 corrLinearVel; ///< used in deserialize() to smoothen out network updates
		osg::Quat corrLastRot, corrNextRot;
		double corrTime, corrTimeStep;
		
		osg::ref_ptr<osg::AnimationPath> animationPath;
		osg::Matrix animationOriginMatrix;
		double animTime;
		bool animPaused;
		osg::AnimationPath::ControlPoint *updateControlPoint;
		double timestamp;
		double lastHeightUpdate, heightUpdateStep;

		osg::ref_ptr<Parameter> speedParam, rotspeedParam, heightParam;
		osg::ref_ptr<moon::Parameter> speedxParam, speedyParam, speedzParam; 
		osg::ref_ptr<moon::Parameter> rotspeedxParam, rotspeedyParam, rotspeedzParam; 
		osg::observer_ptr<MotionModel> motionModel;
	};

	/// @}
}

#endif
