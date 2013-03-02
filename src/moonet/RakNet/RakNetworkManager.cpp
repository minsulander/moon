#include "RakNetworkManager.h"
#include "RakClient.h"
#include "../Player.h"
#include <mlog/Log.h>
#include <RakNet/RakNetworkFactory.h>
#include <RakNet/StringTable.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakSleep.h>
#include <RakNet/RakNetStatistics.h>
#include <iostream>

using namespace mlog;

namespace moonet {
	
	void NetworkManager::init(const bool server, Player *me, const std::string& peer, const int port)
	{
		iamserver = server;
		dout(1, NETWORK) << "Initializing network " << (server ? "server " : "client ")
		<< (me ? "with player" : "without player") << "\n";
		Player::myPlayer = me;
		SocketDescriptor sd;
		if (iamserver)
			sd.port = port;
		else
			sd.port = 0;
		// The network ID authority is the system that creates the common numerical identifier used to lookup pointers.
		// For client/server this is the server
		// For peer to peer this would be true on every system, and you would also have call NetworkID::peerToPeerMode=true;
		networkIdManager.SetIsNetworkIDAuthority(iamserver);
		// Start RakNet, up to 32 connections if the server
		rakPeer->Startup(iamserver ? 32 : 1,0,&sd,1);
		// Start occasional pinging - without which timestamping wouldn't work
		rakPeer->SetOccasionalPing(true);
		// Register our custom connection factory
		replicaManager.SetConnectionFactory(&connectionFactory);
		if (!objectFactory)
			objectFactory = new ObjectFactory;
		// The server should allow systems to connect. Clients do not need to unless you want to use RakVoice or for some other reason want to transmit directly between systems.
		if (iamserver)
			rakPeer->SetMaximumIncomingConnections(32);
		
		if (!iamserver) {
			rakPeer->Connect(peer.c_str(), port, 0, 0, 0);
			dout(1, NETWORK) << "Connecting to " << peer << ":" << port << "\n";
		} else
			dout(1, NETWORK) << "Accepting connections on port " << port << "\n";
		
		systemAddress = serverAddress = rakPeer->GetExternalID(UNASSIGNED_SYSTEM_ADDRESS);

		if (iamserver && !Client::me() && Player::me()) {
			Client *client = new Client;
			Client::mine = client;
			client->SetReplicaManager(&replicaManager);
			client->setSystemAddress(systemAddress);
			client->setConnected(true);
			client->BroadcastConstruction();
			client->AddAutoSerializeTimer(100);
			Player::me()->setOwner(client);
			dout(3, NETWORK) << "  created server client " << client->toString() << "\n";
		}

		active = true;
	}
	
	void NetworkManager::update(const double dt)
	{
		if (!active || !rakPeer)
			return;
		if (Client::me() && Player::me() && !Player::me()->isConstructed()) {
			dout(6, NETWORK) << "Constructing my player\n";
			Client::me()->setPlayer(Player::me());
			Player::me()->construct();
		}
		Packet *packet;
		for (packet = rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet = rakPeer->Receive())
		{
			switch (packet->data[0])
			{
				case ID_CONNECTION_ATTEMPT_FAILED:
					connected = false;
					dout(0, NETWORK) << "Connection attempt failed\n";
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onConnectionFailed();
					break;
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					dout(0, NETWORK) << "No free incoming connections\n";
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onNoFreeIncomingConnections();
					break;
				case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					systemAddress = rakPeer->GetExternalID(UNASSIGNED_SYSTEM_ADDRESS);
					
					dout(1, NETWORK) << "Connection request accepted\n";
					dout(3, NETWORK) << "  my address is " << systemAddress.ToString() << "\n";
					short unsigned int num = 1;
					rakPeer->GetConnectionList(&serverAddress,&num);
					connected = true;
					
					connectionHistory.push_back(serverAddress);
					rakPeer->Ping(serverAddress);
					
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onConnect(NULL);
				}
					break;
				case ID_NEW_INCOMING_CONNECTION:
					dout(0, NETWORK) << "New incoming connection from " << packet->systemAddress.ToString() << "\n";
					connected = true;
				{
					systemAddress = serverAddress = rakPeer->GetExternalID(packet->systemAddress);
					
					Client *client = new Client;
					client->SetReplicaManager(&replicaManager);
					client->setSystemAddress(packet->systemAddress);
					client->setConnected(true);
					client->BroadcastConstruction();
					client->AddAutoSerializeTimer(100);
					dout(3, NETWORK) << "  created client " << client->toString() << "\n";
					
					connectionHistory.push_back(packet->systemAddress);
					rakPeer->Ping(packet->systemAddress);
					
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onConnect(client);
					
				}				
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					dout(0, NETWORK) << "Disconnect from " << packet->systemAddress.ToString() << "\n";
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onDisconnect(Client::getClientByAddress(packet->systemAddress));
					if (iamserver) {
						Client *client = Client::getClientByAddress(packet->systemAddress);
						if (!client)
							dout(ERROR, NETWORK) << "Disconnect from unknown client with address" << packet->systemAddress.ToString() << "\n";
						else
							client->setConnected(false);
						takeObjectsFromClient(client);
					} else
						shutdown();
					break;
				case ID_CONNECTION_LOST:
					dout(0, NETWORK) << "Connection lost from " << packet->systemAddress.ToString() << "\n";
					for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
						(*i)->onConnectionLost(Client::getClientByAddress(packet->systemAddress));
					if (iamserver) {
						Client *client = Client::getClientByAddress(packet->systemAddress);
						if (!client)
							dout(ERROR, NETWORK) << "Connection lost from unknown client with address" << packet->systemAddress.ToString() << "\n";
						else
							client->setConnected(false);
						takeObjectsFromClient(client);
					} else
						shutdown();
					break;
				default:
					dout(WARN, NETWORK) << "Unknown packet ID " << (int) packet->data[0] << "\n";
			}
			//rakPeer->DeallocatePacket(packet);
			//RakSleep(100);
		}
	}
	
	void NetworkManager::shutdown()
	{
		if (!active)
			return;
		dout(1, NETWORK) << "Shutting down network manager\n";
		connected = false;
		active = false;
		if (rakPeer) {
			rakPeer->Shutdown(100,0);
			//RakNetworkFactory::DestroyRakPeerInterface(rakPeer);
			//rakPeer = NULL;
			for (Client::ClientList::iterator i = Client::clients.begin(); i != Client::clients.end(); i++)
				delete *i;
			Client::clients.clear();
		}
		Player::myPlayer = NULL;
	}
	
	RakNet::ReplicaManager2 *NetworkManager::getReplicaManager()
	{ 
		//if (!connected && !iamserver) 
		//	return NULL; 
		return &replicaManager;
	}
	
	void NetworkManager::setObjectFactory(ObjectFactory *factory)
	{
		if (!factory) {
			dout(ERROR, NETWORK) << "NULL object factory\n";
			/// \todo throw exception on error
			return;
		}
		objectFactory = factory;
	}
	
	void NetworkManager::printClientList()
	{
		std::cout << "clients:";
		for (unsigned int i = 0; i < Client::getNumClients(); i++) {
			Client *client = Client::getClient(i);
			std::cout << " " << client->toString();
		}
		std::cout << "\n";
		for (unsigned int i = 0; i < Client::getNumClients(); i++) {
			Client *client = Client::getClient(i);
			if (client->getPlayer() && client->getPlayer()->getOwner() != client)
				std::cout << "Player for " << client->toString() << " belongs to " <<
				(client->getPlayer()->getOwner() ? client->getPlayer()->getOwner()->toString() : "server") << "\n";
		}
	}
	
	void NetworkManager::chatSend(const std::string& message)
	{
		RakNet::BitStream bs;
		if (Client::me())
			bs.Write(Client::me()->GetNetworkID());
		else
			bs.Write(UNASSIGNED_NETWORK_ID);
		bs.Write((unsigned int) message.length()+1);
		bs.Write(message.c_str(), message.length()+1);
		rakPeer->RPC("NetworkManager::RPC_Chat",&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
	}
	
	void NetworkManager::RPC_Chat(RPCParameters *rpc)
	{
		RakNet::BitStream bs(rpc->input, rpc->numberOfBitsOfData*8, true);
		NetworkID ownerID;
		bs.Read(ownerID);
		Client *sender=(Client*) instance().getObject(ownerID);
		char message[128];
		unsigned int len;
		bs.Read(len);
		bs.Read(message,len);
		
		if (sender) {
			Player *player = sender->getPlayer();
			for (ListenerList::iterator i = instance().listeners.begin(); i != instance().listeners.end(); i++)
				(*i)->onChatMessage(message, player);
		}
		if (instance().isServer()){
			RakNet::BitStream bsout;
			bsout.Write(ownerID);
			bsout.Write(len);
			bsout.Write(message, len);
			instance().rakPeer->RPC("NetworkManager::RPC_Chat",&bsout, HIGH_PRIORITY, RELIABLE_ORDERED, 0, rpc->sender, true, 0, UNASSIGNED_NETWORK_ID, 0);
		}
	}
	
	void NetworkManager::changeOwner(NetworkObject *object, Client *newOwner)
	{
		RakNet::BitStream bs;
		bs.Write(object->GetNetworkID());
		if (newOwner)
			bs.Write(newOwner->GetNetworkID());
		else
			bs.Write(UNASSIGNED_NETWORK_ID);
		rakPeer->RPC("NetworkManager::RPC_ChangeOwner",&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
	}
	
	void NetworkManager::RPC_ChangeOwner(RPCParameters *rpc)
	{
		RakNet::BitStream bs(rpc->input, rpc->numberOfBitsOfData*8, true);
		NetworkID objectID, newOwnerID;
		bs.Read(objectID);
		bs.Read(newOwnerID);
		NetworkObject *object = (NetworkObject*) instance().getObject(objectID);
		Client *newOwner = (Client*) instance().getObject(newOwnerID);
		
		if (!object) {
			dout(WARN, NETWORK) << "Received ownership change request with NULL object or owner\n";
			return;
		}
		dout(3, NETWORK) << "RPC ownership change request " << object->networkObjectName() << " #" << object->GetAllocationNumber() << " -> " << (newOwner ? newOwner->toString() : "server") << "\n";
		bool changed = object->changeOwnership(newOwner);
		if (instance().isServer() && changed) {
			RakNet::BitStream bsout;
			bsout.Write(objectID);
			bsout.Write(newOwnerID);
			instance().rakPeer->RPC("NetworkManager::RPC_ChangeOwner", &bsout, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID, 0);
		}
		
	}
	
	void NetworkManager::sendMessage(const short id, const char *data, const short len, Client *destination)
	{
		RakNet::BitStream bs;
		bs.Write(id);
		if (data && len > 0) {
			bs.Write(len);
			bs.Write(data,len);
		} else
			bs.Write((short)0);
		SystemAddress recipient;
		if (destination) {
			recipient = destination->getSystemAddress();
			bs.Write1();
		} else {
			recipient = UNASSIGNED_SYSTEM_ADDRESS;
			bs.Write0();
		}
		rakPeer->RPC("NetworkManager::RPC_Message",&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, recipient, (destination ? false : true), 0, UNASSIGNED_NETWORK_ID,0);
	}
	
	void NetworkManager::RPC_Message(RPCParameters *rpc)
	{
		RakNet::BitStream bs(rpc->input, rpc->numberOfBitsOfData*8, true);
		short id, len;
		char *data = NULL;
		bs.Read(id);
		bs.Read(len);
		if (len > 0) {
			data = (char*) malloc(len);
			bs.Read(data, len);
		}
		bool broadcast = bs.ReadBit();
		bool handled = false;
		for (ListenerList::iterator i = instance().listeners.begin(); i != instance().listeners.end(); i++)
			if ((*i)->onMessage(id, data, len, broadcast))
				handled = true;
		if (!handled)
			dout(WARN, NETWORK) << "Unhandled system message id " << id << " len " << len << "\n";
		
		if (broadcast && instance().isServer()){
			RakNet::BitStream bsout;
			bsout.Write(id);
			bsout.Write(len);
			if (data)
				bsout.Write(data, len);
			instance().rakPeer->RPC("NetworkManager::RPC_Message",&bsout, HIGH_PRIORITY, RELIABLE_ORDERED, 0, rpc->sender, true, 0, UNASSIGNED_NETWORK_ID, 0);
		}
		
		if (data)
			free(data);	
	}
	
	void NetworkManager::sendClientState(const ClientState state)
	{
		RakNet::BitStream bs;
		bs.Write(state);
		rakPeer->RPC("NetworkManager::RPC_ClientState", &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
		dout(4, NETWORK) << "Sending client state " << state << "\n";
	}

	void NetworkManager::RPC_ClientState(RPCParameters *rpc)
	{
		RakNet::BitStream bs(rpc->input, rpc->numberOfBitsOfData*8, true);
		ClientState state;
		bs.Read(state);
		Client *sender = Client::getClientByAddress(rpc->sender);
		if (!sender)
			dout(ERROR, NETWORK) << "Received client state from unknown client address " << rpc->sender.ToString() << "\n";
		else {
			sender->setState(state);
			dout(4, NETWORK) << "Client " << sender->toString() << " changed to state " << state << "\n";
		}
	}
	
	void NetworkManager::addListener(NetworkListener *listener)
	{
		if (!listener)
			return;
		listeners.push_back(listener);
	}
	
	void NetworkManager::removeListener(NetworkListener *listener)
	{
		if (!listener)
			return;
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			if (*i == listener) {
				listeners.erase(i);
				break;
			}
	}
	
	void NetworkManager::registerClient(Client *client)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onClientJoin(client);
	}
	
	void NetworkManager::unregisterClient(Client *client)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onClientGone(client);
	}
	
	void NetworkManager::registerPlayer(Player *player)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onPlayerJoin(player);
	}
	
	void NetworkManager::unregisterPlayer(Player *player)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onPlayerGone(player);
	}
	
	void NetworkManager::downloadComplete()
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onDownloadComplete();
	}
	
	void NetworkManager::registerObject(NetworkObject *object)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onNewObject(object);
	}
	
	void NetworkManager::unregisterObject(NetworkObject *object)
	{
		for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); i++)
			(*i)->onDeleteObject(object);
	}
	
	void NetworkManager::printStatistics()
	{
		if (statisticsLevel <= 0)
			return;
		dout(INFO, NETWORK) << "Ping times (average, low):\n";
		for (unsigned int i = 0; i < connectionHistory.size(); i++) {
			dout(INFO, NETWORK) << connectionHistory[i].ToString() << ": " << rakPeer->GetAveragePing(connectionHistory[i])
				<< " " << rakPeer->GetLowestPing(connectionHistory[i]) << "\n";
		}
		if (statisticsLevel >= 2) {
			dout(INFO, NETWORK) << "Serialize count, average size:\n";
			for (NetworkObject::PacketStatsMap::iterator i = NetworkObject::sendcount.begin(); i != NetworkObject::sendcount.end(); i++) {
				unsigned int size = NetworkObject::packetsize[i->first] / i->second;
				dout(INFO, NETWORK) << "  " << i->first << " " << i->second << " " << size << "\n";
			}
			dout(INFO, NETWORK) << "Deserialize count, average time:\n";
			for (NetworkObject::PacketStatsMap::iterator i = NetworkObject::recvcount.begin(); i != NetworkObject::recvcount.end(); i++) {
				unsigned int time = NetworkObject::packettime[i->first] / i->second;
				dout(INFO, NETWORK) << "  " << i->first << " " << i->second << " " << time << "\n";
			}
		}
		if (statisticsLevel >= 3) {
			dout(INFO, NETWORK) << "\nRakNet statistics:\n";
			char str[65536];
			for (unsigned int i = 0; i < connectionHistory.size(); i++) {
				if (!rakPeer->GetStatistics(connectionHistory[i]))
					continue;
				StatisticsToString(rakPeer->GetStatistics(connectionHistory[i]), str, statisticsLevel-2);
				dout(INFO, NETWORK) << connectionHistory[i].ToString() << ":\n" << str << "\n";
			}
		}
		statisticsLevel = 0;
	}
	
	unsigned int NetworkManager::getObjectPriority(const RakNet::Replica2 *object)
	{
		return priorities[object];
	}
	
	void NetworkManager::setObjectPriority(const RakNet::Replica2 *object, const unsigned int priority)
	{
		priorities[object] = priority;
	}
	
	/// \param seconds interval for regular (or "incremental" if used that way) serializations
	/// \param fullseconds interval for full serializations
	/// \note If \a fullseconds < \a seconds, no "incremental" serializations will be performed (all will be "full").
	/// \see NetworkObject::setSerializationInterval() for setting intervals on individual objects
	void NetworkManager::setDefaultSerializationInterval(const float seconds, const float fullseconds)
	{
		defaultSerializationInterval = seconds;
		defaultFullSerializationInterval = fullseconds;
	}
	
	NetworkManager::NetworkManager()
	:	active(false),
		iamserver(false),
		connected(false),
		rakPeer(NULL),
		objectFactory(NULL),
		statisticsLevel(0),
		defaultSerializationInterval(0.1f),
		defaultFullSerializationInterval(0.5f)
	{
		rakPeer = RakNetworkFactory::GetRakPeerInterface();
		rakPeer->AttachPlugin(&replicaManager);
		rakPeer->SetNetworkIDManager(&networkIdManager);
		networkIdManager.SetIsNetworkIDAuthority(false);
		
		RakNet::StringTable::Instance()->AddString("Player", false);
		
		REGISTER_STATIC_RPC(rakPeer, NetworkManager::RPC_Chat);
		REGISTER_STATIC_RPC(rakPeer, NetworkManager::RPC_ChangeOwner);
		REGISTER_STATIC_RPC(rakPeer, NetworkManager::RPC_Message);
		REGISTER_STATIC_RPC(rakPeer, NetworkManager::RPC_ClientState);
	}
	
	NetworkManager::~NetworkManager()
	{
		shutdown();
		if (objectFactory)
			delete objectFactory;
	}
	
	void NetworkManager::takeObjectsFromClient(Client *client) {
		// Take ownership of objects that belonged to this client	
		for (unsigned int i = 0; i < replicaManager.GetReplicaCount(); i++) {
			NetworkObject *object = dynamic_cast<NetworkObject*> (replicaManager.GetReplicaAtIndex(i));
			if (!object)
				continue;
			if (object->getOwner() == client) {
				object->setOwner(NULL);
			}
		}
	}
	NetworkManager& NetworkManager::instance()
	{
		if (!instanceptr)
			instanceptr = new NetworkManager;
		return *instanceptr;
	}
	
	NetworkManager *NetworkManager::instanceptr = NULL;
	
} // namespace moonet
