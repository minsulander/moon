#ifndef MOON_SKYDOME_H
#define MOON_SKYDOME_H

#include "BaseObject.h"
#include <vector>
#include <osg/Vec4>

namespace moon {
	
	/// \ingroup core objects
	/// @{
	
	class SkyDome : public BaseObject {
	public:
		SkyDome();
		SkyDome(const SkyDome& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, SkyDome);

		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		virtual void realize();
	private:
		osg::Node* createSky();
		
		bool created;
		float radius;
		std::vector<float> elevations;
		std::vector<osg::Vec4> colors;
		std::string texture;
		bool defaultValues;
	};
	
	/// @}
	
}

#endif
