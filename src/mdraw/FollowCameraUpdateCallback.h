#ifndef FOLLOWCAMERAUPDATECALLBACK_H_
#define FOLLOWCAMERAUPDATECALLBACK_H_

#include "Export.h"
#include <osg/NodeCallback>
#include <osg/View>

namespace mdraw {
	
	/// \brief An update callback that follows the current viewing camera
	/// \ingroup draw
	class MDRAW_EXPORT FollowCameraUpdateCallback : public osg::NodeCallback
	{
	public:
		FollowCameraUpdateCallback();
		virtual ~FollowCameraUpdateCallback();
		virtual void operator() (osg::Node *node, osg::NodeVisitor *nv);
		void setDirection(const osg::Vec3& direction) { this->direction = direction; }
		const osg::Vec3& getDirection() { return direction; }
		void setStep(const int step) { this->step = step; }
		const int getStep() { return step; }
	protected:
		osg::Vec3 direction, origpos;
		bool firstupdate;
		int step;
	};
	
}

#endif /*FOLLOWCAMERAUPDATECALLBACK_H_*/
