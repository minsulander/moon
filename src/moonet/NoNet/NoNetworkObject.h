#ifndef MOONET_NONETWORKOBJECT_H
#define MOONET_NONETWORKOBJECT_H

#include <string>

typedef unsigned int NetworkID;

namespace moonet {

class Client;
	
class NetworkObject {
public:
	NetworkObject();
	
	bool setOwner(Client *client) { owner = client; return true; }
	Client *getOwner() const { return owner; }
	virtual const std::string networkObjectName() const { return "NetworkObject"; }
	virtual void construct() { constructed = true; };
	bool isConstructed() const { return constructed; }
	virtual void onConstruction() {}
	virtual void setCloaked(const bool value) { cloaked = value; }
	bool isCloaked() const { return cloaked; }
	void setSerializationInterval(const float seconds, const float fullseconds = 0) {}
	float getSerializationInterval() const { return 0.f; }
	float getFullSerializationInterval() const { return 0.f; }
	
	virtual bool serialize() {};
	virtual void deserialize() {};
	virtual void setVisibility(const bool visible) {}
	virtual bool isVisibleToClient(Client *client) const { return false; }
	virtual void broadcastFullSerialize() {}
	
	NetworkID GetNetworkID() { return 0; }
	bool isRemote() const { return false; }
	
protected:
	void *bitstream;
	double getAverageTimeDiff() { return 0.0; }
private:	
	Client *owner;
	bool cloaked, constructed;
};

}

#endif
