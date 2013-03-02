#include "NoNetworkManager.h"
#include "NoClient.h"
#include "../Player.h"
#include <mlog/Log.h>
#include <iostream>

using namespace mlog;

namespace moonet {

void NetworkManager::init(const bool server, Player *me, const std::string& peer)
{
	iamserver = server;
	dout(1, NETWORK) << "Initializing network " << (server ? "server " : "client ")
						<< (me ? "with player" : "without player") << "\n";
	myPlayer = me;
	if (myPlayer) {
		myClient = new Client;
		myClient->setPlayer(myPlayer);
		myPlayer->setOwner(myClient);
	}
	if (!objectFactory)
		objectFactory = new ObjectFactory;
	connected = true;
	active = true;
}

void NetworkManager::update(const double dt)
{
	return;
}

void NetworkManager::shutdown()
{
	std::cout << "Shutting down network\n";
	connected = false;
	if (myPlayer)
		delete myPlayer;
	if (myClient)
		delete myClient;
	active = false;
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
}

void NetworkManager::chatSend(const std::string& message)
{
	dout(1, NETWORK) << "chatSend " << message << "\n";
}

void NetworkManager::chatReceive(const std::string message, Player *player)
{
	dout(1, NETWORK) << "chatReceive " << message << "\n";
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
}
	
	

NetworkManager::NetworkManager()
:	iamserver(false),
	connected(false),
	myPlayer(NULL),
	myClient(NULL),
	objectFactory(NULL)
{
}

NetworkManager::~NetworkManager()
{
	shutdown();
	if (objectFactory)
		delete objectFactory;
}

NetworkManager& NetworkManager::instance()
{
	if (!instanceptr)
		instanceptr = new NetworkManager;
	return *instanceptr;
}

NetworkManager *NetworkManager::instanceptr = NULL;

} // namespace moonet
