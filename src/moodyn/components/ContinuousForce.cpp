#include "ContinuousForce.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mdraw/LineGeometry.h>
#include <moon/objects/BaseObject.h>

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, ContinuousForce, Force);
	
	ContinuousForce::ContinuousForce()
	: moon::Component()
	, forceIsRel(true)
	, torqueIsRel(true)
	, forcePosIsRel(true)
	, vecsF(NULL)
	, vecsQ(NULL)
	, debugScale(0.f)
	{
	}
	
	ContinuousForce::ContinuousForce(const ContinuousForce& source, const osg::CopyOp& copyop)
	: moon::Component(source, copyop)
	, force(source.force)
	, torque(source.torque)
	, forceIsRel(source.forceIsRel)
	, torqueIsRel(source.torqueIsRel)
	, forcePos(source.forcePos)
	, forcePosIsRel(source.forcePosIsRel)
	, vecsF(NULL)
	, vecsQ(NULL)
	, debugScale(source.debugScale)
	{
	}
	
	void ContinuousForce::parseXML(const TiXmlElement *element)
	{
		//=== ContinuousForce
		//=see superclass Component
		moon::Component::parseXML(element);
		//=* attribute: pos="(vector3)"
		//=. Position on container object where forces will be applied
		moon::XMLParser::parseVector3Attribute(forcePos, element, "pos");
		//=* attribute: rel="true|false"
		//=. Specifies wether the position is in relative or world coordinates
		moon::XMLParser::parseBooleanAttribute(forcePosIsRel, element, "rel");
		//=* element: force value="(vector3)" [N] rel="true|false" pos="(vector3)" [m] relpos="true|false"
		//=. Constant initial force to set - not all that useful
		force = moon::XMLParser::parseVector3(element, "force", "N", true, force);
		forceIsRel = moon::XMLParser::parseBoolean(element, "force", true, forceIsRel, "rel");
		forcePos = moon::XMLParser::parseVector3(element, "force", "", true, forcePos, "pos");
		forcePosIsRel = moon::XMLParser::parseBoolean(element, "force", true, forcePosIsRel, "relpos");
		//=* element: torque value="(vector3)" [Nm] rel="true|false"
		//=. Constant initial torque to set - not all that useful
		torque = moon::XMLParser::parseVector3(element, "torque", "Nm", true, torque);
		torqueIsRel = moon::XMLParser::parseBoolean(element, "torque", true, torqueIsRel, "rel");
		//=* attribute: debugscale="(number)"
		//=. Scale of debug visual line showing force.
		debugScale = moon::XMLParser::parseDoubleAttribute(element, "debugscale", true, debugScale);
	}
	
	void ContinuousForce::writeXML(TiXmlElement *element) const
	{
		moon::Component::writeXML(element);
		/// \todo implement
	}
	
	void ContinuousForce::realize()
	{
		moon::Component::realize();
		if (!getContainer())
			return;
		for (unsigned int i = 0; i < getContainer()->getNumComponents(); i++) {
			Body *b = dynamic_cast<Body*> (getContainer()->getComponent(i));
			if (b) {
				body = b;
				if (debugScale == 0.f)
					debugScale = b->getMass()/9.81f;
			}
		}
	}
	
	void ContinuousForce::unrealize()
	{
		body = NULL;
		moon::Component::unrealize();
	}
	
	void ContinuousForce::update(const double dt)
	{
		moon::Component::update(dt);
		if (!body)
			return;
		if (force.length() > 1e-5 || torque.length() > 1e-5) {
			body->addForceAt(force, forceIsRel, forcePos, forcePosIsRel);
			body->addTorque(torque, torqueIsRel);
			body->enable();
		}
		if (vecsF && vecsQ) {
			osg::Vec3 p = forcePos, f = force, q = torque;
			osg::Quat rot = body->getRotation();
			if (!forcePosIsRel) p = rot.inverse()*p;
			if (!forceIsRel) f = rot.inverse()*f;
			if (!torqueIsRel) q = rot.inverse()*q;
			(*vecsF)[0] = p;
			(*vecsF)[1] = p + f*debugScale;
			(*vecsQ)[1] = q*debugScale;
		}
	}
	
	void ContinuousForce::setForce(const osg::Vec3& F)
	{
		force = F;
	}
	
	void ContinuousForce::setForce(const osg::Vec3& F, const bool rel)
	{
		force = F;
		forceIsRel = rel;
	}
	
	osg::Vec3 ContinuousForce::getForce(const bool rel)
	{
		if (rel == forceIsRel)
			return force;
		if (!body)
			return osg::Vec3(0,0,0);
		if (!forceIsRel)
			return body->getRotation().inverse()*force;
		return body->getRotation()*force;
	}
	
	void ContinuousForce::getForce(osg::Vec3& F, bool& rel)
	{
		F = force;
		rel = forceIsRel;
	}
	
	void ContinuousForce::setForceOffset(const osg::Vec3& pos)
	{
		forcePos = pos;
	}
	
	void ContinuousForce::setForceOffset(const osg::Vec3& pos, const bool rel)
	{
		forcePos = pos;
		forcePosIsRel = rel;
	}
	
	osg::Vec3 ContinuousForce::getForceOffset(const bool rel)
	{
		if (rel == forcePosIsRel)
			return forcePos;
		if (!body)
			return osg::Vec3(0,0,0);
		if (!forcePosIsRel)
			return body->getRotation().inverse()*forcePos;
		return body->getRotation()*forcePos;
	}
	
	void ContinuousForce::getForceOffset(osg::Vec3& pos, bool& rel)
	{
		pos = forcePos;
		rel = forcePosIsRel;
	}
	
	void ContinuousForce::setForceAt(const osg::Vec3& F, const bool frel, const osg::Vec3& pos, const bool posrel)
	{
		force = F;
		forceIsRel = frel;
		forcePos = pos;
		forcePosIsRel = posrel;
	}
	
	void ContinuousForce::setTorque(const osg::Vec3& Q)
	{
		torque = Q;
	}
	
	void ContinuousForce::setTorque(const osg::Vec3& Q, const bool rel)
	{
		torque = Q;
		torqueIsRel = rel;
	}

	osg::Vec3 ContinuousForce::getTorque(const bool rel)
	{
		if (rel == torqueIsRel)
			return torque;
		if (!body)
			return osg::Vec3(0,0,0);
		if (!torqueIsRel)
			return body->getRotation().inverse()*torque;
		return body->getRotation()*torque;
	}
	
	void ContinuousForce::getTorque(osg::Vec3& Q, bool& rel)
	{
		Q = torque;
		rel = torqueIsRel;
	}
	
	void ContinuousForce::icMessage(const unsigned int id, void *data)
	{
		if (id == moon::IC_MSG_DEBUG_DISPLAY_ON) {
			moon::BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer());
			if (object) {
				if (!debugGeode) {
					debugGeode = new osg::Geode;
					{
						vecsF = new osg::Vec3Array;
						vecsF->push_back(osg::Vec3(0,0,0));
						vecsF->push_back(osg::Vec3(0,0,1));
						osg::Geometry *geometry = mdraw::createLineGeometry(osg::PrimitiveSet::LINES, vecsF, osg::Vec4(1,1,0,1));
						geometry->setUseDisplayList(false);
						debugGeode->addDrawable(geometry);
					}
					{
						vecsQ = new osg::Vec3Array;
						vecsQ->push_back(osg::Vec3(0,0,0));
						vecsQ->push_back(osg::Vec3(0,0,-1));
						osg::Geometry *geometry = mdraw::createLineGeometry(osg::PrimitiveSet::LINES, vecsQ, osg::Vec4(1,0,1,1));
						geometry->setUseDisplayList(false);
						debugGeode->addDrawable(geometry);
					}
					debugGeode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
					debugGeode->getOrCreateStateSet()->setMode(GL_DEPTH,osg::StateAttribute::OFF);
					debugGeode->setName(getName() + " force debug node");
				}
				object->addDebugNode(debugGeode.get());
			}
		} else if (id == moon::IC_MSG_DEBUG_DISPLAY_OFF) {
			moon::BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer());
			if (object && debugGeode.valid())
				object->removeDebugNode(debugGeode.get());
		}
	}

}
