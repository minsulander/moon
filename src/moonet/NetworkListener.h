#ifndef MOONET_NETWORKLISTENER_H
#define MOONET_NETWORKLISTENER_H

#include "Client.h"
#include "Player.h"
#include "Export.h"
#include <string>

namespace moonet {

/// A listener for network events that can be registered with the NetworkManager.

/// This is a template class. Derive from this and implement the callbacks you want to
/// react to.

class MOONET_EXPORT NetworkListener {
public:

	/// Called when connected to the server (client), or when a new client connects (server)
	virtual void onConnect(Client *client) {}

	/// Called when disconnected from the server (client), or when a client disconnects (server)
	virtual void onDisconnect(Client *client) {}

	/// Called when connecting to the server fails (client only)
	virtual void onConnectionFailed() {}

	/// Called when no more incoming connection "slots" are available (server only)
	virtual void onNoFreeIncomingConnections() {}
	
	/// Called when the connection to the server is lost (client), or when a client connection is lost (server)
	virtual void onConnectionLost(Client *client) {}
	
	/// Called when a new Client is created
	virtual void onClientJoin(Client *client) {}
	
	/// Called when a Client has disconnected/lost connection
	virtual void onClientGone(Client *client) {}
	
	/// Called when a Player has joined the game
	virtual void onPlayerJoin(Player *player) {}

	/// Called when a Player has disconnected/lost connection
	virtual void onPlayerGone(Player *player) {}
	
	/// Called when a new NetworkObject is constructed
	virtual void onNewObject(NetworkObject *object) {}

	/// Called when a NetworkObject is destructed
	virtual void onDeleteObject(NetworkObject *object) {}

	/// Called when a chat message has been received by the NetworkManager
	/// \return true if the message has been displayed
	virtual bool onChatMessage(const std::string message, Player *player) { return false; }
	
	/// Called when a system messages has been received by the NetworkManager
	/// \return true if the message has been handled
	virtual bool onMessage(const short id, const char *data, const short len, const bool broadcast) { return false; }

	/// Called when all NetworkObjects have been downloaded (client only)
	virtual void onDownloadComplete() {}
	
	virtual ~NetworkListener() {}
};

}

#endif
