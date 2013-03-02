#ifndef MDRAW_QUADGRID_H
#define MDRAW_QUADGRID_H

#include "Export.h"
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geometry>

namespace mdraw {
	
	/// \brief Grid drawable, mostly used for debug graphics
	/// \ingroup draw
    class MDRAW_EXPORT QuadGrid : public osg::Geometry {
	public:
		
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        QuadGrid(const QuadGrid& gridplane,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):
		osg::Geometry(gridplane,copyop) {}
		
		META_Object(mdraw,QuadGrid);
		
		QuadGrid(const osg::Vec4 &params=osg::Vec4(0,0,1,0),
				 const unsigned int grids=10,
				 const float gridsize=1.0f,
				 const osg::Vec4 &color1=osg::Vec4(0.5f, 0.5f, 0.5f, 1.f),
				 const osg::Vec4 &color2=osg::Vec4(0.7f, 0.7f, 0.7f, 1.f));
		
		unsigned int setParams(const osg::Vec4 &params);
		const osg::Vec4& getParams() { return _params; }
		
	protected:
		
		osg::Vec4 _params;
		osg::Vec3Array *_vertices;
		osg::DrawElementsUInt *_draw;
		int _grids;
		float _gridsize;
    };
	
}

#endif
