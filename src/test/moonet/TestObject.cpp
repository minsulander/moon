#include "TestObject.h"
#include <moonet/NetworkManager.h>
#include <RakNet/StringCompressor.h>
#include <iostream>
using namespace moonet;

TestObject::TestObject(const std::string& nname, const float nvalue)
:	NetworkObject(),
	name(nname),
	value(nvalue),
	allowOwnerChange(true)
{
}

bool TestObject::setOwner(moonet::Client *newOwner)
{
	if (moonet::NetworkManager::instance().isServer() && !allowOwnerChange) {
		NetworkObject::setOwner(NULL);
		return false;
	}
	return NetworkObject::setOwner(newOwner);
}

bool TestObject::serialize()
{
	if (!NetworkObject::serialize())
		return false;
#ifdef MOONET_USE_RAKNET
	StringCompressor::Instance()->EncodeString(name.c_str(),name.size()+1,bitstream);
	bitstream->Write(value);
#endif
	return true;
}

void TestObject::deserialize(const double timediff)
{
	NetworkObject::deserialize();
#ifdef MOONET_USE_RAKNET
	char str[128];
	StringCompressor::Instance()->DecodeString(str,sizeof(str),bitstream);
	name = str;
	bitstream->Read(value);
#endif
}
