#ifndef MDRAW_LINEGEOMETRY_H
#define MDRAW_LINEGEOMETRY_H

#include "Export.h"
#include <osg/Geometry>
#include <osg/Geode>

namespace mdraw {
	
	extern MDRAW_EXPORT osg::Geometry *createLineGeometry(int type, osg::Vec3Array* array, const osg::Vec4& color = osg::Vec4(1,1,1,1));
	extern MDRAW_EXPORT osg::Geode *createLineGeode(int type, osg::Vec3Array* array, const osg::Vec4& color = osg::Vec4(1,1,1,1));
	
}

#endif
