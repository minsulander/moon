#include "AnimationPathNode.h"
#include "LineGeometry.h"
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

namespace mdraw {

	osg::Node *createAnimationPathNode(const osg::AnimationPath *path, const osg::Vec4& color)
	{
		if (!path)
			return NULL;
		
		osg::CompositeShape *cshape = new osg::CompositeShape;
		cshape->addChild(new osg::Box(osg::Vec3(0,0,0), 0.5f, 1.f, 0.1f));
		cshape->addChild(new osg::Box(osg::Vec3(0,-0.25f,0.25f), 0.1f, 0.5f, 0.5f));
		osg::ShapeDrawable *sd = new osg::ShapeDrawable(cshape);
		sd->setColor(color);
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(sd);
		osg::Group *group = new osg::Group;
		const osg::AnimationPath::TimeControlPointMap& cpmap = path->getTimeControlPointMap();
		osg::Vec3Array *array = new osg::Vec3Array(cpmap.size());
		unsigned int i = 0;
		for ( osg::AnimationPath::TimeControlPointMap::const_iterator it = cpmap.begin(); it != cpmap.end(); it++) {
			(*array)[i].set(it->second.getPosition());
			osg::MatrixTransform *xform = new osg::MatrixTransform;
			osg::Matrix M;
			it->second.getMatrix(M);
			xform->setMatrix(M);
			xform->addChild(geode);
			group->addChild(xform);
			i++;
		}
		group->addChild(createLineGeode(GL_LINE_STRIP, array, color));
		return group;
	}
	
}
