#include "LineGeometry.h"

namespace mdraw {

	osg::Geometry *createLineGeometry(int type, osg::Vec3Array* array, const osg::Vec4& color)
	{
		if (!array)
			return NULL;
		osg::Geometry *geometry = new osg::Geometry;
		geometry->setVertexArray(array);
		osg::Vec4Array *colors = new osg::Vec4Array(1);
		geometry->setColorArray(colors);
		geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		(*colors)[0] = color;
		geometry->addPrimitiveSet(new osg::DrawArrays(type,0,array->size()));
		return geometry;
	}
	
	osg::Geode *createLineGeode(int type, osg::Vec3Array* array, const osg::Vec4& color)
	{
		if (!array)
			return NULL;
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(createLineGeometry(type, array, color));
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		return geode;
	}

} // namespace
