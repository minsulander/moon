#include "ControlForce.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>
#include <moon/objects/BaseObject.h>

using namespace moon;
using namespace mlog;

namespace moodyn {

	REGISTER_Object_Alias(moodyn, ControlForce, ControlForce);

	ControlForce::ControlForce()
	:	ContinuousForce(),
		ModifierContainer(),
		ParameterContainer()
	{
		forceParam = new moon::Parameter("force", this);
		torqueParam = new moon::Parameter("torque", this);
	}
	
	ControlForce::ControlForce(const ControlForce& source, const osg::CopyOp& copyop)
	:	ContinuousForce(source, copyop),
		ModifierContainer(source, copyop),
		ParameterContainer(source, copyop)
	{
		forceParam = new moon::Parameter("force", this);
		torqueParam = new moon::Parameter("torque", this);
	}
	
	void ControlForce::parseXML(const TiXmlElement *element)
	{
		//=== ControlForce
		//=see superclass ContinuousForce
		ContinuousForce::parseXML(element);
		// Parse modifiers
		//=* modifier targets: x y z torqex torquey torquez x* y* z* torquex* torquey* torquez*
		ModifierContainer::parseXML(element);
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			std::string target = mod->getTargetName();
			if (target == "x" || target == "forcex")
				mod->setTargetIndex(FORCE_X);
			else if (target == "y" || target == "forcey")
				mod->setTargetIndex(FORCE_Y);
			else if (target == "z" || target == "forcez")
				mod->setTargetIndex(FORCE_Z);
			else if (target == "torquex")
				mod->setTargetIndex(TORQUE_X);
			else if (target == "torquey")
				mod->setTargetIndex(TORQUE_Y);
			else if (target == "torquez")
				mod->setTargetIndex(TORQUE_Z);
			else if (target == "x*" || target == "forcex*")
				mod->setTargetIndex(FORCE_X_MULT);
			else if (target == "y*" || target == "forcey*")
				mod->setTargetIndex(FORCE_Y_MULT);
			else if (target == "z*" || target == "forcez*")
				mod->setTargetIndex(FORCE_Z_MULT);
			else if (target == "torquex*")
				mod->setTargetIndex(TORQUE_X_MULT);
			else if (target == "torquey*")
				mod->setTargetIndex(TORQUE_Y_MULT);
			else if (target == "torquez*")
				mod->setTargetIndex(TORQUE_Z_MULT);
		}
	}
	
	void ControlForce::writeXML(TiXmlElement *element) const
	{
		ContinuousForce::writeXML(element);
		ModifierContainer::writeXML(element);
	}
	
	void ControlForce::initialize()
	{
		ContinuousForce::initialize();
		if (getNumModifiers() > 0) {
			BaseObject* object = dynamic_cast<BaseObject*> (getContainer());
			if (!object) {
				dout(ERROR) << "Container for ControlForce '" << getName() << "' is not a BaseObject\n";
				return;
			}
			for (unsigned int i = 0; i < getNumModifiers(); i++) {
				Modifier *mod = getModifier(i);
				if (Parameter *param = object->findParameter(mod->getName())) {
					mod->setParameter(param);
					dout(5) << "ControlForce modifer " << object->getName() << ":" << mod->getName() << " connected\n";
				}
			}
		}
	}
	
	void ControlForce::update(const double dt)
	{
		osg::Vec3 F, Q;
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			const Modifier *mod = getModifier(i);
			switch (mod->getTargetIndex()) {
				case FORCE_X: F += osg::Vec3(mod->get(), 0, 0); break;
				case FORCE_Y: F += osg::Vec3(0, mod->get(), 0); break;
				case FORCE_Z: F += osg::Vec3(0, 0, mod->get()); break;
				case TORQUE_X: Q += osg::Vec3(mod->get(), 0, 0); break;
				case TORQUE_Y: Q += osg::Vec3(0, mod->get(), 0); break;
				case TORQUE_Z: Q += osg::Vec3(0, 0, mod->get()); break;
				case FORCE_X_MULT: F.x() *= mod->get(); break;
				case FORCE_Y_MULT: F.y() *= mod->get(); break;
				case FORCE_Z_MULT: F.z() *= mod->get(); break;
				case TORQUE_X_MULT: Q.x() *= mod->get(); break;
				case TORQUE_Y_MULT: Q.y() *= mod->get(); break;
				case TORQUE_Z_MULT: Q.z() *= mod->get(); break;
			}
		}
		setForce(F);
		setTorque(Q);
		ContinuousForce::update(dt);
		if (forceParam.valid())
			forceParam->set(F.length());
		if (torqueParam.valid())
			torqueParam->set(Q.length());
	}
	
} // namespace
