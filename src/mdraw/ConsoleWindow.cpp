// -*-c++-*- $OGE: ConsoleWindow.cpp,v 1.9 2005/06/11 16:44:49 main Exp $

#include "ConsoleWindow.h"
//#include "mlog/Log.h"
#include <iterator>
#include <fstream>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geometry>

//using namespace moon;
using namespace mdraw;
using namespace std;

// Default constructor
ConsoleWindow::ConsoleWindow(const unsigned int lines, const float x, const float y, const float width,
							 const osg::Vec4 &bgcolor, const osg::Vec4 &textcolor, const osg::Vec4 &cursorcolor)

: basic_ios<char, char_traits<char> >(),
osg::Geode(),
stringstream()

{
    _scrollback = 0;
	_scrollright = 0;
	
    // position, width and height all need to be tweaked so it fits with font size
    _x = x;
    _y = y;
    _lines = lines;
    _cols = 102;
	
    _bgcolor = bgcolor;
    _textcolor = textcolor;
    _cursorcolor = cursorcolor;
	_callback = NULL;
	
    _cursor = '\0';
	
    _text = new osgText::Text;
    _text->setColor(_textcolor);
    _text->setCharacterSizeMode(osgText::Text::OBJECT_COORDS);
    // Try FreeMonoBold and Courier Bold
    if (!setFont("fonts/VeraMono.ttf",1.42,0.595) &&
		!setFont("fonts/FreeMonoBold.ttf",1.42,0.595) &&
		!setFont("fonts/courbd.ttf",1.42,0.594) &&
		!setFont("courbd.ttf",1.42,0.594)) {
		//dout(WARN) << "ConsoleWindow: no good looking font found";
    }
    
    // Set text position
    _height = _text->getCharacterHeight()*(_lines+0.5);
    //dout(5) << "height " << _height << " " << _text->getCharacterHeight() << std::endl;
    if (_height > MAX_HEIGHT-_text->getCharacterHeight())
		_height = MAX_HEIGHT; // no little strip at bottom when console is fullscreen
    _width = width;
	
    //_text->setPosition(osg::Vec3(_x+6,_y-_text->getCharacterHeight(),0));
    _text->setPosition(osg::Vec3(_x+_width/200,_y-_text->getCharacterHeight(),0));
	
    // Create the background box
    _boxvecs = new osg::Vec3Array(4);
    (*_boxvecs)[0] = osg::Vec3(_x,_y,0);
    (*_boxvecs)[1] = osg::Vec3(_x+_width,_y,0);
    (*_boxvecs)[2] = osg::Vec3(_x+_width,_y-_height,0);
    (*_boxvecs)[3] = osg::Vec3(_x,_y-_height,0);
    _boxgeometry = new osg::Geometry;
    _boxgeometry->setVertexArray(_boxvecs);
	setBackgroundColor(_bgcolor);
    _boxgeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
    addDrawable(_boxgeometry);
	
    // Create cursor box
    _cursorvecs = new osg::Vec3Array(4);
    (*_cursorvecs)[0] = osg::Vec3(_x,_y,0);
    (*_cursorvecs)[1] = osg::Vec3(_x+charWidth(),_y,0);
    (*_cursorvecs)[2] = osg::Vec3(_x+charWidth(),_y-charHeight()*1.25,0);
    (*_cursorvecs)[3] = osg::Vec3(_x,_y-charHeight()*1.25,0);
    _cursorgeometry = new osg::Geometry;
    _cursorgeometry->setVertexArray(_cursorvecs);
    osg::Vec4Array *colors = new osg::Vec4Array;
    colors->push_back(_cursorcolor);
    _cursorgeometry->setColorArray(colors);
    _cursorgeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    _cursorgeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
    addDrawable(_cursorgeometry);
	
    addDrawable(_text);
	
    // Turn off depth test and lighting, turn on transparency
    osg::StateSet *stateset = getOrCreateStateSet();
    stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //stateset->setAttribute(new osg::PolygonOffset(1.0f,1.0f),osg::StateAttribute::ON);
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	stateset->setRenderBinDetails(11,"RenderBin");
	
    // Output some debug info
    //dout(5) << "  ConsoleWindow:" << _text->getFontWidth() << "x"
	//    << _text->getFontHeight() << " font, " << _width << "x"
	//    << _height << ", L" << _lines << " C" << _cols << endl;
	
    // Put an empty string on the line buffer, so we have something
    // to work with
    _linebuf.push_back(string(""));
    
    _curline = -1;
    _histsize = 1000;
    _cursorpos = -1;
    _prompt = "";
    _top = true;
}

ConsoleWindow::ConsoleWindow(const ConsoleWindow &copy, 
							 const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY) 
: basic_ios<char, char_traits<char> >(),
osg::Geode(copy, copyop),
stringstream(),
_text(copy._text),
_linebuf(copy._linebuf),
_history(copy._history),
_prompt(copy._prompt),
_x(copy._x),
_y(copy._y),
_width(copy._width),
_height(copy._height),
_lines(copy._lines),
_cols(copy._cols),
_buflines(copy._buflines),
_histsize(copy._histsize),
_curline(copy._curline),
_cursorpos(-1),
_cursor(copy._cursor),
_top(copy._top)
{}

bool ConsoleWindow::setFont(const string& file, double aspect, double widthmult) {
    // The aspect ratio needs to be set because osg doesn't seem to be able
    // to find the characterwidth right
	
    // Load the font
    _text->setFont(file);
    if (_text->getFont() != NULL) {
		_text->setFontResolution(32,32);
		_text->setCharacterSize(.0466,aspect); // (24,0.96)
		//dout(5) << "ConsoleWindow::setFont aspect according to osg is "
		//	<< _text->getCharacterAspectRatio() << endl;
		//dout(5) << "  fontwidth " << _text->getFontWidth() << endl;
		_widthmultiplier = widthmult;
		osgText::String text = _text->getText();
		_text->setText("A");
		osg::BoundingBox b = _text->getBound();
		//dout(5) << "boundingbox x " << b.xMax() << "," << b.xMin() << " y " << b.yMax()-b.yMin() << " radius " << b.radius() << endl;
		_text->setText(text);
    } else {
		// If loading the font fails, use the internal font
		_text->setCharacterSize(.1,1); // (24,121)
		_widthmultiplier = 0.25;
		osgText::String text = _text->getText();
		_text->setText("A");
		osg::BoundingBox b = _text->getBound();
		//dout(5) << "boundingbox x " << b.xMax() << "," << b.xMin() << " y " << b.yMax()-b.yMin() << " radius " << b.radius() << endl;
		//dout(5) << "width " << charWidth() << " height " << charHeight() << "\n";
		return false;
    }
    return true;
}

float ConsoleWindow::charHeight() {
    return _text->getCharacterHeight();
}

float ConsoleWindow::charWidth() {
    return _text->getCharacterHeight()
	/ _text->getCharacterAspectRatio()
	* _widthmultiplier; //FIXME
}

void ConsoleWindow::setBackgroundColor(const osg::Vec4& bgcolor)
{
	_bgcolor = bgcolor;
    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(bgcolor);
    _boxgeometry->setColorArray(colors);
    _boxgeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	_boxgeometry->dirtyDisplayList();
}

void ConsoleWindow::adjustBackgroundBrightness(const float delta)
{
	setBackgroundColor(_bgcolor - osg::Vec4(0,0,0,delta));
}

void ConsoleWindow::scrollUp(unsigned int lines) {
	if (_linebuf.size() < _lines)
		return;
    _scrollback += lines;
    if (_scrollback > _linebuf.size()-_lines)
		_scrollback = _linebuf.size()-_lines;
    update(true); // force update
}

void ConsoleWindow::scrollDown(unsigned int lines) {
    if (lines > _scrollback)
		_scrollback = 0;
    else
		_scrollback -= lines;
    update(true); // force update
}

void ConsoleWindow::scrollRight(unsigned int cols) {
	_scrollright += cols;
	update(true);
}

void ConsoleWindow::scrollLeft(unsigned int cols) {
	if (_scrollright > 0)
		_scrollright -= cols;
	update(true);
}

void ConsoleWindow::del() {
    _scrollback = 0;
    if (_cursorpos >= 0) {
		_linebuf.back().erase(_cursorpos,1);
		update(true);
    }
}

void ConsoleWindow::backSpace() {
    _scrollback = 0;
    if (_cursorpos < 0 && _linebuf.back().size() > _prompt.length()) {
		_linebuf.back().erase(_linebuf.back().size()-1,1);
		update(true);
    } else if (_cursorpos > 0 && _cursorpos > (int)_prompt.length()) {
		_linebuf.back().erase(--_cursorpos,1);
		update(true);
    }
}

void ConsoleWindow::clearLine() {
    _linebuf.back().erase(_prompt.length(),_linebuf.back().length()-1);
    setCursorPosition(-1);
}

void ConsoleWindow::cutLine() {
    if (_cursorpos < 0)
		return;
    _linebuf.back().erase(_cursorpos,_linebuf.back().length()-1);
    update(true);
}

void ConsoleWindow::upHistory() {
    _scrollback = 0;
    if (_curline > 0)
		_curline--;
    else if (_curline == -1) { // -1 means current work buffer
		_savebuf = _linebuf.back();
		_curline = _history.size()-1;
    }
    if (_curline >= 0) {
		_linebuf.back() = _prompt + _history[_curline];
		_cursorpos = -1;
		update(true);
    }
}

void ConsoleWindow::downHistory() {
    _scrollback = 0;
    if (_curline < (int)_history.size()-1) {
		_curline++;
		_linebuf.back() = _prompt+_history[_curline];
    } else {
		_linebuf.back() = _savebuf;
		_curline = -1; // -1 means current work buffer
		_cursorpos = -1;
    }
    update(true);
}

void ConsoleWindow::leftCursor() {
    if (_cursorpos < 0 && _linebuf.back().length() > _prompt.length())
		_cursorpos = _linebuf.back().length()-1;
    else if (_cursorpos > (int)_prompt.length())
		_cursorpos--;
    _scrollback = 0;
    update(true);
}

void ConsoleWindow::rightCursor() {
    if (_cursorpos < 0)
		return;
    if (++_cursorpos >= (int)_linebuf.back().length())
		_cursorpos = -1; // -1 means end of line
    _scrollback = 0;
    update(true);
}

ConsoleWindow& ConsoleWindow::operator<<(const char& ch) {
    string s;
    switch (ch) {
		case 128: // delete
			del();
			break;
		case 8: // backspace
			backSpace();
			break;
		case 10: // newline
		case 13: // carriage return
				 // save current line to history
			put('\n');
			if (_linebuf.back().length() > _prompt.length()) {
				s = _linebuf.back().substr(_prompt.length());
				if (_history.size() == 0 || s != _history[_history.size()-1]) {
					_history.push_back(_linebuf.back().substr(_prompt.length()));
					if (_history.size() > _histsize)
						_history.erase(_history.begin(),_history.begin()+1);
				}
			} else
				_linebuf.back() = _prompt;
			_curline = -1;
			_cursorpos = -1;
			update(true);
			if (_callback.valid())
				_callback->input(this,s);
			break;
		default:
			if (_cursorpos < 0)
				put(ch);
			else {
				s = "";
				s += ch;
				_linebuf.back().insert(_cursorpos,s);
				_cursorpos++;
				update(true);
			}
				_scrollback = 0;
    }
    return *this;
}

// print a line and show a new prompt
void ConsoleWindow::print(const string& s) {
	string str = s;
	while(str.find('\n',0) != string::npos) {
		_linebuf.insert(_linebuf.end()-1,str.substr(0,str.find('\n',0)));
		str = str.substr(str.find('\n',0)+1);
	}
   	_linebuf.insert(_linebuf.end()-1,str);
    _scrollback = 0;
    update(true);
}

void ConsoleWindow::resize(const int lines) {
    if (lines <= 0)
		return;
    _lines = lines;
	if (_lines > MAX_LINES)
		_lines = MAX_LINES;
	
    if (!_text || !_boxvecs)
		return;
    
    // Set text size/position
    _height = _text->getCharacterHeight()*(float)(_lines+0.5);
    if (_height > MAX_HEIGHT-_text->getCharacterHeight())
		_height = MAX_HEIGHT; // no little strip at bottom when console is fullscreen
	
    float y;
    if (_top)
		y = _y;
    else
		y = -1+_height;
	
	
    _text->setPosition(osg::Vec3(_x+_width/200,y-_text->getCharacterHeight(),0));
    //    _text->dirtyDisplayList();
    // Set box size/position
    (*_boxvecs)[0] = osg::Vec3(_x,y,0);
    (*_boxvecs)[1] = osg::Vec3(_x+_width,y,0);
    (*_boxvecs)[2] = osg::Vec3(_x+_width,y-_height,0);
    (*_boxvecs)[3] = osg::Vec3(_x,y-_height,0);
    update(true);
}

void ConsoleWindow::sizeUp(const int lines) {
    if (_top)
		resize(_lines-lines);
    else
		resize(_lines+lines);
}

void ConsoleWindow::sizeDown(const int lines) {
    if (_top)
		resize(_lines+lines);
    else
		resize(_lines-lines);
}

void ConsoleWindow::setPrompt(const std::string& prompt) {
	if (_prompt.length() == 0)
		_linebuf.back() = prompt + _linebuf.back();
	else if (_linebuf.back() == _prompt)
		_linebuf.back() = prompt;
	else if (_linebuf.back().substr(0,_prompt.length()) == _prompt)
		_linebuf.back() = prompt + _linebuf.back().substr(_prompt.length()+1);
	_prompt = prompt;
	update(true);
}

void ConsoleWindow::setCursorPosition(const int cpos) {
    if (cpos < 0 || cpos > (int)_linebuf.back().length()-1)
		_cursorpos = -1;
    else if (cpos < (int)_prompt.length())
		_cursorpos = _prompt.length();
    else
		_cursorpos = cpos;
    update(true);
}

// update() - runs every frame by the update callback
void ConsoleWindow::update(bool force) {
    char ch;
	
    // First thing: Do nothing if there's no change
    if (peek() == EOF && !force) {
		clear();
		return;
    }
    if (_cursor && _linebuf.back().length() > 0)
    	_linebuf.back().erase(_linebuf.back().length()-1,1);
    // Take characters from stringbuffer into linebuffer
    while (peek() != EOF) {
		ch = get();
		if (ch == '\n')
			_linebuf.push_back(string(""));
		else 
			_linebuf.back() += ch;
    }
    if (_cursor)
    	_linebuf.back() += _cursor;
    clear();
	
	// Add prompt if last line is blank
	if (_linebuf.back().length() == 0)
		_linebuf.back() = _prompt;
	// Check horizontal scrolling related to cursor position
	if (_scrollback == 0) {
		if (_cursorpos < 0) {
			if (_linebuf.back().length() < _cols)
				_scrollright = 0;
			else if (_linebuf.back().length() < _scrollright)
				_scrollright = _linebuf.back().length();
			else if (_linebuf.back().length() > _cols-1)
				_scrollright = _linebuf.back().length()-_cols+1;
		} else {
			if (_cursorpos <= (int)_prompt.length())
				_scrollright = 0;
			else if (_cursorpos < (int)_scrollright)
				_scrollright = _cursorpos;
			else if (_cursorpos-_scrollright > _cols-1)
				_scrollright = _cursorpos-_cols+1;
		}
	}
    // Copy the lines to display into a string and set the text
    stringstream stemp;
    if (_linebuf.size() <= _lines) {
		for (unsigned int i = 0; i < _linebuf.size(); i++) {
			if (_linebuf.at(i).length() == 0)
				stemp << " \n";
			else if (_linebuf.at(i).length() <= _scrollright)
				stemp << "<\n";
			else if (_linebuf.at(i).substr(_scrollright).length() > _cols)
				stemp << _linebuf.at(i).substr(_scrollright,_cols-1) << ">" << "\n";
			else
				stemp << _linebuf.at(i).substr(_scrollright) << "\n";
		}
    } else {
		for (unsigned int i = _linebuf.size()-_lines-_scrollback; i < _linebuf.size()-_scrollback; i++) {
			if (_linebuf.at(i).length() == 0)
				stemp << " \n";
			else if (_linebuf.at(i).length() <= _scrollright)
				stemp << "<\n";
			else if (_linebuf.at(i).substr(_scrollright).length() > _cols)
				stemp << _linebuf.at(i).substr(_scrollright,_cols-1) << ">" << "\n";
			else
				stemp << _linebuf.at(i).substr(_scrollright) << "\n";
				
		}
    }
    _text->setText(stemp.str());
    // Reposition cursor
    if (_scrollback == 0) {
		int realcursorpos;
		if (_cursorpos < 0) { // -1 means end of line
			realcursorpos = _linebuf.back().length()-_scrollright;
		} else {
			realcursorpos = _cursorpos-_scrollright;
		}
		float x = _x+realcursorpos*charWidth() + charWidth()/2;
		float y;
		if (_top) {
			if (_linebuf.size() < _lines)
				y = _y-(_linebuf.size()-1)*charHeight() - charHeight()/4;
			else
				y = _y-(_lines-1)*charHeight() - charHeight()/4;
		} else {
			if (_linebuf.size() < _lines)
				y = -1+_height-(_linebuf.size()-1)*charHeight() - charHeight()/4;
			else
				y = -1+_height-(_lines-1)*charHeight() - charHeight()/4;
		}
		(*_cursorvecs)[0] = osg::Vec3(x,y,0);
		(*_cursorvecs)[1] = osg::Vec3(x+charWidth(),y,0);
		(*_cursorvecs)[2] = osg::Vec3(x+charWidth(),y-charHeight(),0);
		(*_cursorvecs)[3] = osg::Vec3(x,y-charHeight(),0);
    } else {
		// No cursor if we're scrolled back
		osg::Vec3 zvec(0,0,0);
		(*_cursorvecs)[0] = zvec;
		(*_cursorvecs)[1] = zvec;
		(*_cursorvecs)[2] = zvec;
		(*_cursorvecs)[3] = zvec;
    }
    _cursorgeometry->dirtyDisplayList();
    // Make sure we redraw
    _text->dirtyDisplayList();
    if (force)
		_boxgeometry->dirtyDisplayList();
}

bool ConsoleWindow::loadHistory(const std::string& filename) {
	//dout(4) << "Loading console history to " << filename << "\n";
	std::ifstream in(filename.c_str());
	char line[100];
	if (!in.good())
		return false;
	while (in.getline(line,100)) {
		_history.push_back(std::string(line));
	}
	//dout(5) << _history.size() << " lines loaded\n";
	return true;
}

bool ConsoleWindow::saveHistory(const std::string& filename) {
	//dout(4) << "Saving console history to " << filename << "\n";
	std::ofstream out(filename.c_str());
	if (!out.good())
		return false;
	for (unsigned int i = 0; i < _history.size(); i++) {
		out << _history[i] << "\n";
	}
	//dout(5) << _history.size() << " lines saved\n";
	return true;
}

void ConsoleWindow::accept(osg::NodeVisitor& nv) {
    update();
    nv.apply(*this);
}

