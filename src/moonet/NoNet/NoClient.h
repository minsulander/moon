#ifndef MOONET_NOCLIENT_H
#define MOONET_NOCLIENT_H

#include "../Player.h"
#include "../NetworkManager.h"

namespace moonet {

	enum ClientState {
		CLIENT_INITIAL,
		CLIENT_READY,
		NUM_CLIENT_STATES
	};
	
	class Client
	{
	public:
		Client();
		
		Player *getPlayer() { return player; }
		void setPlayer(Player *newplayer) { player = newplayer; }
		std::string toString() { return "NoNetClient"; }
		bool isConnected() { if (mine == this) return true; return false; }
		ClientState getState() const { if (mine == this) return CLIENT_READY; return CLIENT_INITIAL; }
		
		static Client *me() { return mine; }
		static unsigned int getNumClients() { return (mine ? 1 : 0); }
		static Client *getClient(unsigned int index) { return mine; }
		static bool isStillAround(Client *client);
		static ClientState getMinimumClientState() { return CLIENT_READY; }
	
	protected:
		Player *player;
		
		static Client *mine;
		friend class NetworkManager;
	};
	
}

#endif

