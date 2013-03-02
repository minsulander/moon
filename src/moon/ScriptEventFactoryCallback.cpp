#include "ScriptEventFactoryCallback.h"
#include "Interpreter.h"
#include <mlog/Log.h>

using namespace mlog;

namespace moon {

	void ScriptEventFactoryCallback::onParseObject(const FactoryProduct *object)
	{
		// see BaseObject::parseXML()
	}
	
	void ScriptEventFactoryCallback::onLoadStart(const std::string& filename)
	{
		if (Interpreter::instance().pushNamed("event.loadStart")) {
			Interpreter::instance().pushString(filename);
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}

	void ScriptEventFactoryCallback::onLoadFinish(const std::string& filename)
	{
		if (Interpreter::instance().pushNamed("event.loadFinish")) {
			Interpreter::instance().pushString(filename);
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}

}
