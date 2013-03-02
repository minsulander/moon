#ifndef MOODYN_EXPLOSION_H
#define MOODYN_EXPLOSION_H

#include "Geometry.h"
#include <moon/components/Component.h>
#include <moon/Destructible.h>
#include <osgParticle/ExplosionEffect>
#include <osgParticle/ExplosionDebrisEffect>

namespace moodyn {
	
	/// \brief Simulation component for explosions
	/// \ingroup components dynamics
	class Explosion : public moon::Component {
	public:
		Explosion();
		Explosion(const Explosion& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Explosion);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;

		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		
		enum ShockDistribution { CONSTANT, LINEAR, QUADRATIC, SPHERICAL };
		
	private:
		osg::ref_ptr<osgParticle::ExplosionEffect> explosion;
		osg::ref_ptr<osgParticle::ExplosionDebrisEffect> debris;
		osg::observer_ptr<osgParticle::ExplosionEffect> explosionInstance;
		osg::observer_ptr<osgParticle::ExplosionDebrisEffect> debrisInstance;
		osg::ref_ptr<Geometry> geometry;
		osg::observer_ptr<osg::Node> debugNode;
		moon::Destructible *destructible;
		double time;
		bool lastDestroyed;
		double shockDuration;
		float shockRadius, shockForce, shockDamage;
		ShockDistribution shockDistribution;
	};
}

#endif
