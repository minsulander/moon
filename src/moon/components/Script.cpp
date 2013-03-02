#include "Script.h"
#include "moon/ObjectFactory.h"
#include "moon/Interpreter.h"
#include "moon/XMLParser.h"
#include <mlog/Log.h>
#include "moon/objects/BaseObject.h"
#include "moon/Scenario.h"
#include <osgDB/FileUtils>

using namespace mlog;

namespace moon {
	
	REGISTER_Object(moon, Script);
	
	Script::Script()
	:	Component(),
		runcount(0),
		interval(0),
		time(0),
		when(INITIALIZE),
		selfptr(NULL),
		selftype("nil")
	{
	}
	
	Script::Script(const Script& source, const osg::CopyOp& copyop)
	:	Component(source, copyop),
		filename(source.filename),
		text(source.text),
		runcount(source.runcount),
		interval(source.interval),
		time(0),
		when(source.when),
		selfptr(NULL),
		selftype("nil")
	{
	}
	
	void Script::parseXML(const TiXmlElement *element)
	{
		//=== Script
		if (element->Attribute("file")) {
			//=* attribute: file
			//=. Filename of a Lua script file to run when scenario is loaded.
			filename = osgDB::findDataFile(element->Attribute("file"));
			if (filename.length() == 0)
				dout(ERROR) << "Script '" << element->Attribute("file") << "' not found\n";
		} else if (element->GetText()) {
			//=* text
			//=. Lua script to run when scenario is loaded.
			text = element->GetText();
		}
		//=* attribute: when="parse|initialize|realize|unrealize|reset|update"
		//=. When to run the script
		std::string whenstr;
		if (XMLParser::parseStringAttribute(whenstr, element, "when")) {
			if (whenstr == "parse")
				when = PARSE;
			else if (whenstr == "initialize")
				when = INITIALIZE;
			else if (whenstr == "realize")
				when = REALIZE;
			else if (whenstr == "unrealize")
				when = UNREALIZE;
			else if (whenstr == "reset")
				when = RESET;
			else if (whenstr == "update")
				when = UPDATE;
			else
				throw ParseException("Unknown 'when' specification: " + whenstr);
		}
		/// \todo parse interval
		if (when == PARSE)
			run();
		Component::parseXML(element);
	}
	
	void Script::writeXML(TiXmlElement *element) const
	{
		/// \todo Implement
		Component::writeXML(element);
	}
	
	void Script::initialize()
	{
		/// Set "self" to container as baseobject or scenario or componentcontainer
		if (BaseObject *object = dynamic_cast<moon::BaseObject*> (getContainer())) {
			selfptr = object;
			selftype = "moon::BaseObject";
		} else if (Scenario *scenario = dynamic_cast<moon::Scenario*> (getContainer())) {
			selfptr = scenario;
			selftype = "moon::Scenario";
		} else {
			selfptr = getContainer();
			selftype = "moon::ComponentContainer";
		}
		if (when == INITIALIZE)
			run();
		Component::initialize();
	}
	
	void Script::realize()
	{
		if (when == REALIZE)
			run();
		Component::realize();
	}
	
	void Script::unrealize()
	{
		if (when == UNREALIZE)
			run();
		Component::unrealize();
	}
	
	void Script::reset()
	{
		if (when == RESET)
			run();
		Component::reset();
	}
	
	void Script::update(const double dt)
	{
		if (when == UPDATE) {
			time += dt;
			while (time > interval) {
				run();
				time -= interval;
			}
		}
		Component::update(dt);
	}
	
	void Script::run()
	{
		if (selfptr)
			Interpreter::instance().setGlobal("self", selfptr, selftype);
		if (filename.length() > 0) {
			int ret = Interpreter::instance().doFile(filename);
			if (ret != 0)
				dout(ERROR, SCRIPT) << filename << ": " << Interpreter::instance().getError() << "\n";
		} else {
			int ret = Interpreter::instance().doString(text);
			if (ret != 0)
				dout(ERROR, SCRIPT) << "Script " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
		if (selfptr)
			Interpreter::instance().setGlobal("self", NULL, "nil");
		runcount++;
	}
	
	void Script::setSelf(void *data, const std::string& type)
	{
		selfptr = data;
		selftype = type;
	}

}
