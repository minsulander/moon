#include "Body.h"
#include "moodyn/World.h"
#include <mlog/Log.h>
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>

#ifdef _MSC_VER
#	pragma warning(disable:4800)
#endif

// Reference mass defined by World - used to keep masses around 1 and scale forces/torques etc
// appropriately. This should help improve numerical stability of ODE.
#define REFMASS World::instance().getReferenceMass()

using namespace moon;
using namespace mlog;

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, Body, Body);
	
	Body::Body()
	:	Component(),
		bodyID(0),
		startdisabled(false)
	{
		mass.mass = 1.f/REFMASS;
		mass.I[0] = 1.f/REFMASS;
		mass.I[5] = 1.f/REFMASS;
		mass.I[10] = 1.f/REFMASS;
	}
	
	Body::Body(const Body& other, const osg::CopyOp copyop)
	:	Component(other, copyop),
		bodyID(0),
		mass(other.mass),
		startdisabled(other.startdisabled)
	{
	}

	void Body::parseXML(const TiXmlElement *element)
	{
		Component::parseXML(element);
		//=== Body
		//=* element: mass value="(number)" [kg]
		double m = XMLParser::parseDouble(element,"mass","kg",true,0.0)/REFMASS;
		//=* element: density value="(number)" [kg / m^3]
		double rho = XMLParser::parseDouble(element,"density","kg / m^3",true,0.0)/REFMASS;
		
		//=* element: box sides="(vector3)" [m]
		osg::Vec3 sides = XMLParser::parseVector3(element,"box","m",true,osg::Vec3(0,0,0),"sides");
		if (sides.length() > 0) {
			if (rho)
				dMassSetBox(&mass,rho,sides.x(),sides.y(),sides.z());
			else if (m)
				dMassSetBoxTotal(&mass,m,sides.x(),sides.y(),sides.z());
		}
		
		//=* element: sphere radius="(number)" [m]
		double radius = XMLParser::parseDouble(element,"sphere","m",true,0.0,"radius");
		if (radius > 0) {
			if (rho)
				dMassSetSphere(&mass,rho,radius);
			else
				dMassSetSphereTotal(&mass,m,radius);
		}
		
		//=* element: capsule radius="(number)" length="(number)" [m] direction="1|2|3"
		radius = XMLParser::parseDouble(element,"capsule","m",true,0.0,"radius");
		double length = XMLParser::parseDouble(element,"capsule","m",true,0.0,"length");
		int direction = XMLParser::parseInt(element,"capsule","",true,3,"direction");
		if (length > 0) {
			if (rho)
				dMassSetCapsule(&mass,rho,direction,radius,length);
			else
				dMassSetCapsuleTotal(&mass,m,direction,radius,length);
		}
		
		//=* element: cylinder radius="(number)" length="(number)" [m] direction="1|2|3"
		radius = XMLParser::parseDouble(element,"cylinder","m",true,0.0,"radius");
		length = XMLParser::parseDouble(element,"cylinder","m",true,0.0,"length");
		direction = XMLParser::parseInt(element,"cylinder","",true,3,"direction");
		if (length > 0) {
			if (rho)
				dMassSetCylinder(&mass,rho,direction,radius,length);
			else
				dMassSetCylinderTotal(&mass,m,direction,radius,length);
		}
		//=* element: <inertia center="(vector3)>(matrix)</inertia>
		//=. Inertia matrix, either specified as 6 values (Ixx Iyy Izz Ixy Ixz Iyz) or a 3x3 matrix
		std::vector<double> I;
		if (XMLParser::parseVector(I, element, "inertia", false, "kg / m^2")) {
			osg::Vec3 cm = osg::Vec3(0,0,0); 
			XMLParser::parseVector3(cm,element,"inertia","meter","center");
			for (size_t i = 0; i < I.size(); i++)
				I[i] /= REFMASS;
			if (I.size() == 6)
				dMassSetParameters(&mass,m,cm.x(),cm.y(),cm.z(),I[0],I[1],I[2],I[3],I[4],I[5]);
			else if (I.size() == 9)
				dMassSetParameters(&mass,m,cm.x(),cm.y(),cm.z(),I[0],I[4],I[8],I[1],I[2],I[5]);
			else
				throw ParseException("Illegal inertia matrix size",element->FirstChildElement("inertia"));
		}
		
		//=* element: translate value="(vector3)" [m]
		osg::Vec3 mtrans = XMLParser::parseVector3(element,"translate","m",true,osg::Vec3(0,0,0));
		if (mtrans.length() > 1e-5)
			dMassTranslate(&mass,mtrans.x(),mtrans.y(),mtrans.z());
		/*
		dout(7) << "    mass " << mass.mass << " cg " << mass.c[0] << "," << mass.c[1] << "," << mass.c[2] << "\n";
		dout(7) << "    inertia " << mass.I[0] << " " << mass.I[1] << " " << mass.I[2] << "\n"
		<< "            " << mass.I[4] << " " << mass.I[5] << " " << mass.I[6] << "\n"
		<< "            " << mass.I[8] << " " << mass.I[9] << " " << mass.I[10] << "\n";
		*/
		//=* element: startdisabled value="true|false"
		startdisabled = XMLParser::parseBoolean(element,"startdisabled",true,false);
		/// \todo parse auto disable threshold etc
	}
	
	void Body::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		float rm = REFMASS;
		XMLParser::setDouble(element, "mass", mass.mass*rm);
		std::stringstream ss;
		ss << mass.I[0]*rm << " " << mass.I[1]*rm << " " << mass.I[2]*rm << " "
		<< mass.I[4]*rm << " " << mass.I[5]*rm << " " << mass.I[6]*rm << " "
		<< mass.I[8]*rm << " " << mass.I[9]*rm << " " << mass.I[10]*rm;
		XMLParser::setString(element, "inertia", ss.str());
		osg::Vec3 mtrans(mass.c[0], mass.c[1], mass.c[2]);
		if (mtrans.length() > 1e-5)
			XMLParser::setVector3(element, "translate", mtrans);
		if (startdisabled)
			XMLParser::setBoolean(element, "startdisabled", true);
	}
	
	void Body::realize()
	{
		Component::realize();
		if (bodyID)
			return;
		bodyID = dBodyCreate(World::instance().id());
		dBodySetMass(bodyID, &mass);
	}
	
	void Body::unrealize()
	{
		Component::unrealize();
		if (!bodyID) 
			return;
		dBodyDestroy(bodyID);
		bodyID = 0;
	}
	
	void Body::setTransformation(const osg::Matrix& M) {
		if (!bodyID)
			return;
		osg::Vec3 pos = M.getTrans();
		osg::Quat rot = M.getRotate();
		dQuaternion q; q[0] = rot.w(); q[1] = rot.x(); q[2] = rot.y(); q[3] = rot.z();
		dBodySetPosition(bodyID,pos.x(),pos.y(),pos.z());
		dBodySetQuaternion(bodyID,q);
		//dBodyEnable(bodyID);
	}
	
	osg::Matrix Body::getTransformation() {
		osg::Matrix M = osg::Matrix::identity();
		if (!bodyID)
			return M;
		const dReal* p = dBodyGetPosition(bodyID);
		const dReal* q = dBodyGetQuaternion(bodyID);
		M.setRotate(osg::Quat(q[1],q[2],q[3],q[0]));
		M.setTrans(osg::Vec3(p[0],p[1],p[2]));
		return M;
	}
	
	void Body::setPosition(const osg::Vec3& pos) {
		if (!bodyID)
			return;
		dBodySetPosition(bodyID,pos.x(),pos.y(),pos.z());
		//dBodyEnable(bodyID);
	}
	
	const osg::Vec3 Body::getPosition() {
		if (!bodyID)
			return osg::Vec3(0,0,0);
		const dReal* p = dBodyGetPosition(bodyID);
		return osg::Vec3(p[0],p[1],p[2]);
	}
	
	void Body::setRotation(const osg::Quat& rot) {
		if (!bodyID)
			return;
		dQuaternion q; q[0] = rot.w(); q[1] = rot.x(); q[2] = rot.y(); q[3] = rot.z();
		dBodySetQuaternion(bodyID,q);
		//dBodyEnable(bodyID);
	}
	
	const osg::Quat Body::getRotation() {
		if (!bodyID)
			return osg::Quat(0,0,0,0);
		const dReal* q = dBodyGetQuaternion(bodyID);
		return osg::Quat(q[1],q[2],q[3],q[0]);
	}
	
	void Body::setVelocity(const osg::Vec3& vel, const bool rel) {
		if (!bodyID)
			return;
		if (rel) {
			dVector3 vE;
			dBodyVectorToWorld(bodyID,vel.x(),vel.y(),vel.z(),vE);
			dBodySetLinearVel(bodyID,vE[0],vE[1],vE[2]);
			return;
		}
		dBodySetLinearVel(bodyID,vel.x(),vel.y(),vel.z());
		dBodyEnable(bodyID);
	}
	
	const osg::Vec3 Body::getVelocity(const bool rel) {
		if (!bodyID)
			return osg::Vec3(0,0,0);
		const dReal *vE = dBodyGetLinearVel(bodyID);
		if (rel) {
			dVector3 vB;
			dBodyVectorFromWorld(bodyID,vE[0],vE[1],vE[2],vB);
			return osg::Vec3(vB[0],vB[1],vB[2]);		
		}
		return osg::Vec3(vE[0],vE[1],vE[2]);
	}
	
	void Body::setAngularVelocity(const osg::Vec3& vel, const bool rel) {
		if (!bodyID)
			return;
		if (rel) {
			dVector3 vE;
			dBodyVectorToWorld(bodyID,vel.x(),vel.y(),vel.z(),vE);
			dBodySetAngularVel(bodyID,vE[0],vE[1],vE[2]);
			return;
		}
		dBodySetAngularVel(bodyID,vel.x(),vel.y(),vel.z());
		dBodyEnable(bodyID);
	}
	
	const osg::Vec3 Body::getAngularVelocity(const bool rel) {
		if (!bodyID)
			return osg::Vec3(0,0,0);
		const dReal *vE = dBodyGetAngularVel(bodyID);
		if (rel) {
			dVector3 vB;
			dBodyVectorFromWorld(bodyID,vE[0],vE[1],vE[2],vB);
			return osg::Vec3(vB[0],vB[1],vB[2]);		
		}
		return osg::Vec3(vE[0],vE[1],vE[2]);
	}
	
	void Body::addForce(const osg::Vec3& force, const bool rel) {
		if (!bodyID)
			return;
		osg::Vec3 F = force/REFMASS;
		if (rel)
			return dBodyAddRelForce(bodyID,F.x(),F.y(),F.z());
		dBodyAddForce(bodyID,F.x(),F.y(),F.z());
	}
	
	void Body::addForceAt(const osg::Vec3& force, const bool rel, const osg::Vec3& pos, const bool relpos) {
		if (!bodyID)
			return;
		osg::Vec3 F = force/REFMASS;
		if (rel && relpos)
			return dBodyAddRelForceAtRelPos(bodyID,F.x(),F.y(),F.z(),pos.x(),pos.y(),pos.z());
		else if (rel)
			return dBodyAddRelForceAtPos(bodyID,F.x(),F.y(),F.z(),pos.x(),pos.y(),pos.z());
		else if (relpos)
			return dBodyAddForceAtRelPos(bodyID,F.x(),F.y(),F.z(),pos.x(),pos.y(),pos.z());
		return dBodyAddForceAtPos(bodyID,F.x(),F.y(),F.z(),pos.x(),pos.y(),pos.z());	
	}
	
	void Body::addTorque(const osg::Vec3& torque, const bool rel) {
		if (!bodyID)
			return;
		osg::Vec3 Q = torque/REFMASS;
		if (rel)
			return dBodyAddRelTorque(bodyID,Q.x(),Q.y(),Q.z());
		dBodyAddTorque(bodyID,Q.x(),Q.y(),Q.z());
	}
	
	void Body::setForce(const osg::Vec3& force, const bool rel) {
		if (!bodyID)
			return;
		osg::Vec3 F = force/REFMASS;
		if (rel) {
			dVector3 fE;
			dBodyVectorToWorld(bodyID,F.x(),F.y(),F.z(),fE);
			dBodySetForce(bodyID,fE[0],fE[1],fE[2]);
			return;
		}
		dBodySetForce(bodyID,F.x(),F.y(),F.z());
	}
	
	void Body::setTorque(const osg::Vec3& torque, const bool rel) {
		if (!bodyID)
			return;
		osg::Vec3 Q = torque/REFMASS;
		if (rel) {
			dVector3 qE;
			dBodyVectorToWorld(bodyID,Q.x(),Q.y(),Q.z(),qE);
			dBodySetTorque(bodyID,qE[0],qE[1],qE[2]);
			return;
		}
		dBodySetTorque(bodyID,Q.x(),Q.y(),Q.z());
	}
	
	const osg::Vec3 Body::getForce(const bool rel) {
		if (!bodyID)
			return osg::Vec3(0,0,0);
		const dReal *fE = dBodyGetForce(bodyID);
		if (rel) {
			dVector3 fB;
			dBodyVectorFromWorld(bodyID,fE[0],fE[1],fE[2],fB);
			return osg::Vec3(fB[0],fB[1],fB[2])*REFMASS;		
		}
		return osg::Vec3(fE[0],fE[1],fE[2])*REFMASS;
	}
	
	const osg::Vec3 Body::getTorque(const bool rel) {
		if (!bodyID)
			return osg::Vec3(0,0,0);
		const dReal *qE = dBodyGetTorque(bodyID);
		if (rel) {
			dVector3 qB;
			dBodyVectorFromWorld(bodyID,qE[0],qE[1],qE[2],qB);
			return osg::Vec3(qB[0],qB[1],qB[2])*REFMASS;		
		}
		return osg::Vec3(qE[0],qE[1],qE[2])*REFMASS;
	}
	
	const double Body::getMass() {
		return mass.mass*REFMASS;
	}
	
	void Body::setMass(const double newmass) {
		dMassAdjust(&mass, newmass/REFMASS);
		if (!bodyID)
			return;
		dBodySetMass(bodyID,&mass);
	}
	
	const bool Body::isEnabled() const {
		if (!bodyID)
			return false;
		return (dBodyIsEnabled(bodyID) == 1);
	}
	
	void Body::enable() {
		if (!bodyID)
			return;
		dBodyEnable(bodyID);
	}
	
	void Body::disable() {
		if (!bodyID)
			return;
		dBodyDisable(bodyID);
	}
	
	bool Body::isConnectedTo(Body *other) {
		if (!other || !other->id() || !id())
			return false;
		return dAreConnected(id(), other->id());
	}
	
	dBodyID Body::id() { return bodyID; }

	Body::~Body()
	{
		unrealize();
	}
	
} // namespace
