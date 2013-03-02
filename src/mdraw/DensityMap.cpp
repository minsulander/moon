#include "DensityMap.h"
#include <osg/MatrixTransform>
#include <osgUtil/LineSegmentIntersector>
#include <cstdlib>

namespace mdraw {
	
	DensityMap::DensityMap(osg::Image *imagein)
	:	osg::Object(),
		image(imagein),
		bbox(0,1,0,1,-10000,10000)
	{
		for (int i = 0; i < 4; i++)
			density[i] = 0;
	}
	
	DensityMap::DensityMap(const DensityMap& source, const osg::CopyOp& copyop)
	:	osg::Object(source, copyop),
		image(source.image),
		bbox(source.bbox)
	{
		for (int i = 0; i < 4; i++) {
			density[i] = source.density[i];
			positions[i] = source.positions[i];
		}
	}
	
	void DensityMap::setBounds(const float xmin, const float xmax, const float ymin, const float ymax)
	{
		bbox.set(xmin, ymin, bbox.zMin(), xmax, ymax, bbox.zMax());
	}
	
	void DensityMap::getBounds(float& xmin, float& xmax, float& ymin, float& ymax) const
	{
		xmin = bbox.xMin();
		xmax = bbox.xMax();
		ymin = bbox.yMin();
		ymax = bbox.yMax();
	}
	
	void DensityMap::setDensity(const float value)
	{
		for (int i = 0; i < 4; i++)
			density[i] = value;
	}
	
	float DensityMap::getPixelDensity(const unsigned int s, const unsigned int t, const Channel channel) const
	{
		if (!image)
			return 0;
		return image->getColor(s,t)[channel]*density[channel]/(image->s()*image->t());
	}
	
	void DensityMap::generate(const Channel channel)
	{
		positions[channel].clear();
		if (!image)
			return;
		unsigned int smax = image->s();
		unsigned int tmax = image->t();
		float xx = (bbox.xMax()-bbox.xMin())/(smax+1);
		float yy = (bbox.yMax()-bbox.yMin())/(tmax+1);
		for (unsigned int t = 0; t < tmax; t++) {
			for (unsigned int s = 0; s < smax; s++) {
				generatePixel(channel, osg::Vec3(bbox.xMin()+xx*s+xx/2, bbox.yMin()+yy*t+yy/2, 0), 
							  osg::Vec3(xx,yy,0), getPixelDensity(s,t,channel));
			}
		}
	}
	
	void DensityMap::generate()
	{
		for (int ch = 0; ch < 4; ch++)
			generate((Channel) ch);
	}

	/// \param terrainNode Terrain node clamp positions to
	/// \param align If set, normals will be generated and createNode() will align nodes to terrain surface normal
	void DensityMap::setHeights(const Channel channel, osg::Node *terrainNode, const bool align)
	{
		if (!terrainNode) return;
		if (align)
			normals[channel].clear();
		for (unsigned int i = 0; i < positions[channel].size(); i++) {
			osg::Vec3 pos = positions[channel][i];
			osg::Vec3 normal(0,0,1);
			getIntersection(osg::Vec3(pos.x(), pos.y(), bbox.zMax()), osg::Vec3(pos.x(), pos.y(), bbox.zMin()),
							terrainNode, pos, normal);
			positions[channel][i] = pos;
			normals[channel].push_back(normal);
		}
	}
	
	/// \param terrainNode Terrain node clamp positions to
	/// \param align If set, normals will be generated and createNode() will align nodes to terrain surface normal
	void DensityMap::setHeights(osg::Node *terrainNode, const bool align)
	{
		for (int ch = 0; ch < 4; ch++)
			setHeights((Channel) ch, terrainNode, align);
	}
	
	void DensityMap::setHeights(const Channel channel, osg::HeightField *hf, const bool align)
	{
		if (!hf) return;
		if (align)
			normals[channel].clear();
		float xi = hf->getXInterval();
		float yi = hf->getYInterval();
		unsigned int nc = hf->getNumColumns();
		unsigned int nr = hf->getNumRows();
		for (unsigned int i = 0; i < positions[channel].size(); i++) {
			osg::Vec3 pos = positions[channel][i];
			unsigned int r = (unsigned int)floor(pos.y()/yi);
			unsigned int c = (unsigned int)floor(pos.x()/xi);
			if (r > nr || c > nc)
				continue;
			pos.z() = hf->getHeight(c, r);
			positions[channel][i] = pos;
			if (align)
				normals[channel].push_back(hf->getNormal(c, r));
		}
	}
	
	void DensityMap::setHeights(osg::HeightField *hf, const bool align)
	{
		for (int ch = 0; ch < 4; ch++)
			setHeights((Channel) ch, hf, align);
	}
	
	osg::Node* DensityMap::createNode(const Channel channel, osg::Node *node)
	{
		if (!node) return NULL;
		bool align = false;
		if (normals[channel].size() == positions[channel].size())
			align = true;
		osg::Group *group = new osg::Group;
		for (unsigned int i = 0; i < positions[channel].size(); i++) {
			osg::Vec3 pos = positions[channel][i];
			osg::Matrix M = osg::Matrix::translate(pos);
			if (align)
				M = osg::Matrix::rotate(osg::Vec3(0,0,1), normals[channel][i]) * M;
			osg::MatrixTransform *xform = new osg::MatrixTransform;
			xform->setMatrix(M);
			xform->addChild(node);
			group->addChild(xform);
		}
		return group;
	}

	void DensityMap::generatePixel(const Channel channel, const osg::Vec3& center, const osg::Vec3& range, const float pixeldens)
	{
		float randf = (float) rand() / RAND_MAX;
		int num = (int) floor(pixeldens+randf);
		float randangle = ((float) rand() / RAND_MAX)*M_PI*2.f;
		
		if (num == 0) return;
		// Position "like dots on dice" for numbers 1-5
		else if (num == 1) {
			// with a bit of randomness
			float randx = ((float) rand() / RAND_MAX) - 0.5f;
			float randy = ((float) rand() / RAND_MAX) - 0.5f;
			positions[channel].push_back(center+ osg::Vec3(randx*range.x(), randy*range.y(), 0));
			return;
		} else if (num == 2) {
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*range/4);
			positions[channel].push_back(center-osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*range/4);
			return;
		} else if (num == 3) {
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(range.x()/4,0,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(0,range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(0,-range.y()/4,0));
			return;
		} else if (num == 4) {
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(range.x()/4,range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(range.x()/4,-range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(-range.x()/4,range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(-range.x()/4,-range.y()/4,0));
			return;
		} else if (num == 5) {
			positions[channel].push_back(center);
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(range.x()/4,range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(range.x()/4,-range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(-range.x()/4,range.y()/4,0));
			positions[channel].push_back(center+osg::Matrix::rotate(randangle,osg::Vec3(0,0,1))*osg::Vec3(-range.x()/4,-range.y()/4,0));
			return;
		} else {
			// Position randomly within range
			for (int i = 0; i < num; i++) {
				float x = ((float) rand()/RAND_MAX) * range.x();
				float y = ((float) rand()/RAND_MAX) * range.y();
				positions[channel].push_back(center + osg::Vec3(x,y,0));
			}
		}
			
	}
	
	bool DensityMap::getIntersection(const osg::Vec3& start, const osg::Vec3& end, osg::Node *node, osg::Vec3& pos, osg::Vec3& normal)
	{
		// Run intersector
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(start, end);
		osgUtil::IntersectionVisitor iv(intersector.get());
		node->accept(iv);
		// Go through intersections
		osgUtil::LineSegmentIntersector::Intersections& ixns = intersector->getIntersections();
		if (ixns.size() > 0) {
			osgUtil::LineSegmentIntersector::Intersection ix = *ixns.begin();
			// Move to intersection point
			pos = ix.getWorldIntersectPoint();
			normal = ix.getWorldIntersectNormal();
			return true;
		}
		return false;
	}
	
}
