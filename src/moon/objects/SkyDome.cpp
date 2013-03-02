#include "SkyDome.h"
#include "moon/ObjectFactory.h"
#include "mlog/Log.h"
#include "moon/XMLParser.h"
#include <mdraw/FollowCameraUpdateCallback.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osg/Depth>
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include <osg/io_utils>

#ifdef _MSC_VER
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#endif

using namespace osg;
using namespace mlog;

namespace moon {
	
	REGISTER_Object(moon, SkyDome);
	
    const float default_elevations[] = { -10.0, -5.0, 0.0, 15.0, 30.0, 60.0, 90.0  };
    const float default_colors[][4] =
	{
	{ 0.0, 0.0, 0.15 },
	{ 0.0, 0.0, 0.15 },
	{ 0.4, 0.4, 0.7 },
	{ 0.2, 0.2, 0.6 },
	{ 0.15, 0.15, 0.5 },
	{ 0.1, 0.1, 0.4 },
	{ 0.1, 0.1, 0.4 },
    };
	
	SkyDome::SkyDome()
	:	BaseObject(),
		created(false),
		radius(10000.0f),
		defaultValues(true)
	{
		for (unsigned int i = 0; i < sizeof(default_elevations)/sizeof(float); i++)
			elevations.push_back(default_elevations[i]);
		std::vector<osg::Vec4> color;
		for (unsigned int i = 0; i < elevations.size(); i++)
			colors.push_back(osg::Vec4(default_colors[i][0], default_colors[i][1], default_colors[i][2], 1.0));
	}
	
	SkyDome::SkyDome(const SkyDome& other, const osg::CopyOp& copy)
	:	BaseObject(other),
		created(other.created),
		radius(other.radius),
		elevations(other.elevations),
		colors(other.colors),
		texture(other.texture),
		defaultValues(other.defaultValues)
	{
	}
	
	void SkyDome::parseXML(const TiXmlElement *element)
	{
		BaseObject::parseXML(element);
		//=== SkyDome
		//=See superclass BaseObject for more parameters.
		//=* attribute: image="(string)"
		//=. Setup a sky dome with the specified texture file
		if (element->Attribute("image")) {
			texture = XMLParser::parseStringAttribute(element, "image");
			elevations.clear();
			colors.clear();
			//=* attribute: start="(number)" [degrees] (default -5.0)
			//=. Start (bottom) elevation that the lower edge of the image corresponds to
			float start = XMLParser::parseDoubleAttribute(element, "start", true, -5.0);
			//=* attribute: interval="(number)" [degrees] (default 10.0)
			//=. Elevation interval for the sky dome geometry
			float interval = XMLParser::parseDoubleAttribute(element, "interval", true, 10.0);
			for (float a = start; a < 90.0; a += interval) {
				elevations.push_back(a);
				colors.push_back(osg::Vec4(1,1,1,1));
			}
			elevations.push_back(90.0);
			colors.push_back(osg::Vec4(1,1,1,1));
			defaultValues = false;
		}
		//=* attribute: radius="(number)" [m] (default 10000)
		double value;
		if (XMLParser::parseDoubleAttribute(value, element, "radius")) {
			radius = value;
			defaultValues = false;
		}
		if (element->FirstChildElement("elevation")) {
			//=* repeatable element: elevation angle="(number)" [degrees, required] color="(vector4)" [required]
			//=. Elevations (above the horizon) and colors that make up the color gradient of the sky dome
			//=. <b>Must be specified in ascending order</b>
			elevations.clear();
			colors.clear();
			for (const TiXmlElement *ee = element->FirstChildElement("elevation"); ee; ee = ee->NextSiblingElement("elevation")) {
				double elevation = XMLParser::parseDoubleAttribute(ee, "angle");
				osg::Vec4 color = XMLParser::parseVector4Attribute(ee, "color");
				elevations.push_back(elevation);
				colors.push_back(color);
			}
			defaultValues = false;
		}
		//=* element: texture file="(string)"
		//=. A texture which is loaded and modulated on top of colors as specified above
		if (XMLParser::parseString(texture, element, "texture","file")) {
			dout(5) << "    texture: " << texture << "\n";
			defaultValues = false;
		}
	}
	
	void SkyDome::writeXML(TiXmlElement *element) const
	{
		BaseObject::writeXML(element);
		
		if (defaultValues)
			return;
		
		bool shortspec = false;
		if (texture.length() > 0) {
			element->SetAttribute("image", texture);
			shortspec = true;
			for (unsigned int i = 0; i < colors.size(); i++) {
				if (colors[i] != osg::Vec4(1,1,1,1))
					shortspec = false;
			}
		}
		element->SetDoubleAttribute("radius", radius);
		if (shortspec) {
			element->SetDoubleAttribute("start", elevations[0]);
			element->SetDoubleAttribute("interval", elevations[1]-elevations[0]);
		} else {
			for (unsigned int i = 0; i < elevations.size(); i++) {
				TiXmlElement *elevationElement = new TiXmlElement("elevation");
				elevationElement->SetDoubleAttribute("angle", elevations[i]);
				std::stringstream ss; ss << colors[i];
				elevationElement->SetAttribute("color", ss.str());
				element->LinkEndChild(elevationElement);
			}
		}

		// "undo" saving of position which is set by camera following
		element->RemoveAttribute("pos");
	}
	
	void SkyDome::realize()
	{
		if (!created) {
			dout(5) << "Creating sky dome\n";
			osg::Node *sky = createSky();
			addNode(sky);
			// Add a follow update callback
			mdraw::FollowCameraUpdateCallback *follow = new mdraw::FollowCameraUpdateCallback();
			follow->setDirection(osg::Vec3(1,1,0));
			transform->setCullCallback(follow);
		}
		BaseObject::realize();
	}
	
	osg::Node* SkyDome::createSky()
	{
		int i, j;
		
		float x, y, z;
		float alpha, theta;
		int nlev = elevations.size();
		int nlaz = 19;
		Geometry *geom = new Geometry;
		
		Vec3Array& coords = *(new Vec3Array(19*nlev));
		Vec4Array& colorv = *(new Vec4Array(19*nlev));
		Vec2Array& tcoords = *(new Vec2Array(19*nlev));
		
		
		int ci = 0;
		
		for( i = 0; i < nlev; i++ )
		{
			for( j = 0; j < nlaz; j++ )
			{
				alpha = osg::DegreesToRadians(elevations[i]);
				theta = osg::DegreesToRadians((float)(j*(nlaz+1)));
				
				x = radius * cosf( alpha ) * cosf( theta );
				y = radius * cosf( alpha ) * -sinf( theta );
				z = radius * sinf( alpha );
				
				coords[ci][0] = x;
				coords[ci][1] = y;
				coords[ci][2] = z;
				
				colorv[ci][0] = colors[i][0];
				colorv[ci][1] = colors[i][1];
				colorv[ci][2] = colors[i][2];
				colorv[ci][3] = colors[i][3];
				
				tcoords[ci][0] = (float)j/(float)(nlaz-1);
				tcoords[ci][1] = (float)i/(float)(nlev-1);
				
				ci++;
			}
			
			
		}
		
		for( i = 0; i < nlev-1; i++ )
		{
			DrawElementsUShort* drawElements = new DrawElementsUShort(PrimitiveSet::TRIANGLE_STRIP);
			drawElements->reserve(38);
			
			for( j = 0; j <= 18; j++ )
			{
				drawElements->push_back((i+1)*19+j);
				drawElements->push_back((i+0)*19+j);
			}
			
			geom->addPrimitiveSet(drawElements);
		}
		
		geom->setVertexArray( &coords );
		geom->setTexCoordArray( 0, &tcoords );
		
		geom->setColorArray( &colorv );
		geom->setColorBinding( Geometry::BIND_PER_VERTEX );
		
		StateSet *dstate = new StateSet;

		if (texture.length() > 0) {
			Texture2D *tex = new Texture2D;
			osg::Image *image = osgDB::readImageFile(texture);
			if (!image)
				dout(ERROR) << "Failed to load skydome texture '" << texture << "'\n";
			tex->setImage(image);
			dstate->setTextureAttributeAndModes(0, tex, StateAttribute::ON );
			dstate->setTextureAttribute(0, new TexEnv );
		}

		// disable lighting and culling
		dstate->setMode( GL_LIGHTING, StateAttribute::OFF );
		dstate->setMode( GL_CULL_FACE, StateAttribute::ON );

		/// disable fog
		dstate->setMode(GL_FOG, osg::StateAttribute::OFF );
    	
		// clear the depth to the far plane.
		osg::Depth* depth = new osg::Depth;
		depth->setFunction(osg::Depth::ALWAYS);
		depth->setRange(1.0,1.0);   
		dstate->setAttributeAndModes(depth,StateAttribute::ON );
		
		dstate->setRenderBinDetails(-2,"RenderBin");
		
		geom->setStateSet( dstate );
		
		Geode *geode = new Geode;
		geode->addDrawable( geom );
		geode->setName( "SkyDome" );
				
		return geode;
	}
	

} // namespace
