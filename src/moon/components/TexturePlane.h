#ifndef MOON_TexturePlane_H
#define MOON_TexturePlane_H

#include "moon/components/VisualModel.h"

namespace moon {
	
	/// \ingroup core components
	/// @{

	class MOON_EXPORT TexturePlane : public VisualModel {
	public:
		TexturePlane();
		TexturePlane(const TexturePlane& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, TexturePlane);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual osg::Node *getNode();
		
	private:
		double width, length;
		osg::Vec4 color;
		std::string teximage;
		double texscale;
		osg::Vec3 panvelocity;
		bool nofog, nolight;
		
		osg::ref_ptr<osg::Node> planeNode;
		
		osg::Node* createPlane();
	};

	/// @}
	
}

#endif
