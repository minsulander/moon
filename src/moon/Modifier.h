#ifndef MOON_MODIFIER_H
#define MOON_MODIFIER_H

#include "FactoryProduct.h"
#include "Parameter.h"
#include <osg/observer_ptr>
#include <vector>
#include <map>
#include <string>

namespace moon {
	
	/// \brief Modifies a property of a ModifierContainer depending on the value of a Parameter
	/// \ingroup core
	class MOON_EXPORT Modifier : public moon::FactoryProduct {
	public:
		Modifier();
		Modifier(const Modifier& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Modifier);
		
		virtual ~Modifier();
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Set default value to use when not tied to a Parameter
		void set(const float value);
		/// Get the current target value
		float get() const;
		/// Calculate output based on input value
		virtual float calculate(const float value) const;
		/// Set the input parameter
		void setParameter(Parameter *param);
		/// Get the input parameter
		Parameter* getParameter() { return parameter.get(); }
		/// Set ratio between parameter (input) and modifier (output) value
		void setRatio(const float val) { ratio = val; }
		/// Get ratio between parameter (input) and modifier (output) value
		float getRatio() const { return ratio; }
		/// Set offset between parameter (input) and modifier (output) value
		void setOffset(const float val) { offset = val; }
		/// Set offset between parameter (input) and modifier (output) value
		float getOffset() const { return offset; }
		
		void setTargetIndex(const unsigned int value) { targetIndex = value; }
		unsigned int getTargetIndex() const { return targetIndex; }
		const std::string& getTargetName() const { return targetStr; }
		
	private:
		osg::observer_ptr<Parameter> parameter;
		float value, ratio, offset;
		unsigned int targetIndex;
		std::string targetStr;
	};
	
	/// Table interpolation modifier
	class MOON_EXPORT Table : public Modifier {
	public:
		Table();
		Table(const Table& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Table);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual float calculate(const float val) const;
		void add(const float inval, const float outval);
		
	private:
		std::vector<float> in, out;
	};
	
	/// Simple range modifier
	class MOON_EXPORT Range : public Modifier {
	public:
		Range();
		Range(const Range& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Range);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual float calculate(const float val) const;
		/// Set low end of the range
		void setLow(const float value);
		/// Set high end of the range
		void setHigh(const float value);
		/// Value of the target to be set when the Parameter is within the range
		void setWithinValue(const float value);
		/// Value of the target to be set when the Parameter is outside the range
		void setOutsideValue(const float value);
	private:
		float low, high, within_value, outside_value;
		bool low_set, high_set, abs_value;
	};
	
	/*
	 /// "Smoothing" modifier used to avoid abrupt changes in a sound property
	 class Smooth : public Modifier, public moon::SimulationListener {
	 public:
	 Smooth(Sound *object = NULL, TargetProperty property=GAIN);
	 Smooth(const Smooth& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
	 META_Object(moon, Smooth);
	 
	 virtual void parseXML(const TiXmlElement *element);
	 virtual void set(const float value);
	 virtual void update(const double dt);
	 private:
	 float max_delta, min_delta, value, target_value;
	 };
	 */
	
	/// \brief Container for modifiers
	/// \ingroup core
	class MOON_EXPORT ModifierContainer : virtual public Parsable {
	public:
		ModifierContainer();
		ModifierContainer(const ModifierContainer& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		unsigned int getNumModifiers() const;
		Modifier* getModifier(const unsigned int index);
		const Modifier* getModifier(const unsigned int index) const;
		void addModifier(Modifier *modifier);
		void removeModifier(Modifier *modifier);
		
		virtual void parseXML(const TiXmlElement* element);
		virtual void writeXML(TiXmlElement* element) const;
		
	private:
		typedef std::vector< osg::ref_ptr<Modifier> > ModifierList;
		ModifierList modifiers;
	};
	
	/// Exception thrown by Modifier classes on errors
	class MOON_EXPORT ModifierException : public std::exception {
	public:
		ModifierException(const std::string& nmessage, const Modifier* nmod = NULL) { 
			message = nmessage;
			modifier = nmod;
		}
		
		~ModifierException() throw() { modifier = NULL; }
		virtual const char* what() const throw() { return message.c_str(); }
		const Modifier *getModifier() { return modifier; }
	private:
		std::string message;
		const Modifier *modifier;
	};
	
}

#endif
