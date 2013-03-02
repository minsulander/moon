#include "TexturePlane.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include <osg/Geometry>
#include <osg/BlendFunc>
#include <osg/TextureRectangle>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osgDB/ReadFile>
#include <osg/io_utils>

namespace moon {

	REGISTER_Object(moon, TexturePlane);

	class TexturePanCallback : public osg::NodeCallback
	{
	public:
		TexturePanCallback(osg::TexMat* ntexmat,
						   const osg::Vec3 npanvelocity) :
        texmat(ntexmat),
		panvelocity(npanvelocity)
		{
		}
		
		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
		{
			// Check that it is a proper visitor
			if (!texmat || nv->getVisitorType() != osg::NodeVisitor::UPDATE_VISITOR || !nv->getFrameStamp())
				return;
			double currTime = nv->getFrameStamp()->getSimulationTime();
			texmat->setMatrix(osg::Matrix::translate(panvelocity * currTime));
			prevTime = currTime;
			nv->traverse(*node);
		}
		
	private:
		osg::TexMat* texmat;
		osg::Vec3 panvelocity;
		double delay;
		double prevTime;
	};
	
	TexturePlane::TexturePlane()
	:	VisualModel(),
		width(10000),
		length(10000),
		color(osg::Vec4(1.f,1.f,1.f,1.f)),
		texscale(1),
		nofog(false),
		nolight(false)
	{
	}
	
	TexturePlane::TexturePlane(const TexturePlane& other, const osg::CopyOp& copyop)
	:	VisualModel(other, copyop),
		width(other.width),
		length(other.length),
		color(other.color),
		teximage(other.teximage),
		texscale(other.texscale),
		panvelocity(other.panvelocity),
		nofog(other.nofog),
		nolight(other.nolight)
	{
	}
	
	void TexturePlane::parseXML(const TiXmlElement *element)
	{
		VisualModel::parseXML(element);
		//=== TexturePlane
		//=See superclass VisualModel for more parameters.
		//=* attribute: width="(number)"
		XMLParser::parseDoubleAttribute(width, element, "width");
		//=* attribute: length="(number)"
		XMLParser::parseDoubleAttribute(length, element, "length");
		//=* attribute: image="(filename)"
		//=. Texture filename
		XMLParser::parseStringAttribute(teximage, element, "image");
		//=* attribute: texscale="(number)"
		//=. How many repetitions of the texture cover the entire plane
		XMLParser::parseDoubleAttribute(texscale, element, "texscale");
		//=* attribute: color="(vector4)"
		XMLParser::parseVector4Attribute(color, element, "color");
		//=* attribute: panvel="(vector3)"
		//=. Apply a texture panning velocity (usefol for cloud layers etc)
		XMLParser::parseVector3Attribute(panvelocity, element, "panvel");
		//=* attribute: nofog="true|false"
		XMLParser::parseBooleanAttribute(nofog, element, "nofog");
		//=* attribute: nolight="true|false"
		XMLParser::parseBooleanAttribute(nolight, element, "nolight");
	}
	
	void TexturePlane::writeXML(TiXmlElement *element) const
	{
		VisualModel::writeXML(element);
		element->SetDoubleAttribute("width", width);
		element->SetDoubleAttribute("length", length);
		std::stringstream ss;
		ss << color;
		element->SetAttribute("color", ss.str());
		if (teximage.length() > 0) {
			element->SetAttribute("image", teximage);
			element->SetDoubleAttribute("texscale", texscale);
		}
		ss.str("");
		ss << panvelocity;
		element->SetAttribute("panvel", ss.str());
		element->SetAttribute("nofog", nofog);
		element->SetAttribute("nolight", nolight);
	}
	
	osg::Node* TexturePlane::getNode()
	{
		if (!planeNode)
			planeNode = createPlane();
		return planeNode.get();
	}
	
	osg::Node* TexturePlane::createPlane()
	{
		osg::Geometry *geometry = new osg::Geometry;
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(geometry);
		osg::StateSet* state = geometry->getOrCreateStateSet();
		
		osg::Vec3Array *vertices = new osg::Vec3Array;
		vertices->push_back(osg::Vec3(-width/2,-length/2,0));
		vertices->push_back(osg::Vec3(width/2,-length/2,0));
		vertices->push_back(osg::Vec3(width/2,length/2,0));
		vertices->push_back(osg::Vec3(-width/2,length/2,0));
		geometry->setVertexArray(vertices);
		
		osg::Vec3Array *normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0,0,1));
		geometry->setNormalArray(normals);
		geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(color);
		geometry->setColorArray(colors);
		geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		
		// setup texture
		osg::Texture2D* texture = new osg::Texture2D;
		
		// load image
		if (teximage.length() > 0) {
			osg::Image* img = osgDB::readImageFile(teximage);
			texture->setImage(img);
			osg::Vec2Array *texcoords = new osg::Vec2Array;
			texcoords->push_back(osg::Vec2(0,0));
			texcoords->push_back(osg::Vec2(width/texscale,0));
			texcoords->push_back(osg::Vec2(width/texscale,width/texscale));
			texcoords->push_back(osg::Vec2(0,width/texscale));
			geometry->setTexCoordArray(0, texcoords);
			texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::MIRROR);
			texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::MIRROR);

			osg::TexMat* texmat = new osg::TexMat;
			texmat->setScaleByTextureRectangleSize(true);
			
			state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
			state->setTextureAttributeAndModes(0, texmat, osg::StateAttribute::ON);
			if (panvelocity.length() > 1e-5)
				geode->setUpdateCallback(new TexturePanCallback(texmat, panvelocity/texscale));
		}

		geometry->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
		// enable transparency
		if (fabs(color.w() - 1.f) > 1e-5) {
			osg::BlendFunc *bf = new osg::BlendFunc();
			bf->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			//bf->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE);
			state->setAttributeAndModes(bf,osg::StateAttribute::ON);
			state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		}
		
		// disable lighting and culling
		if (nolight)
			state->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
		
		/// disable fog
		if (nofog)
			state->setMode(GL_FOG, osg::StateAttribute::OFF );

		return geode;
	}
}
