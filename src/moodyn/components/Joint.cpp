#include "Joint.h"
#include "moodyn/World.h"
#include "moodyn/ode_osg.h"
#include <mlog/Log.h>
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <moon/objects/BaseObject.h>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/io_utils>

using namespace moon;
using namespace mlog;

/// Reference mass defined by World - used to keep masses around 1 and scale forces/torques etc
/// appropriately. This should help improve numerical stability of ODE.
#define REFMASS World::instance().getReferenceMass()

namespace moodyn
{
	
	REGISTER_Object_Alias(moodyn, Joint, Joint);
	
	class SliderJointCallback : public osg::NodeCallback {
	public:
		SliderJointCallback(Joint* j, int w) : joint(j),which(w) {}
		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
			if (!node || nv->getVisitorType() != osg::NodeVisitor::UPDATE_VISITOR || !nv->getFrameStamp() || !joint || !joint->getBody1())
				return;
			osg::Geode* geode = (osg::Geode*) node;
			osg::CompositeShape* cshape = (osg::CompositeShape*) geode->getDrawable(0)->getShape();
			osg::Cylinder* cyl = (osg::Cylinder*) cshape->getChild(0);
			
			if (which == 1) {
				osg::Vec3 pos2;
				if (joint->getBody2())
					pos2 = joint->getBody2()->getPosition();
				else
					pos2 = joint->getBody1()->getPosition()+joint->getAxis(false);
				osg::Vec3 pos;
				pos = joint->getBody1()->getRotation().inverse()*(pos2-joint->getBody1()->getPosition());
				osg::Quat rot;
				rot.makeRotate(osg::Vec3(0,0,1),pos);
				cyl->setHeight(pos.length()*0.5);
				cyl->setCenter(pos*0.25);
				cyl->setRotation(rot);
				geode->getDrawable(0)->dirtyDisplayList();
			} else if (joint->getBody2()) {
				osg::Vec3 pos;
				pos = joint->getBody2()->getRotation().inverse()*(joint->getBody1()->getPosition()-joint->getBody2()->getPosition());
				osg::Quat rot;
				rot.makeRotate(osg::Vec3(0,0,1),pos);
				cyl->setHeight(pos.length()*0.5);
				cyl->setCenter(pos*0.25);
				cyl->setRotation(rot);
				geode->getDrawable(0)->dirtyDisplayList();
			}
		}
	protected:
		Joint* joint;
		int which;
	};
	
	osg::TessellationHints* Joint::default_hints = NULL;
	osg::Vec4 Joint::default_color1 = osg::Vec4(0.5f, 0.5f, 0.7f, 0.5f);
	osg::Vec4 Joint::default_color2 = osg::Vec4(0.7f, 0.5f, 0.1f, 0.5f);
	
	Joint::Joint(const JointType newtype)
	:	moon::Component(),
		moon::ModifierContainer(),
		moon::ParameterContainer(),
		type(newtype),
		jointID(NULL),
		body1(NULL),
		body2(NULL),
		pendingAttachment(false),
		breakImpulse(dInfinity),
		breakAngularImpulse(dInfinity),
		feedback(NULL),
		refDeflection(0.f),
		refDeflection2(0.f),
		steerDeflection(0.f),
		steerDeflection2(0.f),
		resetRefDeflection(0.f),
		resetRefDeflection2(0.f),
		steering(false),
		steering2(false),
		debugscale(0.2f)
	{
		steerParam = new moon::Parameter("steer", this);
		forceParam = new moon::Parameter("force", this);
		torqueParam = new moon::Parameter("torque", this);
		parameters[STEER_TOLERANCE] = 1e-5f;
		parameters[STEER_TOLERANCE2] = 1e-5f;
	}
	
	Joint::Joint(const Joint& joint, const osg::CopyOp copyop)
	:	moon::Component(joint, copyop),
		moon::ModifierContainer(joint, copyop),
		moon::ParameterContainer(joint, copyop),
		type(joint.type),
		jointID(NULL),
		body1(joint.body1),
		body2(joint.body2),
		connectName(joint.connectName),
		pendingAttachment(false),
		anchor(joint.anchor),
		axis(joint.axis),
		axis2(joint.axis2),
		parameters(joint.parameters),
		breakImpulse(joint.breakImpulse),
		breakAngularImpulse(joint.breakAngularImpulse),
		feedback(NULL),
		refDeflection(joint.refDeflection),
		refDeflection2(joint.refDeflection2),
		steerDeflection(joint.steerDeflection),
		steerDeflection2(joint.steerDeflection2),
		resetRefDeflection(joint.resetRefDeflection),
		resetRefDeflection2(joint.resetRefDeflection2),
		steering(false),
		steering2(false),
		debugscale(joint.debugscale)
	{
		steerParam = new moon::Parameter("steer", this);
		forceParam = new moon::Parameter("force", this);
		torqueParam = new moon::Parameter("torque", this);
	}
	
	Joint::~Joint()
	{
		if (feedback)
			delete feedback;
		unrealize();
	}
	
	void Joint::parseXML(const TiXmlElement* element)
	{
		Component::parseXML(element);
		if (!element->Value())
			return;
		
		//=== Joint
		//=* attribute: type="ball|hinge|slider|universal|hinge2|fixed|amotor"
		// Parse joint type
		std::string typestr;
		if (XMLParser::parseStringAttribute(typestr, element,"type")) {
			if (typestr == std::string("ball"))				type = BALL;
			else if (typestr == std::string("hinge"))		type = HINGE;
			else if (typestr == std::string("slider"))		type = SLIDER;
			else if (typestr == std::string("universal"))	type = UNIVERSAL;
			else if (typestr == std::string("hinge2"))		type = HINGE2;
			else if (typestr == std::string("fixed"))		type = FIXED;
			else if (typestr == std::string("amotor"))		type = AMOTOR;
			else throw ParseException("Unknown joint type '" + typestr + "'", element);
			dout(4) << "   " << typestr << " joint";
		}
		if (type == NONE)
			throw ParseException("Missing joint type for '" + getName() + "'", element);
		
		//=* attribute: connect="(string)"
		//=. Name of object to connect the joint to
		XMLParser::parseStringAttribute(connectName, element, "connect");
		
		/// \todo Document joint parameters
		//=See the ODE manual for explanations of these joint parameters.

		// Parse joint anchor and axis
		//=* attribute or element: anchor pos="(vector3)" [m]
		if (type != SLIDER && type != FIXED) {
			osg::Vec3 anchor;
			if (XMLParser::parseVector3Attribute(anchor, element, "anchor") ||
				XMLParser::parseVector3(anchor, element, "anchor", "m", "pos"))
				setAnchor(anchor);
		}
		//=* attribute or element: axis value="(vector3)" (applicable to all but ''ball'' and ''fixed'' joints)
		if (type != BALL && type != FIXED) {
			osg::Vec3 axis;
			if (XMLParser::parseVector3Attribute(axis, element, "axis") ||
				XMLParser::parseVector3(axis, element, "axis", ""))
				setAxis(axis);
		}
		//=** attribute or element: axis2 value="(vector3)" (applicable to ''universal'' and ''hinge2'' joints)
		if (type == UNIVERSAL || type == HINGE2) {
			osg::Vec3 axis2;
			if (XMLParser::parseVector3Attribute(axis2, element, "axis2") ||
				XMLParser::parseVector3(axis2, element, "axis2", ""))
				setAxis2(axis2);
		}
		
		// Parse ODE parameters
		std::string unit = "radian";
		std::string unit2 = "radian/s";
		std::string unit3 = "N m";
		if (type == SLIDER) {
			unit = "m";
			unit2 = "m/s";
			unit3 = "N";
		}
		double value;
		//=Units of the following parameters vary depending on joint type.
		//=* element: stop lo="(number)" hi="(number)"
		if (XMLParser::parseDouble(value,element,"stop",unit,"lo")) setParameter(LOSTOP, value);
		if (XMLParser::parseDouble(value,element,"stop",unit,"hi")) setParameter(HISTOP, value);
		//=* element: velocity value="(number)"
		if (XMLParser::parseDouble(value,element,"velocity",unit2)) setParameter(VELOCITY, value);
		//=* element: maxforce value="(number)"
		if (XMLParser::parseDouble(value,element,"maxforce",unit3)) setParameter(MAXFORCE, value/REFMASS);
		//=* element: fudge value="(number)"
		if (XMLParser::parseDouble(value,element,"fudge","")) setParameter(FUDGE, value);
		//=* element: bounce value="(number)"
		if (XMLParser::parseDouble(value,element,"bounce","")) setParameter(BOUNCE, value);
		//=* element: cfm value="(number)"
		if (XMLParser::parseDouble(value,element,"cfm","")) setParameter(CFM, value);
		//=* element: stop_erp value="(number)"
		if (XMLParser::parseDouble(value,element,"stop_erp","")) setParameter(STOP_ERP, value);
		//=* element: stop_cfm value="(number)"
		if (XMLParser::parseDouble(value,element,"stop_cfm","")) setParameter(STOP_CFM, value);
		//=* element: suspension_erp value="(number)"
		if (XMLParser::parseDouble(value,element,"suspension_erp","")) setParameter(SUSPENSION_ERP, value);
		//=* element: suspension_cfm value="(number)"
		if (XMLParser::parseDouble(value,element,"suspension_cfm","")) setParameter(SUSPENSION_CFM, value);
		//=Joint parameters '''stop2''' to '''suspension_cfm2''' can be specified for second axis, if applicable.
		//=These are specified the same way as above.
		if (XMLParser::parseDouble(value,element,"stop2",unit,"lo")) setParameter(LOSTOP2, value);
		if (XMLParser::parseDouble(value,element,"stop2",unit,"hi")) setParameter(HISTOP2, value);
		if (XMLParser::parseDouble(value,element,"velocity2",unit2)) setParameter(VELOCITY2, value);
		if (XMLParser::parseDouble(value,element,"maxforce2",unit3)) setParameter(MAXFORCE2, value/REFMASS);
		if (XMLParser::parseDouble(value,element,"fudge2","")) setParameter(FUDGE2, value);
		if (XMLParser::parseDouble(value,element,"bounce2","")) setParameter(BOUNCE2, value);
		if (XMLParser::parseDouble(value,element,"cfm2","")) setParameter(CFM2, value);
		if (XMLParser::parseDouble(value,element,"stop_erp2","")) setParameter(STOP_ERP2, value);
		if (XMLParser::parseDouble(value,element,"stop_cfm2","")) setParameter(STOP_CFM2, value);
		if (XMLParser::parseDouble(value,element,"suspension_erp2","")) setParameter(SUSPENSION_ERP2, value);
		if (XMLParser::parseDouble(value,element,"suspension_cfm2","")) setParameter(SUSPENSION_CFM2, value);
		if (XMLParser::parseDouble(value,element,"stop3",unit,"lo")) setParameter(LOSTOP3, value);
		if (XMLParser::parseDouble(value,element,"stop3",unit,"hi")) setParameter(HISTOP3, value);
		if (XMLParser::parseDouble(value,element,"velocity3",unit2)) setParameter(VELOCITY3, value);
		if (XMLParser::parseDouble(value,element,"maxforce3",unit3)) setParameter(MAXFORCE3, value/REFMASS);
		if (XMLParser::parseDouble(value,element,"fudge3","")) setParameter(FUDGE3, value);
		if (XMLParser::parseDouble(value,element,"bounce3","")) setParameter(BOUNCE3, value);
		if (XMLParser::parseDouble(value,element,"cfm3","")) setParameter(CFM3, value);
		if (XMLParser::parseDouble(value,element,"stop_erp3","")) setParameter(STOP_ERP3, value);
		if (XMLParser::parseDouble(value,element,"stop_cfm3","")) setParameter(STOP_CFM3, value);
		if (XMLParser::parseDouble(value,element,"suspension_erp3","")) setParameter(SUSPENSION_ERP3, value);
		if (XMLParser::parseDouble(value,element,"suspension_cfm3","")) setParameter(SUSPENSION_CFM3, value);
		//=* element: spring value="(number)" [N/m]
		//=. Spring constant. If specified, adds spring forces to the joint.
		if (XMLParser::parseDouble(value,element,"spring","N/m"))
			setParameter(SPRING, value);
		if (XMLParser::parseDouble(value,element,"spring2","N/m"))
			setParameter(SPRING2, value);
		//=* element: damp value="(number)" [N s / m]
		//=. Daming constant. If specified, adds damping forces to the joint.
		if (XMLParser::parseDouble(value,element,"damp","N s / m"))
			setParameter(DAMP, value);
		if (XMLParser::parseDouble(value,element,"damp2","N s / m"))
			setParameter(DAMP2, value);
		for (ParameterMap::iterator i = parameters.begin(); i != parameters.end(); i++)
			dout(4) << " param" << i->first << "=" << i->second;

		//=* element: steervelocity value="(number)" [m/s or rad/s]
		if (XMLParser::parseDouble(value,element,"steervelocity", unit2)) setParameter(STEER_VELOCITY, value);
		if (XMLParser::parseDouble(value,element,"steervelocity2", unit2)) setParameter(STEER_VELOCITY2, value);
		//=* element: steertolerance value="(number)" [m or rad]
		if (XMLParser::parseDouble(value,element,"steertolerance", unit)) setParameter(STEER_TOLERANCE, value);
		if (XMLParser::parseDouble(value,element,"steertolerance2", unit)) setParameter(STEER_TOLERANCE2, value);

		//=* element: break value="(number)" [N s]
		//=. If joint force impulse exceeds this value, the joint will detach.
		breakImpulse = XMLParser::parseDouble(element,"break","N s",true,dInfinity);
		//=* element: breakAngularImpulse value="(number)" [N m s]
		//=. If joint angular (torque) impulse exceeds this value, the joint will detach.
		breakAngularImpulse = XMLParser::parseDouble(element,"break_angular","N m s",true,dInfinity);
		
		dout(4) << "\n";

		// Parse modifiers
		//=* modifier targets: steer steer2
		ModifierContainer::parseXML(element);
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			std::string target = mod->getTargetName();
			if (target == "1" || target == "steer" || target == "steer1")
				mod->setTargetIndex(STEER);
			else if (target == "2" || target == "steer2")
				mod->setTargetIndex(STEER2);
		}
	}
	
	void Joint::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		ModifierContainer::writeXML(element);
		/// \todo Implement
	}
	
	osg::Vec3 Joint::getAnchor(const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			return body1->getTransformation().getRotate()*anchor + body1->getTransformation().getTrans();
		else if (!relativebody1 && body2.valid() && body1.valid())
			return body2->getTransformation().getRotate().inverse() * (body1->getTransformation().getTrans() + body1->getTransformation().getRotate()*anchor - body2->getTransformation().getTrans());
		return anchor;
	}
	
	void Joint::setAnchor(const osg::Vec3& newanchor, const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			anchor = body1->getTransformation().getRotate().inverse()*(newanchor - body1->getTransformation().getTrans());
		else if (!relativebody1 && body2.valid() && body1.valid())
			anchor = body1->getTransformation().getRotate().inverse()*(body2->getTransformation().getRotate()*newanchor + body2->getTransformation().getTrans() - body1->getTransformation().getTrans());
		else
			anchor = newanchor;
		
		osg::Vec3 worldAnchor = anchor;
		if (body1.valid()) {
			worldAnchor = body1->getTransformation().getTrans() + body1->getTransformation().getRotate()*anchor;
			if (jointID) {
				OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
				switch (type) {
					case BALL: dJointSetBallAnchor(jointID, worldAnchor.x(), worldAnchor.y(), worldAnchor.z()); break;
					case HINGE: dJointSetHingeAnchor(jointID, worldAnchor.x(), worldAnchor.y(), worldAnchor.z()); break;
					case UNIVERSAL: dJointSetUniversalAnchor(jointID, worldAnchor.x(), worldAnchor.y(), worldAnchor.z()); break;
					case HINGE2: dJointSetHinge2Anchor(jointID, worldAnchor.x(), worldAnchor.y(), worldAnchor.z()); break;
					default: break;
				}
			}
		}
	}
	
	osg::Vec3 Joint::getAnchorWorld()
	{
		if (!jointID)
			return osg::Vec3(0,0,0);
		dVector3 result;
		switch (type) {
			case BALL: dJointGetBallAnchor(jointID, result); break;
			case HINGE: dJointGetHingeAnchor(jointID, result); break;
			case UNIVERSAL: dJointGetUniversalAnchor(jointID, result); break;
			case HINGE2: dJointGetHinge2Anchor(jointID, result); break;
			default: return osg::Vec3(0,0,0);
		}
		return osgVec3FromOde(result);
	}
	
	osg::Vec3 Joint::getAnchor2World()
	{
		if (!jointID)
			return osg::Vec3(0,0,0);
		dVector3 result;
		switch (type) {
			case BALL: dJointGetBallAnchor2(jointID, result); break;
			case HINGE: dJointGetHingeAnchor2(jointID, result); break;
			case UNIVERSAL: dJointGetUniversalAnchor2(jointID, result); break;
			case HINGE2: dJointGetHinge2Anchor2(jointID, result); break;
			default: return osg::Vec3(0,0,0);
		}
		return osgVec3FromOde(result);
	}
	
	osg::Vec3 Joint::getAxis(const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			return body1->getTransformation().getRotate()*axis;
		else if (!relativebody1 && body2.valid() && body1.valid())
			return body2->getTransformation().getRotate().inverse()*body1->getTransformation().getRotate()*axis;
		return axis;
	}
	
	void Joint::setAxis(const osg::Vec3& newaxis, const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			axis = body1->getTransformation().getRotate().inverse()*newaxis;
		else if (!relativebody1 && body2.valid() && body1.valid())
			axis = body2->getTransformation().getRotate()*body1->getTransformation().getRotate().inverse()*newaxis;
		else
			axis = newaxis;
		
		osg::Vec3 worldAxis = axis;
		if (body1.valid())
			worldAxis = body1->getTransformation().getRotate()*axis;
		if (jointID) {
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
			switch (type) {
				case HINGE: dJointSetHingeAxis(jointID, worldAxis.x(), worldAxis.y(), worldAxis.z()); break;
				case SLIDER: dJointSetSliderAxis(jointID, worldAxis.x(), worldAxis.y(), worldAxis.z()); break;
				case UNIVERSAL: dJointSetUniversalAxis1(jointID, worldAxis.x(), worldAxis.y(), worldAxis.z()); break;
				case HINGE2: dJointSetHinge2Axis1(jointID, worldAxis.x(), worldAxis.y(), worldAxis.z()); break;
				default: break;
			}
		}
	}
	
	osg::Vec3 Joint::getAxis2(const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			return body1->getTransformation().getRotate()*axis2;
		else if (!relativebody1 && body2.valid() && body1.valid())
			return body2->getTransformation().getRotate().inverse()*body1->getTransformation().getRotate()*axis2;
		return axis2;
	}
	
	void Joint::setAxis2(const osg::Vec3& newaxis2, const bool relative, const bool relativebody1)
	{
		if (!relative && body1.valid())
			axis2 = body1->getTransformation().getRotate()*newaxis2;
		else if (!relativebody1 && body2.valid() && body1.valid())
			axis2 = body2->getTransformation().getRotate()*body1->getTransformation().getRotate().inverse()*newaxis2;
		else
			axis2 = newaxis2;
		
		osg::Vec3 worldAxis2 = axis2;
		if (body1.valid())
			worldAxis2 = body1->getTransformation().getRotate()*axis2;
		if (jointID) {
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
			switch (type) {
				case UNIVERSAL: dJointSetUniversalAxis2(jointID, worldAxis2.x(), worldAxis2.y(), worldAxis2.z()); break;
				case HINGE2: dJointSetHinge2Axis2(jointID, worldAxis2.x(), worldAxis2.y(), worldAxis2.z()); break;
				default: break;
			}
		}
	}
	
	void Joint::setParameter(const JointParameter& parameter, const float value) {
		if (!jointID) {
			parameters[parameter] = value;
			return;
		}
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		switch (type) {
			case HINGE: dJointSetHingeParam(jointID,parameter,value); break;
			case SLIDER: dJointSetSliderParam(jointID,parameter,value); break;
			case HINGE2: dJointSetHinge2Param(jointID,parameter,value); break;
			case UNIVERSAL: dJointSetUniversalParam(jointID,parameter,value); break;
			case AMOTOR: dJointSetAMotorParam(jointID,parameter,value); break;
			default: break;
		}
	}
	
	float Joint::getParameter(const JointParameter& parameter) {
		if (!jointID || parameter > _END_ODE_PARAMETERS)
			return parameters[parameter];
		switch (type) {
			case HINGE: return dJointGetHingeParam(jointID,parameter); break;
			case SLIDER: return dJointGetSliderParam(jointID,parameter); break;
			case HINGE2: return dJointGetHinge2Param(jointID,parameter); break;
			case UNIVERSAL: return dJointGetUniversalParam(jointID,parameter); break;
			case AMOTOR: return dJointGetAMotorParam(jointID,parameter); break;
			default: break;
		}
		return 0;
	}
	
	void Joint::attach()
	{
		if (!jointID) {
			pendingAttachment = true;
			dout(8) << "Joint attachment pending due to unrealized joint\n";
			return;
		}
		if ((body1.valid() && !body1->isRealized()) || (body2.valid() && !body2->isRealized())) {
			pendingAttachment = true;
			dout(8) << "Joint attachment pending due to unrealized body\n";
			return;
		}
		if (jointID) {
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
			dJointAttach(jointID, body1.valid() ? body1->id() : 0, body2.valid() ? body2->id() : 0);
			pendingAttachment = false;
		}
	}
	
	void Joint::attach(Body* b1, Body* b2)
	{
		body1 = b1;
		body2 = b2;
		attach();
	}
	
	osg::Node* Joint::createDebugNode(int which)
	{
		osg::Geode* geode = new osg::Geode;
		osg::CompositeShape* cshape = new osg::CompositeShape;
		osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(cshape,default_hints);
		geode->addDrawable(shapedraw);
		
		if (which == 1) {
			shapedraw->setColor(default_color1);
			osg::Vec3 apos = getAnchor();
			osg::Quat rot;
			rot.makeRotate(osg::Vec3(0,0,1),apos);	
			osg::Cylinder* cyl1 = new osg::Cylinder(apos*0.5,debugscale*0.5,apos.length());
			cyl1->setRotation(rot);
			cshape->addChild(cyl1);
			
			osg::Cylinder* acyl = NULL;
			switch (type) {
				case BALL:
					cshape->addChild(new osg::Sphere(apos,debugscale));
					break;
				case HINGE:
				case UNIVERSAL:
				case HINGE2:
					acyl = new osg::Cylinder(apos,debugscale,debugscale*4.0);
					rot.makeRotate(osg::Vec3(0,0,1),getAxis());
					acyl->setRotation(rot);
					cshape->addChild(acyl);
					break;
				default: break;
			}
		} else if (which == 2) {
			shapedraw->setColor(default_color2);
			osg::Vec3 apos = getAnchor(true, false);
			osg::Quat rot;
			rot.makeRotate(osg::Vec3(0,0,1),apos);	
			osg::Cylinder* cyl1 = new osg::Cylinder(apos*0.5,debugscale*0.4,apos.length());
			cyl1->setRotation(rot);
			cshape->addChild(cyl1);
			
			osg::Cylinder* acyl = NULL;
			switch (type) {
				case BALL:
					cshape->addChild(new osg::Sphere(apos,debugscale*0.8));
					break;
				case HINGE:
					acyl = new osg::Cylinder(apos,debugscale*0.8,debugscale*4.0);
					rot.makeRotate(osg::Vec3(0,0,1),getAxis(true,false));
					acyl->setRotation(rot);
					cshape->addChild(acyl);
					break;
				case UNIVERSAL:
				case HINGE2:
					acyl = new osg::Cylinder(apos,debugscale*0.8,debugscale*4.0);
					rot.makeRotate(osg::Vec3(0,0,1),getAxis2(true,false));
					acyl->setRotation(rot);
					cshape->addChild(acyl);
					break;
				default: break;
			}
		}
		if (type == SLIDER)
			geode->setUpdateCallback(new SliderJointCallback(this,which));
		return geode;
	}
	
	void Joint::initialize()
	{
		Component::initialize();
		if (getNumModifiers() > 0) {
			BaseObject* object = dynamic_cast<BaseObject*> (getContainer());
			if (!object) {
				dout(ERROR) << "Container for Joint '" << getName() << "' is not a BaseObject\n";
				return;
			}
			for (unsigned int i = 0; i < getNumModifiers(); i++) {
				Modifier *mod = getModifier(i);
				if (Parameter *param = object->findParameter(mod->getName())) {
					mod->setParameter(param);
					dout(5) << "Joint modifer " << object->getName() << ":" << mod->getName() << " connected\n";
				} else
					dout(5) << "No connection for joint modifier " << object->getName() << ":" << mod->getName() << "\n";
			}
		}
	}
	
	void Joint::reset()
	{
		Component::reset();
		refDeflection = resetRefDeflection;
		refDeflection2 = resetRefDeflection2;
		attach();
	}
	
	void Joint::setResetState()
	{
		resetRefDeflection = refDeflection;
		resetRefDeflection2 = refDeflection2;
		Component::setResetState();
	}
	
	void Joint::realize()
	{
		dout(8) << "Realize joint " << getName() << "\n";
		if (!body2.valid() && connectName.length() > 0) {
			dout(WARN) << "Joint '" << getName() << "' missing connection to '" << connectName << "'\n";
			return;
		}
		if (jointID) {
			attach(body1.get(), body2.get());
			updateAnchorsAndAxes();
			return;
		}

		Component::realize();
		{
		    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		    dWorldID world = World::instance().id();
		    dJointGroupID group = 0;
		    switch (type) {
				case BALL: jointID = dJointCreateBall(world,group); break;
				case HINGE: jointID = dJointCreateHinge(world,group); break;
				case SLIDER: jointID = dJointCreateSlider(world,group); break;
				case UNIVERSAL: jointID = dJointCreateUniversal(world,group); break;
				case HINGE2: jointID = dJointCreateHinge2(world,group); break;
				case FIXED: jointID = dJointCreateFixed(world,group); break;
				case AMOTOR:
					dout(ERROR) << "AMotor joint not yet implemented\n";
					return;
				default: break;
		    }
		}
		attach(body1.get(), body2.get());
		dout(8) << "update anchor w " << getAnchor(false) << " r " << getAnchor();
		if (body1.valid())
			dout(8) << " b " << body1->getTransformation().getTrans();
		dout(8) << "\n";
		updateAnchorsAndAxes();
		{
		    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		    for (ParameterMap::iterator i = parameters.begin(); i != parameters.end() && i->first != _END_ODE_PARAMETERS; i++) {
			switch (type) {
				case HINGE: dJointSetHingeParam(jointID,i->first,i->second); break;
				case SLIDER: dJointSetSliderParam(jointID,i->first,i->second); break;
				case HINGE2: dJointSetHinge2Param(jointID,i->first,i->second); break;
				case UNIVERSAL: dJointSetUniversalParam(jointID,i->first,i->second); break;
				case AMOTOR: dJointSetAMotorParam(jointID,i->first,i->second); break;
				default: break;
			}
		    }
		}
		if (feedback || (forceParam.valid() && forceParam->isConnected()) || (torqueParam.valid() && torqueParam->isConnected()) || breakImpulse != dInfinity || breakAngularImpulse != dInfinity)
			initFeedback();
	}
	
	void Joint::unrealize()
	{
		Component::unrealize();
		if (!jointID)
			return;
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		dJointDestroy(jointID);
		jointID = 0;
	}
	
	bool Joint::isRealized() const
	{
		return (jointID != 0);
	}
	
	void Joint::updateAnchorsAndAxes()
	{
		if (!jointID)
			return;
		setAnchor(getAnchor());
		setAxis(getAxis());
		setAxis2(getAxis2());
	}
	
	void Joint::update(const double dt)
	{
		if (pendingAttachment && isRealized() && 
			(body1.valid() && body1->isRealized() || (body2.valid() && body2->isRealized()))) {
			attach(body1.get(), body2.get());
			dout(8) << "Pending joint attached\n";
		}
		if (!body1 || !body1->isEnabled())
			return;

		// Modifiers
		float s = 0.f, s2 = 0.f;
		bool dosteer = false, dosteer2 = false;
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			const Modifier *mod = getModifier(i);
			switch (mod->getTargetIndex()) {
				case STEER: s += mod->get(); dosteer = true; break;
				case STEER2: s2 += mod->get(); dosteer2 = true; break;
			}
		}
		if (dosteer)
			steer(s);
		if (dosteer2)
			steer2(s2);
		
		// Steering
		if (steering) {
			float velocity = getParameter(VELOCITY);
			if ((velocity > 0 && getDeflection() + velocity*dt > steerDeflection) || (velocity < 0 && getDeflection() + velocity*dt < steerDeflection)) {
				velocity = 0.1*(steerDeflection-getDeflection())/dt;
				setParameter(VELOCITY, velocity);
			}
			refDeflection += velocity*dt;
			//if ((velocity > 0 && getDeflection() >= steerDeflection) || (velocity < 0 && getDeflection() <= steerDeflection)) {
			if (fabs(getDeflection()-steerDeflection) < getParameter(STEER_TOLERANCE)) {
				setParameter(VELOCITY, 0.f);
				steering = false;
				refDeflection = steerDeflection;
			}
		}
		if (steering2) {
			float velocity = getParameter(VELOCITY2);
			if ((velocity > 0 && getDeflection2() + velocity*dt > steerDeflection2) || (velocity < 0 && getDeflection2() + velocity*dt < steerDeflection2)) {
				velocity = 0.1*(steerDeflection2-getDeflection2())/dt;
				setParameter(VELOCITY2, velocity);
			}
			refDeflection2 += velocity*dt;
			//if ((velocity > 0 && getDeflection2() >= steerDeflection2) || (velocity < 0 && getDeflection2() <= steerDeflection2)) {
			if (fabs(getDeflection2()-steerDeflection2) < getParameter(STEER_TOLERANCE2)) {
				setParameter(VELOCITY2, 0.f);
				steering2 = false;
				refDeflection2 = steerDeflection2;
			}
		}

		// Spring/damping
		if (type == HINGE2 && (parameters[SPRING] || parameters[DAMP])) {
			float kp = parameters[SPRING]/REFMASS;
			float kd = parameters[DAMP]/REFMASS;
			setParameter(SUSPENSION_ERP, dt*kp / (dt*kp+kd));
			setParameter(SUSPENSION_CFM, 1.0 / (dt*kp+kd));
		} else {
			if (parameters[SPRING])
				addForce(-parameters[SPRING]*(getDeflection()-refDeflection));
			if (parameters[DAMP])
				addForce(-parameters[DAMP]*(getRate()-getParameter(VELOCITY)));
			if (parameters[SPRING2])
				addForce(0, -parameters[SPRING2]*(getDeflection2()-refDeflection2));
			if (parameters[DAMP2])
				addForce(0, -parameters[DAMP2]*(getRate2()-getParameter(VELOCITY2)));
		}
		
		// Feedback
		if (feedback && (osgVec3FromOde(feedback->f1).length()*REFMASS*dt > breakImpulse ||
						 osgVec3FromOde(feedback->f2).length()*REFMASS*dt > breakImpulse || 
						 osgVec3FromOde(feedback->t1).length()*REFMASS*dt > breakAngularImpulse ||
						 osgVec3FromOde(feedback->t2).length()*REFMASS*dt > breakAngularImpulse)) {
			dJointAttach(jointID,0,0);
		}
		
		// Audio params
		if (steerParam.valid()) {
			if (steering || steering2)
				steerParam->set(std::max(fabs(getDeflection() - steerDeflection), fabs(getDeflection2() - steerDeflection2)));
			else
				steerParam->set(0);
		}
		if (feedback) {
			if (forceParam.valid())
				forceParam->set(osgVec3FromOde(feedback->f1).length()*REFMASS);
			if (torqueParam.valid())
				torqueParam->set(osgVec3FromOde(feedback->f1).length()*REFMASS);
		}
	}
	
	float Joint::getDeflection()
	{
		if (!jointID)
			return 0;
		switch (type) {
			case HINGE: return dJointGetHingeAngle(jointID);
			case SLIDER: return dJointGetSliderPosition(jointID);
			case UNIVERSAL: return dJointGetUniversalAngle1(jointID);
			case HINGE2: return dJointGetHinge2Angle1(jointID);
			default: break;
		}
		return 0;
	}
	
	float Joint::getDeflection2()
	{
		if (!jointID)
			return 0;
		if (type == UNIVERSAL)
			return dJointGetUniversalAngle2(jointID);
		return 0;
	}
	
	float Joint::getRate()
	{
		if (!jointID)
			return 0;
		switch (type) {
			case HINGE: return dJointGetHingeAngleRate(jointID);
			case SLIDER: return dJointGetSliderPositionRate(jointID);
			case UNIVERSAL: return dJointGetUniversalAngle1Rate(jointID);
			case HINGE2: return dJointGetHinge2Angle1Rate(jointID);
			default: break;
		}
		return 0;
	}
	
	float Joint::getRate2()
	{
		if (!jointID)
			return 0;
		switch (type) {
			case UNIVERSAL: return dJointGetUniversalAngle2Rate(jointID);
			case HINGE2: return dJointGetHinge2Angle2Rate(jointID);
			default: break;
		}
		return 0;
	}
	
	void Joint::setRefDeflection(const float value) { refDeflection = value; }
	void Joint::setRefDeflection2(const float value) { refDeflection2 = value; }
	float Joint::getRefDeflection() const { return refDeflection; }
	float Joint::getRefDeflection2() const { return refDeflection2; }
	
	void Joint::steer(const float deflection, const float vel)
	{
		float error = deflection - getDeflection();
		if (fabs(error) < getParameter(STEER_TOLERANCE))
			return;
		float velocity = vel;
		if (velocity < 1e-8)
			velocity = getParameter(STEER_VELOCITY);
		if (velocity < 1e-8)
			dout(WARN) << "Attempt to steer joint " << getName() << " with zero velocity " << velocity << "\n";
		steerDeflection = deflection;
		if (error > 0)
			setParameter(VELOCITY, velocity);
		else
			setParameter(VELOCITY, -velocity);
		steering = true;
	}
	
	void Joint::steer2(const float deflection, const float vel)
	{
		float error = deflection - getDeflection2();
		if (fabs(error) < getParameter(STEER_TOLERANCE2))
			return;
		float velocity = vel;
		if (velocity < 1e-8)
			velocity = getParameter(STEER_VELOCITY2);
		if (velocity < 1e-8)
			dout(WARN) << "Attempt to steer joint " << getName() << " with zero velocity " << velocity << "\n";
		steerDeflection2 = deflection;
		if (error > 0)
			setParameter(VELOCITY2, velocity);
		else
			setParameter(VELOCITY2, -velocity);
		steering2 = true;
	}
	
	void Joint::addForce(const float f1, const float f2, const float f3)
	{
		if (!jointID)
			return;
		float F1 = f1/REFMASS;
		float F2 = f2/REFMASS;
		float F3 = f3/REFMASS;
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		switch (type) {
			case HINGE: dJointAddHingeTorque(jointID,F1); break;
			case SLIDER: dJointAddSliderForce(jointID,F1); break;
			case UNIVERSAL: dJointAddUniversalTorques(jointID,F1,F2); break;
			case HINGE2: dJointAddHinge2Torques(jointID,F1,F2); break;
			case AMOTOR: dJointAddAMotorTorques(jointID,F1,F2,F3); break;
			default: break;
		}
	}
	
	/// \note This will return zero-vector if initFeedback() hasn't been called
	osg::Vec3 Joint::getForce1(const bool relative, const bool relativebody1)
	{
		if (!feedback)
			return osg::Vec3(0,0,0);
		osg::Vec3 v = osgVec3FromOde(feedback->f1)*REFMASS;
		if (relative && relativebody1) {
			if (body1.valid())
				return body1->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else if (relative) {
			if (body2.valid())
				return body2->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else
			return v;
	}
	
	/// \note This will return zero-vector if initFeedback() hasn't been called
	osg::Vec3 Joint::getForce2(const bool relative, const bool relativebody1)
	{
		if (!feedback)
			return osg::Vec3(0,0,0);
		osg::Vec3 v = osgVec3FromOde(feedback->f2)*REFMASS;
		if (relative && relativebody1) {
			if (body1.valid())
				return body1->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else if (relative) {
			if (body2.valid())
				return body2->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else
			return v;
	}
	
	/// \note This will return zero-vector if initFeedback() hasn't been called
	osg::Vec3 Joint::getTorque1(const bool relative, const bool relativebody1)
	{
		if (!feedback)
			return osg::Vec3(0,0,0);
		osg::Vec3 v = osgVec3FromOde(feedback->t1)*REFMASS;
		if (relative && relativebody1) {
			if (body1.valid())
				return body1->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else if (relative) {
			if (body2.valid())
				return body2->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else
			return v;
	}
	
	/// \note This will return zero-vector if initFeedback() hasn't been called
	osg::Vec3 Joint::getTorque2(const bool relative, const bool relativebody1)
	{
		if (!feedback)
			return osg::Vec3(0,0,0);
		osg::Vec3 v = osgVec3FromOde(feedback->t2)*REFMASS;
		if (relative && relativebody1) {
			if (body1.valid())
				return body1->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else if (relative) {
			if (body2.valid())
				return body2->getTransformation().getRotate().inverse()*v;
			else
				throw DynamicsException("getForce1() called relative to nonexistant body");
		} else
			return v;
	}
	
	void Joint::initFeedback()
	{
		if (!feedback)
			feedback = new dJointFeedback;
		memset(feedback,0,sizeof(dJointFeedback));
		if (!jointID)
			return;
		dJointSetFeedback(jointID,feedback);
	}
	
} // namespace ogeDyn
