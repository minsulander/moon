#ifndef MOONET_TESTOBJECT_H
#define MOONET_TESTOBJECT_H

#include <moonet/NetworkObject.h>
#include <moonet/ObjectFactory.h>
#include <string>

class TestObject : public moonet::NetworkObject {
public:
	TestObject(const std::string& name = "new", const float value = 0);
	
	virtual const char* objectName() { return "TestObject"; }
	virtual bool setOwner(moonet::Client *newOwner);
	virtual bool serialize();
	virtual void deserialize(const double timediff = 0);

	std::string name;
	float value;
	bool allowOwnerChange;
	bool visible;
};

class TestObjectFactory : public moonet::ObjectFactory {
public:
	moonet::NetworkObject *create(const std::string& objectName)
	{
		if (objectName == "TestObject")
			return new TestObject;
		return NULL;
	}
};

enum TestSystemMessage {
	CREATE_CLIENT_OBJECT,
	CHECK_CLIENT_OBJECT,
	CHECK_SERVER_OBJECT,
	CHECK_OBJECT_DELETED,
	SET_CLIENT_VALUES,
	TAKE_OWNERSHIP,
	GIVE_OWNERSHIP,
	CHECK_DONE,
	CLIENT_DISMISSED
};

#endif
