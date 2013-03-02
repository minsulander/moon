#ifndef MOODYN_CONTROLFORCE_H
#define MOODYN_CONTROLFORCE_H

#include "ContinuousForce.h"
#include <moon/Modifier.h>

namespace moodyn {
	
	/// \brief A controllable ContinuousForce
	/// \ingroup components dynamics
	class MOODYN_EXPORT ControlForce : public ContinuousForce, public moon::ModifierContainer, public moon::ParameterContainer {
	public:
		ControlForce();
		ControlForce(const ControlForce& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, ControlForce);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void update(const double dt);
		
		enum ControlForceModifierTarget {
			NO_TARGET,
			FORCE_X,
			FORCE_Y,
			FORCE_Z,
			TORQUE_X,
			TORQUE_Y,
			TORQUE_Z,
			FORCE_X_MULT,
			FORCE_Y_MULT,
			FORCE_Z_MULT,
			TORQUE_X_MULT,
			TORQUE_Y_MULT,
			TORQUE_Z_MULT
		};
		
	private:
		osg::ref_ptr<moon::Parameter> forceParam, torqueParam;
	};
}

#endif
