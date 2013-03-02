#include "NetworkGame.h"
#include "ObjectFactory.h"
#include "mlog/Log.h"

using namespace mlog;
using namespace moonet;

namespace moon {
	
	REGISTER_Object(moon, NetworkGame);
	
	NetworkGame::NetworkGame()
	:	FactoryProduct(),
		NetworkObject()
	{
		setSerializationInterval(0.5, 5.0);
	}
	
	NetworkGame::NetworkGame(const NetworkGame& other, const osg::CopyOp& copyop)
	:	FactoryProduct(other),
		NetworkObject(other)
	{
	}
	
	void NetworkGame::parseXML(const TiXmlElement *element)
	{
	}
	
	void NetworkGame::writeXML(TiXmlElement *element) const
	{
	}
	
	bool NetworkGame::serialize(const bool full)
	{
#ifdef MOONET_USE_RAKNET
		// Write full data (name, scenario etc) at larger intervals
		if (full) {
			StringCompressor::Instance()->EncodeString(getName().c_str(), getName().size()+1, bitstream);
			StringCompressor::Instance()->EncodeString(scenarioName.c_str(), scenarioName.size()+1, bitstream);
		}
		dout(5, NETWORK) << "Send game time " << gametime << "\n";
		bitstream->Write(gametime);
#endif
		return true;
	}
	
	void NetworkGame::deserialize(const bool full, const double timediff)
	{
#ifdef MOONET_USE_RAKNET
		char str[128];
		if (full) {
			StringCompressor::Instance()->DecodeString(str, sizeof(str), bitstream);
			setName(str);
			StringCompressor::Instance()->DecodeString(str, sizeof(str), bitstream);
			scenarioName = str;
		}
		bitstream->Read(gametime);
		dout(5, NETWORK) << "Receive game time " << gametime << " + " << timediff << " = " << gametime + timediff << "\n";
		gametime += timediff;
		for (ListenerList::iterator it = listeners.begin(); it != listeners.end(); it++)
			(*it)->updateNetworkGame(this, full);
#endif
	}
	
	void NetworkGame::registerListener(NetworkGameListener *listener)
	{
		if (!listener) return;
		listeners.push_back(listener);
	}
	
	void NetworkGame::unregisterListener(NetworkGameListener *listener)
	{
		for (ListenerList::iterator it = listeners.begin(); it != listeners.end(); it++) {
			if (*it == listener) {
				listeners.erase(it);
				return;
			}
		}
	}
	
	NetworkGame::ListenerList NetworkGame::listeners;
	
}
