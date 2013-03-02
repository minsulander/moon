#include "ScriptEventNetworkListener.h"
#include "Interpreter.h"
#include <mlog/Log.h>

using namespace moonet;
using namespace mlog;

namespace moon {
	
	void ScriptEventNetworkListener::onConnect(Client *client)
	{
		if (Interpreter::instance().pushNamed("event.connect")) {
			Interpreter::instance().pushUserType(client, "moonet::Client");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}

	void ScriptEventNetworkListener::onDisconnect(Client *client)
	{
		if (Interpreter::instance().pushNamed("event.disconnect")) {
			Interpreter::instance().pushUserType(client, "moonet::Client");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void ScriptEventNetworkListener::onConnectionFailed()
	{
		if (Interpreter::instance().pushNamed("event.connectionFailed")) {
			if (Interpreter::instance().pCall(0,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void ScriptEventNetworkListener::onNoFreeIncomingConnections()
	{
		if (Interpreter::instance().pushNamed("event.noFreeIncomingConnections")) {
			if (Interpreter::instance().pCall(0,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void ScriptEventNetworkListener::onConnectionLost(Client *client)
	{
		if (Interpreter::instance().pushNamed("event.connectionLost")) {
			Interpreter::instance().pushUserType(client, "moonet::Client");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void ScriptEventNetworkListener::onPlayerJoin(Player *player)
	{
		if (Interpreter::instance().pushNamed("event.playerJoin")) {
			Interpreter::instance().pushUserType(player, "moonet::Player");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	void ScriptEventNetworkListener::onPlayerGone(Player *player)
	{
		if (Interpreter::instance().pushNamed("event.playerGone")) {
			Interpreter::instance().pushUserType(player, "moonet::Player");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
		}
	}
	
	bool ScriptEventNetworkListener::onChatMessage(const std::string message, Player *player)
	{
		if (Interpreter::instance().pushNamed("event.chat")) {
			Interpreter::instance().pushString(message);
			Interpreter::instance().pushUserType(player, "moonet::Player");
			if (Interpreter::instance().pCall(2,0) != 0)
				dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
			return true;
		}
		return false;
	}

} // namespace
