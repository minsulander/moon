#include "GridPlane.h"
#include <osg/StateSet>
#include <osg/LightModel>
#include <osg/Depth>

using namespace osg;

namespace mdraw {
	
	GridPlane::GridPlane(const int grids, const osg::Vec4& params, 
						 const float gridsize, const osg::Vec4& color) : osg::Geometry() {
		_params = params;
		_grids = grids;
		_gridsize = gridsize;
		
		// Make the grid
		_vertices = new osg::Vec3Array;
		setParams(params);
		setVertexArray(_vertices);
		_draw = new DrawElementsUInt(PrimitiveSet::LINES,0);
		for (size_t i=0; i < _vertices->size(); i++) {
			if ((i+1) % (2*_grids+1) != 0) {
				_draw->push_back(i);
				_draw->push_back(i+1);
			}
			if (i < _vertices->size()-(_grids*2+1)) {
				_draw->push_back(i);
				_draw->push_back(i+_grids*2+1);
			}
		}
		addPrimitiveSet(_draw);
		// Set color
		osg::Vec4Array* colors = new Vec4Array;
		colors->push_back(color);
		setColorArray(colors);
		setColorBinding(Geometry::BIND_OVERALL);
		// Disable lighting
		StateSet *state = getOrCreateStateSet();
		LightModel *lightm = new LightModel;
		lightm->setAmbientIntensity(Vec4(1.0f,1.0f,1.0f,1.0f));
		state->setAttribute(lightm);
	}
	
	void GridPlane::remakeGrid() {
		// Make the normal vector
		osg::Vec3 normal(_params.x(),_params.y(),_params.z());
		normal.normalize();
		// Make two unit vectors 'u' and 'v' parallell with the plane
		osg::Vec3 u(-normal.z(),normal.x(),normal.y());
		osg::Vec3 v = u ^ normal;
		
		_vertices->clear();
		
		for (float f=-_grids*_gridsize; f<=_grids*_gridsize;f+=_gridsize) {
			for (float g=-_grids*_gridsize; g<=_grids*_gridsize;g+=_gridsize) {
				_vertices->push_back(u*f + v*g + normal*_params.w());
			}
		}
		dirtyDisplayList();
	}
	
}
