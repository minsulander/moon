#include "Modifier.h"
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <mlog/Log.h>
#include <iostream>
#include <sstream>
#include <cmath>

namespace moon {
	
	// Register objects with factory
	REGISTER_Object_Alias(moon, Modifier, Modifier);
	REGISTER_Object_Alias(moon, Table, Table);
	REGISTER_Object_Alias(moon, Range, Range);
	//REGISTER_Object_Alias(moon, Smooth, Smooth);
	
	Modifier::Modifier()
    : parameter(NULL), value(0), ratio(1), offset(0), targetIndex(0)
	{
	}
	
	Modifier::Modifier(const Modifier& other, const osg::CopyOp& copyop)
	: parameter(other.parameter), value(other.value), ratio(other.ratio), offset(other.offset),
	  targetIndex(other.targetIndex), targetStr(other.targetStr)
	{
		// the name is used as an identifier for which parameter to connect to
		setName(other.getName());
	}
	
	Modifier::~Modifier()
	{
		if (parameter.valid())
			parameter->disconnect();
	}
	
	void Modifier::set(const float nvalue)
	{
		value = nvalue;
	}
	
	float Modifier::get() const
	{
		if (parameter.valid())
			 return calculate(parameter->get());
		return calculate(value);
	}
	
	float Modifier::calculate(const float val) const
	{
		return val * ratio + offset;
	}
	
	void Modifier::setParameter(Parameter *param)
	{
		if (parameter == param)
			return;
		if (parameter.valid())
			parameter->disconnect();
		parameter = param;
		if (parameter.valid())
			parameter->connect();
	}
	
	void Modifier::parseXML(const TiXmlElement *element)
	{
		//=== Modifier
		std::string str;
		//=* attribute: param="(name)"
		if (XMLParser::parseStringAttribute(str, element, "param"))
			setName(str);
		//=* attribute: target="(name or integer)"
		XMLParser::parseStringAttribute(targetStr, element, "target");
		int i;
		if (XMLParser::parseIntAttribute(i, element, "target"))
			targetIndex = i;
		//=* attribute: ratio="(number)" offset="(number)"
		//=. Scaling and offset applied to input parameter (value = param * ratio + offset).
		double val;
		if (XMLParser::parseDoubleAttribute(val, element, "ratio"))
			ratio = val;
		if (XMLParser::parseDoubleAttribute(val, element, "offset"))
			offset = val;
	}
	
	void Modifier::writeXML(TiXmlElement *element) const
	{
		if (targetStr.length() > 0)
			element->SetAttribute("target", targetStr);
		if (getName().length() > 0)
			element->SetAttribute("param", getName());
		if (fabs(ratio-1.f) > 1e-5)
			element->SetDoubleAttribute("ratio", ratio);
		if (fabs(offset) > 1e-5)
			element->SetDoubleAttribute("offset", offset);
	}
	
	Table::Table()
    :	Modifier()
	{
	}
	
	Table::Table(const Table& other, const osg::CopyOp& copyop)
	:	Modifier(other),
	in(other.in),
	out(other.out)
	{
	}
	
	void Table::parseXML(const TiXmlElement *element)
	{
		//=== Table
		//=See superclass Modifier
		//=* text
		//=. Table of parameter (input) and corresponding modifier (output) values
		std::string svalues = element->GetText();
		std::size_t j = 0;
		while ((j = svalues.find_first_of(",:;/=", j)) != std::string::npos)
			svalues[j] = ' ';
		std::stringstream ssvalues(svalues);
		float i,o;
		while (ssvalues >> i && ssvalues >> o) {
			add(i,o);
		}
		Modifier::parseXML(element);
	}
	
	void Table::writeXML(TiXmlElement *element) const
	{
		std::stringstream ss;
		for (unsigned int i = 0; i < in.size(); i++) {
			ss << in[i] << "=" << out[i] << " ";
		}
		TiXmlText *text = new TiXmlText(ss.str());
		element->LinkEndChild(text);
	}
	
	float interpolateLinear(const std::vector<float>& x, const std::vector<float>& y, const float xi)
	{
		int len = x.size();
		if (x[len-1] > x[0]) {
			int idx = -1;
			for (int i = 0; i < len; i++) {
				if (x[i] > xi) {
					idx = i;
					break;
				}
			}
			if (idx < 0)
				return y[len-1];
			else if (idx == 0)
				return y[0];
			else
				return y[idx-1]+(y[idx]-y[idx-1])/(x[idx]-x[idx-1])*(xi-x[idx-1]);
		} else if (x[len-1] < x[0]) {
			int idx = -1;
			for (int i = 0; i < len; i++) {
				if (x[i] < xi) {
					idx = i;
					break;
				}
			}
			if (idx < 0)
				return y[len-1];
			else if (idx == 0)
				return y[0];
			else
				return y[idx]+(y[idx]-y[idx-1])/(x[idx]-x[idx-1])*(xi-x[idx-1]);
		} else
			return y[0];
	}
	
	float Table::calculate(const float val) const
	{
		return interpolateLinear(in, out, Modifier::calculate(val));
	}
	
	void Table::add(const float inval, const float outval)
	{
		in.push_back(inval);
		out.push_back(outval);
	}
	
	Range::Range()
    :	Modifier(),
	low(0),
	high(0),
	within_value(1),
	outside_value(0),
	low_set(false),
	high_set(false),
	abs_value(false)
	{
	}
	
	Range::Range(const Range& other, const osg::CopyOp& copyop)
	:	Modifier(other),
	low(other.low),
	high(other.high),
	within_value(other.within_value),
	outside_value(other.outside_value),
	low_set(other.low_set),
	high_set(other.high_set),
	abs_value(other.abs_value)
	{
	}
	
	void Range::parseXML(const TiXmlElement *element)
	{
		//=== Range
		//=See superclass Modifier
		//=* attribute: lo="(number)" hi="(number)"
		//=. High and low limits of paremeter (input) values that define the range.
		double value;
		if (XMLParser::parseDoubleAttribute(value, element, "lo"))
			setLow(value);
		if (XMLParser::parseDoubleAttribute(value, element, "hi"))
			setHigh(value);
		//=* attribute: within="(number)" outside="(number)"
		//=. Modifier (output) value when parameter (input) value is within and outside the range, respectively.
		if (XMLParser::parseDoubleAttribute(value, element, "within"))
			within_value = value;
		if (XMLParser::parseDoubleAttribute(value, element, "outside"))
			outside_value = value;
		//=* attribute: abs="true|false"
		XMLParser::parseBooleanAttribute(abs_value, element, "abs");
		Modifier::parseXML(element);
	}
	
	float Range::calculate(const float val) const
	{
		float value = within_value;
		float invalue = Modifier::calculate(val);
		if (abs_value)
			invalue = std::fabs(Modifier::get());
		if (low_set && invalue < low)
			value = outside_value;
		if (high_set && invalue > high)
			value = outside_value;
		return value;
	}
	
	void Range::setLow(const float nlow) { low = nlow; low_set = true; }
	void Range::setHigh(const float nhigh) { high = nhigh; high_set = true; }
	void Range::setWithinValue(const float value) { within_value = value; }
	void Range::setOutsideValue(const float value) { outside_value = value; }
	
	/*
	 Smooth::Smooth(Sound* object, TargetProperty nproperty)
	 :	Modifier(object),
	 SimulationListener(),
	 max_delta(-1.0),
	 min_delta(-1.0)
	 {
	 property = nproperty;
	 target_value = value = -1.234;
	 }
	 
	 Smooth::Smooth(const Smooth& other, const osg::CopyOp& copyop)
	 :	Modifier(other),
	 SimulationListener(),
	 max_delta(other.max_delta),
	 min_delta(other.min_delta),
	 target_value(other.target_value),
	 value(other.value)
	 {
	 }
	 
	 void Smooth::parseXML(const TiXmlElement *element)
	 {
	 double value;
	 if (XMLParser::parseDoubleAttribute(value, element, "maxdelta"))
	 max_delta = value;
	 if (XMLParser::parseDoubleAttribute(value, element, "mindelta"))
	 min_delta = value;
	 Modifier::parseXML(element);
	 }
	 
	 void Smooth::set(const float nvalue)
	 {
	 //target_value = nvalue;
	 target_value = getCurrentValue();
	 // no direct modifications
	 if (value >= 0)
	 Modifier::set(value);
	 }
	 
	 void Smooth::update(const double dt)
	 {
	 if (!parameter || !sound.valid())
	 return;
	 if (value < 0)
	 value = getCurrentValue();
	 if (target_value < 0)
	 target_value = getCurrentValue();
	 if (max_delta >= 0) {
	 if (value < target_value && (target_value - value)/dt > max_delta)
	 value += max_delta*dt;
	 else if (value > target_value && (value - target_value)/dt > max_delta)
	 value -= max_delta*dt;
	 else
	 value = target_value;
	 } else
	 value = target_value;
	 if (min_delta >= 0) {
	 if (std::fabs(value - getCurrentValue()) < min_delta)
	 value = getCurrentValue();
	 }
	 Modifier::set(value);
	 }
	 */
	
	ModifierContainer::ModifierContainer()
	{
	}
	
	ModifierContainer::ModifierContainer(const ModifierContainer& source, const osg::CopyOp& copyop)
	{
		for (unsigned int i = 0; i < source.getNumModifiers(); i++) {
			Modifier *mod = dynamic_cast<Modifier*> (source.getModifier(i)->clone(copyop));
			if (mod) {
				addModifier(mod);
			}
		}
	}
	
	unsigned int ModifierContainer::getNumModifiers() const { return modifiers.size(); }
	Modifier* ModifierContainer::getModifier(const unsigned int i) { return modifiers[i].get(); }
	const Modifier* ModifierContainer::getModifier(const unsigned int i) const { return modifiers[i].get(); }
	void ModifierContainer::addModifier(Modifier *mod) { modifiers.push_back(mod); }
	
	void ModifierContainer::removeModifier(Modifier *mod)
	{
		for (ModifierList::iterator it = modifiers.begin(); it != modifiers.end(); it++) {
			if (*it == mod) {
				modifiers.erase(it);
				break;
			}
		}
	}
	
	void ModifierContainer::parseXML(const TiXmlElement *element)
	{
		ObjectFactory::ObjectList objects = ObjectFactory::instance().parseObjects(element, false);
		for (ObjectFactory::ObjectList::iterator it = objects.begin(); it != objects.end(); it++) {
			Modifier *mod = dynamic_cast<Modifier*> (it->get());
			if (mod)
				addModifier(mod);
		}
	}
	
	void ModifierContainer::writeXML(TiXmlElement *element) const
	{
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			const Modifier *mod = getModifier(i);
			TiXmlElement *modElement = new TiXmlElement(mod->libraryName() + std::string("_") + mod->className());
			mod->writeXML(modElement);
			element->LinkEndChild(modElement);
		}
	}
	
} // namespace
