#ifndef MOONET_NONETWORKMANAGER_H
#define MOONET_NONETWORKMANAGER_H

#include "../NetworkListener.h"
#include "../ObjectFactory.h"
#include <vector>

namespace moonet {

class Client;
class Player;
class NetworkListener;
class NetworkObject;

class NetworkManager {
public:

	void init(const bool server, Player *me = NULL, const std::string& peer = "");
	void update(const double dt);
	void shutdown();
	
	bool isServer() { return iamserver; }
	bool isClient() { return !iamserver; }
	bool isConnected() { return true; }
	bool isActive() { return active; }
	void setObjectFactory(ObjectFactory* factory);
	ObjectFactory* getObjectFactory() { return objectFactory; }
	void printClientList();
	
	void chatSend(const std::string& message);
	void chatReceive(const std::string message, Player *player);
	
	void addListener(NetworkListener* listener);
	void removeListener(NetworkListener * listener);
	void registerClient(Client *client);
	void unregisterClient(Client *client);
	void registerPlayer(Player *player);
	void unregisterPlayer(Player *player);
	void downloadComplete();
	void registerObject(NetworkObject *object);
	void unregisterObject(NetworkObject *object);
	
	void doStatistics(int i) { doingStatistics = true; }
	bool isDoingStatistics() { return doingStatistics; }
	void printStatistics();
	
	unsigned int getObjectPriority(void* object) { return 0; }
	void setObjectPriority(void* object, const unsigned int priority) {}
	
	void sendMessage(const short id, const char *data = NULL, const short len = 0, Client *destination = NULL)  {}
	NetworkObject *getObject(const NetworkID id) { return NULL; }
	
	float getDefaultSerializationInterval() { return 0; }
	float getDefaultFullSerializationInterval() { return 0; }
	void setDefaultSerializationInterval(const float seconds, const float fullseconds = 0) {}

	static NetworkManager& instance();
protected:
	NetworkManager(); // pure singleton
	virtual ~NetworkManager();
	
	bool iamserver, connected, active;
	int port;
	ObjectFactory *objectFactory;
	Player *myPlayer;
	Client *myClient;
	bool doingStatistics;
	
	typedef std::vector< NetworkListener* > ListenerList;
	ListenerList listeners;
	
	static NetworkManager *instanceptr;
};

}

#endif
