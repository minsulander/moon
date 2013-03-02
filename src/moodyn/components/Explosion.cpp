#include "Explosion.h"
#include "moodyn/objects/DynamicPhysicalObject.h"
#include <moon/objects/BaseObject.h>
#include <moon/ObjectFactory.h>
#include <moon/SimulationManager.h>
#include <mdraw/utils.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>
#include <osg/io_utils>

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, Explosion, Explosion);
	
	class ExplosiveContactCallback : public moodyn::ContactCallback
	{
	public:
		ExplosiveContactCallback(const float nshock, const float ndamage, const Explosion::ShockDistribution ndistribution)
		: shock(nshock), damage(ndamage), distribution(ndistribution) {}
		
		virtual bool operator()(Geometry *own, Geometry *other) {
			osg::Vec3 v = other->getPosition(0) - own->getPosition(0);
			float dist = v.length();
			v.normalize();
			Body *body = other->getBody();
			if (body && body->isRealized()) {
				body->enable();
				osg::Vec3 F;
				switch (distribution) {
					case Explosion::CONSTANT: F = v * shock; break;
					case Explosion::LINEAR: F = v * shock / dist; break;
					case Explosion::QUADRATIC: F = v * shock / (dist*dist); break;
					case Explosion::SPHERICAL: F = v * shock / (4.0f*M_PI*dist*dist); break;
				}
				body->addForce(F);
			}
			PhysicalObject *physical = (PhysicalObject*) other->getUserData();
			if (!damaged[other] && physical) {
				float d = 0.0;
				switch (distribution) {
					case Explosion::CONSTANT: d = damage; break;
					case Explosion::LINEAR: d = damage / dist; break;
					case Explosion::QUADRATIC: d = damage / (dist*dist); break;
					case Explosion::SPHERICAL: d = damage / (4.0f*M_PI*dist*dist); break;
				}
				physical->damage(d, moon::Destructible::EXPLOSION);
			}
			damaged[other] = true;
			return false;
		}
		
	protected:
		std::map< Geometry*, bool> damaged;
		float shock, damage;
		Explosion::ShockDistribution distribution;
	};
	
	Explosion::Explosion()
	:	Component(),
		explosion(new osgParticle::ExplosionEffect),
		destructible(NULL),
		time(0.0),
		lastDestroyed(false),
		shockDuration(0.1f),
		shockRadius(3.f),
		shockForce(100.f),
		shockDamage(100.f),
		shockDistribution(LINEAR)
	{
		setRealizeMode(moon::Component::SPECIFIC);
	}
	
	Explosion::Explosion(const Explosion& source, const osg::CopyOp& copyop)
	:	Component(source, copyop),
		explosion(new osgParticle::ExplosionEffect(*source.explosion.get())),
		destructible(NULL),
		time(0.0),
		lastDestroyed(false),
		shockDuration(source.shockDuration),
		shockRadius(source.shockRadius),
		shockForce(source.shockForce),
		shockDamage(source.shockDamage),
		shockDistribution(source.shockDistribution)
	{
		setRealizeMode(moon::Component::SPECIFIC);
		if (source.debris.valid())
			debris = new osgParticle::ExplosionDebrisEffect(*source.debris.get());
	}
	
	void Explosion::parseXML(const TiXmlElement *element)
	{
		Component::parseXML(element);
		double value;
		std::string str;
		//=== Explosion
		
		//=* attribute: scale="(number)"
		if (moon::XMLParser::parseDoubleAttribute(value, element, "scale"))
			explosion->setScale(value);
		//=* attribute: intensity="(number)"
		if (moon::XMLParser::parseDoubleAttribute(value, element, "intensity"))
			explosion->setIntensity(value);
		//=* attribute: duration="(number)" [seconds]
		//=. Sets both emitter and particle duration to same value
		if (moon::XMLParser::parseDoubleAttribute(value, element, "duration")) {
			explosion->setEmitterDuration(value);
			explosion->setParticleDuration(value);
		}
		//=* attribute: emitter_duration="(number)" [seconds]
		if (moon::XMLParser::parseDoubleAttribute(value, element, "emitter_duration"))
			explosion->setEmitterDuration(value);
		//=* attribute: particle_duration="(number)" [seconds]
		if (moon::XMLParser::parseDoubleAttribute(value, element, "particle_duration"))
			explosion->setParticleDuration(value);
		//=* attribute: texture="(filename)"
		if (moon::XMLParser::parseStringAttribute(str, element, "texture"))
			explosion->setTextureFileName(str);
		//=* element: debris
		//=. Adds debris particle effect, supports same attributes as above
		if (const TiXmlElement *debrisElement = element->FirstChildElement("debris")) {
			if (!debris.valid()) {
				debris = new osgParticle::ExplosionDebrisEffect;
				debris->setScale(explosion->getScale());
			}
			if (moon::XMLParser::parseDoubleAttribute(value, debrisElement, "scale"))
				debris->setScale(value);
			if (moon::XMLParser::parseDoubleAttribute(value, debrisElement, "intensity"))
				debris->setIntensity(value);
			if (moon::XMLParser::parseDoubleAttribute(value, debrisElement, "duration")) {
				debris->setEmitterDuration(value);
				debris->setParticleDuration(value);
			}
			if (moon::XMLParser::parseDoubleAttribute(value, debrisElement, "emitter_duration"))
				debris->setEmitterDuration(value);
			if (moon::XMLParser::parseDoubleAttribute(value, debrisElement, "particle_duration"))
				debris->setParticleDuration(value);
			if (moon::XMLParser::parseStringAttribute(str, debrisElement, "texture"))
				debris->setTextureFileName(str);
		}
		//=* element: shock
		if (const TiXmlElement *shockElement = element->FirstChildElement("shock")) {
			//=** attribute: duration="(number)"
			if (moon::XMLParser::parseDoubleAttribute(value, shockElement, "duration"))
				shockDuration = value;
			//=** attribute: radius="(number)"
			if (moon::XMLParser::parseDoubleAttribute(value, shockElement, "radius"))
				shockRadius = value;
			//=** attribute: force="(number)"
			//=. Total shock force. The actual shock force imparted on a nearby object is this value divided by a spherical surface around the explosion.
			if (moon::XMLParser::parseDoubleAttribute(value, shockElement, "force"))
				shockForce = value;
			//=** attribute: damage="(number)"
			//=. Total damage (in the explosion category). Same calculation of actual damage sa above.
			if (moon::XMLParser::parseDoubleAttribute(value, shockElement, "damage"))
				shockDamage = value;
			//=** attribute: distribution="constant|linear|quadratic|spherical"
			if (moon::XMLParser::parseStringAttribute(str, shockElement, "distribution")) {
				if (str == "constant")
					shockDistribution = CONSTANT;
				else if (str == "linear")
					shockDistribution = LINEAR;
				else if (str == "quadratic")
					shockDistribution = QUADRATIC;
				else if (str == "spherical")
					shockDistribution = SPHERICAL;
				else
					throw moon::ParseException("Invalid shock distribution specified", shockElement);
			}
		}
	}
	
	void Explosion::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		element->SetDoubleAttribute("scale", explosion->getScale());
		element->SetDoubleAttribute("intensity", explosion->getIntensity());
		element->SetDoubleAttribute("emitter_duration", explosion->getEmitterDuration());
		element->SetDoubleAttribute("particle_duration", explosion->getParticleDuration());
		element->SetAttribute("texture", explosion->getTextureFileName());
		if (debris.valid()) {
			TiXmlElement *debrisElement = new TiXmlElement("debris");
			debrisElement->SetDoubleAttribute("scale", explosion->getScale());
			debrisElement->SetDoubleAttribute("intensity", explosion->getIntensity());
			debrisElement->SetDoubleAttribute("emitter_duration", explosion->getEmitterDuration());
			debrisElement->SetDoubleAttribute("particle_duration", explosion->getParticleDuration());
			debrisElement->SetAttribute("texture", explosion->getTextureFileName());
			element->LinkEndChild(debrisElement);
		}
		if (shockDuration > 1e-5) {
			TiXmlElement *shockElement = new TiXmlElement("shock");
			shockElement->SetDoubleAttribute("duration", shockDuration);
			shockElement->SetDoubleAttribute("radius", shockRadius);
			shockElement->SetDoubleAttribute("force", shockForce);
			shockElement->SetDoubleAttribute("damage", shockDamage);
			element->LinkEndChild(shockElement);
		}
	}
	
	void Explosion::initialize()
	{
		destructible = dynamic_cast<moon::Destructible*> (getContainer());
		if (!destructible)
			mlog::dout(mlog::WARN) << "Container of explosion " << getName() << " is not destructible\n";
	}
	
	void Explosion::realize()
	{
		mlog::dout(5) << "Realizing explosion " << getName() << "\n";
		if (isRealized())
			return;
		time = 0;
		moon::BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer());
		if (object) {
			/// \todo Set default radiuses and shock properties based on object bounding sphere and body mass
			if (shockDuration > 1e-5) {
				geometry = new Geometry;
				geometry->addShape(Geometry::SPHERE, shockRadius);
				if (DynamicPhysicalObject *dynamic = dynamic_cast<DynamicPhysicalObject*> (getContainer())) {
					if (dynamic->getBody())
						geometry->setBody(dynamic->getBody());
					else
						geometry->setTransformation(object->getWorldTransformMatrix());
				} else
					geometry->setTransformation(object->getWorldTransformMatrix());
				geometry->setContactCallback(new ExplosiveContactCallback(shockForce, shockDamage, shockDistribution));
				geometry->realize();
				debugNode = geometry->createDebugNode();
				mdraw::setDebugDrawMode(debugNode.get(), mdraw::TRANSPARENT);
				object->addDebugNode(debugNode.get());
			}

			if (object->getDisplayMode() & moon::BaseObject::DISPLAY_NORMAL) {
				explosionInstance = new osgParticle::ExplosionEffect(*explosion.get());
				explosionInstance->getEmitter()->setReferenceFrame(osgParticle::ParticleProcessor::RELATIVE_RF);
				object->addNode(explosionInstance.get());
				if (debris.valid()) {
					debrisInstance = new osgParticle::ExplosionDebrisEffect(*debris.get());
					debrisInstance->setPosition(object->getWorldTransformMatrix().getTrans());
					object->getRoot()->getTransform()->getParent(0)->addChild(debrisInstance.get());
				}
			}
			
		}
		Component::realize();
	}
	
	void Explosion::unrealize()
	{
		if (!isRealized())
			return;
		moon::BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer());
		if (object) {
			object->removeNode(explosionInstance.get());
			if (debrisInstance.valid())
				object->getRoot()->getTransform()->getParent(0)->removeChild(debrisInstance.get());
			object->removeDebugNode(debugNode.get());
		}
		if (geometry.valid())
			geometry->unrealize();
		Component::unrealize();
	}
	
	void Explosion::update(const double dt)
	{
		if (!destructible)
			return;
		if (destructible->isDestroyed() && !lastDestroyed)
			realize();
		else if (!destructible->isDestroyed() && lastDestroyed)
			unrealize();
		lastDestroyed = destructible->isDestroyed();
		if (!isRealized())
			return;
		time += dt;
		if (time > shockDuration && geometry.valid() && geometry->isRealized()) {
			geometry->unrealize();
			moon::BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer());
			if (object)
				object->removeDebugNode(debugNode.get());
		}
		if (time > explosion->getEmitterDuration()+explosion->getParticleDuration()) {
			unrealize();
		}
	}

}
