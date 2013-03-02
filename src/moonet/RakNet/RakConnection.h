#ifndef MOONET_RAKCONNECTION_H
#define MOONET_RAKCONNECTION_H

#undef __BITSTREAM_NATIVE_END
#ifdef _MSC_VER
#	pragma warning(disable:4275)
#endif

#include "../Export.h"
#include <RakNet/ReplicaManager2.h>

namespace moonet {

/// One instance of Connection_RM2 is implicitly created per connection that uses ReplicaManager2.
class MOONET_EXPORT Connection : public RakNet::Connection_RM2
{
	// Callback used to create objects
	// See Connection_RM2::Construct in ReplicaManager2.h for a full explanation of each parameter
	RakNet::Replica2* Construct(RakNet::BitStream *replicaData, SystemAddress sender, RakNet::SerializationType type, RakNet::ReplicaManager2 *replicaManager, RakNetTime timestamp, NetworkID networkId, bool networkIDCollision);

	// Callback for sorting initial download
	virtual void SortInitialDownload(DataStructures::List<RakNet::Replica2*>& ordered,
									 DataStructures::List<RakNet::Replica2*>& initial);
	
	// Callback when we finish downloading all objects from a new connection
	// See Connection_RM2::DeserializeDownloadComplete in ReplicaManager2.h for a full explanation of each parameter
	virtual void DeserializeDownloadComplete(RakNet::BitStream *objectData, SystemAddress sender, RakNet::ReplicaManager2 *replicaManager, RakNetTime timestamp, RakNet::SerializationType serializationType);

};

/// This is a required (by RakNet) class factory, that creates and destroys instances of ReplicaManager2DemoConnection
class MOONET_EXPORT ConnectionFactory : public RakNet::Connection_RM2Factory {
	virtual RakNet::Connection_RM2* AllocConnection(void) const { return new Connection; }
	virtual void DeallocConnection(RakNet::Connection_RM2* s) const { delete s; }
};

}

#endif
