#ifndef MOODYN_JOINT_H
#define MOODYN_JOINT_H

#include "Body.h"
#include <moon/components/Component.h>
#include <moon/Modifier.h>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <ode/ode.h>

namespace moodyn
{
	
	/// \brief Physical joint
	/// \ingroup components dynamics
	class MOODYN_EXPORT Joint : public moon::Component, public moon::ModifierContainer, public moon::ParameterContainer {
	public:
		enum JointType {
			NONE=0,
			BALL,
			HINGE,
			SLIDER,
			UNIVERSAL,
			HINGE2,
			FIXED,
			AMOTOR
		};
		
		// This list needs to correspond to ODE
		enum JointParameter {
			LOSTOP=dParamLoStop, 
			HISTOP,
			VELOCITY,
			MAXFORCE,
			FUDGE,
			BOUNCE,
			CFM,
			STOP_ERP,
			STOP_CFM,
			SUSPENSION_ERP,
			SUSPENSION_CFM,
			LOSTOP2=dParamLoStop2, 
			HISTOP2,
			VELOCITY2,
			MAXFORCE2,
			FUDGE2,
			BOUNCE2,
			CFM2,
			STOP_ERP2,
			STOP_CFM2,
			SUSPENSION_ERP2,
			SUSPENSION_CFM2,
			LOSTOP3=dParamLoStop3, 
			HISTOP3,
			VELOCITY3,
			MAXFORCE3,
			FUDGE3,
			BOUNCE3,
			CFM3,
			STOP_ERP3,
			STOP_CFM3,
			SUSPENSION_ERP3,
			SUSPENSION_CFM3,
			_END_ODE_PARAMETERS,
			
			SPRING,
			DAMP,
			SPRING2,
			DAMP2,
			STEER_VELOCITY,
			STEER_VELOCITY2,
			STEER_TOLERANCE,
			STEER_TOLERANCE2
		};
		
		static osg::TessellationHints *default_hints;
		static osg::Vec4 default_color1;
		static osg::Vec4 default_color2;
		
		Joint(const JointType type = NONE);
		Joint(const Joint& joint, const osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Joint);
		
		virtual ~Joint();
		dJointID id() { return jointID; }
		
		void parseXML(const TiXmlElement *element);
		void writeXML(TiXmlElement *element) const;
		
		const JointType& getType() { return type; }
		
		/// Get joint anchor (if applicable)
		osg::Vec3 getAnchor(const bool relative = true, const bool relativebody1 = true);
		/// Set joint anchor (if applicable)
		void setAnchor(const osg::Vec3& anchor, const bool relative = true, const bool relativebody1 = true);
		/// Get joint axis (if applicable)
		osg::Vec3 getAnchorWorld();
		osg::Vec3 getAnchor2World();
		osg::Vec3 getAxis(const bool relative = true, const bool relativebody1 = true);
		/// Set joint axis (if applicable)
		void setAxis(const osg::Vec3& axis, const bool relative = true, const bool relativebody1 = true);
		/// Get joint second axis (if applicable)
		osg::Vec3 getAxis2(const bool relative = true, const bool relativebody1 = true);
		/// Set joint second axis (if applicable)
		void setAxis2(const osg::Vec3& axis2, const bool relative = true, const bool relativebody1 = true);
		/// Set a joint parameter
		void setParameter(const JointParameter& parameter, const float value);
		/// Get a joint parameter
		float getParameter(const JointParameter& parameter);
		
		Body* getBody1() { return body1.get(); }
		Body* getBody2() { return body2.get(); }
		void attach();
		void attach(Body* body1, Body* body2 = NULL);
		void detach() { attach(0,0); }
		const std::string& getConnectName() { return connectName; }
		
		osg::Node* createDebugNode(int which);
		
		virtual void update(const double dt);
		
		float getDeflection();
		float getDeflection2();
		float getRate();
		float getRate2();
		void addForce(const float F1, const float F2=0, const float F3=0);
		void setRefDeflection(const float value);
		float getRefDeflection() const;
		void setRefDeflection2(const float value);
		float getRefDeflection2() const;
		void steer(const float deflection, const float velocity = 0.f);
		void steer2(const float deflection, const float velocity = 0.f);
		
		/// Get force applied by this joint on first body
		osg::Vec3 getForce1(const bool relative = true, const bool relativebody1 = true);
		/// Get force applied by this joint on second body
		osg::Vec3 getForce2(const bool relative = true, const bool relativebody1 = true);
		/// Get torque applied by this joint on first body
		osg::Vec3 getTorque1(const bool relative = true, const bool relativebody1 = true);
		/// Get torque applied by this joint on second body
		osg::Vec3 getTorque2(const bool relative = true, const bool relativebody1 = true);
		
		void setBreakImpulse(const float impulse) { breakImpulse = impulse; }
		float getBreakImpulse() const { return breakImpulse; }
		void setBreakAngularImpulse(const float impulse) { breakAngularImpulse = impulse; }
		float getBreakAngularImpulse() const { return breakAngularImpulse; }
		
		virtual void initialize();
		virtual void reset();
		virtual void setResetState();
		virtual void realize();
		virtual void unrealize();
		virtual bool isRealized() const;
		
		void updateAnchorsAndAxes();

		/// Initialize force/torque feedback from ODE
		void initFeedback();
		
		enum JointModifierTarget {
			NO_TARGET,
			STEER,
			STEER2
		};
		
	private:
		
		JointType type;
		dJointID jointID;
		osg::observer_ptr<Body> body1,body2;
		std::string connectName;
		bool pendingAttachment;
		
		// Joint parameters
		osg::Vec3 anchor, axis, axis2;
		typedef std::map<int, float> ParameterMap;
		ParameterMap parameters;
		
		float breakImpulse, breakAngularImpulse;
		dJointFeedback *feedback;
		float refDeflection, refDeflection2;
		float steerDeflection, steerDeflection2;
		float resetRefDeflection, resetRefDeflection2;
		bool steering, steering2;
		float debugscale;
		
		osg::ref_ptr<moon::Parameter> steerParam, forceParam, torqueParam;
		
	};
	
}

#endif
