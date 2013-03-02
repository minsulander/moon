#include <unittest++/UnitTest++.h>
#include <moonet/NetworkManager.h>
#include <moonet/Client.h>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "TestObject.h"

using namespace moonet;

bool done = false;
Client *testclient = NULL;
TestObject *testobject = NULL;
NetworkManager& netman = NetworkManager::instance();
bool check_done = false;

enum State {
	INIT,
	CONNECTED,
	DISCONNECTED,
	CHECKING_CLIENT_OBJECT,
	CHECKING_SERVER_OBJECT,
	DONE
};
State state;

class TimeOutException : public std::exception
{
	public:
	const char* what() { return "timeout"; }
};

float totaltime = 0;
void update() {
	netman.update(0.01);
	usleep(10000);
	totaltime += 0.01;
	if (totaltime > 10)
		throw TimeOutException(); // a quick 'n easy way to get out and still have test report
}

void waitForCheckDone() {
	while (!check_done)
		update();
	check_done = false;
}

class ServerNetworkListener : public moonet::NetworkListener
{
public:
	virtual void onConnect(Client *client)
	{
		std::cout << "server: client " << client->toString() << " connected\n";
		testclient = client;
		totaltime = 0;
		state = CONNECTED;
	}
	virtual void onDisconnect(Client *client)
	{ 
		if (state != DONE) {
			std::cout << "server: client " << client->toString() << " disconnected\n";
			state = DISCONNECTED;
		}
	}
	virtual void onConnectionLost(Client *client)
	{
		std::cout << "server: lost connection\n";
		state = DISCONNECTED;
	}
	virtual void onPlayerJoin(Player *player)
	{
		std::cout << "server: player " << player->getName() << " joined\n";
		netman.sendSystemMessage(CREATE_CLIENT_OBJECT);
	}
	virtual void onNewObject(NetworkObject *object) 
	{
		testobject = dynamic_cast<TestObject*>(object);
		if (testobject && testobject->name == "ClientObject") {
			std::cout << "server: got client object\n";
			state = CHECKING_CLIENT_OBJECT;
		}
	}
	virtual void onDeleteObject(NetworkObject *object)
	{
		if (testobject == object) {
			testobject = NULL;
			std::cout << "server: delete object\n";
		}
	}
	virtual bool onSystemMessage(const short id, const char *data, const short len)
	{
		switch (id) {
			case CHECK_DONE:
				check_done = true;
				break;
			default:
				return false;
		}
		return true;
	}
	
};

TEST(ServerTest) {
	netman.init(true);
	netman.setObjectFactory(new TestObjectFactory);
	netman.addListener(new ServerNetworkListener);
	netman.doStatistics();
	
	while (state != DONE && state != DISCONNECTED) {
		switch (state) {
			case CHECKING_CLIENT_OBJECT:
				CHECK_EQUAL("ClientObject", testobject->name);
				CHECK_CLOSE(4711, testobject->value, 0.1);
				CHECK_EQUAL(testclient, testobject->getOwner());
				// Try changing a bunch of stuff (shouldn't be reflected on client because we're not the owner)
				testobject->name = "blaj";
				testobject->value = 76314;
				update();
				netman.sendSystemMessage(CHECK_CLIENT_OBJECT);
				waitForCheckDone();
				// Take ownership and change values
				std::cout << "server: taking it and changing stuff\n";
				testobject->name = "ServerObject";
				testobject->value = 5555;
				testobject->setOwner(NULL);
				update();
				netman.sendSystemMessage(CHECK_SERVER_OBJECT);
				waitForCheckDone();
				// Delete it
				std::cout << "server: deleting it\n";
				delete testobject;
				update();
				netman.sendSystemMessage(CHECK_OBJECT_DELETED);
				waitForCheckDone();
				state = CHECKING_SERVER_OBJECT;
				break;
			case CHECKING_SERVER_OBJECT:
				std::cout << "server: create server object\n";
				testobject = new TestObject("ServerObject", 5555);
				testobject->construct();
				update();
				netman.sendSystemMessage(CHECK_SERVER_OBJECT);
				waitForCheckDone();
				// Server gives ownership to client
				std::cout << "server: giving it to client\n";
				testobject->setOwner(testclient);
				update();
				netman.sendSystemMessage(SET_CLIENT_VALUES);
				while (testobject->value == 5555)
					update();
				CHECK_EQUAL("ClientObject", testobject->name);
				CHECK_CLOSE(4711, testobject->value, 0.1);
				CHECK_EQUAL(testclient, testobject->getOwner());				
				netman.sendSystemMessage(CHECK_CLIENT_OBJECT);
				waitForCheckDone();
				// Client gives ownership to server
				std::cout << "server: taking it from client\n";
				netman.sendSystemMessage(GIVE_OWNERSHIP);
				while (testobject->getOwner())
					update();
				testobject->name = "ServerObject";
				testobject->value = 5555;
				testobject->BroadcastSerialize(); update(); // enforce an update now
				netman.sendSystemMessage(CHECK_SERVER_OBJECT);
				waitForCheckDone();
				// Client takes ownership from server
				netman.sendSystemMessage(TAKE_OWNERSHIP);
				while (!testobject->getOwner())
					update();
				CHECK_EQUAL(testclient, testobject->getOwner());
				netman.sendSystemMessage(SET_CLIENT_VALUES);
				while (testobject->value == 5555)
					update();
				CHECK_EQUAL("ClientObject", testobject->name);
				CHECK_CLOSE(4711, testobject->value, 0.1);
				CHECK_EQUAL(testclient, testobject->getOwner());				
				netman.sendSystemMessage(CHECK_CLIENT_OBJECT);
				waitForCheckDone();
				state = DONE;
				break;
			default:
				break;
		}
		update();
	}
	
	CHECK_EQUAL(DONE, state);
		
	netman.sendSystemMessage(CLIENT_DISMISSED);
	update();
	
	netman.printStatistics();

	netman.shutdown();
}

/// \todo Add tests where server has client (not dedicated) and ownership change is not allowed etc..

