#ifndef MOODYN_PIDCONTROLLER_H
#define MOODYN_PIDCONTROLLER_H

#include "moodyn/Export.h"
#include <moon/components/Component.h>

namespace moodyn {
	
	/// \brief Simple model of a one-variable PID controller
	/// \ingroup components dynamics
	class MOODYN_EXPORT PIDController : public moon::Component
	{
	public:
		PIDController();
		PIDController(const PIDController& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, PIDController);
		
		void parseXML(const TiXmlElement* element);
		void writeXML(TiXmlElement* element) const;
		
		void setGain(const float kp, const float ki = 0.0, const float kd = 0.0);
		virtual void update(const double dt);
		float calculate(const float in, const float ref, const double dt);
		void reset();
		
		void setInput(const float value) { in = value; }
		float getInput() const { return in; }
		void setRef(const float value) { ref = value; }
		float getRef() const { return ref; }
		
		void setOutputLimit(const float limit);
		float getOutputLimit() const { return outlimit; }
		float getKp() const { return Kp; }
		float getKi() const { return Ki; }
		float getKd() const { return Kd; }
		void setIntMax(const float limit);
		float getIntMax() const { return intmax; }
		void setInScale(const float scale) { inscale = scale; }
		float getInScale() const { return inscale; }
		void setRefScale(const float scale) { refscale = scale; }
		float getRefScale() const { return refscale; }
		float getOutput() const { return out; }
		
	protected:
		float ref, in, out;
		// Proportional, integerator and derivator gains
		float Kp, Ki, Kd;
		// Integrator sum and previous values for derivator
		float intsum, prev;
		// Limits and scaling
		float outlimit, intmax;
		float inscale, refscale;
	};
}

#endif
