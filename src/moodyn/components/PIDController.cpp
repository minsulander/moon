#include "PIDController.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <limits>

using namespace moon;

namespace moodyn
{
	
	REGISTER_Object_Alias(moodyn, PIDController, PID);
	
	PIDController::PIDController()
	: Component(),
	ref(0.f), in(0.f), out(0.f),
	Kp(0.f), Ki(0.f), Kd(0.f),
	intsum(0.f), prev(0.f),
	inscale(1.f), refscale(1.f)
	{
		outlimit = std::numeric_limits<float>::infinity();
		intmax = std::numeric_limits<float>::infinity();
	}
	
	PIDController::PIDController(const PIDController& source, const osg::CopyOp& copyop)
	: Component(source, copyop),
	ref(0.f), in(0.f), out(0.f),
	Kp(source.Kp), Ki(source.Ki), Kd(source.Kd),
	intsum(0.f), prev(0.f),
	outlimit(source.outlimit), intmax(source.intmax),
	inscale(source.inscale), refscale(source.refscale)
	{
	}
	
	void PIDController::parseXML(const TiXmlElement *element)
	{
		//=== PIDController
		//=see superclass Component
		Component::parseXML(element);
		double value;
		//=* attribute: p="(number)" i="(number)" d="(number)"
		//=. Proportional, integral, derivative gains, respectively.
		if (XMLParser::parseDoubleAttribute(value, element, "p"))
			Kp = value;
		if (XMLParser::parseDoubleAttribute(value, element, "i"))
			Ki = value;
		if (XMLParser::parseDoubleAttribute(value, element, "d"))
			Kd = value;
		//=* attribute: intmax="(number)"
		//=. Maximum integrator sum.
		if (XMLParser::parseDoubleAttribute(value, element, "intmax"))
			intmax = value;
		//=* attribute: limit="(number)"
		//=. Output signal amplitude limit.
		if (XMLParser::parseDoubleAttribute(value, element, "limit"))
			outlimit = value;
		//=* attribute: inscale="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "inscale"))
			inscale = value;
		//=* attribute: refscale="(number)"
		if (XMLParser::parseDoubleAttribute(value, element, "refscale"))
			refscale = value;
	}
	
	void PIDController::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		/// \todo implement
	}
	
	void PIDController::setGain(const float kp, const float ki, const float kd)
	{
		Kp = kp;
		Ki = ki;
		Kd = kd;
	}
	
	void PIDController::update(const double dt)
	{
		/// \todo improve integration and differentiation
		float error = refscale*(ref) - inscale*(in);
		float der = (error-prev)/dt;
		intsum += error*dt;
		if (intsum > intmax)
			intsum = intmax;
		if (intsum < -intmax)
			intsum = -intmax;
		float output = Kp*error + Ki*intsum + Kd*der;
		prev = error;
		if (output > outlimit)
			output = outlimit;
		if (output < -outlimit)
			output = -outlimit;
		out = output;
	}
	
	float PIDController::calculate(const float input, const float reference, const double dt)
	{
		in = input; ref = reference;
		update(dt);
		return out;
	}
	
	void PIDController::reset()
	{
		intsum = 0;
		prev = 0;
	}
	
	void PIDController::setOutputLimit(const float limit)
	{
		outlimit = limit;
	}
	
	void PIDController::setIntMax(const float limit)
	{
		intmax = limit;
	}
	
} // namespace Heli
