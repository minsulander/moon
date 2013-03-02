#ifndef MOON_CONSOLEHANDLER_H
#define MOON_CONSOLEHANDLER_H

#include "Export.h"
#include "mdraw/ConsoleWindow.h"
#include <osgGA/GUIEventHandler>

namespace moon
{
	
	/// \brief Event handler for the console
	/// \ingroup core
	class MOON_EXPORT ConsoleHandler : public osgGA::GUIEventHandler {
	public:
		ConsoleHandler(mdraw::ConsoleWindow* console);
		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
		void setKeyEventToggleConsole(int key) { togglekey = key; }
	protected:
		mdraw::ConsoleWindow* console;
		int togglekey;
	};
	
}

#endif

