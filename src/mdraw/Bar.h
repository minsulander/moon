#ifndef MDRAW_BAR_H
#define MDRAW_BAR_H

#include "Valuator.h"
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geode>
#include <osg/Geometry>

namespace mdraw {
	
	/// \brief A bargraph valuator
	/// \ingroup draw
    class MDRAW_EXPORT Bar : public osg::Geode, public Valuator {
	public:
		
		enum Orientation {
			HORIZONTAL,
			VERTICAL
		};
		
		enum Mode {
			STATIC,
			FALL
		};
		
		Bar(const float length = 1.0, const float width = 0.1, 
			const osg::Vec3 center = osg::Vec3(0,0,0),
			const Orientation orientation = HORIZONTAL);
        Bar(const Bar& bar,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		META_Node(mdraw,Bar);
		
		void setSize(const float length, const float width);
		virtual void setValue(const float value, const unsigned int index = 0);
		void setMin(const float min) { _min = min; }
		void setMax(const float max) { _max = max; }
		void setCenter(const osg::Vec3 center);
		void setOrientation(Orientation o);
		void setSpacing(const float spacing);
		void setBorderColor(const osg::Vec4 color);
		void setBarColor(const osg::Vec4 color);
		void setMarkColor(const osg::Vec4 color);
		void setMarkWidth(const float width);
		void setMarkThickness(const float thickness);
		void setMark(const float value);
		
		void setDrawBorder(const bool b) { _drawborder = b; update(); }
		void setDrawBar(const bool b) { _drawbar = b; update(); }
		void setDrawMark(const bool b) { _drawmark = b; update(); }
		void setLimitValue(const bool b) { _limit = b; }
		
		void setMarkMode(const Mode mode) { _markmode = mode; _drawmark = true; }
		void setMarkRate(const float rate) { _markrate = rate; }
		void setMarkDelay(const float delay) { _markdelay = delay; }
		void setBarMode(const Mode mode) { _barmode = mode; _drawbar = true; }
		void setBarRate(const float rate) { _barrate = rate; }
		void setBarDelay(const float delay) { _bardelay = delay; }
		
		float getLength() const { return _length; }
		float getWidth() const { return _width; }
		virtual float getValue(const unsigned int index = 0) const { return _value*_max; }
		float getMax() const { return _max; }
		const osg::Vec3& getCenter() const { return _center; }
		Orientation getOrientation() const { return _orientation; }
		float getSpacing() const { return _spacing; }
		const osg::Vec4& getBorderColor() const { return _bordercolor; }
		const osg::Vec4& getBarColor() const { return _barcolor; }
		const osg::Vec4& getMarkColor() const { return _markcolor; }
		float getMarkWidth() const { return _markwidth; }
		float getMarkThickness() const { return _markthickness; }
		float getMark() const { return _mark*_max; }
		Mode getMarkMode() const { return _markmode; }
		float getMarkRate() const { return _markrate; }
		float getMarkDelay() const { return _markdelay; }
		Mode getBarMode() const { return _barmode; }
		float getBarRate() const { return _barrate; }
		float getBarDelay() const { return _bardelay; }
		
		virtual void setValuePtr(const float *ptr, const unsigned int index = 0);
		virtual osg::Node* asNode() { return this; }
		virtual int getIndex(const std::string& name);
		
		virtual void traverse(osg::NodeVisitor& nv);
		
	protected:
		
		void update();		
		void createGeometry();
		
		float _length, _width;
		osg::Vec3 _center;
		Orientation _orientation;
		
		osg::Vec3Array *_barvecs, *_bordervecs, *_markvecs;
		osg::Vec4Array *_barcolors, *_bordercolors, *_markcolors;
		osg::Geometry *_bargeometry, *_bordergeometry, *_markgeometry;
		
		float _value, _region, _min, _max, _mark;
		float _spacing,_borderthickness,_markwidth,_markthickness;
		osg::Vec4 _bordercolor,_barcolor,_markcolor;
		
		bool _drawborder, _drawbar, _drawmark, _limit;
		
		float _time, _marktime, _markdelay,_markrate, _bartime, _bardelay, _barrate;
		Mode _markmode, _barmode;
		
		const float *_valueptr;
		const float *_markptr;
    };
	
}

#endif
