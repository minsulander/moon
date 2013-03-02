#include "Bar.h"
#include "mlog/Log.h"

using namespace std;

namespace mdraw {
	
	Bar::Bar(const float length, const float width, const osg::Vec3 center,
			 const Orientation orientation) :
    _length(length),
    _width(width),
    _center(center),
    _orientation(orientation),
    _value(0),
    _region(0),
    _min(0),
    _max(1),
    _mark(0),
    _spacing(0),
    _borderthickness(0.01f),
    _markwidth(width),
    _markthickness(0.01f),
    _bordercolor(osg::Vec4(0.5f, 0.5f, 0.5f, 1.f)),
    _barcolor(osg::Vec4(0.8f, 0.8f, 0.8f, 1.f)),
    _markcolor(osg::Vec4(1,1,1,1)),
    _drawborder(true),
    _drawbar(false),
    _drawmark(false),
    _limit(true),
    _time(0),
    _marktime(0),
    _markdelay(1),
    _markrate(1),
    _bartime(0),
    _bardelay(0.2f),
    _barrate(2),
    _markmode(STATIC),
    _barmode(STATIC),
    _valueptr(NULL),
	_markptr(NULL)
	{
		createGeometry();
	}
	
	Bar::Bar(const Bar& source, const osg::CopyOp& copyop)
	: osg::Geode(source, copyop),
    _length(source._length),
    _width(source._width),
    _center(source._center),
    _orientation(source._orientation),
    _value(source._value),
    _region(source._region),
    _min(source._min),
    _max(source._max),
    _mark(source._mark),
    _spacing(source._spacing),
    _borderthickness(source._borderthickness),
    _markwidth(source._markwidth),
    _markthickness(source._markthickness),
    _bordercolor(source._bordercolor),
    _barcolor(source._barcolor),
    _markcolor(source._markcolor),
    _drawborder(source._drawborder),
    _drawbar(source._drawbar),
    _drawmark(source._drawmark),
    _limit(source._limit),
    _time(source._time),
    _marktime(source._marktime),
    _markdelay(source._markdelay),
    _markrate(source._markrate),
    _bartime(source._bartime),
    _bardelay(source._bardelay),
    _barrate(source._barrate),
    _markmode(source._markmode),
    _barmode(source._barmode),
    _valueptr(source._valueptr),
	_markptr(source._markptr)
	{
		createGeometry();
	}
	
	void Bar::setSize(const float length, const float width) {
		_length = length;
		_width = width;
		update();
	}
	
	void Bar::setValue(const float nvalue, const unsigned int index) {
		float value = (nvalue-_min)/(_max-_min);
		if (_limit && value > 1)
			value = 1;
		else if (_limit && value < 0)
			value = 0;
		if (index == 0) {
			_value = value;
			_drawbar = true;
		} else {
			_mark = value;
			_drawmark = true;
			_marktime = _time;
		}
		update();
	}
	
	void Bar::setCenter(const osg::Vec3 center) {
		_center = center;
		update();
	}
	
	void Bar::setOrientation(Orientation o) {
		_orientation = o;
		update();
	}
	
	void Bar::setSpacing(const float spacing) {
		_spacing = spacing;
		update();
	}
	
	void Bar::setBorderColor(const osg::Vec4 color) {
		_bordercolor = color;
		update();
	}
	
	void Bar::setBarColor(const osg::Vec4 color) {
		_barcolor = color;
		update();
	}
	
	void Bar::setMarkColor(const osg::Vec4 color) {
		_markcolor = color;
		update();
	}
	
	void Bar::setMarkWidth(const float width) {
		_markwidth = width;
		update();
	}
	
	void Bar::setMarkThickness(const float thickness) {
		_markthickness = thickness;
		update();
	}
	
	void Bar::setMark(const float value) {
		_mark = (value-_min)/(_max-_min);
		if (_limit && _mark > 1)
			_mark = 1;
		else if (_limit && _mark < 0)
			_mark = 0;
		_marktime = _time;
		_drawmark = true;
		update();
	}
	
	void Bar::setValuePtr(const float *ptr, const unsigned int index)
	{
		if (index == 0)
			_valueptr = ptr;
		else
			_markptr = ptr;
	}
	
	int Bar::getIndex(const std::string& name)
	{
		if (name == "bar")
			return 0;
		else if (name == "mark")
			return 1;
		return -1;
	}
	
	void Bar::traverse(osg::NodeVisitor& nv) {
		if (nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR) {
			float time = nv.getFrameStamp()->getReferenceTime();
			float dt = time-_time;
			_time = time;
			
			if (_valueptr)
				setValue(*_valueptr);
			if (_markptr)
				setMark(*_markptr);
			
			if (_drawmark) {
				// Make mark follow bar
				if (_markmode != STATIC && _mark < _value) {
					_mark = _value;
					_marktime = _time;
				}
				// Make mark fall after delay has run out
				if (_time - _marktime > _markdelay) {
					if (_markmode == FALL) {
						if (_mark > _value)
							_mark -= _markrate*dt;
						update();
					}
				}
			}
			if (_time - _bartime > _bardelay) {
				if (_barmode == FALL) {
					if (_value > 0)
						_value -= _barrate*dt;
					if (_value < 0)
						_value = 0;
					update();
				}
			}
		}
	}
	
	void Bar::update() {
		(*_bordercolors)[0] = _bordercolor;
		(*_barcolors)[0] = _barcolor;
		(*_markcolors)[0] = _markcolor;
		float zero = -_min/(_max-_min);
		if (_orientation == HORIZONTAL) {
			if (_drawborder) {
				(*_bordervecs)[0] = (_center+osg::Vec3(-_length/2-_spacing,-_width/2-_spacing,0));
				(*_bordervecs)[1] = (_center+osg::Vec3(-_length/2-_spacing,_width/2+_spacing,0));
				(*_bordervecs)[2] = (_center+osg::Vec3(_length/2+_spacing,_width/2+_spacing,0));
				(*_bordervecs)[3] = (_center+osg::Vec3(_length/2+_spacing,-_width/2-_spacing,0));
			}
			if (_drawbar) {
				(*_barvecs)[0] = (_center+osg::Vec3(-_length/2+zero*_length,-_width/2,0));
				(*_barvecs)[1] = (_center+osg::Vec3(-_length/2+zero*_length,_width/2,0));
				(*_barvecs)[2] = (_center+osg::Vec3(-_length/2+_value*_length,_width/2,0));
				(*_barvecs)[3] = (_center+osg::Vec3(-_length/2+_value*_length,-_width/2,0));
			}
			if (_drawmark) {
				(*_markvecs)[0] = (_center+osg::Vec3(-_length/2+_mark*_length-_markthickness/2,-_markwidth/2,0));
				(*_markvecs)[1] = (_center+osg::Vec3(-_length/2+_mark*_length-_markthickness/2,_markwidth/2,0));
				(*_markvecs)[2] = (_center+osg::Vec3(-_length/2+_mark*_length+_markthickness/2,_markwidth/2,0));
				(*_markvecs)[3] = (_center+osg::Vec3(-_length/2+_mark*_length+_markthickness/2,-_markwidth/2,0));
			}
		} else {
			if (_drawborder) {
				(*_bordervecs)[0] = (_center+osg::Vec3(-_width/2-_spacing,-_length/2-_spacing,0));
				(*_bordervecs)[1] = (_center+osg::Vec3(-_width/2-_spacing,_length/2+_spacing,0));
				(*_bordervecs)[2] = (_center+osg::Vec3(_width/2+_spacing,_length/2+_spacing,0));
				(*_bordervecs)[3] = (_center+osg::Vec3(_width/2+_spacing,-_length/2-_spacing,0));
			}
			if (_drawbar) {
				(*_barvecs)[0] = (_center+osg::Vec3(-_width/2,-_length/2+zero*_length,0));
				(*_barvecs)[1] = (_center+osg::Vec3(-_width/2,-_length/2+_value*_length,0));
				(*_barvecs)[2] = (_center+osg::Vec3(_width/2,-_length/2+_value*_length,0));
				(*_barvecs)[3] = (_center+osg::Vec3(_width/2,-_length/2+zero*_length,0));
			}
			if (_drawmark) {
				(*_markvecs)[0] = (_center+osg::Vec3(-_markwidth/2,-_length/2+_mark*_length-_markthickness/2,0));
				(*_markvecs)[1] = (_center+osg::Vec3(-_markwidth/2,-_length/2+_mark*_length+_markthickness/2,0));
				(*_markvecs)[2] = (_center+osg::Vec3(_markwidth/2,-_length/2+_mark*_length+_markthickness/2,0));
				(*_markvecs)[3] = (_center+osg::Vec3(_markwidth/2,-_length/2+_mark*_length-_markthickness/2,0));
			}
		}
		if (_drawborder)
			_bordergeometry->dirtyDisplayList();
		if (_drawbar)
			_bargeometry->dirtyDisplayList();
		if (_drawmark)
			_markgeometry->dirtyDisplayList();
	}
	
	void Bar::createGeometry()
	{
		removeDrawables(0, getNumDrawables());
		
		// Create border
		_bordergeometry = new osg::Geometry;
		_bordergeometry->setName("border");
		_bordervecs = new osg::Vec3Array;
		_bordervecs->resize(4);
		_bordergeometry->setVertexArray(_bordervecs);
		_bordergeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,4));
		_bordercolors = new osg::Vec4Array;
		_bordercolors->push_back(_bordercolor);
		_bordergeometry->setColorArray(_bordercolors);
		_bordergeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		addDrawable(_bordergeometry);
		
		// Create bar
		_bargeometry = new osg::Geometry;
		_bargeometry->setName("bar");
		_barvecs = new osg::Vec3Array;
		_barvecs->resize(4);
		_bargeometry->setVertexArray(_barvecs);
		_bargeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
		_barcolors = new osg::Vec4Array;
		_barcolors->push_back(_barcolor);
		_bargeometry->setColorArray(_barcolors);
		_bargeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		addDrawable(_bargeometry);
		
		// Create mark
		_markgeometry = new osg::Geometry;
		_markgeometry->setName("mark");
		_markvecs = new osg::Vec3Array;
		_markvecs->resize(4);
		_markgeometry->setVertexArray(_markvecs);
		_markgeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
		_markcolors = new osg::Vec4Array;
		_markcolors->push_back(_markcolor);
		_markgeometry->setColorArray(_markcolors);
		_markgeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		addDrawable(_markgeometry);
		
		setSize(_length,_width);
	}
	
}
