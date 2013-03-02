#ifndef MOON_SCRIPTEVENTNETWORKLISTENER_H
#define MOON_SCRIPTEVENTNETWORKLISTENER_H

#include "Export.h"
#include "moonet/NetworkManager.h"
#include "moonet/NetworkListener.h"

namespace moon {
	
	/// \addtogroup script
	/// @{
	
	/// NetworkListener that runs scripts on network events
	class MOON_EXPORT ScriptEventNetworkListener : public moonet::NetworkListener {
	public:
		virtual void onConnect(moonet::Client *client);
		virtual void onDisconnect(moonet::Client *client);
		virtual void onConnectionFailed();
		virtual void onNoFreeIncomingConnections();
		virtual void onConnectionLost(moonet::Client *client);
		virtual void onPlayerJoin(moonet::Player *player);
		virtual void onPlayerGone(moonet::Player *player);
		virtual bool onChatMessage(const std::string message, moonet::Player *player);
		virtual ~ScriptEventNetworkListener() {}
	};

	/// @}
}

#endif
