#ifndef MOON_CONTROL_H
#define MOON_CONTROL_H

#include "Export.h"
#include <osg/Object>
#include <vector>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// A control for something that the user/player can interact with
	class MOON_EXPORT Control : public osg::Referenced {
	public:
		enum ControlType {
			MOMENTARY,
			TOGGLE,
			AXIS
		};
		
		Control(const std::string& newname, const ControlType& newtype) : name(newname), type(newtype), value(0), bound(false) {}
		virtual void setValue(const float newvalue) { value = newvalue; }
		float getValue() const { return value; }
		void setType(const ControlType& newtype) { type = newtype; }
		const ControlType& getType() const { return type; }
		void setName(const std::string& newname) { name = newname; }
		const std::string& getName() const { return name; }
		bool isBound() const { return bound; }
		void setBound(const bool value) { bound = value; }
		
	protected:
		std::string name;
		ControlType type;
		float value;
		bool bound;
	};
	
	class MOON_EXPORT ControlCallback : public osg::Referenced {
	public:
		virtual void operator()(Control* control)=0;
	};
	
	/// A control which, upon user interaction, calls its associated callback
	class MOON_EXPORT CallbackControl : public Control {
	public:
		CallbackControl(const std::string& newname, const ControlType& newtype, ControlCallback* newcallback) 
		: Control(newname,newtype), callback(newcallback) {}
		virtual void setValue(const float newvalue);
	protected:
		osg::ref_ptr<ControlCallback> callback;
	};
	
	class ListenerControl;
	typedef std::vector< osg::ref_ptr<ListenerControl> > ListenerControlList;
	
	class MOON_EXPORT ControlListener {
	public:
		virtual void controlUpdate(Control* control)=0;
		virtual void bindControls();
		virtual void unbindControls();
		ListenerControl* getControl(const std::string& name);
		virtual ~ControlListener() {}
	protected:
		ListenerControlList controls;
		friend class ListenerControl;
	};
	
	/// A control which, upon user interaction, calls the controlUpdate() function in a listener class
	class MOON_EXPORT ListenerControl : public Control {
	public:
		ListenerControl(const std::string& newname, const ControlType& newtype, ControlListener* newlistener = NULL);
		virtual void setValue(const float newvalue);
		void setListener(ControlListener* newlistener);
	protected:
		ControlListener* listener;
	};
	
	/// @}
}

#endif

