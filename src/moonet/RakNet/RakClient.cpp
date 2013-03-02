#include "RakClient.h"
#include "RakNetworkManager.h"
#include <RakNet/StringTable.h>
#include <RakNet/StringCompressor.h>
#include <mlog/Log.h>
#include <iostream>
#include <sstream>

using namespace RakNet;
using namespace mlog;

namespace moonet {
	
	Client::Client()
	:	player(NULL),
		systemAddress(UNASSIGNED_SYSTEM_ADDRESS),
		registered(false),
		connected(false),
		state(CLIENT_INITIAL)
	{
		clients.push_back(this);
	}
	
	Client::~Client()
	{
		if (registered)
			NetworkManager::instance().unregisterClient(this);
		if (player) {
			//player->BroadcastDestruction();
			delete player;
		}
		if (mine == this)
			mine = NULL;
	}
	
	std::string Client::toString() const
	{
		std::stringstream ss;
		ss << systemAddress.ToString();
		if (player)
			ss << "(" << player->getName() << ")";
		if (!connected)
			ss << "(!)";
		return ss.str();
	}
	
	void Client::setConnected(const bool value)
	{
		connected = value;
		if (!connected && player != NULL) {
			delete player;
			player = NULL;
		}
	}
	
	// Implemented member of Replica2: This function encodes the identifier for this class, so the class factory can create it
	bool Client::SerializeConstruction(RakNet::BitStream *bitStream, SerializationContext *serializationContext)
	{
		StringTable::Instance()->EncodeString("Client",128,bitStream);
		return true;
	}
	// Implemented member of Replica2: Write the data members of this class. ReplicaManager2 works with pointers as well as any other kind of data
	bool Client::Serialize(RakNet::BitStream *bitStream, SerializationContext *serializationContext)
	{
		if (player)
			bitStream->Write(player->GetNetworkID());
		else
			bitStream->Write(UNASSIGNED_NETWORK_ID);
		bitStream->Write(systemAddress);
		bitStream->Write(state);
		if (NetworkManager::instance().isServer()) {
			if (systemAddress == serializationContext->recipientAddress)
				bitStream->Write(true);
			else
				bitStream->Write(false);
		}
		return true;
	}
	// Implemented member of Replica2: Read what I wrote in Serialize() immediately above
	void Client::Deserialize(RakNet::BitStream *bitStream, SerializationType serializationType, SystemAddress sender, RakNetTime timestamp)
	{
		NetworkID playerNetworkId;
		bitStream->Read(playerNetworkId);
		if (playerNetworkId != UNASSIGNED_NETWORK_ID)
			player=(Player*) NetworkManager::instance().getObject(playerNetworkId);
		bitStream->Read(systemAddress);
		bitStream->Read(state);
		if (!NetworkManager::instance().isServer()) {
			bool isMine = false;
			bitStream->Read(isMine);
			if (isMine) {
				if (mine == NULL)
					dout(3, NETWORK) << "My client: " << toString() << "\n";
				mine = this;
				if (systemAddress != NetworkManager::instance().getSystemAddress())
					dout(WARN, NETWORK) << "Client " << systemAddress.ToString() << " is mine, but my address is "
					<< NetworkManager::instance().getSystemAddress().ToString() << " - endian troubles?\n";
			}
		}
		if (player)
			player->setOwner(this);
		if (!registered && Client::mine != this) {
			NetworkManager::instance().registerClient(this);
			dout(3, NETWORK) << "New client " << systemAddress.ToString() << "\n";
			registered = true;
		}
	}
	
	Client *Client::getClientByAddress(const SystemAddress& address)
	{
		for (ClientList::iterator i = clients.begin(); i != clients.end(); i++) {
			if ((*i)->systemAddress == address)
				return *i;
		}
		return NULL;
	}
	
	void Client::deleteClientByAddress(const SystemAddress& address)
	{
		for (ClientList::iterator i = clients.begin(); i != clients.end(); i++) {
			if ((*i)->systemAddress == address) {
				delete *i;
				clients.erase(i);
				break;
			}
		}
	}
	
	bool Client::isStillAround(Client *client)
	{
		bool found = false;
		for (ClientList::iterator i = clients.begin(); i != clients.end(); i++) {
			if (*i == client && client->isConnected())
				found = true;
		}
		return found;
	}
	
	ClientState Client::getMinimumClientState()
	{
		if (clients.size() == 0)
			return CLIENT_INITIAL;
		ClientState minState = NUM_CLIENT_STATES;
		for (ClientList::iterator i = clients.begin(); i != clients.end(); i++) {
			std::cout << "me " << (Client::me() ? Client::me()->toString() : "server") << " " << (*i)->toString() << " state " << (*i)->getState() << "\n";
			if ((*i)->getState() < minState)
				minState = (*i)->getState();
		}
		return minState;
	}
	
	Client *Client::mine = NULL;
	Client::ClientList Client::clients;
	
	/** \class Client
	 One client instance is created on the server per new connection. The server can also have its
	 own client (if "hosting" a game instead of being a "dedicated" server). Every NetworkObject has
	 a Client as its owner. A client may or may not have a Player, depending on if it has yet joined
	 the game or not.
	 
	 \todo This could just as well be a NetworkObject, no?
	 */
}
