#include "Environment.h"
#include "XMLParser.h"
#include "ObjectFactory.h"
#include "mlog/Log.h"
#include "NodeMask.h"
#include "moon/objects/Light.h"
#include <osg/Fog>
#include <osg/Depth>
#include <osg/LightModel>
#include <osg/io_utils>
#include <osgShadow/ShadowMap>
#include <osgShadow/ShadowVolume>
#include <osgShadow/ShadowTexture>
#include <osgShadow/SoftShadowMap>
#include <osgShadow/ParallelSplitShadowMap>
#include <osgShadow/LightSpacePerspectiveShadowMap>
#include <osgShadow/StandardShadowMap>

using namespace mlog;

namespace moon {
	
	REGISTER_Object(moon, Environment);
	
	Environment::Environment()
	:	Component(),
		clearcolor(0.2f, 0.2f, 0.4f, 1.f),
		lightingmode(osg::View::HEADLIGHT),
		global_light_ambient(0.f, 0.f, 0.f, 1.f),
		global_light_diffuse(0.8f, 0.8f, 0.8f, 1.f),
		global_light_specular(1.f, 1.f, 1.f, 1.f)
	{
		states = new osg::StateSet;
	}
	
	Environment::Environment(const Environment& other, const osg::CopyOp& copyop)
	:	Component(other, copyop),
		clearcolor(other.clearcolor),
		lightingmode(other.lightingmode),
		global_light_ambient(other.global_light_ambient),
		global_light_diffuse(other.global_light_diffuse),
		global_light_specular(other.global_light_specular)
	{
		states = new osg::StateSet(*other.states.get());
	}
	
	void Environment::parseXML(const TiXmlElement *element)
	{
		//=== Environment
		//=* element: clear color="(vector4)"
		clearcolor = XMLParser::parseVector4(element,"clear","",true,clearcolor,"color");
		
		//=* element: lighting
		//=** attribute: mode="none|headlight|skylight" (default "none")
		if (element->FirstChildElement("lighting")) {
			std::string lightingmodestr = XMLParser::parseString(element,"lighting",true,"none","mode");
			if (lightingmodestr == "none")
				lightingmode = osg::View::NO_LIGHT;
			else if (lightingmodestr == "headlight")
				lightingmode = osg::View::HEADLIGHT;
			else if (lightingmodestr == "skylight")
				lightingmode = osg::View::SKY_LIGHT;
			//=** attribute: ambient="(vector4)"
			//=. Ambient intensity
			osg::Vec4 ambient = XMLParser::parseVector4(element,"lighting","",true,osg::Vec4(0.1f,0.1f,0.1f,1.f),"ambient");
			//=** attribute: local="true|false" (default false)
			bool local = XMLParser::parseBoolean(element,"lighting",true,false,"local");
			//=** attribute: twosided="true|false" (default false)
			bool twosided = XMLParser::parseBoolean(element,"lighting",true,false,"twosided");
			osg::LightModel *lm = new osg::LightModel;
			lm->setAmbientIntensity(ambient);
			lm->setLocalViewer(local);
			lm->setTwoSided(twosided);
			states->setAttributeAndModes(lm);		
		}
		
		//=* element: light
		//=. Light colors for the default headlight/skylight
		if (element->FirstChildElement("light")) {
			//=** attribute: ambient="(vector4)"
			global_light_ambient = XMLParser::parseVector4(element,"light","",true,global_light_ambient,"ambient");
			//=** attribute: diffuse="(vector4)"
			global_light_diffuse = XMLParser::parseVector4(element,"light","",true,global_light_diffuse,"diffuse");
			//=** attribute: specular="(vector4)"
			global_light_specular = XMLParser::parseVector4(element,"light","",true,global_light_specular,"specular");
		}
		
		//=* element: fog
		const TiXmlElement *fogElement = element->FirstChildElement("fog");
		if (fogElement) {
			osg::Fog *fog = new osg::Fog;
			//=** attribute: mode="linear|exp|exp2" (default "linear")
			std::string mode = XMLParser::parseStringAttribute(fogElement,"mode",true,"linear");
			if (mode == "linear")
				fog->setMode(osg::Fog::LINEAR);
			else if (mode == "exp")
				fog->setMode(osg::Fog::EXP);
			else if (mode == "exp2")
				fog->setMode(osg::Fog::EXP2);
			else
				throw ParseException("Unknown fog mode '" + mode + "'", fogElement);
			//=** attribute: density="(number)"
			if (fogElement->Attribute("density"))
				fog->setDensity(XMLParser::parseDoubleAttribute(fogElement,"density"));
			//=** attribute: start="(number)"
			if (fogElement->Attribute("start"))
				fog->setStart(XMLParser::parseDoubleAttribute(fogElement,"start"));
			//=** attribute: end="(number)"
			if (fogElement->Attribute("end"))
				fog->setEnd(XMLParser::parseDoubleAttribute(fogElement,"end"));
			//=** attribute: color="(vector4)"
			fog->setColor(XMLParser::parseVector4Attribute(fogElement,"color",true,clearcolor));
			states->setAttributeAndModes(fog);
		}
		//=* element: shadow
		const TiXmlElement *shadowElement = element->FirstChildElement("shadow");
		if (shadowElement) {
			shadowedScene = new osgShadow::ShadowedScene;
			//=** attribute: technique="sm|ssm|stsm|st|sv|pssm|lispsm" (default "sm")
			std::string str;
			XMLParser::parseStringAttribute(str, shadowElement, "technique");
			if (str == "sv") {
				// hint to tell viewer to request stencil buffer when setting up windows
				osg::DisplaySettings::instance()->setMinimumNumStencilBits(8);
				
				osg::ref_ptr<osgShadow::ShadowVolume> sv = new osgShadow::ShadowVolume;
				//sv->setDynamicShadowVolumes(updateLightPosition);
				//while (arguments.read("--two-sided")) sv->setDrawMode(osgShadow::ShadowVolumeGeometry::STENCIL_TWO_SIDED);
				//while (arguments.read("--two-pass")) sv->setDrawMode(osgShadow::ShadowVolumeGeometry::STENCIL_TWO_PASS);
				
				shadowedScene->setShadowTechnique(sv.get());
			} else if (str == "st") {
				osg::ref_ptr<osgShadow::ShadowTexture> st = new osgShadow::ShadowTexture;
				shadowedScene->setShadowTechnique(st.get());
			} else if (str == "stsm") {
				osg::ref_ptr<osgShadow::StandardShadowMap> st = new osgShadow::StandardShadowMap;
				shadowedScene->setShadowTechnique(st.get());
			} else if (str == "pssm") {
				int mapcount = 3;
				//while (arguments.read("--mapcount", mapcount));
				osg::ref_ptr<osgShadow::ParallelSplitShadowMap> pssm = new osgShadow::ParallelSplitShadowMap(NULL,mapcount);
				/*
				int mapres = 1024;
				while (arguments.read("--mapres", mapres))
					pssm->setTextureResolution(mapres);
				
				while (arguments.read("--debug-color")) { pssm->setDebugColorOn(); }
				
				
				int minNearSplit=0;
				while (arguments.read("--minNearSplit", minNearSplit))
					if ( minNearSplit > 0 ) {
						pssm->setMinNearDistanceForSplits(minNearSplit);
						std::cout << "ParallelSplitShadowMap : setMinNearDistanceForSplits(" << minNearSplit <<")" << std::endl;
					}
				
				int maxfardist = 0;
				while (arguments.read("--maxFarDist", maxfardist))
					if ( maxfardist > 0 ) {
						pssm->setMaxFarDistance(maxfardist);
						std::cout << "ParallelSplitShadowMap : setMaxFarDistance(" << maxfardist<<")" << std::endl;
					}
				
				int moveVCamFactor = 0;
				while (arguments.read("--moveVCamFactor", moveVCamFactor))
					if ( maxfardist > 0 ) {
						pssm->setMoveVCamBehindRCamFactor(moveVCamFactor);
						std::cout << "ParallelSplitShadowMap : setMoveVCamBehindRCamFactor(" << moveVCamFactor<<")" << std::endl;
					}
				 */
				
				double polyoffsetfactor = pssm->getPolygonOffset().x();
				double polyoffsetunit   = pssm->getPolygonOffset().y();
				//while (arguments.read("--PolyOffset-Factor", polyoffsetfactor));
				//while (arguments.read("--PolyOffset-Unit", polyoffsetunit));
				pssm->setPolygonOffset(osg::Vec2(polyoffsetfactor,polyoffsetunit));
				shadowedScene->setShadowTechnique(pssm.get());
			} else if (str == "ssm") {
				osg::ref_ptr<osgShadow::SoftShadowMap> sm = new osgShadow::SoftShadowMap;
				shadowedScene->setShadowTechnique(sm.get());
			} else if (str == "lispsm") {
				osg::ref_ptr<osgShadow::MinimalShadowMap> sm = NULL;
				/*
				if( arguments.read( "--ViewBounds" ) )
					sm = new osgShadow::LightSpacePerspectiveShadowMapVB;
				else if( arguments.read( "--CullBounds" ) )
					sm = new osgShadow::LightSpacePerspectiveShadowMapCB;
				else // if( arguments.read( "--DrawBounds" ) ) // default
					sm = new osgShadow::LightSpacePerspectiveShadowMapDB;
				 */
				sm = new osgShadow::LightSpacePerspectiveShadowMapVB;
				shadowedScene->setShadowTechnique( sm.get() );
				if( sm.valid() ) 
				{
					//while( arguments.read("--debugHUD") )           
					//	sm->setDebugDraw( true );
					
					float minLightMargin = 10.f;
					float maxFarPlane = 0;
					unsigned int texSize = 1024;
					unsigned int baseTexUnit = 0;
					unsigned int shadowTexUnit = 1;
					
					/*
					while ( arguments.read("--moveVCamFactor", minLightMargin ) );
					while ( arguments.read("--minLightMargin", minLightMargin ) );
					while ( arguments.read("--maxFarDist", maxFarPlane ) );
					while ( arguments.read("--mapres", texSize ));
					while ( arguments.read("--baseTextureUnit", baseTexUnit) );
					while ( arguments.read("--shadowTextureUnit", shadowTexUnit) );
					 */
					
					sm->setMinLightMargin( minLightMargin );
					sm->setMaxFarPlane( maxFarPlane );
					sm->setTextureSize( osg::Vec2s( texSize, texSize ) );
					sm->setShadowTextureCoordIndex( shadowTexUnit );
					sm->setShadowTextureUnit( shadowTexUnit );
					sm->setBaseTextureCoordIndex( baseTexUnit );
					sm->setBaseTextureUnit( baseTexUnit );
				}
			} else if (str == "sm" || str.length() == 0) {
				// Default "sm" for shadowmap
				osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
				shadowedScene->setShadowTechnique(sm.get());
				int mapres;
				if (XMLParser::parseIntAttribute(mapres, shadowElement, "mapres"))
					sm->setTextureSize(osg::Vec2s(mapres,mapres));
			} else
				throw ParseException("Unknown shadow technique", shadowElement);
			shadowedScene->setReceivesShadowTraversalMask(NodeMask::RECEIVE_SHADOW);
			shadowedScene->setCastsShadowTraversalMask(NodeMask::CAST_SHADOW);
		}
		Component::parseXML(element);
	}
	
	void Environment::writeXML(TiXmlElement *element) const
	{
		XMLParser::setVector4(element, "clear", clearcolor, "color");
		switch (lightingmode) {
			case osg::View::NO_LIGHT: XMLParser::setString(element, "lighting", "none", "mode"); break;
			case osg::View::HEADLIGHT: XMLParser::setString(element, "lighting", "headlight", "mode"); break;
			case osg::View::SKY_LIGHT: XMLParser::setString(element, "lighting", "skylight", "mode"); break;
		}
		const osg::LightModel *lm = dynamic_cast<const osg::LightModel*> (states->getAttribute(osg::StateAttribute::LIGHTMODEL));
		if (lm) {
			XMLParser::setVector4(element, "lighting", lm->getAmbientIntensity(), "ambient");
			XMLParser::setBoolean(element, "lighting", lm->getLocalViewer(), "local");
			XMLParser::setBoolean(element, "lighting", lm->getTwoSided(), "twosided");
		}
		if (lightingmode != osg::View::NO_LIGHT) {
			XMLParser::setVector4(element, "light", global_light_ambient, "ambient");
			XMLParser::setVector4(element, "light", global_light_diffuse, "diffuse");
			XMLParser::setVector4(element, "light", global_light_specular, "specular");
		}
		const osg::Fog *fog = dynamic_cast<const osg::Fog*> (states->getAttribute(osg::StateAttribute::FOG));
		if (fog) {
			TiXmlElement *fogElement = new TiXmlElement("fog");
			switch (fog->getMode()) {
				case osg::Fog::LINEAR: fogElement->SetAttribute("mode", "linear");
				case osg::Fog::EXP: fogElement->SetAttribute("mode", "exp");
				case osg::Fog::EXP2: fogElement->SetAttribute("mode", "exp2");
			}
			fogElement->SetDoubleAttribute("density", fog->getDensity());
			fogElement->SetDoubleAttribute("start", fog->getStart());
			fogElement->SetDoubleAttribute("end", fog->getEnd());
			std::stringstream ss; ss << fog->getColor();
			fogElement->SetAttribute("color", ss.str());
		}
		/// \todo write shadowed scene
		Component::writeXML(element);
	}
	
	void Environment::apply(osg::Group *group)
	{
		group->getOrCreateStateSet()->merge(*states.get());
		Light::globalLightStateSet = group->getOrCreateStateSet();
	}
	
	void Environment::apply(osg::Camera *camera)
	{
		camera->setClearColor(clearcolor);
		camera->getView()->setLightingMode(lightingmode);
		osg::Light *light = camera->getView()->getLight();
		if (light) {
			if (lightingmode == osg::View::NO_LIGHT)
				camera->getView()->setLight(NULL);
			else {
				light->setAmbient(global_light_ambient);
				osg::Vec4 c = light->getAmbient();
				light->setDiffuse(global_light_diffuse);
				c = light->getDiffuse();
				light->setSpecular(global_light_specular);
				c = light->getSpecular();				
				Light::setLightNumUsed(light->getLightNum());
				dout(5) << "Light num " << light->getLightNum() << " used by viewer\n";
			}
		}
	}
	
} // namespace
