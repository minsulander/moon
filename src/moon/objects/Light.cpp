#include "Light.h"
#include "moon/XMLParser.h"
#include "moon/ObjectFactory.h"
#include "mlog/Log.h"
#include "moon/objects/Camera.h"
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/StateAttribute>
#include <osgSim/LightPointNode>

using namespace mlog;

namespace moon {
	
	REGISTER_Object(moon, Light);
	
	Light::Light()
	:	BaseObject(),
		local(false),
		fadeRangeIn(0.f),
		fadeRangeOut(0.f)
	{
		setNormallyVisible(false);
		light = new osg::Light;
		light->setDirection(osg::Vec3(0,1,0));
		light->setPosition(osg::Vec4(0,0,0,1));
	}
	
	Light::Light(const Light& other, const osg::CopyOp& copyop)
	:	BaseObject(other, copyop),
		local(other.local),
		ambient(other.ambient),
		diffuse(other.diffuse),
		specular(other.specular),
		fadeRangeIn(other.fadeRangeIn),
		fadeRangeOut(other.fadeRangeOut)
	{
		light = new osg::Light(*other.light.get());
	}
	
	void Light::parseXML(const TiXmlElement *element)
	{
		double d;
		osg::Vec3 v3; osg::Vec4 v4;
		BaseObject::parseXML(element);
		//=== Light
		//=See superclass BaseObject for more parameters
		//=If no position or attitude is set for the light, it is assumed to be non-positional.
		//=* attribute: local="true|false"
		XMLParser::parseBooleanAttribute(local, element, "local");
		//=* element: ambient value="(vector4)"
		if (XMLParser::parseVector4(v4, element, "ambient")) {
			ambient = v4;
			light->setAmbient(v4);
		}
		//=* element: diffuse value="(vector4)"
		if (XMLParser::parseVector4(v4, element, "diffuse")) {
			diffuse = v4;
			light->setDiffuse(v4);
		}
		//=* element: specular value="(vector4)"
		if (XMLParser::parseVector4(v4, element, "specular")) {
			specular = v4;
			light->setSpecular(v4);
		}
		//=* element: direction value="(vector3)"
		if (XMLParser::parseVector3(v3, element, "direction"))
			light->setDirection(v3);
		//=* element: constant_attenuation value="(number)"
		if (XMLParser::parseDouble(d, element, "constant_attenuation"))
			light->setConstantAttenuation(d);
		//=* element: linear_attenuation value="(number)"
		if (XMLParser::parseDouble(d, element, "linear_attenuation"))
			light->setLinearAttenuation(d);
		//=* element: quadratic_attenuation value="(number)"
		if (XMLParser::parseDouble(d, element, "quadratic_attenuation"))
			light->setQuadraticAttenuation(d);
		//=* element: spot_exponent value="(number)"
		if (XMLParser::parseDouble(d, element, "spot_exponent"))
			light->setSpotExponent(d);
		//=* element: spot_cutoff value="(number)"
		if (XMLParser::parseDouble(d, element, "spot_cutoff"))
			light->setSpotCutoff(d);
		//=* element: fade in="(number)" out="(number)" [meter]
		if (XMLParser::parseDouble(d, element, "fade", "meter", "in"))
			fadeRangeIn = d;
		if (XMLParser::parseDouble(d, element, "fade", "meter", "out"))
			fadeRangeOut = d;
		if (fadeRangeIn > 1e-5 && fadeRangeOut < 1e-5)
			fadeRangeOut = fadeRangeIn*1.1;
		if (fadeRangeOut > 1e-5 && fadeRangeIn < 1e-5)
			fadeRangeIn = fadeRangeOut*0.9;
	}
	
	void Light::writeXML(TiXmlElement *element) const
	{
		BaseObject::writeXML(element);
		if (!light)
			return;
		const Light *templateObject = (const Light*) getTemplate();
		if (!templateObject->light)
			return;
		if (!templateObject || light->getAmbient() != templateObject->light->getAmbient())
			XMLParser::setVector4(element, "ambient", light->getAmbient());
		if (!templateObject || light->getDiffuse() != templateObject->light->getDiffuse())
			XMLParser::setVector4(element, "diffuse", light->getDiffuse());
		if (!templateObject || light->getSpecular() != templateObject->light->getSpecular())
			XMLParser::setVector4(element, "specular", light->getSpecular());
		if (!templateObject || light->getDirection() != templateObject->light->getDirection())
			XMLParser::setVector3(element, "direction", light->getDirection());
		if (!templateObject || light->getConstantAttenuation() != templateObject->light->getConstantAttenuation())
			XMLParser::setDouble(element, "constant_attenuation", light->getConstantAttenuation());
		if (!templateObject || light->getLinearAttenuation() != templateObject->light->getLinearAttenuation())
			XMLParser::setDouble(element, "linear_attenuation", light->getLinearAttenuation());
		if (!templateObject || light->getQuadraticAttenuation() != templateObject->light->getQuadraticAttenuation())
			XMLParser::setDouble(element, "quadratic_attenuation", light->getQuadraticAttenuation());
		if (!templateObject || light->getSpotExponent() != templateObject->light->getSpotExponent())
			XMLParser::setDouble(element, "spot_exponent", light->getSpotExponent());
		if (!templateObject || light->getSpotCutoff() != templateObject->light->getSpotCutoff())
			XMLParser::setDouble(element, "spot_cutoff", light->getSpotCutoff());
		if (!templateObject || fadeRangeIn != templateObject->fadeRangeIn)
			XMLParser::setDouble(element, "fade", fadeRangeIn, "in");
		if (!templateObject || fadeRangeOut != templateObject->fadeRangeOut)
			XMLParser::setDouble(element, "fade", fadeRangeOut, "out");
	}
	
	void Light::realize()
	{
		if (isRealized())
			return;
		osg::observer_ptr<osg::StateSet> lightStateSet = getStateSet();
		if (!lightStateSet.valid()) {
			dout(ERROR) << "No state set for light\n";
			return;
		}
		// Set first available light number
		int maxLights = 8;
		//glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
		int lightNum = 0;
		for (lightNum = 0; lightNum <= maxLights; lightNum++)
			if (!lightUsed[lightNum])
				break;
		if (lightNum == maxLights) {
			dout(WARN) << "Light " << getName() << " failed to realize - out of OpenGL lights\n";
			return;
		}
		light->setLightNum(lightNum);
		lightUsed[lightNum] = true;
		dout(5) << "Light " << getName() << " realized with light num " << light->getLightNum() << "\n";
		lightsource = new osg::LightSource;
		if ((getPosition() == osg::Vec3(0,0,0)) && (getAttitude() == osg::Vec3(0,0,0)))
			lightsource->setReferenceFrame(osg::LightSource::ABSOLUTE_RF);
		lightsource->setLight(light.get());
		transform->addChild(lightsource.get());
		lightsource->setLocalStateSetModes(osg::StateAttribute::ON);
		lightsource->setStateSetModes(*lightStateSet.get(),osg::StateAttribute::ON);
		lightStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		BaseObject::realize();
	}
	
	void Light::unrealize()
	{
		osg::observer_ptr<osg::StateSet> lightStateSet = getStateSet();
		if (!lightStateSet.valid()) {
			dout(ERROR) << "No state set for light\n";
			return;
		}
		dout(5) << "Light " << getName() << " unrealized\n";
		if (lightsource.valid()) {
			lightsource->setStateSetModes(*lightStateSet.get(), osg::StateAttribute::OFF);
			lightsource->setLocalStateSetModes(osg::StateAttribute::OFF);
			lightsource->setLight(NULL);
			transform->removeChild(lightsource.get());
			lightsource = NULL;
		}
		lightUsed[light->getLightNum()] = false;
		light->setLightNum(-1);
		BaseObject::unrealize();
	}
	
	void Light::setDisplayMode(const unsigned int mode)
	{
		if (mode == DISPLAY_DEBUG) {
			osg::Group *group = new osg::Group;
			osg::Geode* geode = new osg::Geode;
			osg::CompositeShape* cshape = new osg::CompositeShape;
			osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(cshape);
			shapedraw->setColor(light->getDiffuse());
			geode->addDrawable(shapedraw);
			if (light->getSpotExponent() > 0) {
				osg::Quat rot;
				rot.makeRotate(osg::Vec3(0,0,1), -light->getDirection());
				osg::Cylinder *cyl = new osg::Cylinder(osg::Vec3(0,-0.5,0), 0.05, 1);
				cyl->setRotation(rot);
				cshape->addChild(cyl);
				osg::Cone *cone = new osg::Cone(osg::Vec3(0,0,0), 0.25, 0.5);
				cone->setRotation(rot);
				cshape->addChild(cone);
			} else {
				osg::Sphere *sphere = new osg::Sphere(osg::Vec3(0,0,0), 0.25);
				cshape->addChild(sphere);
			}
			//geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
			group->addChild(geode);
			
			osgSim::LightPointNode *lpn = new osgSim::LightPointNode;
			lpn->addLightPoint(osgSim::LightPoint(osg::Vec3(-0.2,0,0.3),light->getAmbient()));
			lpn->addLightPoint(osgSim::LightPoint(osg::Vec3(0,0,0.3),light->getDiffuse()));
			lpn->addLightPoint(osgSim::LightPoint(osg::Vec3(0.2,0,0.3),light->getSpecular()));
			lpn->setMaxPixelSize(5);
			group->addChild(lpn);
			
			addDebugNode(group);
		}
		BaseObject::setDisplayMode(mode);
	}
	
	void Light::setLightNumUsed(const int num, const bool value)
	{
		lightUsed[num] = value;
	}
	
	void Light::setLocal(const bool value) {
		if (value == local)
			return;
		bool wasRealized = isRealized();
		unrealize();
		local = value;
		if (wasRealized)
			realize();
	}
	
	bool Light::isLocal() const { return local; }
	
	void Light::update(const double dt)
	{
		Camera *cam = CameraManipulator::instance().getActiveCamera();
		if (cam && fadeRangeOut > 1e-5) {
			float range = cam->getRange(this);
			if (range > fadeRangeOut) {
				if (isRealized())
					unrealize();
			} else if (range > fadeRangeIn) {
				float multiplier = 1.f - (range-fadeRangeIn)/(fadeRangeOut-fadeRangeIn);
				light->setAmbient(ambient*multiplier);
				light->setDiffuse(diffuse*multiplier);
				light->setSpecular(specular*multiplier);
				if (!isRealized())
					realize();
			}
		}
		BaseObject::update(dt);
	}
	
	osg::StateSet* Light::getStateSet()
	{
		if (local)
			return getRoot()->getTransform()->getOrCreateStateSet();	
		else
			return globalLightStateSet.get();
	}

	Light::LightNumUseMap Light::lightUsed;
	osg::observer_ptr<osg::StateSet> Light::globalLightStateSet = NULL;
	
} // namespace

