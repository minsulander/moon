#include "FollowCameraUpdateCallback.h"

#include <osg/MatrixTransform>
#include <osgUtil/CullVisitor>

namespace mdraw {
	
	FollowCameraUpdateCallback::FollowCameraUpdateCallback()
	{
		direction = osg::Vec3(1,1,1);
		origpos = osg::Vec3(0,0,0);
		step = 0;
		firstupdate = true;
	}
	
	FollowCameraUpdateCallback::~FollowCameraUpdateCallback()
	{
	}
	
	void FollowCameraUpdateCallback::operator() (osg::Node *node, osg::NodeVisitor *nv)
	{
		if (nv->getVisitorType() == osg::NodeVisitor::CULL_VISITOR && node->asTransform()->asMatrixTransform()) {
			osg::MatrixTransform* transform = (osg::MatrixTransform*) node;
			osg::Vec3 eye = nv->getEyePoint()+origpos;
			osg::Vec3 direye(eye.x()*direction.x(),eye.y()*direction.y(),eye.z()*direction.z());
			osg::Vec3 pos;
			if (step != 0) {
				int ix = (int)direye.x();
				pos.x() = ix-(ix % step);
				int iy = (int)direye.y();
				pos.y() = iy-(iy % step);
				int iz = (int)direye.z();
				pos.z() = iz-(iz % step);
			} else
				pos = direye;
			osg::Matrix M = transform->getMatrix();
			if (firstupdate) {
				origpos = M.getTrans();
				firstupdate = false;
				//dout(5) << "FollowCameraUpdateCallback origpos=" << origpos.x() << "," << origpos.y() << "," << origpos.z()
				//		<< " direye " << direye.x() << "," << direye.y() << "," << direye.z() << "\n";
			} 
			M.setTrans(M.getTrans()+pos);
			transform->setMatrix(M);
		}
		nv->traverse(*node);
	}
	
}
