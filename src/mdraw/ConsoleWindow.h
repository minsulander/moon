#ifndef MDRAW_CONSOLEWINDOW_H
#define MDRAW_CONSOLEWINDOW_H

#include "Export.h"
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geode>
#include <osg/State>
#include <osg/CopyOp>
#include <osgText/Text>
#include <sstream>
#include <deque>
#include <iostream>

namespace mdraw {
	
	class ConsoleWindow;
	
	class MDRAW_EXPORT ConsoleCallback : public osg::Referenced {
	public:
		virtual void input(ConsoleWindow* window, const std::string& line) = 0;
	};
	
	/// \brief Console window for user interaction
	/// \ingroup draw
    class MDRAW_EXPORT ConsoleWindow : public osg::Geode, public std::stringstream {
	public:
		
		// Constructors
		ConsoleWindow(const unsigned int lines = 42,
					  const float x = -1,
					  const float y = 1,
					  const float width = 2,
					  const osg::Vec4 &bgcolor = osg::Vec4(0,0,0,0.5),
					  const osg::Vec4 &textcolor = osg::Vec4(1,1,1,1),
					  const osg::Vec4 &cursorcolor = osg::Vec4(1,0.3,0.3,0.5));
		
		ConsoleWindow(const ConsoleWindow &copy, 
					  const osg::CopyOp &copyop);
		META_Object(ogeDraw, ConsoleWindow);
		
		// Public methods
		bool setFont(const std::string& file, double aspect, double widthmult);
		float charHeight();
		float charWidth();
		void setBackgroundColor(const osg::Vec4& color);
		const osg::Vec4& getBackgroundColor() const { return _bgcolor; }
		void adjustBackgroundBrightness(const float delta);
		void scrollUp(unsigned int lines);
		void scrollDown(unsigned int lines);
		void pageUp() { scrollUp(_lines); }
		void pageDown() { scrollDown(_lines); }
		void scrollRight(unsigned int cols);
		void scrollLeft(unsigned int cols);
		void scrollHome() { _scrollback = _linebuf.size()-_lines; update(true); }
		void scrollEnd() { _scrollback = 0; update(true); }
		void del();
		void backSpace();
		void clearLine();
		void cutLine();
		void upHistory();
		void downHistory();
		void leftCursor();
		void rightCursor();
		ConsoleWindow& operator<<(const char& ch);
		//ConsoleWindow& operator<<(char& ch) { return *this << (const char) ch; }
		void putch(const char ch) { *this << ch; }
		void print(const std::string& s);
		void resize(const int lines);
		void sizeUp(const int lines);
		void sizeDown(const int lines);
		
		// Access methods
		void setPrompt(const std::string& prompt);
		void setCursor(const char cursor) { _cursor = cursor; }
		void setCursorPosition(const int cpos);
		unsigned int getNumLines() { return _lines; }
		void setTop(const bool top) { _top = top; resize(getNumLines()); }
		bool getTop() { return _top; }
		float getHeight() { return _height; }
		std::string getLastLine() { return _linebuf.back(); }
		
		void setCallback(ConsoleCallback* callback) { _callback = callback; }
		bool loadHistory(const std::string& filename);
		bool saveHistory(const std::string& filename);
		
		void accept(osg::NodeVisitor& nv);
		
	protected:
		
		void update(bool force = false);
		
		// Protected data members
		osgText::Text *_text;
		osg::Vec3Array *_boxvecs, *_cursorvecs;
		osg::Geometry *_boxgeometry, *_cursorgeometry;
		mutable std::deque<std::string> _linebuf;
		std::vector<std::string> _history;
		std::string _savebuf, _prompt;
		osg::ref_ptr<ConsoleCallback> _callback;
		
		osg::Vec4 _bgcolor, _textcolor, _cursorcolor;
		
		float _x,_y,_width, _height;
		unsigned int _lines, _cols;
		unsigned int _buflines, _scrollback, _scrollright;
		unsigned int _histsize;
		int _curline, _cursorpos;
		char _cursor;
		bool _top;
		
		float _widthmultiplier;
		
		static const unsigned int MAX_HEIGHT = 2;
		static const unsigned int MAX_LINES = 42;
    };
	
}

#endif
