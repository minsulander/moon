#include "ConsoleHandler.h"
#include "mlog/Log.h"

#include <osg/Switch>
#include <iostream>

using namespace std;
using namespace mlog;

namespace moon
{
	
ConsoleHandler::ConsoleHandler(mdraw::ConsoleWindow* console)
	: togglekey(0)
{
	this->console = console;
}

bool ConsoleHandler::handle (const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
{
	if (ea.getHandled())
		return false;
	if (console->getNumParents() == 0)
		return false;
	osg::Switch* sw = dynamic_cast<osg::Switch*>(console->getParent(0));
	if (!sw)
		return false;
	if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN || ea.getEventType() == osgGA::GUIEventAdapter::KEYUP) {
		// Toggle the console
		if (togglekey && ea.getKey() == togglekey) {
			if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
				if (sw)
					sw->setChildValue(console,!sw->getChildValue(console));
				else
					dout(WARN) << "No console window" << endl;
			}
			return true;
		}
		// Don't handle any more events if the console is disabled
		if (!sw || !sw->getChildValue(console))
			return false;
		// Steal all key-up events when console is enabled
		if (ea.getEventType() == osgGA::GUIEventAdapter::KEYUP)
			return true;
		// Send ASCII characters to console
		if (ea.getKey() > 25 && ea.getKey() < 255) {
			*console << (char)ea.getKey();
			console->scrollEnd();
			return true;
		}
		// Handle specific key presses
		switch (ea.getKey()) {
			case 10:
			case 13:
			case osgGA::GUIEventAdapter::KEY_Return:
			case osgGA::GUIEventAdapter::KEY_KP_Enter:
				*console << '\n';
				console->scrollEnd();
				// TODO send to listener
				break;
			case osgGA::GUIEventAdapter::KEY_BackSpace:
			case osgGA::GUIEventAdapter::KEY_KP_Delete:
				console->backSpace();
				break;
			case osgGA::GUIEventAdapter::KEY_Delete:
			case 4: // ctrl-d
				console->del();
				break;
			case 11: // ctrl-k
				console->cutLine();
				break;
			case osgGA::GUIEventAdapter::KEY_Left:
			case osgGA::GUIEventAdapter::KEY_KP_Left:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollLeft(1);
				else
					console->leftCursor();
				break;
			case osgGA::GUIEventAdapter::KEY_Right:
			case osgGA::GUIEventAdapter::KEY_KP_Right:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollRight(1);
				else
					console->rightCursor();
				break;
			case osgGA::GUIEventAdapter::KEY_Home:
			case 1: // ctrl-a
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollHome();
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->setTop(true);
				else
					console->setCursorPosition(0);
				break;
			case osgGA::GUIEventAdapter::KEY_End:
			case 5: // ctrl-e
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollEnd();
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->setTop(false);
				else
					console->setCursorPosition(-1);
				break;
			case osgGA::GUIEventAdapter::KEY_Up:
			case osgGA::GUIEventAdapter::KEY_KP_Up:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT &&
					ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->adjustBackgroundBrightness(0.05);
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollUp(1);
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->sizeUp(1);
				else
					console->upHistory();
				break;
			case osgGA::GUIEventAdapter::KEY_Down:
			case osgGA::GUIEventAdapter::KEY_KP_Down:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT &&
					ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->adjustBackgroundBrightness(-0.05);
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)
					console->scrollDown(1);
				else if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->sizeDown(1);
				else
					console->downHistory();
				break;
			case osgGA::GUIEventAdapter::KEY_Page_Up:
			case osgGA::GUIEventAdapter::KEY_KP_Page_Up:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->sizeUp(10);
				else
					console->pageUp();
				break;
			case osgGA::GUIEventAdapter::KEY_Page_Down:
			case osgGA::GUIEventAdapter::KEY_KP_Page_Down:
				if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
					console->sizeDown(10);
				else
					console->pageDown();
				break;
			default:
				return false;
		}
		return true;
	}
	// Steal all key up events when console is active
	//if (sw && sw->getChildValue(console) && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP)
	//	return true;
	return false;
}
	
} // namespace oge

