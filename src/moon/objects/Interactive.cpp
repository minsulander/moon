#include "Interactive.h"
#include "moon/ControlHandler.h"
#include "moon/NodeMask.h"
#include "mlog/Log.h"

using namespace mlog;

namespace moon {
	
	/// Override this function to define object-specific response to user/player interaction
	void Interactive::interaction(const InteractionType type)
	{
		for (InteractionCallbackList::iterator it = callbacks.begin(); it != callbacks.end(); it++)
			(*it)->interaction(type);
	}
	
	void Interactive::addInteractionCallback(InteractionCallback *callback)
	{
		callbacks.push_back(callback);
	}
	
	void Interactive::removeInteractionCallback(InteractionCallback *callback)
	{
		for (InteractionCallbackList::iterator it = callbacks.begin(); it != callbacks.end(); it++) {
			if (it->get() == callback) {
				callbacks.erase(it);
				break;
			}
		}
	}
	
	
	InteractionHandler::InteractionHandler()
	:	osgGA::GUIEventHandler()
	{
		actionControl = new ListenerControl("Action", Control::MOMENTARY, this);
	}
	
	InteractionHandler::~InteractionHandler()
	{
	}
	
	bool InteractionHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
	{
		if (!actionControl->isBound()) {
			ControlHandler::instance().bind(actionControl.get());
		}
		return false;
	}
	
	void InteractionHandler::controlUpdate(Control *control)
	{
		if (control == actionControl.get() && control->getValue() >= 0.5) {
			BaseObject *object = ControlHandler::instance().pick(moon::NodeMask::INTERACTIVE);
			if (object) {
				Interactive *interactive = dynamic_cast<Interactive*> (object);
				if (interactive) {
					dout(3) << "Action: " << object->getName() << "\n";
					interactive->interaction(ACTION);
				} else
					dout(3) << "Action: " << object->getName() << " (not interactive)\n";
			} else
				dout(3) << "Action: (no object)\n";
		}
	}

} // namespace
