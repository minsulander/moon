#ifndef CONTROLHANDLER_H_
#define CONTROLHANDLER_H_

#include "Export.h"
#include "Control.h"
#include "objects/BaseObject.h"
#include "SimulationManager.h"
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <string>
#include <stack>

class TiXmlElement;

namespace moon
{
	
	/// \addtogroup core
	/// @{
	
	/// A user interaction event
	struct MOON_EXPORT Event {
		
		enum EventType {
			NONE=0,
			KEY,
			MOUSE_BUTTON,
			MOUSE_MOVE,
			MOUSE_SCROLL,
			
			JOY_AXIS,
			JOY_BUTTON,
			JOY_HAT,
			
			MIDI_DATA
		};
		
		Event() : type(NONE), device(0), id(0), value(0), x(0), y(0) {}
		Event(EventType ntype, unsigned int ndevice, unsigned int nid) : type(ntype), device(ndevice), id(nid), value(0), x(0), y(0) {} 
		
		static const std::string typeStr(const EventType type);
		
		EventType type;
		unsigned int device;
		unsigned int id;
		float value;
		float x, y;
	};
	
	/// Binding used by the ControlHandler to update a Control when an Event occurs
	struct MOON_EXPORT ControlBinding {
		
		ControlBinding(const Event& bindevent = Event(), const std::string& name = "", const float ngain = 1.0) 
		: event(bindevent), 
		direction(1), 
		incrate(0), 
		decrate(0), 
		threshold(0.5), 
		nullzone(0),
		gain(ngain), 
		grab(false), 
		resetonrelease(false),
		nameref(name)
		{}
		
		Event event;
		float direction;
		float incrate, decrate, threshold, nullzone, gain;
		bool grab, resetonrelease;
		std::string nameref;
		osg::ref_ptr<Control> control;
		std::stack< osg::ref_ptr<Control> > controlstack;
	};
	
	/// A set of control bindings
	class MOON_EXPORT ControlBindingSet : public FactoryProduct {
	public:
		ControlBindingSet();
		ControlBindingSet(const ControlBindingSet& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, ControlBindingSet);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		unsigned int getNumBindings() const { return bindings.size(); }
		ControlBinding& getBinding(const unsigned int index) { return bindings[index]; }
		const ControlBinding& getBinding(const unsigned int index) const { return bindings[index]; }
	private:
		static unsigned int getKey(const std::string& name);
		typedef std::vector<ControlBinding> BindingList;
		BindingList bindings;
	};
	
	/// The control handler updates controls when OSG/joystick/other event occur
	class MOON_EXPORT ControlHandler : public osgGA::GUIEventHandler
	{
	public:
		ControlHandler();
		virtual ~ControlHandler();
		void load(const std::string& filename);
		void parseBindings(TiXmlElement* element);
		bool initJoysticks();
		const int getJoystickIndex(const std::string& name);
		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
		bool pollEvents();
		virtual void update(const double dt);
		
		void bind(const ControlBinding& binding);
		void bind(const ControlBindingSet* set);
		void bind(const Event& event, const std::string& name, const float gain = 1.0);
		void bind(const Event& event, const Event& complement, const std::string& name, const float gain = 1.0);
		void bind(const int key, const std::string& name, const float gain = 1.0);
		void bind(const int key, const int complement_key, const std::string& name, const float gain = 1.0);
		bool bind(Control* control);
		void unbind(Control* control);
		
                moon::BaseObject* pick(const float x,const float y, const osg::Node::NodeMask mask = 0xFFFFFFFF);
                moon::BaseObject* pick(const osg::Node::NodeMask mask = 0xFFFFFFFF);
		void setViewer(osgViewer::Viewer *viewer);
		
		osg::Group *getDebugHUD(int mode = 0);
		void enable();
		void disable();
		bool isEnabled() const { return enabled; }
		
		void setGrabInhibited(const bool value);
		bool isGrabInhibited() const { return grabinhibit; }
		
		static ControlHandler& instance();
		
		using osgGA::GUIEventHandler::ref;
		using osgGA::GUIEventHandler::unref;
		
	private:
		bool callHandlers(Event& event, bool isreset = false);
		typedef std::vector<ControlBinding> BindingList;
		BindingList bindings;
		typedef std::map<Control*, ControlBinding*> ActiveBindingMap;
		ActiveBindingMap activebinding;
		std::map<unsigned int, float> lastvalue;
		int mousebutton;
		float refx, refy, pickx, picky;
		bool joystick;
		osgViewer::Viewer *viewer;
		osgViewer::GraphicsWindow *window;
		bool grabbed, grabconstantly, grabinhibit;
		float joystick_epsilon;
		osg::ref_ptr<osg::Group> debugHUDgroup;
		bool enabled;
		
		static ControlHandler* instanceptr;
	};
	
	/// @}
}

#endif /*CONTROLHANDLER_H_*/
