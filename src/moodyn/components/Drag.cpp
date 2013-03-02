#include "Drag.h"
#include "moodyn/Atmosphere.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <moon/objects/BaseObject.h>
#include <mlog/Log.h>
#include <mdraw/utils.h>
#include <osg/io_utils>

namespace moodyn {

	REGISTER_Object_Alias(moodyn, Drag, Drag);
	
	Drag::Drag()
	: ContinuousForce()
	, cd(0.47f) // drag coefficient of a sphere according to wikipedia
	, areaSource(BBOX)
	{
	}
	
	Drag::Drag(const Drag& source, const osg::CopyOp& copyop)
	: ContinuousForce(source, copyop)
	, cd(source.cd)
	, A(source.A)
	, areaSource(source.areaSource)
	{
	}
	
	void Drag::parseXML(const TiXmlElement *element)
	{
		//=== Drag
		//=see superclass ContinuousForce
		ContinuousForce::parseXML(element);
		double value;
		//=* attribute: cd="(number)"
		if (moon::XMLParser::parseDoubleAttribute(value, element, "cd"))
			cd = value;
		std::string str;
		//=* attribute: area="bsphere|bbox"
		if (moon::XMLParser::parseStringAttribute(str, element, "area")) {
			if (str == "bsphere")
				areaSource = BSPHERE;
			else if (str == "bbox")
				areaSource = BBOX;
			else
				throw moon::ParseException("Invalid area specification", element);
		}
	}
	
	void Drag::writeXML(TiXmlElement *element) const
	{
		ContinuousForce::writeXML(element);
		element->SetDoubleAttribute("cd", cd);
	}
	
	void Drag::realize()
	{
		object = dynamic_cast<moon::KinematicObject*> (getContainer());
		if (!object) {
			mlog::dout(mlog::ERROR) << "Drag '" << getName() << "' is a component of non-kinematic object\n";
			return;
		}
		ContinuousForce::realize();
		osg::ref_ptr<osg::Group> node = new osg::Group(*object->getTransform()->asGroup());
		if (areaSource == BSPHERE) {
			setForceOffset(node->getBound().center(), true);
			float r = node->getBound().radius();
			float S = M_PI*r*r;
			A.set(S,S,S);
		} else if (areaSource == BBOX) {
			osg::BoundingBox bbox = mdraw::getBoundingBox(node.get());
			setForceOffset(bbox.center(), true);
			float sx = bbox.xMax()-bbox.xMin();
			float sy = bbox.yMax()-bbox.yMin();
			float sz = bbox.zMax()-bbox.zMin();
			A.set(sy*sz,sx*sz,sx*sy);
		}
	}
	
	void Drag::update(const double dt)
	{
		if (!isRealized() || !object)
			return;
		AtmosphericProperties atmo;
		if (Atmosphere::current())
			Atmosphere::current()->calculate(atmo, getBody()->getPosition());
		osg::Vec3 vn = getBody()->getVelocity(false);
		float v = vn.length();
		vn.normalize();
		osg::Vec3 vnr = getBody()->getVelocity(true);
		vnr.normalize();
		float S = fabs(vnr*A);
		setForce(-vn*0.5f*atmo.rho*v*v*S*cd, false);
		ContinuousForce::update(dt);
	}
	
}
