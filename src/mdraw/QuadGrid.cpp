#include "QuadGrid.h"

#include <osg/StateSet>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

namespace mdraw {
	
	QuadGrid::QuadGrid(const osg::Vec4& params, const unsigned int grids, 
					   const float gridsize, const osg::Vec4& color1,
					   const osg::Vec4& color2) : osg::Geometry() {
		_params = params;
		_grids = grids;
		_gridsize = gridsize;
		
		// Make the grid
		_vertices = new osg::Vec3Array;
		unsigned int vecs = setParams(params);
		setVertexArray(_vertices);
		addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,vecs));
		
		// Set color
		osg::Vec4Array* colors = new osg::Vec4Array;
		for (unsigned int i = 0; i < grids; i++) {
			for (unsigned int i = 0; i < grids; i++) {
				colors->push_back(color1);
				colors->push_back(color2);
			}
			for (unsigned int i = 0; i < grids; i++) {
				colors->push_back(color2);
				colors->push_back(color1);
			}
		}
		setColorArray(colors);
		setColorBinding(Geometry::BIND_PER_PRIMITIVE);
		
		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(params.x(),params.y(),params.z()));
		setNormalArray(normals);
		setNormalBinding(Geometry::BIND_OVERALL);
		
	}
	
	unsigned int QuadGrid::setParams(const osg::Vec4& params) {
		// Make the normal vector
		osg::Vec3 normal(params.x(),params.y(),params.z());
		normal.normalize();
		// Make two unit vectors 'ex' and 'ey' parallell with the plane
		osg::Vec3 ey(-normal.z(),normal.x(),normal.y());
		osg::Vec3 ex = ey ^ normal;
		
		_vertices->clear();
		unsigned int count = 0;
		for (float y=-_grids*_gridsize; y<_grids*_gridsize;y+=_gridsize) {
			for (float x=-_grids*_gridsize; x<_grids*_gridsize;x+=_gridsize) {
				_vertices->push_back(ex*x + ey*y + normal*params.w());
				_vertices->push_back(ex*x + ey*(y+_gridsize) + normal*params.w());
				_vertices->push_back(ex*(x+_gridsize) + ey*(y+_gridsize) + normal*params.w());
				_vertices->push_back(ex*(x+_gridsize) + ey*y + normal*params.w());
				osg::Vec3 v = ex*x + ey*y;
				osg::Vec3 w = ex*x + ey*(y+_gridsize);
				count += 4;
			}
		}
		dirtyDisplayList();
		_params = params;
		return count;
	}
	
}
