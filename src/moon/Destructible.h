#ifndef MOON_DESTRUCTIBLE_H
#define MOON_DESTRUCTIBLE_H

#include "Parsable.h"
#include <map>

#ifdef _MSC_VER
// disable warning about "... needs to have dll-interface"
#	pragma warning(disable:4251)
#endif

namespace moon {
	
	/// \brief An object that can be damaged and ultimately destroyed
	/// \ingroup core
	class MOON_EXPORT Destructible : virtual public Parsable {
	public:

		enum StandardDamageCategories { DEFAULT, CONTACT, CONTACT_TORQUE, FIRE, EXPLOSION };
		
		Destructible();
		Destructible(const Destructible& source);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element, const Destructible *templateObject = NULL) const;
		
		/// Inflict damage of the specified magnitude and (optionally) category
		virtual void damage(const float magnitude, const unsigned int category = DEFAULT);
		/// Get health (%)
		float getHealth() const;
		/// Set health (%)
		void setHealth(const float value);
		/// Destroy the object (set health to 0% and mark it as destroyed)
		virtual void destroy();
		bool isDestroyed() const;
		/// Set damage resistance values
		void setDamageResistance(const float ratio, const float threshold = 0.f, const unsigned int category = DEFAULT);
		/// Get damage ratio for specified category
		float getDamageRatio(const unsigned int category = DEFAULT) const;
		/// Get damage threshold for specified category
		float getDamageThreshold(const unsigned int category = DEFAULT) const;
		/// Get total amount of damage received for the specified category
		float getHealthReduction(const unsigned int category = DEFAULT) const;
		
	protected:
		virtual void undestroy();
		
	private:
		float health;
		bool destroyed;
		typedef std::map< unsigned int, float> DamageMap;
		DamageMap damageThreshold, damageRatio;
		DamageMap healthReduction;
	};
	
}

#endif
