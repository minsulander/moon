#include "RakNetworkObject.h"
#include "RakNetworkManager.h"
#include "RakClient.h"
#include "../Player.h"
#include <mlog/Log.h>
#include <RakNet/StringTable.h>
#include <RakNet/StringCompressor.h>
#include <iostream>

#ifndef WIN32
#include <arpa/inet.h>
#endif

// Used temporarily while trying to decide which method to use...
//#define USE_RPC_OWNER_CHANGE

using namespace mlog;
using namespace RakNet;

namespace moonet {
	
	inline void endian_swap(unsigned int& x)
	{
		x = (x>>24) | 
        ((x<<8) & 0x00FF0000) |
        ((x>>8) & 0x0000FF00) |
        (x<<24);
	}
	
	NetworkObject::NetworkObject()
	: 	RakNet::Replica2(),
		bitstream(NULL),
		cloaked(true),
		owner(NULL),
		dirtyOwner(false),
		origOwner(NULL),
		constructed(false),
		fullSerializeCount(0),
		forceFullSerialize(false),
		averageTimeDiff(0),
		timeDiffIndex(0)
	{
		setSerializationInterval(NetworkManager::instance().getDefaultSerializationInterval(), NetworkManager::instance().getDefaultFullSerializationInterval());
		SetReplicaManager(NetworkManager::instance().getReplicaManager());
		ClearAutoSerializeTimers();
		for (int i = 0; i < 10; i++)
			timeDiffs[i] = 0;
	}
	
	NetworkObject::NetworkObject(const NetworkObject& other)
	:	RakNet::Replica2(),
		bitstream(NULL),
		cloaked(other.cloaked),
		owner(other.owner),
		dirtyOwner(other.dirtyOwner),
		origOwner(other.origOwner),
		constructed(false),
		serializationInterval(other.serializationInterval),
		fullSerializeCountInterval(other.fullSerializeCountInterval),
		fullSerializeCount(0),
		forceFullSerialize(false),
		averageTimeDiff(0),
		timeDiffIndex(0)
	{
		SetReplicaManager(NetworkManager::instance().getReplicaManager());
		ClearAutoSerializeTimers();
		for (int i = 0; i < 10; i++)
			timeDiffs[i] = 0;
	}
	
	NetworkObject::~NetworkObject()
	{
		// Delete completely
		if (owner == Client::me() || NetworkManager::instance().isServer()) {
			dout(4, NETWORK) << "Destructing " << networkObjectName() << " #" << GetAllocationNumber() << "\n";
			BroadcastDestruction();
		} else
			dout(4, NETWORK) << "Deleting " << networkObjectName() << " #" << GetAllocationNumber() << "\n";
		
		// Another possibility: Delete if server - transfer ownership to server if client
		//if (NetworkManager::instance().isServer())
		//	BroadcastDestruction();
		//else
		//	setOwner(NULL);
		
		//NetworkManager::instance().unregisterObject(this);
		
	}
	
	void NetworkObject::construct()
	{
		if (NetworkManager::instance().isServer())
			owner = NULL;
		else if (Client::me())
			owner = Client::me();
		else {
			dout(ERROR, NETWORK) << "construct() called with no client\n";
			return;
		}
		/*
		 if (!QueryIsConstructionAuthority()) {
		 dout(ERROR, NETWORK) << "Cannot construct " << networkObjectName() << " #" << GetAllocationNumber() << " because I don't have the authority\n";
		 dout(1, NETWORK) << "  owned by " << (owner ? owner->toString() : "server") << " (" << owner << "), I am " << Client::me()->toString() << " (" << Client::me() << ")\n";
		 //return;
		 }
		 */
		dout(2, NETWORK) << "Constructing " << networkObjectName() << " #" << GetAllocationNumber() << " (" << this << ") interval " << serializationInterval << "\n";
		cloaked = false;
		constructed = true;
		BroadcastConstruction();
		AddAutoSerializeTimer(serializationInterval);
		onConstruction();
	}
	
	Client *NetworkObject::getOwner() const
	{
		return owner;
	}
	
	bool NetworkObject::isRemote() const
	{
		if (!NetworkManager::instance().isActive())
			return false;
		if (isConstructed() && NetworkManager::instance().isClient() && !NetworkManager::instance().isServer() && (!Client::me() || getOwner() != Client::me()))
			return true;
		if (NetworkManager::instance().isServer() && getOwner() && getOwner() != Client::me())
			return true;
		return false;
	}
	
	/// If we're not the server, this will not necessarily set the owner permamently.
	/// The owner will be set and the object serialized and transmitted to the server. 
	/// If the server does not allow the owner change, the owner will be reset on the next call to 
	/// Deserialize(). If the object is not yet constructed however, the owner can be set directly.
	/// \return true if the owner is directly set, false otherwise.
	bool NetworkObject::setOwner(Client *newOwner)
	{
		if (owner == newOwner) {
			dirtyOwner = false;
			return true;
		}
		if (!constructed) {
			owner = newOwner;
			onOwnerChange();
			return true;
		}
		
		if (NetworkManager::instance().isServer()) {
			if (!changeOwnership(newOwner)) {
				return false;
			}
#ifdef USE_RPC_OWNER_CHANGE
			NetworkManager::instance().changeOwner(this, newOwner);
#endif
			return true;
		}
		dout(3, NETWORK) << "" << networkObjectName() << " #" << GetAllocationNumber() << " set owner -> ";
		if (newOwner)
			dout(3, NETWORK) << newOwner->toString() << "\n";
		else
			dout(3, NETWORK) << "server\n";
		
#ifdef USE_RPC_OWNER_CHANGE
		NetworkManager::instance().changeOwner(this, newOwner);
#else
		owner = newOwner;
		dirtyOwner = true;
		BroadcastSerialize();
		dirtyOwner = false;
		if (owner == Client::me() || NetworkManager::instance().isServer())
			AddAutoSerializeTimer(serializationInterval);
		else
			ClearAutoSerializeTimers();
#endif
		onOwnerChange();
		return false;
	}
	
	void NetworkObject::setCloaked(const bool value)
	{
		if (owner == Client::me())
			cloaked = value;
	}
	
	void NetworkObject::setSerializationInterval(const float seconds, const float fullseconds)
	{
		serializationInterval = (int) (seconds*1000);
		if (fullseconds > 1e-5)
			fullSerializeCountInterval = (int) (fullseconds/seconds);
		if (GetTimeToNextAutoSerialize() >= 0)
			AddAutoSerializeTimer(serializationInterval);
	}
	
	bool NetworkObject::isVisibleToClient(Client *client) const
	{
		if (!client)
			return false;
		return true;
	}
	
	void NetworkObject::broadcastFullSerialize()
	{
		forceFullSerialize = true;
		BroadcastSerialize();
		forceFullSerialize = false;
	}
	
	// Implemented member of Replica2: This function encodes the identifier for this class, so the class factory can create it
	bool NetworkObject::SerializeConstruction(RakNet::BitStream *bitStream, SerializationContext *serializationContext)
	{
		dout(8, NETWORK) << "SerializeConstruction " << networkObjectName() 
		<< " to " << serializationContext->recipientAddress.ToString() << "\n";
		StringTable::Instance()->EncodeString(networkObjectName().c_str(),128,bitStream);
		forceFullSerialize = true;
		Serialize(bitStream, serializationContext);
		forceFullSerialize = false;
		return true;
	}
	
	// Implemented member of Replica2: Write the data members of this class. ReplicaManager2 works with pointers as well as any other kind of data
	bool NetworkObject::Serialize(RakNet::BitStream *bitStream, SerializationContext *serializationContext)
	{
		//dout(9, NETWORK) << "Serialize " << networkObjectName() << " #" << GetAllocationNumber() << " -> " << serializationContext->recipientAddress.ToString() << "\n";
		if (!constructed)
			return false;
		
		serializationContext->timestamp = RakNet::GetTime();
		
		if (NetworkManager::instance().isServer() && !Client::isStillAround(owner))
			owner = NULL;
		
		bitStream->Write(dirtyOwner);
		//if (dirtyOwner) {
		if (owner)
			bitStream->Write(owner->GetNetworkID());
		else
			bitStream->Write(UNASSIGNED_NETWORK_ID);
		//}
		
		//dout(10, NETWORK) << "  owner " << (owner ? owner->toString() : "server") << "\n";
		
		if (!NetworkManager::instance().isServer() && owner == Client::me()) {//NetworkManager::instance().getMyNetworkObject() == this)
			bitStream->Write(cloaked);
			//if (cloaked)
			//	dout(10, NETWORK) << "  cloaked\n";
		}
		
		bool ret = true;
		if (/*!dirtyOwner &&*/ !cloaked && (owner == Client::me() || NetworkManager::instance().isServer())) {
			//dout(10, NETWORK) << "  object data\n";
			bool full = false;
			if (forceFullSerialize || ++fullSerializeCount > fullSerializeCountInterval) {
				fullSerializeCount = 0;
				full = true;
			}
			bitStream->Write(full);
			bitstream = bitStream;
			ret = serialize(full);
		} else
			bitstream = NULL;
		
		if (ret && NetworkManager::instance().isDoingStatistics()) {
			packetsize[networkObjectName()] += bitStream->GetNumberOfBytesUsed();
			sendcount[networkObjectName()]++;
		}
		
		//dirtyOwner = false;
		return ret;
	}
	
	// Implemented member of Replica2: Read what I wrote in Serialize() immediately above
	void NetworkObject::Deserialize(RakNet::BitStream *bitStream, SerializationType serializationType, SystemAddress sender, RakNetTime timestamp)
	{
		//dout(6, NETWORK) << "Deserialize " << networkObjectName() << " #" << GetAllocationNumber() << "\n";
		// avoid some endianness issues (BitStream seems to swap endianness correctly, but not timestamps and system addresses)
		/*
		if (timestamp > 100000)
			endian_swap(timestamp);
			*/
		RakNetTime timediff = 0;
		if (timestamp)
			timediff = RakNet::GetTime() - timestamp;
		// timestamps still seem f*8#¤/(cked up sometimes.. use average from statistics if available
		if (timediff > 100000) {
			if (NetworkManager::instance().isDoingStatistics())
				timediff = packettime[networkObjectName()] / recvcount[networkObjectName()];
			else
				timediff = 0;
		}
		if (timediff != 0) {
			//dout(7, NETWORK) << "  time diff " << timediff << "\n";
			if (NetworkManager::instance().isDoingStatistics()) {
				packettime[networkObjectName()] += timediff;
				recvcount[networkObjectName()]++;
			}
			// Calculate average time diff over the last 10 updates
			if (++timeDiffIndex >= 10)
				timeDiffIndex = 0;
			timeDiffs[timeDiffIndex] = timediff;
			averageTimeDiff = 0;
			for (int i = 0; i < 10; i++)
				averageTimeDiff += timeDiffs[i];
			averageTimeDiff /= 10000.0;
		}
		bitStream->Read(dirtyOwner);
		//if (dirtyOwner) {
		NetworkID ownerNetworkId;
		bitStream->Read(ownerNetworkId);
		Client *newowner = (Client*) NetworkManager::instance().getObject(ownerNetworkId);
		if (owner != newowner) { // && (dirtyOwner || !constructed)) {
			changeOwnership(newowner, sender);
		}
		//dout(7, NETWORK) << "  owner " << (owner ? owner->toString() : "server") << "\n";
		//}
		if (NetworkManager::instance().isServer())
			bitStream->Read(cloaked);
		else if (owner != Client::me())
			cloaked = false;
		//if (cloaked)
		//	dout(7, NETWORK) << "  cloaked\n";
		
		if (/*!dirtyOwner && */!cloaked && (owner != Client::me() || (!Client::me() && !NetworkManager::instance().isServer())) && (sender == NetworkManager::instance().getServerAddress() || owner == Client::getClientByAddress(sender))) {
			//dout(7, NETWORK) << "  object data\n";
			bool full = false;
			bitStream->Read(full);
			//if (full)
			//	dout(7, NETWORK) << "  full\n";
			bitstream = bitStream;
			deserialize(full, timediff/1000.0);
			if (!constructed) {
				dout(3, NETWORK) << "Deserialized " << networkObjectName() << " #" << GetAllocationNumber() << " for the first time\n";
				constructed = true;
				onConstruction();
				NetworkManager::instance().registerObject(this);
			}
		} else
			bitstream = NULL;
		/// \todo Need to check visibility of ALL objects on the server to make them come visible again...
		/*
		 if (NetworkManager::instance().isServer() && Client::me()) {
		 if (cloaked || !isVisibleToClient(Client::me()))
		 setVisibility(false);
		 else
		 setVisibility(true);
		 }
		 */
		dirtyOwner = false;
		
	}
	
	void NetworkObject::DeserializeDestruction(RakNet::BitStream *bitStream, SerializationType serializationType, SystemAddress sender, RakNetTime timestamp)
	{
		dout(3, NETWORK) << "DeserializeDestruction " << networkObjectName() 
		<< " from " << sender.ToString() << "\n";
		NetworkManager::instance().unregisterObject(this);
	}
	
	// Implemented member of Replica2: Should this object be visible to this connection? If not visible, Serialize() will not be sent to that system.
	BooleanQueryResult NetworkObject::QueryVisibility(Connection_RM2 *connection)
	{
		if (NetworkManager::instance().isServer() ) {
			if (connection) {
				Client *client = Client::getClientByAddress(connection->GetSystemAddress());
				if (!isVisibleToClient(client))
					return BQR_NO;
			}
			return cloaked ? BQR_NO : BQR_YES;
		} else
			return BQR_ALWAYS; // You never cloak your own updates to the server
	}
	
	BooleanQueryResult NetworkObject::QueryConstruction(Connection_RM2 *connection)
	{
		/// \todo This (together with client state stuff) didn't work and should be removed
		/* 
		if (NetworkManager::instance().isServer() ) {
			if (connection) {
				Client *client = Client::getClientByAddress(connection->GetSystemAddress());
				if (!client || (!owner && client->getState() < CLIENT_READY && !sendIfClientNotReady))
					return BQR_NO;
			}
			return BQR_YES;
		} else
		 */
			return BQR_ALWAYS;
	}
	
	// Implemented member of Replica2: Called when our visibility changes. While not visible, we will not get updates from Serialize() for affected connection(s)
	void NetworkObject::DeserializeVisibility(RakNet::BitStream *bitStream, SerializationType serializationType, SystemAddress sender, RakNetTime timestamp)
	{
		if (SerializationContext::IsVisible(serializationType))
			dout(2, NETWORK) << "" << networkObjectName() << " #" << GetAllocationNumber() << " is visible\n";
		else
			dout(2, NETWORK) << "" << networkObjectName() << " #" << GetAllocationNumber() << " is invisible\n";
		setVisibility(SerializationContext::IsVisible(serializationType));
	}
	
	bool NetworkObject::QueryIsDestructionAuthority (void) const
	{
	  return NetworkManager::instance().isServer() || (owner && owner == Client::me());
	}
	
	/// Objects that are not visible are not serialized automatically with ReplicaManager2::AutoSerialize()
	bool NetworkObject::QueryIsVisibilityAuthority (void) const
	{
		return NetworkManager::instance().isServer() || (owner && owner == Client::me());//NetworkManager::instance().isServer() || (owner && owner == Client::me()); //NetworkManager::instance().getMyNetworkObject() == this;
	}
	
	bool NetworkObject::QueryIsSerializationAuthority (void) const
	{
		return NetworkManager::instance().isServer() || (owner && owner == Client::me()) || dirtyOwner; //NetworkManager::instance().getMyNetworkObject() == this;
	}
	
	bool NetworkObject::changeOwnership(Client *newOwner, SystemAddress sender)
	{
		Client *senderClient = Client::getClientByAddress(sender);
		if (NetworkManager::instance().isServer()) {
			// only permit change of ownership client->server or server->client
			if (owner == NULL || sender == UNASSIGNED_SYSTEM_ADDRESS || owner == senderClient || !Client::isStillAround(owner)) {
				if (newOwner) {
					if (!Client::me() || newOwner != Client::me()) {
						dout(3, NETWORK) << "" << networkObjectName() << " #" << GetAllocationNumber() << " changed owner -> client " << newOwner->toString() << "\n";
						owner = newOwner;
#ifndef USE_RPC_OWNER_CHANGE
						dirtyOwner = true;
						if (constructed)
							BroadcastSerialize();
						else
							dout(WARN, NETWORK) << "Owner change to client for non-constructed object\n";
#endif
						BroadcastSerialize();
						ClearAutoSerializeTimers();
						dirtyOwner = false;
						onOwnerChange();
						return true;
					}
				} else {
					dout(3, NETWORK) << "" << networkObjectName() << " #" << GetAllocationNumber() << " changed owner -> server\n";
					owner = newOwner;
#ifndef USE_RPC_OWNER_CHANGE
					dirtyOwner = true;
					if (constructed)
						BroadcastSerialize();
#endif
					dirtyOwner = false;
					BroadcastSerialize();
					AddAutoSerializeTimer(serializationInterval);
					onOwnerChange();
					return true;
				}
			} else {
				// not permitted
				//dirtyOwner = true;
				dirtyOwner = false;
#ifndef USE_RPC_OWNER_CHANGE
				if (constructed)
					BroadcastSerialize();
#endif
				if (!owner || owner == Client::me())
					AddAutoSerializeTimer(serializationInterval);
				dout(WARN, NETWORK) << "Owner change not allowed for " << networkObjectName() << " #" << GetAllocationNumber() << ": ";
				if (owner)
					dout(WARN, NETWORK) << owner->toString();
				else
					dout(WARN, NETWORK) << "server";
				dout(WARN, NETWORK) << " -> ";
				if (newOwner)
					dout(WARN, NETWORK) << newOwner->toString();
				else
					dout(WARN, NETWORK) << "server";
				dout(WARN, NETWORK) << " (requested by " << Client::getClientByAddress(sender)->toString() << ")\n";
				SendSerialize(sender);
				return false;
			}
		}
		ClearAutoSerializeTimers();
		if (newOwner == Client::me()) {
			dout(3, NETWORK) << networkObjectName() << " #" << GetAllocationNumber() << " changed owner -> me\n";
			AddAutoSerializeTimer(serializationInterval);
		} else if (newOwner)
			dout(3, NETWORK) << networkObjectName() << " #" << GetAllocationNumber() << " changed owner -> " << newOwner->toString() << "\n";
		else
			dout(3, NETWORK) << networkObjectName() << " #" << GetAllocationNumber() << " changed owner -> server\n";
		owner = newOwner;
		dirtyOwner = false;
		onOwnerChange();
		
		return true;
	}
	
	NetworkObject::PacketStatsMap 
	NetworkObject::packetsize,
	NetworkObject::sendcount,
	NetworkObject::packettime,
	NetworkObject::recvcount;
	
	/** \class NetworkObject
	 A network object is replicated over the network. It has an associated owner Client, or
	 if owner is set to \c NULL, it is owned by the server. Setting the owner can be done with
	 the setOwner() method, but keep in mind that the server may not allow an owner change. 
	 See the setOwner() documentation for more on that.
	 
	 A user may inherit from NetworkObject and overload the serialize() and deserialize() methods
	 to communicate object data across the network. These use the protected member \c bitstream
	 which is set by the RakNet overloaded Serialize() and Deserialize() methods. The only reason
	 for this is so that the dummy NetworkObject (used if \c MOONET_USE_RAKNET is not defined)
	 interface can remain independent of RakNet.
	 
	 Network replication of the object doesn't start until the user calls construct(). After that,
	 network replication will be automatic (autoserialized) at a rate which can be controlled by
	 calling setSerializationInterval(). Replication can be temporarily disabled by cloaking, see
	 setCloaked(). Destruction of the object across the network will be done through the destructor,
	 provided that the object is owned by Client::me().
	 
	 */
	
} // namespace moonet
