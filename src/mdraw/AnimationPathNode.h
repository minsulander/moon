#ifndef MDRAW_ANIMATIONPATHNODE_H
#define MDRAW_ANIMATIONPATHNODE_H

#include "Export.h"
#include <osg/AnimationPath>
#include <osg/Vec4>

namespace mdraw {

	extern MDRAW_EXPORT osg::Node* createAnimationPathNode(const osg::AnimationPath *path, const osg::Vec4& color = osg::Vec4(1,1,1,1));
	
}

#endif
