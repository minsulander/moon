#include <unittest++/UnitTest++.h>
#include <moonet/NetworkManager.h>
#include <moonet/Client.h>
#include <moonet/Player.h>
#include <iostream>
#include <unistd.h>

#include "TestObject.h"

using namespace moonet;

bool done = false;
TestObject *testobject = NULL;
NetworkManager& netman = NetworkManager::instance();

enum State {
	INIT,
	CONNECTED,
	WAITING,
	CHECKING_CLIENT_OBJECT,
	CHECKING_SERVER_OBJECT,
	CHECKING_OBJECT_DELETED,
	DISCONNECTED,
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

class ClientNetworkListener : public moonet::NetworkListener
{
public:
	virtual void onConnect(Client *client)
	{
		std::cout << "client: connected\n";
		totaltime = 0;
		state = CONNECTED;
	}
	virtual void onDisconnect(Client *client)
	{ 
		std::cout << "client: disconnected\n";
		state = DISCONNECTED;
	}
	virtual void onConnectionLost(Client *client)
	{ 
		std::cout << "client: lost connection\n";
		state = DISCONNECTED;
	}
	virtual void onNewObject(NetworkObject *object) 
	{
		testobject = dynamic_cast<TestObject*>(object);
		if (testobject) {
			std::cout << "client: got server object\n";
		}
	}
	virtual void onDeleteObject(NetworkObject *object)
	{
		if (testobject == object) {
			testobject = NULL;
			std::cout << "client: delete object\n";
		}
	}
	virtual bool onSystemMessage(const short id, const char *data, const short len)
	{
		switch (id) {
			case CREATE_CLIENT_OBJECT:
				std::cout << "client: creating client object\n";
				testobject = new TestObject("ClientObject", 4711);
				testobject->construct();
				break;
			case CHECK_CLIENT_OBJECT:
				state = CHECKING_CLIENT_OBJECT;
				break;
			case CHECK_SERVER_OBJECT:
				state = CHECKING_SERVER_OBJECT;
				break;
			case CHECK_OBJECT_DELETED:
				state = CHECKING_OBJECT_DELETED;
				break;
			case SET_CLIENT_VALUES:
				while (testobject->getOwner() != Client::me())
					update();
				std::cout << "client: setting client values\n";
				testobject->name = "ClientObject";
				testobject->value = 4711;
				break;
			case TAKE_OWNERSHIP:
				std::cout << "client: taking ownership\n";
				testobject->setOwner(Client::me());
				break;
			case GIVE_OWNERSHIP:
				std::cout << "client: giving ownership to server\n";
				testobject->setOwner(NULL);
				break;
			case CLIENT_DISMISSED:
				std::cout << "client: i am dismissed\n";
				state = DONE;
				break;
			default:
				return false;
		}
		return true;
	}	
};

TEST(ClientTest) {
	netman.init(false, new Player("ClientPlayer"), "localhost");
	netman.setObjectFactory(new TestObjectFactory);
	netman.addListener(new ClientNetworkListener);
	
	while (state != DONE && state != DISCONNECTED) {
		switch (state) {
			case CHECKING_CLIENT_OBJECT:
				std::cout << "client: checking client object\n";
				CHECK_EQUAL("ClientObject", testobject->name);
				CHECK_CLOSE(4711, testobject->value, 0.1);
				CHECK_EQUAL(Client::me(), testobject->getOwner());
				netman.sendSystemMessage(CHECK_DONE);
				state = WAITING;
				break;
			case CHECKING_SERVER_OBJECT:
				std::cout << "client: checking server object\n";
				CHECK_EQUAL("ServerObject", testobject->name);
				CHECK_CLOSE(5555, testobject->value, 0.1);
				CHECK(!testobject->getOwner());
				netman.sendSystemMessage(CHECK_DONE);
				state = WAITING;
				break;
			case CHECKING_OBJECT_DELETED:
				CHECK(!testobject);
				netman.sendSystemMessage(CHECK_DONE);
				state = WAITING;
				break;
			default:
				break;
		}
		update();
	}
	
	CHECK(state == DONE);

	netman.shutdown();
}
