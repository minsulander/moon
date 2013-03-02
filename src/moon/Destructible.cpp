#include "Destructible.h"
#include "XMLParser.h"
#include <sstream>

namespace moon {

	Destructible::Destructible()
	: health(100.f), destroyed(false) {}
	
	Destructible::Destructible(const Destructible& source)
	:	health(source.health),
		destroyed(source.destroyed),
		damageThreshold(source.damageThreshold),
		damageRatio(source.damageRatio),
		healthReduction(source.healthReduction)
	{}
	
	void Destructible::parseXML(const TiXmlElement *element)
	{
		double value;
		if (XMLParser::parseDoubleAttribute(value, element, "health"))
			setHealth(value);
		for (const TiXmlElement *damageElement = element->FirstChildElement("damage"); damageElement; damageElement = damageElement->NextSiblingElement("damage")) {
			unsigned int category = DEFAULT;
			std::string catstr;
			if (XMLParser::parseStringAttribute(catstr, damageElement, "category")) {
				if (catstr == "contact")
					category = CONTACT;
				else if (catstr == "contact_torque")
					category = CONTACT_TORQUE;
				else if (catstr == "fire")
					category = FIRE;
				else if (catstr == "explosion")
					category = EXPLOSION;
				else {
					std::stringstream ss; ss.str(catstr);
					if (!(ss >> category))
						throw ParseException("Invalid damage category: " + catstr);
				}
			}
			damageRatio[category] = XMLParser::parseDoubleAttribute(damageElement, "ratio");
			if (XMLParser::parseDoubleAttribute(value, damageElement, "threshold"))
				damageThreshold[category] = value;
		}
	}
	
	void Destructible::writeXML(TiXmlElement *element, const Destructible *templateObject) const
	{
		if ((templateObject && fabs(health-templateObject->health) > 1e-5) || (!templateObject && health < 99.999))
			element->SetAttribute("health", (int)ceil(health));
		for (DamageMap::const_iterator it = damageRatio.begin(); it != damageRatio.end(); it++) {
			DamageMap::const_iterator it_th = damageThreshold.find(it->first);
			if (templateObject) {
				DamageMap::const_iterator tit = templateObject->damageRatio.find(it->first);
				DamageMap::const_iterator tit_th = templateObject->damageThreshold.find(it->first);
				if (tit == templateObject->damageRatio.end() || it->second != tit->second ||
					tit_th == templateObject->damageThreshold.end() || it_th->second != tit_th->second) {
					TiXmlElement *damageElement = new TiXmlElement("damage");
					damageElement->SetAttribute("category", it->first);
					damageElement->SetDoubleAttribute("ratio", it->second);
					damageElement->SetDoubleAttribute("threshold", it_th->second);
					element->LinkEndChild(damageElement);
				}
			}
		}
	}
	
	void Destructible::damage(const float value, const unsigned int category)
	{
		if (!destroyed && damageRatio[category] && value > damageThreshold[category]) {
			float reduce = (value - damageThreshold[category])*damageRatio[category];
			health -= reduce;
			healthReduction[category] += reduce;
			if (health <= 0.f)
				destroy();
		}
	}
	
	float Destructible::getHealth() const { return health; }
	
	void Destructible::setHealth(const float value)
	{
		health = value;
		if (health <= 0.f && !destroyed)
			destroy();
		else if (destroyed)
			undestroy();
	}
	
	void Destructible::destroy()
	{
		health = 0.f;
		destroyed = true;
	}
	
	bool Destructible::isDestroyed() const { return destroyed; }
	
	void Destructible::setDamageResistance(const float ratio, const float threshold, const unsigned int category)
	{
		damageRatio[category] = ratio;
		damageThreshold[category] = threshold;
	}
	
	float Destructible::getDamageRatio(const unsigned int category) const {
		DamageMap::const_iterator it = damageRatio.find(category);
		if (it == damageRatio.end())
			return 0.f;
		return it->second;
	}
	
	float Destructible::getDamageThreshold(const unsigned int category) const {
		DamageMap::const_iterator it = damageThreshold.find(category);
		if (it == damageThreshold.end())
			return 0.f;
		return it->second;
	}
	
	float Destructible::getHealthReduction(const unsigned int category) const
	{
		DamageMap::const_iterator it = healthReduction.find(category);
		if (it == healthReduction.end())
			return 0.f;
		return it->second;
	}
	
	void Destructible::undestroy()
	{
		healthReduction.clear();
		destroyed = false;
	}
	
}
