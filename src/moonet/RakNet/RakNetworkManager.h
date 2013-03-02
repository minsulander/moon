#ifndef MOONET_RAKNETWORKMANAGER_H
#define MOONET_RAKNETWORKMANAGER_H

#undef __BITSTREAM_NATIVE_END
#ifdef _MSC_VER
#	pragma warning(disable:4251)
#endif

#include "RakClient.h"
#include "RakConnection.h"
#include "../NetworkListener.h"
#include "../ObjectFactory.h"
#include "../Export.h"
#include <RakNet/RakPeerInterface.h>
#include <RakNet/ReplicaManager2.h>
#include <RakNet/NetworkIDManager.h>
#include <vector>

#define MOONET_DEFAULT_PORT 53728

namespace moonet {
	
	class Client;
	class Player;
	class NetworkObject;
	
	/// \brief Application-level singleton class used for things such as connecting etc..
	/// \ingroup net
	class MOONET_EXPORT NetworkManager {
	public:
		/// Set up a connection as server or client, with or without player
		void init(const bool server, Player *me = NULL, const std::string& peer = "", const int port = MOONET_DEFAULT_PORT);
		/// "Main-loop" method that sends/receives packets and reacts to it
		void update(const double dt);
		/// Disconnect and clean-up
		void shutdown();
		
		bool isActive() { return active; }
		bool isServer() { return iamserver; }
		bool isClient() { return !iamserver || Client::me() != NULL; }
		bool isConnected() { return connected; }
		/// Get RakNet system address of ourselves
		const SystemAddress& getSystemAddress() const { return systemAddress; }
		/// Get RakNet system address of the server
		const SystemAddress& getServerAddress() const { return serverAddress; }
		RakNet::ReplicaManager2 *getReplicaManager();
		/// Set ObjectFactory to use for creating new NetworkObjects (except Client and Player)
		void setObjectFactory(ObjectFactory* factory);
		/// Get current ObjectFactory
		ObjectFactory* getObjectFactory() { return objectFactory; }
		/// Get an object based on its RakNet NetworkID
		void* getObject(const NetworkID& id) { return networkIdManager.GET_OBJECT_FROM_ID(id); }
		void printClientList();
		
		/// Send a chat message to all connected clients
		void chatSend(const std::string& message);
		/// Static RPC method for receiving a chat message
		static void RPC_Chat(RPCParameters *rpc);
		
		/// Request a NetworkObject ownership change using RPC
		void changeOwner(NetworkObject *object, Client *newOwner);
		/// Static RPC method for ownership change
		static void RPC_ChangeOwner(RPCParameters *rpc);
		
		/// Send a "system message" (virtually anything) to all clients on the network
		void sendMessage(const short id, const char *data = NULL, const short len = 0, Client *destination = NULL);
		/// Static RPC method for "system messages"
		static void RPC_Message(RPCParameters *rpc);
		
		/// Tell server about our client state
		void sendClientState(const ClientState state);
		/// Static RPC method for client state
		static void RPC_ClientState(RPCParameters *rpc);
		
		/// Add a NetworkListener
		void addListener(NetworkListener* listener);
		/// Remove a NetworkListener
		void removeListener(NetworkListener * listener);
		
		/// \todo is there a better way to notify listeners than having these register callbacks?
		
		/// Callback used by Client, so that NetworkListeners can be notified
		void registerClient(Client *client);
		/// Callback used by Client, so that NetworkListeners can be notified
		void unregisterClient(Client *client);
		/// Callback used by Player, so that NetworkListeners can be notified
		void registerPlayer(Player *player);
		/// Callback used by Player, so that NetworkListeners can be notified
		void unregisterPlayer(Player *player);
		/// Callback used by Connection, so that NetworkListeners can be notified
		void downloadComplete();
		/// Callback used by NetworkObject, so that NetworkListeners can be notified
		void registerObject(NetworkObject *object);
		/// Callback used by NetworkObject, so that NetworkListeners can be notified
		void unregisterObject(NetworkObject *object);
		
		/// Do packet size/timing statistics for NetworkObjects
		void doStatistics(int level = 1) { statisticsLevel = level; }
		bool isDoingStatistics() { return statisticsLevel > 0; }
		/// Print the NetworkObject statistics, typically called before the application quits
		void printStatistics();
		
		/// Get object ordering priority (used for initial download ordering)
		unsigned int getObjectPriority(const RakNet::Replica2* object);
		/// Set object ordering priority (used for initial download ordering)
		void setObjectPriority(const RakNet::Replica2* object, const unsigned int priority);
		
		/// Get default serialization (network update) interval
		float getDefaultSerializationInterval() { return defaultSerializationInterval; }
		/// Get default full serialization (network update) interval
		float getDefaultFullSerializationInterval() { return defaultFullSerializationInterval; }
		/// Set default serialization (network update) intervals
		void setDefaultSerializationInterval(const float seconds, const float fullseconds = 0);
		
		static NetworkManager& instance();
	protected:
		NetworkManager(); // pure singleton
		virtual ~NetworkManager();
		
		void takeObjectsFromClient(Client *client);
		
		bool active, iamserver, connected;
		NetworkIDManager networkIdManager;
		RakNet::ReplicaManager2 replicaManager;
		RakPeerInterface *rakPeer;
		SystemAddress systemAddress, serverAddress;
		ConnectionFactory connectionFactory;
		ObjectFactory *objectFactory;
		Player *myPlayer;
		int statisticsLevel;
		float defaultSerializationInterval, defaultFullSerializationInterval;
		
		typedef std::map< const RakNet::Replica2*, unsigned int> PriorityMap;
		PriorityMap priorities;
		
		typedef std::vector< NetworkListener* > ListenerList;
		ListenerList listeners;
		
		std::vector<SystemAddress> connectionHistory;
		
		static NetworkManager *instanceptr;
	};
	
}

#endif
