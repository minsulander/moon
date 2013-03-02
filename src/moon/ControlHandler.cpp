#include "ControlHandler.h"
#include "mlog/Log.h"
#include "XMLParser.h"
#include "ObjectFactory.h"
#include "Interpreter.h"
#include "mdraw/Bar.h"
#include <osgText/Text>

using namespace mlog;

#ifdef MOON_USE_SDL_JOYSTICK
#include <SDL/SDL.h>
#endif

#ifdef MOON_USE_PLIB_JOYSTICK
#include <plib/js.h>
#endif

#include <sstream>
#include <iomanip>

namespace moon
{
	
	const std::string Event::typeStr(const EventType type) {
		std::string str;
		switch (type) {
			case NONE: str = "NONE"; break;
			case KEY: str = "Key"; break;
			case MOUSE_BUTTON: str = "MouseButton"; break;
			case MOUSE_MOVE: str = "MouseMove"; break;
			case MOUSE_SCROLL: str = "MouseScroll"; break;
			case JOY_AXIS: str = "JoystickAxis"; break;
			case JOY_BUTTON: str = "JoystickButton"; break;
			case JOY_HAT: str = "JoystickHat"; break;
			case MIDI_DATA: str = "MIDI"; break;
			default: str ="UNKNOWN"; break;
		}
		return str;
	}
	
	REGISTER_Object_Alias(moon, ControlBindingSet, Controls);
	
	ControlBindingSet::ControlBindingSet()
	{
	}
	
	ControlBindingSet::ControlBindingSet(const ControlBindingSet& other, const osg::CopyOp& copyop)
	:	bindings(other.bindings)
	{
	}
	
	void ControlBindingSet::parseXML(const TiXmlElement *element)
	{
		//=== Controls
		//=Control bindings
		for (const TiXmlElement* el = element->FirstChildElement(); el; el = el->NextSiblingElement()) {
			ControlBinding binding;
			Event event;
			event.device = XMLParser::parseIntAttribute(el,"device",true,0);
			if (el->Value() == std::string("key")) {
				//=* repeatable element: key [code="(integer)" | char="(string)" | sym="(string)" ]
				event.type = Event::KEY;
				unsigned int code;
				std::string str;
				if (XMLParser::parseValueAttribute(code, el, "code"))
					event.id = code;
				else if (XMLParser::parseStringAttribute(str, el, "char")) {
					if (str.length() == 1)
						event.id = str[0];
					else if (str.length() != 0)
						throw ParseException("Invalid key character '" + str + "'", el);
				} else if (XMLParser::parseStringAttribute(str, el, "sym")) {
					event.id = getKey(str);
					if (!event.id)
						throw ParseException("Unknown key symbol '" + str + "'", el);
				} else
					throw ParseException("Missing code, char or sym attribute for key event", el);
			} else if (el->Value() == std::string("mouse")) {
				//=* repeatable element: mouse button="(integer)|left|middle|right|wheel" axis="x|y"
				std::string button = XMLParser::parseStringAttribute(el,"button",true,"none");
				std::string axis = XMLParser::parseStringAttribute(el,"axis",true,"none");
				event.id = 0;
				if (button == "left") {
					event.type = Event::MOUSE_BUTTON;
					event.id |= 1;
				} else if (button == "middle") {
					event.type = Event::MOUSE_BUTTON;
					event.id |= 2;
				} else if (button == "right") {
					event.type = Event::MOUSE_BUTTON;
					event.id |= 4;
				} else if (button == "wheel") {
					event.type = Event::MOUSE_SCROLL;
					event.id = 0;
				} 
				if (axis == "x" || axis == "X") {
					event.type = Event::MOUSE_MOVE;
					event.id |= 0x10;
				} else if (axis == "y" || axis == "Y") {
					event.type = Event::MOUSE_MOVE;
					event.id |= 0x20;
				}
				binding.grab = XMLParser::parseBooleanAttribute(el,"grab",true,false);
				binding.resetonrelease = XMLParser::parseBooleanAttribute(el,"resetrelease",true,false);
			} else if (el->Value() == std::string("joystick")) {
				//=* repeatable element: joystick name="(string)" axis="(int)" button="(int)" hat="(int)"
				int device = XMLParser::parseIntAttribute(el,"id",true,-1);
				std::string name = XMLParser::parseStringAttribute(el,"name",true,"");
				if (name.length() > 0)
					device = ControlHandler::instance().getJoystickIndex(name);
				if (device < 0)
					continue;
				event.device = device;
				int axis = XMLParser::parseIntAttribute(el,"axis",true,-1);
				int button = XMLParser::parseIntAttribute(el,"button",true,-1);
				int hat = XMLParser::parseIntAttribute(el,"hat",true,-1);
				if (axis >= 0) {
					event.type = Event::JOY_AXIS;
					event.id = axis;
				} else if (button >= 0) {
					event.type = Event::JOY_BUTTON;
					event.id = button;
				} else if (hat >= 0) {
					event.type = Event::JOY_HAT;
					event.id = hat;
					/// \todo Hat direction?
				}
			}
			binding.event = event;
			//=* Applicable to all of the above:
			//=** attribute: control="(string)"
			//=. The control name this input should be bound to.
			binding.nameref = XMLParser::parseStringAttribute(el,"control");
			//=** attribute: gain="(number)"
			binding.gain = XMLParser::parseDoubleAttribute(el,"gain",true,1);
			//=** attribute: invert="true|false"
			bool invert = XMLParser::parseBooleanAttribute(el,"invert",true,false);
			if (invert) binding.direction = -1;
			//=** attribute: incrate="(number)"
			//=. Rate of increase when buttons/keys are controlling axis controls
			binding.incrate = XMLParser::parseDoubleAttribute(el,"incrate",true,0);
			//=** attribute: decrate="(number)"
			//=. Rate of decrease when buttons/keys are controlling axis controls
			binding.decrate = XMLParser::parseDoubleAttribute(el,"decrate",true,0);
			//=** attribute: threshold="(number)"
			//=. Threshold when mouse/joystick axes are controlling trigger/switch controls
			binding.threshold = XMLParser::parseDoubleAttribute(el,"threshold",true,0.5);
			//=* attribute: null="(number)"
			//=. Minimum movement of axis for it to be considered a value
			binding.nullzone = XMLParser::parseDoubleAttribute(el, "nullzone", true, 0);
			dout(4) << "  " << Event::typeStr(event.type) << " device " << event.device << " id " << event.id;
			bindings.push_back(binding);
			
			//=* Mouse events:
			//=** attribute: grab="true|false"
			//=** attribute: resetrelease="true|false"
			
			// Parse complemental key / joy button
			if (binding.event.type == Event::KEY) {
				//=* Key events:
				//=** attribute: negcode="(integer)" | negchar="(string)" | negsym="(string)"
				//=. Key code for complemental/negative control direction
				binding.event.id = 0;
				unsigned int code;
				std::string str;
				if (XMLParser::parseValueAttribute(code, el, "negcode"))
					binding.event.id = code;
				else if (XMLParser::parseStringAttribute(str, el, "negchar")) {
					if (str.length() == 1)
						binding.event.id = str[0];
					else if (str.length() != 0)
						throw ParseException("Invalid key character '" + str + "'", el);
				} else if (XMLParser::parseStringAttribute(str, el, "negsym")) {
					binding.event.id = getKey(str);
					if (!event.id)
						throw ParseException("Unknown key symbol '" + str + "'", el);
				}
				if (binding.event.id > 0) {
					binding.direction = -binding.direction;
					dout(4) << " complement " << binding.event.id;
					bindings.push_back(binding);
				}
			} else if (binding.event.type == Event::JOY_BUTTON) {
				//=* Joystick events:
				//=** attribute: negbutton="(integer)"
				//=. Button for complemental/negative control direction
				int button = XMLParser::parseIntAttribute(el,"negbutton",true,-1);
				if (button >= 0) {
					binding.event.id = button;
					binding.direction = -binding.direction;
					dout(4) << " complement " << binding.event.id;
					bindings.push_back(binding);
				}
			}
			dout(4) << " controls " << binding.nameref;
			dout(4) << "\n";
		}
	}
	
	void ControlBindingSet::writeXML(TiXmlElement *element) const
	{
		/// \todo Implement
	}

	unsigned int ControlBindingSet::getKey(const std::string& fullname)
	{

		unsigned int key = 0;

		std::string name = fullname;
		size_t ix;
		do {
			ix = name.find_first_of("- ");
			if (ix != std::string::npos) {
				std::string modname = name.substr(0,ix);
				name = name.substr(ix+1);
				if (modname == "shift") key |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
				else if (modname == "leftshift") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_SHIFT;
				else if (modname == "rightshift") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_SHIFT;
				else if (modname == "control") key |= osgGA::GUIEventAdapter::MODKEY_CTRL;
				else if (modname == "leftcontrol") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL;
				else if (modname == "rightcontrol") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_CTRL;
				else if (modname == "alt") key |= osgGA::GUIEventAdapter::MODKEY_ALT;
				else if (modname == "leftalt") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_ALT;
				else if (modname == "rightalt") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_ALT;
				else if (modname == "meta") key |= osgGA::GUIEventAdapter::MODKEY_META;
				else if (modname == "leftmeta") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_META;
				else if (modname == "rightmeta") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_META;
				else if (modname == "super") key |= osgGA::GUIEventAdapter::MODKEY_SUPER;
				else if (modname == "leftsuper") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_SUPER;
				else if (modname == "rightsuper") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_SUPER;
				else if (modname == "hyper") key |= osgGA::GUIEventAdapter::MODKEY_HYPER;
				else if (modname == "lefthyper") key |= osgGA::GUIEventAdapter::MODKEY_LEFT_HYPER;
				else if (modname == "righthyper") key |= osgGA::GUIEventAdapter::MODKEY_RIGHT_HYPER;
				//else if (modname == "") key |= osgGA::GUIEventAdapter::MODKEY_;
			}
		} while (ix != std::string::npos);
		key = key << 16;

		if (name == "space") key |= osgGA::GUIEventAdapter::KEY_Space;
		else if (name == "backspace") key |= osgGA::GUIEventAdapter::KEY_BackSpace;
		else if (name == "tab") key |= osgGA::GUIEventAdapter::KEY_Tab;
		else if (name == "linefeed") key |= osgGA::GUIEventAdapter::KEY_Linefeed;
		else if (name == "clear") key |= osgGA::GUIEventAdapter::KEY_Clear;
		else if (name == "return") key |= osgGA::GUIEventAdapter::KEY_Return;
		else if (name == "pause") key |= osgGA::GUIEventAdapter::KEY_Pause;
		else if (name == "scroll_lock") key |= osgGA::GUIEventAdapter::KEY_Scroll_Lock;
		else if (name == "sysreq") key |= osgGA::GUIEventAdapter::KEY_Sys_Req;
		else if (name == "escape") key |= osgGA::GUIEventAdapter::KEY_Escape;
		else if (name == "delete") key |= osgGA::GUIEventAdapter::KEY_Delete;
		else if (name == "home") key |= osgGA::GUIEventAdapter::KEY_Home;
		else if (name == "left") key |= osgGA::GUIEventAdapter::KEY_Left;
		else if (name == "up") key |= osgGA::GUIEventAdapter::KEY_Up;
		else if (name == "right") key |= osgGA::GUIEventAdapter::KEY_Right;
		else if (name == "down") key |= osgGA::GUIEventAdapter::KEY_Down;
		else if (name == "prior") key |= osgGA::GUIEventAdapter::KEY_Prior;
		else if (name == "pageup") key |= osgGA::GUIEventAdapter::KEY_Page_Up;
		else if (name == "next") key |= osgGA::GUIEventAdapter::KEY_Next;
		else if (name == "pagedown") key |= osgGA::GUIEventAdapter::KEY_Page_Down;
		else if (name == "end") key |= osgGA::GUIEventAdapter::KEY_End;
		else if (name == "begin") key |= osgGA::GUIEventAdapter::KEY_Begin;
		else if (name == "select") key |= osgGA::GUIEventAdapter::KEY_Select;
		else if (name == "print") key |= osgGA::GUIEventAdapter::KEY_Print;
		else if (name == "execute") key |= osgGA::GUIEventAdapter::KEY_Execute;
		else if (name == "insert") key |= osgGA::GUIEventAdapter::KEY_Insert;
		else if (name == "undo") key |= osgGA::GUIEventAdapter::KEY_Undo;
		else if (name == "redo") key |= osgGA::GUIEventAdapter::KEY_Redo;
		else if (name == "menu") key |= osgGA::GUIEventAdapter::KEY_Menu;
		else if (name == "find") key |= osgGA::GUIEventAdapter::KEY_Find;
		else if (name == "cancel") key |= osgGA::GUIEventAdapter::KEY_Cancel;
		else if (name == "help") key |= osgGA::GUIEventAdapter::KEY_Help;
		else if (name == "break") key |= osgGA::GUIEventAdapter::KEY_Break;
		else if (name == "modeswitch") key |= osgGA::GUIEventAdapter::KEY_Mode_switch;
		else if (name == "scriptswitch") key |= osgGA::GUIEventAdapter::KEY_Script_switch;
		else if (name == "numlock") key |= osgGA::GUIEventAdapter::KEY_Num_Lock;
		else if (name == "keypad_space") key |= osgGA::GUIEventAdapter::KEY_KP_Space;
		else if (name == "keypad_tab") key |= osgGA::GUIEventAdapter::KEY_KP_Tab;
		else if (name == "keypad_enter") key |= osgGA::GUIEventAdapter::KEY_KP_Enter;
		else if (name == "keypad_f1") key |= osgGA::GUIEventAdapter::KEY_KP_F1;
		else if (name == "keypad_f2") key |= osgGA::GUIEventAdapter::KEY_KP_F2;
		else if (name == "keypad_f3") key |= osgGA::GUIEventAdapter::KEY_KP_F3;
		else if (name == "keypad_f4") key |= osgGA::GUIEventAdapter::KEY_KP_F4;
		else if (name == "keypad_home") key |= osgGA::GUIEventAdapter::KEY_KP_Home;
		else if (name == "keypad_left") key |= osgGA::GUIEventAdapter::KEY_KP_Left;
		else if (name == "keypad_up") key |= osgGA::GUIEventAdapter::KEY_KP_Up;
		else if (name == "keypad_down") key |= osgGA::GUIEventAdapter::KEY_KP_Down;
		else if (name == "keypad_prior") key |= osgGA::GUIEventAdapter::KEY_KP_Prior;
		else if (name == "keypad_pageup") key |= osgGA::GUIEventAdapter::KEY_KP_Page_Up;
		else if (name == "keypad_next") key |= osgGA::GUIEventAdapter::KEY_KP_Next;
		else if (name == "keypad_pagedown") key |= osgGA::GUIEventAdapter::KEY_KP_Page_Down;
		else if (name == "keypad_end") key |= osgGA::GUIEventAdapter::KEY_KP_End;
		else if (name == "keypad_begin") key |= osgGA::GUIEventAdapter::KEY_KP_Begin;
		else if (name == "keypad_insert") key |= osgGA::GUIEventAdapter::KEY_KP_Insert;
		else if (name == "keypad_delete") key |= osgGA::GUIEventAdapter::KEY_KP_Delete;
		else if (name == "keypad_equal") key |= osgGA::GUIEventAdapter::KEY_KP_Equal;
		else if (name == "keypad_multiply") key |= osgGA::GUIEventAdapter::KEY_KP_Multiply;
		else if (name == "keypad_add") key |= osgGA::GUIEventAdapter::KEY_KP_Add;
		else if (name == "keypad_separator") key |= osgGA::GUIEventAdapter::KEY_KP_Separator;
		else if (name == "keypad_subtract") key |= osgGA::GUIEventAdapter::KEY_KP_Subtract;
		else if (name == "keypad_decimal") key |= osgGA::GUIEventAdapter::KEY_KP_Decimal;
		else if (name == "keypad_divide") key |= osgGA::GUIEventAdapter::KEY_KP_Divide;
		else if (name == "keypad0") key |= osgGA::GUIEventAdapter::KEY_KP_0;
		else if (name == "keypad1") key |= osgGA::GUIEventAdapter::KEY_KP_1;
		else if (name == "keypad2") key |= osgGA::GUIEventAdapter::KEY_KP_2;
		else if (name == "keypad3") key |= osgGA::GUIEventAdapter::KEY_KP_3;
		else if (name == "keypad4") key |= osgGA::GUIEventAdapter::KEY_KP_4;
		else if (name == "keypad5") key |= osgGA::GUIEventAdapter::KEY_KP_5;
		else if (name == "keypad6") key |= osgGA::GUIEventAdapter::KEY_KP_6;
		else if (name == "keypad7") key |= osgGA::GUIEventAdapter::KEY_KP_7;
		else if (name == "keypad8") key |= osgGA::GUIEventAdapter::KEY_KP_8;
		else if (name == "keypad9") key |= osgGA::GUIEventAdapter::KEY_KP_9;
		else if (name == "f1") key |= osgGA::GUIEventAdapter::KEY_F1;
		else if (name == "f2") key |= osgGA::GUIEventAdapter::KEY_F2;
		else if (name == "f3") key |= osgGA::GUIEventAdapter::KEY_F3;
		else if (name == "f4") key |= osgGA::GUIEventAdapter::KEY_F4;
		else if (name == "f5") key |= osgGA::GUIEventAdapter::KEY_F5;
		else if (name == "f6") key |= osgGA::GUIEventAdapter::KEY_F6;
		else if (name == "f7") key |= osgGA::GUIEventAdapter::KEY_F7;
		else if (name == "f8") key |= osgGA::GUIEventAdapter::KEY_F8;
		else if (name == "f9") key |= osgGA::GUIEventAdapter::KEY_F9;
		else if (name == "f10") key |= osgGA::GUIEventAdapter::KEY_F10;
		else if (name == "f11") key |= osgGA::GUIEventAdapter::KEY_F11;
		else if (name == "f12") key |= osgGA::GUIEventAdapter::KEY_F12;
		//...
		else if (name == "leftshift") key |= osgGA::GUIEventAdapter::KEY_Shift_L;
		else if (name == "rightshift") key |= osgGA::GUIEventAdapter::KEY_Shift_R;
		else if (name == "leftcontrol") key |= osgGA::GUIEventAdapter::KEY_Control_L;
		else if (name == "rightcontrol") key |= osgGA::GUIEventAdapter::KEY_Control_R;
		else if (name == "capslock") key |= osgGA::GUIEventAdapter::KEY_Caps_Lock;
		else if (name == "shiftlock") key |= osgGA::GUIEventAdapter::KEY_Shift_Lock;
		else if (name == "leftmeta") key |= osgGA::GUIEventAdapter::KEY_Meta_L;
		else if (name == "rightmeta") key |= osgGA::GUIEventAdapter::KEY_Meta_R;
		else if (name == "leftalt") key |= osgGA::GUIEventAdapter::KEY_Alt_L;
		else if (name == "rightalt") key |= osgGA::GUIEventAdapter::KEY_Alt_R;
		else if (name == "leftsuper") key |= osgGA::GUIEventAdapter::KEY_Super_L;
		else if (name == "rightsuper") key |= osgGA::GUIEventAdapter::KEY_Super_R;
		else if (name == "lefthyper") key |= osgGA::GUIEventAdapter::KEY_Hyper_L;
		else if (name == "righthyper") key |= osgGA::GUIEventAdapter::KEY_Hyper_R;
		//else if (name == "") key |= osgGA::GUIEventAdapter::KEY_;
		else if (name.length() == 1)
			key |= name[0];
		return key;
	}
	
	
	ControlHandler::ControlHandler()
	:	osgGA::GUIEventHandler()
	{
		joystick = false;
		mousebutton = 0;
		viewer = NULL;
		window = NULL;
		instanceptr = this;
		refx = refy = -3; // means that it will be reset upon first mouse move event
		grabbed = false;
		grabconstantly = false;
		grabinhibit = false;
		joystick_epsilon = 0.001;
		enabled = true;
	}
	
	ControlHandler::~ControlHandler()
	{
	}
	
	void ControlHandler::load(const std::string& filename)
	{
		TiXmlDocument doc(filename);
		bool ok = doc.LoadFile();
		if (ok) {
			dout(1) << "Parsing XML file '" << filename << "'\n";
			TiXmlHandle hDoc(&doc);
			TiXmlElement* pElem;
			pElem=hDoc.FirstChildElement().Element();
			if (!pElem->Value() || std::string(pElem->Value()) != "moon")
				throw ParseException(std::string("No top-level 'moon' element in '") + filename + "'");
			else
				pElem = pElem->FirstChildElement();
			for (; pElem; pElem=pElem->NextSiblingElement()) {
				
				if (std::string(pElem->Value()) == "controls") {
					parseBindings(pElem);
				}
			}
		} else
			throw ParseException(std::string("Unable to load XML file '") + filename + "': " + doc.ErrorDesc());
	}
	
	void ControlHandler::parseBindings(TiXmlElement* element)
	{
		// Global parameters
		joystick_epsilon = XMLParser::parseDouble(element,"joystick_epsilon","",true,joystick_epsilon);
	}
	
	/*********************************************************************************************/
	/* We have two options here, just because I don't want to throw away code (yet)... use PLIB  */
	/* or SDL for joysticks... set the appropriate define.                                       */
	/*********************************************************************************************/
	
#if defined(MOON_USE_PLIB_JOYSTICK)
	
	std::vector<jsJoystick*> joys;
	std::vector<float*> joy_axes, old_axes;
	std::vector<int> joy_btns, old_btns;
	
	bool ControlHandler::initJoysticks() {
		return false;
		dout(2) << "Initializing joysticks\n";
		jsInit();
		bool done = false;
		while (!done) {
			jsJoystick *joy = new jsJoystick(joys.size());
			if (joy->notWorking())
				done = true;
			else {
				int num = joys.size();
				joys.push_back(joy);
				dout(1) << "  #" << num << ": " << joy->getName();
				dout(2) << ": " << joy->getNumAxes() << " axes, " << joy->getNumButtons() << " buttons";
				dout(1) << "\n";
				joy_axes.push_back(new float[joy->getNumAxes()]);
				old_axes.push_back(new float[joy->getNumAxes()]);
				joy_btns.push_back(0);
				old_btns.push_back(0);
				joy->read(&old_btns[num], old_axes[num]);
			}
		}
		joystick = true;
		return true;
	}
	
	const int ControlHandler::getJoystickIndex(const std::string& name)
	{
		if (!joystick)
			return -1;
		for (unsigned int i = 0; i < joys.size(); i++) {
			if (joys[i] && name == joys[i]->getName())
				return i;
		}
		return -1;
	}
	
	bool ControlHandler::pollEvents() {
		if (!joystick)
			return false;
		bool handled = false;
		for (unsigned int i = 0; i < joys.size(); i++) {
			joys[i]->read(&joy_btns[i], joy_axes[i]);
			if (joy_btns[i] != old_btns[i]) {
				int change = joy_btns[i] ^ old_btns[i];
				int btn = 0;
				std::stringstream butss;
				for (unsigned int j = 1; j < 0x80000000; j *= 2) {
					if (change & j) {
						dout(8) << "joy button " << btn << ": " << (joy_btns[i] & j ? true : false) << "\n";
						if (joy_btns[i] & j)
							butss << btn << "  "; 
						// Joystick button up/down
						Event ev;
						ev.type = Event::JOY_BUTTON;
						ev.device = i;
						ev.id = btn;
						ev.value = (joy_btns[i] & j ? true : false);
						if (callHandlers(ev))
							handled = true;
					}
					btn++;
				}
				if (debugHUDgroup.valid()) {
					osgText::Text *text = (osgText::Text*) ((osg::Geode*)debugHUDgroup->getChild(0)->asGroup()->getChild(i)->asGroup()->getChild(0))->getDrawable(1);
					text->setText(butss.str());
				}
			}
			for (int j = 0; j < joys[i]->getNumAxes(); j++) {
				if (fabs(joy_axes[i][j] - old_axes[i][j]) > joystick_epsilon) {
					dout(8) << "joy " << i << " axis " << j << ": " << joy_axes[i][j] << "\n";
					old_axes[i][j] = joy_axes[i][j];
					// Joystick axis motion
					Event ev;
					ev.type = Event::JOY_AXIS;
					ev.device = i;
					ev.id = j;
					ev.value = joy_axes[i][j];
					ev.x = 0;
					ev.y = 0;
					if (callHandlers(ev))
						handled = true;
				}	
			}
			old_btns[i] = joy_btns[i];
		}
		return handled;
	}
	
	/*********************************************************************************************/
	
#elif defined(MOON_USE_SDL_JOYSTICK)
	
	std::vector<SDL_Joystick*> joys;
	
	bool ControlHandler::initJoysticks() {
		dout(INFO) << "Initializing joysticks\n";
		// Initialize SDL joystick subsystem (and video because SDL doesn't give us any joystick events otherwise)
		if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
			dout(WARN) << "Joystick initialization failed: " << SDL_GetError() << std::endl;
			return false;
		}
		atexit(SDL_Quit);
		if (SDL_NumJoysticks() <= 0) {
			dout(INFO) << "  No joysticks found\n";
			return true;
		}
		// Open all joysticks
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick *joy = SDL_JoystickOpen(i);
			dout(1) << "  #" << i << ": " << SDL_JoystickName(i);
			if (joy) {
				joys.push_back(joy);
				dout(2) << ": " << SDL_JoystickNumAxes(joy) << " axes, "
				<< SDL_JoystickNumButtons(joy) << " buttons, "
				<< SDL_JoystickNumBalls(joy) << " balls, "
				<< SDL_JoystickNumHats(joy) << " hats";
			} else
				dout(1) << " failed to open";
			dout(1) << "\n";
		}
		joystick = true;
		
		return true;
	}
	
	const int ControlHandler::getJoystickIndex(const std::string& name)
	{
		if (!joystick)
			return -1;
		for (int i = 0; i < SDL_NumJoysticks(); i++)
			if (name == SDL_JoystickName(i))
				return i;
		return -1;
	}
	
	// pollEvents - polls events that are not handled by OSG
	bool ControlHandler::pollEvents() {
		// Poll joystick events using SDL
		if (joystick) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_JOYAXISMOTION) {
					// Joystick axis motion
					Event ev;
					ev.type = Event::JOY_AXIS;
					ev.device = event.jaxis.which;
					ev.id = event.jaxis.axis;
					ev.value = (double)event.jaxis.value/32768.0;
					ev.x = 0;
					ev.y = 0;
					if (callHandlers(ev)) return true;
				} else if (event.type == SDL_JOYBUTTONUP || event.type == SDL_JOYBUTTONDOWN) {
					// Joystick button up/down
					Event ev;
					ev.type = Event::JOY_BUTTON;
					ev.device = event.jbutton.which;
					ev.id = event.jbutton.button;
					ev.value = event.jbutton.state;
					if (callHandlers(ev)) return true;
				} else if (event.type == SDL_JOYHATMOTION) {
					// Joystick hat motion
					Event ev;
					ev.type = Event::JOY_HAT;
					ev.device = event.jhat.which;
					ev.id = event.jhat.hat;
					ev.value = event.jhat.value;
					if (callHandlers(ev)) return true;
				} else if (event.type == SDL_JOYBALLMOTION) {
					// Joystick trackball motion
					Event ev;
					ev.type = Event::JOY_HAT;
					ev.device = event.jball.which;
					ev.id = event.jball.ball+100;
					ev.value = 0;
					ev.x = event.jball.xrel;
					ev.y = event.jball.yrel;
					if (callHandlers(ev)) return true;
				}
			}
		}
		return false;
	}
	
	/*********************************************************************************************/

#else
	
	bool ControlHandler::initJoysticks()
	{
		return false;
	}
	
	const int ControlHandler::getJoystickIndex(const std::string& name)
	{
		return -1;
	}
	
	bool ControlHandler::pollEvents() {
		return false;
	}
	
#endif
	
	
	bool ControlHandler::handle (const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
	{
		if (ea.getHandled() || !enabled)
			return false;
		
		Event ev;
		bool handled = false;
		
		switch(ea.getEventType()) {
				
			case osgGA::GUIEventAdapter::FRAME:
				return false;
				break;
			case osgGA::GUIEventAdapter::KEYDOWN:
			case osgGA::GUIEventAdapter::KEYUP:
				ev.type = Event::KEY;
				ev.device = 0;
				ev.id = ea.getKey();
				//if (ev.id > 0xff || !isprint((char)ev.id))
					//ev.id += (ea.getModKeyMask() & ~(osgGA::GUIEventAdapter::MODKEY_NUM_LOCK | osgGA::GUIEventAdapter::MODKEY_CAPS_LOCK)) << 16;
				ev.id += ea.getModKeyMask() << 16;
				ev.value = (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN);
				if (callHandlers(ev)) handled = true;
				break;
			case osgGA::GUIEventAdapter::DRAG:
				ev.type = Event::MOUSE_MOVE;
				ev.device = 0;
				ev.x = ea.getXnormalized();
				ev.y = ea.getYnormalized();
				ev.id = 0x10 | mousebutton;
				ev.value = (ev.x-refx);
				if (callHandlers(ev)) handled = true;
				ev.id = 0x20 | mousebutton;
				ev.value = (ev.y-refy);
				if (callHandlers(ev)) handled = true;
				pickx = ea.getX();
				picky = ea.getY();
				break;
			case osgGA::GUIEventAdapter::MOVE:
				if (refx < -2) {
					refx = ea.getXnormalized();
					refy = ea.getYnormalized();
				}
				ev.type = Event::MOUSE_MOVE;
				ev.device = 0;
				ev.x = ea.getXnormalized();
				ev.y = ea.getYnormalized();
				ev.id = 0x10;
				ev.value = ev.x-refx;
				if (callHandlers(ev)) handled = true;
				ev.id = 0x20;
				ev.value = ev.y-refy;
				if (callHandlers(ev)) handled = true;
				pickx = ea.getX();
				picky = ea.getY();
				break;
			case osgGA::GUIEventAdapter::PUSH:
			case osgGA::GUIEventAdapter::DOUBLECLICK:
			case osgGA::GUIEventAdapter::RELEASE:
				ev.type = Event::MOUSE_BUTTON;
				ev.device = 0;
				ev.id = ea.getButton();
				if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE) {
					ev.value = 1;
					mousebutton = ev.id;
					refx = ea.getXnormalized();
					refy = ea.getYnormalized();
				} else {
					ev.value = 0;
					mousebutton = 0;
					refx = -3;
					refy = -3;
				}
				ev.x = ea.getXnormalized();
				ev.y = ea.getYnormalized();
				if (callHandlers(ev))
					handled = true;
				if (ev.value == 0) {
					// Reset axis/drag movement
					ev.type = Event::MOUSE_MOVE;
					ev.id = 0x10 | ea.getButton();
					if (callHandlers(ev, true))
						handled = true;
					ev.id = 0x20 | ea.getButton();
					if (callHandlers(ev, true))
						handled = true;
					if (grabbed && window && !grabconstantly) {
						window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
						window->requestWarpPointer((ea.getXmax()-ea.getXmin())/2.0,(ea.getYmax()-ea.getYmin())/2.0);
						refx = refy = 0;
						grabbed = false;
					}
				}
				pickx = ea.getX();
				picky = ea.getY();
				break;
			default:
				if (ea.getEventType() != 65535)
					dout(8) << "Unimplemented event " << ea.getEventType() << "\n";
		}
		
		// Get viewer and graphics window for grabbing mouse
		if (!viewer)
			viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
		if (viewer && !window) {
			osgViewer::Viewer::Windows windows;
			viewer->getWindows(windows);
			if (windows.size() > 0)
				window = windows[0];
			else
				dout(ERROR) << "Could not get window from viewer\n";
		}
		// Wrap around screen/window edges
		if (grabbed && window && (ea.getEventType() == osgGA::GUIEventAdapter::DRAG || ea.getEventType() == osgGA::GUIEventAdapter::MOVE) 
			&& (fabs(ea.getXnormalized()) > 0.99 || fabs(ea.getYnormalized()) > 0.99)) {
			window->requestWarpPointer((ea.getXmax()-ea.getXmin())/2.0,(ea.getYmax()-ea.getYmin())/2.0);
			refx = refy = 0;
		} 
                //return handled;
                return false;
	}
	
	void ControlHandler::update(const double dt)
	{
		pollEvents();
		
		for (BindingList::iterator i = bindings.begin(); i != bindings.end(); i++) {
			if (! i->control.valid())
				continue;
			Control& control = *i->control.get();
			ControlBinding& binding = *i;
			if (control.getType() == Control::AXIS && (!activebinding[&control] || activebinding[&control] == &binding)) {
				if (binding.event.type == Event::KEY || binding.event.type == Event::MOUSE_BUTTON || binding.event.type == Event::JOY_BUTTON) {
					// Update axes controlled by keys/buttons
					// using incrate and decrate to gradually increase/decrease axis value 
					if (binding.event.value != 0 && binding.incrate > 0) {
						control.setValue(control.getValue() + dt*binding.incrate*binding.gain*binding.direction);
						if (fabs(control.getValue()) > binding.event.value*binding.gain)
							control.setValue(binding.event.value*binding.gain*binding.direction);
					} else if (binding.decrate > 0 && binding.event.value == 0 && 
							   (binding.direction > 0 && control.getValue() > 0 ||
								binding.direction < 0 && control.getValue() < 0)) {
						control.setValue(control.getValue() - dt*binding.decrate*binding.gain*binding.direction);
						if (binding.direction > 0 && control.getValue() < 0)
							control.setValue(0);
						else if (binding.direction < 0 && control.getValue() > 0)
							control.setValue(0);
					} else if (fabs(binding.event.value) >= 1e-5 && binding.incrate <= 0) {
						control.setValue(binding.event.value*binding.gain*binding.direction);
					}
				}
				// Reset value (send one-shot axis value) for mouse-looking motion
				if (binding.grab) {
					binding.event.value = 0;
				}
			}
		}
		
		if (debugHUDgroup.valid()) {
			std::stringstream ss;
			for (BindingList::iterator i = bindings.begin(); i != bindings.end(); i++) {
				if (! i->control.valid())
					continue;
				Control& control = *i->control.get();
				ControlBinding& binding = *i;
				if ((!activebinding[&control] || activebinding[&control] == &binding)) {
					ss << binding.event.type << " " << binding.event.device << " " << binding.event.id
					<< " : " << control.getType() << " " << control.getName()
					<< " = " << control.getValue() << "\n";
				}
			}
			((osgText::Text*)((osg::Geode*)debugHUDgroup->getChild(1))->getDrawable(0))->setText(ss.str());
		}
	}
	
	void ControlHandler::bind(const ControlBinding& binding)
	{
		// Insert them instead of adding them to the end, so that the most recent bindings get bound
		bindings.insert(bindings.begin(), binding);
	}

	
	void ControlHandler::bind(const ControlBindingSet *set)
	{
		if (!set) return;
		for (unsigned int i = 0; i < set->getNumBindings(); i++)
			bind(set->getBinding(i));
	}
	
	void ControlHandler::bind(const Event& event, const std::string& name, const float gain) 
	{
		bind(ControlBinding(event, name, gain));
	}
	
	void ControlHandler::bind(const Event& event, const Event& complement, const std::string& name, const float gain)
	{
		bind(ControlBinding(event, name, gain));
		ControlBinding cbind(complement, name, gain);
		cbind.direction = -1;
		bind(cbind);
	}
	
	void ControlHandler::bind(const int key, const std::string& name, const float gain)
	{
		bind(ControlBinding(Event(Event::KEY, 0, key), name, gain));
	}
			 
	void ControlHandler::bind(const int key, const int complement_key, const std::string& name, const float gain)
	{
		bind(ControlBinding(Event(Event::KEY, 0, key), name, gain));
		ControlBinding cbind(Event(Event::KEY, 0, complement_key), name, gain);
		cbind.direction = -1;
		bind(cbind);
	}
	
	bool ControlHandler::bind(Control* control)
	{
		if (!control)
			return false;
		bool found = false;
		grabconstantly = false;
		for (BindingList::iterator i = bindings.begin(); i != bindings.end(); i++) {
			if (i->nameref == control->getName()) {
				i->controlstack.push(i->control);
				i->control = control;
				activebinding[control] = &(*i);
				control->setBound(true);
				found = true;
			}
			// If a mouse-grabbing mouse move (not drag) binding exists, grab constantly 
			if (i->control.valid() && i->grab && !grabinhibit && i->event.type == Event::MOUSE_MOVE && !(i->event.id & 0x0F)) {
				grabconstantly = true;
			}
		}
		if (window) {
			if (grabconstantly)
				window->setCursor(osgViewer::GraphicsWindow::NoCursor);
			else
				window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
			grabbed = grabconstantly;
		}
		if (found)
			dout(6) << "bound control " << control->getName() << "\n";
		
		return found;
	}
	
	void ControlHandler::unbind(Control* control)
	{
		if (!control)
			return;
		grabconstantly = false;
		for (BindingList::iterator i = bindings.begin(); i != bindings.end(); i++) {
			if (i->control == control) {
				i->control = NULL;
				control->setBound(false);
				// Re-bind if there are controls on the stack
				if (i->controlstack.size() > 0) {
					bind(i->controlstack.top().get());
					i->controlstack.pop();
				}
			}
			// If a mouse-grabbing mouse move (not drag) binding exists, grab constantly 
			if (i->control.valid() && i->grab && !grabinhibit && i->event.type == Event::MOUSE_MOVE && !(i->event.id & 0x0F)) {
				grabconstantly = true;
			}
		}
		if (window) {
			if (grabconstantly)
				window->setCursor(osgViewer::GraphicsWindow::NoCursor);
			else
				window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
			grabbed = grabconstantly;
		}
		
	}
	
	bool ControlHandler::callHandlers(Event& event, bool isreset)
	{
		dout(8) << "event " << event.type << " device " << event.device << " id " << event.id
		<< " value " << event.value << " x " << event.x << " y " << event.y;
		for (BindingList::iterator i = bindings.begin(); i != bindings.end(); i++) {
			bool match = false;
			if (i->event.type == event.type && i->event.device == event.device && i->control.valid()) {
				// Handle modkey masks
				if (event.type == Event::KEY && i->event.id & 0xFFFF0000) {
					unsigned short eid = event.id & 0xFFFF;
					unsigned short bid = i->event.id & 0xFFFF;
					unsigned short emod = (event.id >> 16) & 0xFFFF;
					unsigned short bmod = (i->event.id >> 16) & 0xFFFF;
					if (eid == bid) {
						if (emod == bmod)
							match = true;
						else {
							match = true;
							// pair-wise modifier key matching... shift-control-* shouldn't match
							// just shift-* etc...
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_SHIFT) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_SHIFT))
								match = false;
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_CTRL) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_CTRL))
								match = false;
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_ALT) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_ALT))
								match = false;
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_META) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_META))
								match = false;
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_SUPER) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_SUPER))
								match = false;
							if ((bmod & osgGA::GUIEventAdapter::MODKEY_HYPER) &&
								!(emod & bmod & osgGA::GUIEventAdapter::MODKEY_HYPER))
								match = false;
						}
					}
				} else if (i->event.id == (event.id & 0xFFFF))
					match = true;
			}
			if (match) {
				Control& control = *i->control.get();
				ControlBinding& binding = *i;
				activebinding[&control] = &binding;
				int index = i-bindings.begin();
				
				if (!binding.resetonrelease && isreset)
					return false;
				
				if (event.type == Event::MOUSE_MOVE && binding.grab) {
					if (event.id & 0x10) {
						refx = event.x;
						event.value *= 10.0;
					}
					if (event.id & 0x20) {
						refy = event.y;
						event.value *= 10.0;
					}
					if (!grabinhibit) {
						if (window)
							window->setCursor(osgViewer::GraphicsWindow::NoCursor);
						grabbed = true;
					}
					// inhibit mouse movement with no button mapping when grab is inhibited
					if (grabinhibit && !(event.id & 0x0F))
						continue;
				}
				
				switch (control.getType()) {
					case Control::AXIS:
						if (event.type == Event::MOUSE_MOVE || event.type == Event::JOY_AXIS) {
							// Controlled by "real" axis controller
							int sign = 1;
							if (event.value < 0)
								sign = -1;
							if (fabs(event.value) > binding.nullzone)
								control.setValue((event.value-binding.nullzone*sign)/(1.0-binding.nullzone)*binding.gain*binding.direction);
							else
								control.setValue(0);
						} else {
							// Controlled by keys/buttons - see updateSimulation()
							if (event.value == 0 && binding.decrate <= 0)
								control.setValue(0);
							// else control will be updated in updateSimulation()
						}
						break;
					case Control::MOMENTARY:
						if (event.value >= binding.threshold)
							control.setValue(binding.gain);
						else
							control.setValue(0);
						break;
					case Control::TOGGLE:
						if (event.value >= binding.threshold && lastvalue[index] < binding.threshold) {
							if (control.getValue())
								control.setValue(0);
							else
								control.setValue(binding.gain);
						}
						lastvalue[index]=event.value;
						break;
				}

				binding.event.value = event.value;
				
				dout(8) << " control " << control.getName() << "=" << control.getValue() << std::endl;
				return true;
			}
		}
		if (event.type == Event::KEY && event.value == 1) {
			// Call event function (if it exists)
			if (Interpreter::instance().pushNamed("event.keyPress")) {
				Interpreter::instance().pushInt(event.id);
				if (Interpreter::instance().pCall(1,1) != 0) {
					dout(8) << "\n";
					dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
					return false;
				}
				bool ret = Interpreter::instance().popBool();
				if (ret) {
					dout(8) << " event.keyPress\n";
					return true;
				}
			}
		}
		dout(8) << "\n";
		return false;
	}
	
        moon::BaseObject* ControlHandler::pick(const float x, const float y, const osg::Node::NodeMask mask) {
		if (!viewer)
			return NULL;
		osgUtil::LineSegmentIntersector::Intersections ixns;
                viewer->computeIntersections(x, y, ixns, mask);
                dout(2) << "pick " << x << ", " << y << " - " << ixns.size() << " nodes: ";
		for (osgUtil::LineSegmentIntersector::Intersections::iterator i = ixns.begin(); i != ixns.end(); i++) {
			osgUtil::LineSegmentIntersector::Intersection ixn = *i;
			for (osg::NodePath::reverse_iterator j = ixn.nodePath.rbegin(); j != ixn.nodePath.rend(); j++) {
				if ((*j)->getName().length() > 0)
					dout(2) << (*j)->getName();
				else
					dout(2) << "(" << (*j)->className() << ")";
				if ((*j)->getUserData()) {
					dout(2) << " (udata)";
					osg::Referenced* ptr=(*j)->getUserData();
					moon::BaseObject* obj = dynamic_cast<moon::BaseObject*>(ptr);
					if (obj) {
						dout(2) << " (match)\n";
						return obj;
					}
					
				}
				dout(2) << " ";
			}
		}
		dout(2) << "\n";
		return NULL;
	}
	
        moon::BaseObject* ControlHandler::pick(const osg::Node::NodeMask mask) {
            return pick(pickx, picky, mask);
        }

        void ControlHandler::setViewer(osgViewer::Viewer *viewer) {
		this->viewer = viewer;
	}
	
	osg::Group *ControlHandler::getDebugHUD(int mode) {
		if (mode == 0) {
			debugHUDgroup = new osg::Group;
			// Note: changing the order of nodes here needs a change in pollEvents() !
			osg::Group *joygroup = new osg::Group;
			debugHUDgroup->addChild(joygroup);
#ifdef MOON_USE_PLIB_JOYSTICK
			for (unsigned int i = 0; i < joys.size(); i++) {
				osg::Group *group = new osg::Group;
				osgText::Text *label = new osgText::Text;
				label->setText(joys[i]->getName());
				label->setCharacterSize(0.03);
				label->setPosition(osg::Vec3(-0.97,0.91-0.25*i,0));
				label->setFont("fonts/arial.ttf");
				osg::Geode *textgeo = new osg::Geode;
				textgeo->addDrawable(label);
				group->addChild(textgeo);
				
				label = new osgText::Text;
				label->setCharacterSize(0.03);
				label->setPosition(osg::Vec3(-0.95+0.05*joys[i]->getNumAxes(),0.88-0.25*i,0));
				label->setFont("fonts/arial.ttf");
				textgeo->addDrawable(label);
				for (int j = 0; j < joys[i]->getNumAxes(); j++) {
					mdraw::Bar *bar = new mdraw::Bar(0.2,0.025,osg::Vec3(-0.95+0.05*j,0.8-0.25*i,0),mdraw::Bar::VERTICAL);
					bar->setMin(-1);
					bar->setMax(1);
					bar->setValuePtr(&joy_axes[i][j]);
					group->addChild(bar);
				}
				joygroup->addChild(group);
			}
#endif		
			
			{
				// Controls debug text
				osgText::Text *label = new osgText::Text;
				label->setText("Controls");
				label->setCharacterSize(0.03);
				label->setPosition(osg::Vec3(-0.99,0,0));
				label->setFont("fonts/arial.ttf");
				osg::Geode *textgeo = new osg::Geode;
				textgeo->addDrawable(label);
				debugHUDgroup->addChild(textgeo);
			}		
			
			return debugHUDgroup.get();
		}
		return NULL;
	}
	
	void ControlHandler::enable() {
		if (window) {
			if (grabconstantly)
				window->setCursor(osgViewer::GraphicsWindow::NoCursor);
			else
				window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
			grabbed = grabconstantly;
		}
		enabled = true;
	}
	
	void ControlHandler::disable() {
		if (grabbed && window) {
			window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
			//window->requestWarpPointer((ea.getXmax()-ea.getXmin())/2.0,(ea.getYmax()-ea.getYmin())/2.0);
			refx = refy = 0;
			grabbed = false;
		}
		enabled = false;
	}
	
	void ControlHandler::setGrabInhibited(const bool value) {
		grabinhibit = value;
		if (grabinhibit && window) {
			window->setCursor(osgViewer::GraphicsWindow::RightArrowCursor);
			//window->requestWarpPointer((ea.getXmax()-ea.getXmin())/2.0,(ea.getYmax()-ea.getYmin())/2.0);
			refx = refy = 0;
			grabbed = grabconstantly = false;
		}
	}
	
	ControlHandler& ControlHandler::instance() {
		if (!instanceptr)
			instanceptr = new ControlHandler;
		return *instanceptr;
	}
	
	ControlHandler* ControlHandler::instanceptr = NULL;
	
} // namespace
