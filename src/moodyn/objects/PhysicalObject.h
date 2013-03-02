#ifndef MOON_PHYSICALOBJECT_H
#define MOON_PHYSICALOBJECT_H

#include "moodyn/components/Geometry.h"
#include <moon/objects/KinematicObject.h>
#include <moon/Destructible.h>

namespace moodyn {

	/// \brief An object with physics geometry, supports moodyn::Geometry component
	/// \ingroup dynamics objects
	class MOODYN_EXPORT PhysicalObject : public moon::KinematicObject, public moon::Destructible {
	public:
		PhysicalObject();
		PhysicalObject(const PhysicalObject& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, PhysicalObject);

		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;

		virtual void addComponent(Component* component);

		virtual void initialize();
		virtual void reset();
		virtual void setResetState();
		virtual void realize();
		virtual void unrealize();

		virtual void setDisplayMode(const unsigned int mode);
		virtual void updateTransformation(const bool parentUpdate = false);

		/// Set physics geometry attached to this object
		virtual void setGeometry(moodyn::Geometry *geometry);
		/// Get physics geometry attached to this object
		moodyn::Geometry* getGeometry();

		virtual void destroy();
		virtual void update(const double dt);

	protected:
        virtual ~PhysicalObject();

		class ContactCallback : public moodyn::ContactCallback {
			virtual bool operator()(moodyn::Geometry *own, moodyn::Geometry *other);
		};
		class ContactFeedbackCallback : public moodyn::ContactFeedbackCallback {
			virtual bool operator()(moodyn::Geometry *own, moodyn::Geometry *other);
		};
		class NearCallback : public moodyn::NearCallback {
			virtual bool operator()(moodyn::Geometry *own, moodyn::Geometry *other);
		};

		virtual bool onContact(PhysicalObject *other);
		virtual bool onContactFeedback(PhysicalObject *other);
		virtual bool onNear(PhysicalObject *other);

		void initContactCallback();
		void initContactFeedbackCallback();
		void initNearCallback();

	private:
		float resetHealth;
		osg::observer_ptr<moodyn::Geometry> geometry;
		osg::observer_ptr<osg::Node> geometryDebugNode;
		bool luaContactCallback, luaContactFeedbackCallback;
		double destructionTime, destructionHideTime, destructionUnrealizeTime, destructionRemoveTime;
		osg::ref_ptr<moon::Parameter> contactParam, contactTorqueParam;
	};
}

#endif
