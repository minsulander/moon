#include "Control.h"
#include "ControlHandler.h"

namespace moon {
	
	void CallbackControl::setValue(const float newvalue)
	{
		Control::setValue(newvalue);
		if (callback.valid())
			(*callback)(this);
	}
	
	void ControlListener::bindControls()
	{
		for (ListenerControlList::iterator i = controls.begin(); i != controls.end(); i++)
			if (i->valid()) ControlHandler::instance().bind(i->get());
	}
	
	void ControlListener::unbindControls()
	{
		for (ListenerControlList::iterator i = controls.begin(); i != controls.end(); i++)
			if (i->valid()) ControlHandler::instance().unbind(i->get());
	}
	
	ListenerControl* ControlListener::getControl(const std::string& name)
	{
		for (ListenerControlList::iterator i = controls.begin(); i != controls.end(); i++)
			if ((*i)->getName() == name)
				return i->get();
		return NULL;
	}
	
	ListenerControl::ListenerControl(const std::string& newname, const ControlType& newtype, ControlListener* newlistener)
	: Control(newname,newtype)
	{ 
		listener = NULL;
		setListener(newlistener);
	}
	
	void ListenerControl::setValue(const float newvalue)
	{
		Control::setValue(newvalue);
		if (listener)
			listener->controlUpdate(this);
	}
	
	void ListenerControl::setListener(ControlListener* newlistener) {
		if (listener) {
			for (ListenerControlList::iterator i = listener->controls.begin(); i != listener->controls.end(); i++)
				if (i->get() == this)
					listener->controls.erase(i);
		}
		listener = newlistener;
		if (newlistener)
			newlistener->controls.push_back(this);
	}
		
}

