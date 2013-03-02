#ifndef MDRAW_GRIDPLANE_H
#define MDRAW_GRIDPLANE_H

#include "Export.h"
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geometry>

namespace mdraw {
	
	/// \brief Grid drawable, mostly used for debug graphics
	/// \ingroup draw
    class MDRAW_EXPORT GridPlane : public osg::Geometry {
	public:
		
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        GridPlane(const GridPlane& gridplane,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):
		osg::Geometry(gridplane,copyop) {}
		
		META_Object(mdraw,GridPlane);
		
		GridPlane(const int grids=10, const osg::Vec4 &params=osg::Vec4(0.0,0.0,1.0,0),		  
				  const float gridsize=1.0f, const osg::Vec4 &color=osg::Vec4(0.5,0.5,0.5,1.0));
		
		void setParams(const osg::Vec4 &params) { _params = params; remakeGrid(); }
		const osg::Vec4& getParams() { return _params; }
		void setGridSize(const float gridsize) { _gridsize = gridsize; remakeGrid(); }
		const float getGridSize() { return _gridsize; }
		
	protected:
		
		void remakeGrid();
		
		osg::Vec4 _params;
		osg::Vec3Array *_vertices;
		osg::DrawElementsUInt *_draw;
		int _grids;
		float _gridsize;
    };
	
}

#endif
