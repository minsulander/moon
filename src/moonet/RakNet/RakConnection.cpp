#include "RakConnection.h"
#include "RakClient.h"
#include "RakNetworkManager.h"
#include "../Player.h"
#include <mlog/Log.h>
#include <RakNet/StringTable.h>
#include <iostream>

using namespace mlog;
using namespace RakNet;

namespace moonet {

/// This creates a NetworkObject based on its networkObjectName() method..
/// Creates a Client or Player, or calls the user-specified ObjectFactory.
/// To add network objects for creation, make your own ObjectFactory - do not override this..
/// \sa ObjectFactory, NetworkManager::setObjectFactory()
Replica2* Connection::Construct(RakNet::BitStream *replicaData, SystemAddress sender, SerializationType type, ReplicaManager2 *replicaManager, RakNetTime timestamp, NetworkID networkId, bool networkIDCollision)
{
	// In our two Serialize() functions above, we used StringTable to encode the name of the class. Here we read it out, and create the desired object.
	char objectName[128];
	StringTable::Instance()->DecodeString(objectName,128,replicaData);
	dout(6, NETWORK) << "Connection::Construct(" << objectName << ")\n";
	if (networkIDCollision) {
		dout(ERROR, NETWORK) << "Network ID collision while creating " << objectName << " from " << sender.ToString() << "\n";
		return 0;
	}
	if (strcmp(objectName,"Client") == 0)
		return new Client;
	if (strcmp(objectName,"Player") == 0) {
		Player *player = new Player;
		if (NetworkManager::instance().isServer()) {
			player->owner = Client::getClientByAddress(sender);
		}
		player->cloaked = false;
		dout(6, NETWORK) << "  created Player owned by " << (player->owner ? player->owner->toString() : "server") << "\n";
		return player;
	}
	NetworkObject *object = NetworkManager::instance().getObjectFactory()->createNetworkObject(objectName);
	if (object) {
		if (NetworkManager::instance().isServer())
			object->owner = Client::getClientByAddress(sender);
		object->cloaked = false;
		dout(6, NETWORK) << "  created " << object->networkObjectName() << " owned by " << (object->owner ? object->owner->toString() : "server") << "\n";
		object->Deserialize(replicaData, type, sender, timestamp);
	} else
		dout(ERROR, NETWORK) << "Unknown network object '" << objectName << "'\n";
	return object;
}

/// Callback for sorting initial download
void Connection::SortInitialDownload(DataStructures::List<Replica2*>& ordered,
									 DataStructures::List<Replica2*>& initial) {
	for (unsigned int i = 0; i < initial.Size(); i++) {
		unsigned int priority = NetworkManager::instance().getObjectPriority(initial[i]);
		if (priority == 0) {
			ordered.Insert(initial[i]);
			continue;
		}
		int index = 0;
		for (unsigned int j = 0; j < ordered.Size(); j++) {
			if (NetworkManager::instance().getObjectPriority(ordered[j]) < priority)
				break;
			index++;
		}
		ordered.Insert(initial[i], index);
	}
}

/// Callback when we finish downloading all objects from a new connection
/// See Connection_RM2::ReceiveDownload in ReplicaManager2.h for a full explanation of each parameter
void Connection::DeserializeDownloadComplete(RakNet::BitStream *objectData, SystemAddress sender, ReplicaManager2 *replicaManager, RakNetTime timestamp, SerializationType serializationType)
{
	// Since the system is inherently peer to peer, download notifications go both ways, not just server to client.
	// Just ignore download notifications from clients in a client/server app
	//if (isServer==false)
	//	printf("Download complete\n");
	if (!NetworkManager::instance().isServer())
		dout(1, NETWORK) << "Deserialize download complete\n";
	NetworkManager::instance().downloadComplete();
}

/** \class Connection
 From the RakNet examples:<br>
 The most important function to implement is Construct() as this creates your game objects.
 It is designed this way so you can override per-connection behavior in your own game classes
 See Connection_RM2::Construct in ReplicaManager2.h for a full explanation of each parameter
*/

} // namespace moonet
