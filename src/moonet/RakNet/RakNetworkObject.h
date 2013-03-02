#ifndef MOONET_RAKNETWORKOBJECT_H
#define MOONET_RAKNETWORKOBJECT_H

#undef __BITSTREAM_NATIVE_END
#ifdef _MSC_VER
#	pragma warning(disable:4251)
#endif

#include "RakConnection.h"
#include "../Export.h"
#include <RakNet/ReplicaManager2.h>
#include <RakNet/StringTable.h>
#include <RakNet/StringCompressor.h>
#include <string>
#include <map>

namespace moonet {
	
	class Client;
	
	/// \brief An object that is replicated over the network
	/// \ingroup net
	class MOONET_EXPORT NetworkObject : public RakNet::Replica2 {
	public:
		NetworkObject();
		NetworkObject(const NetworkObject& other);
		virtual ~NetworkObject();
		
		/// Get the owner client of this object
		Client *getOwner() const;
		/// Get object name used to represent the class on the network
		virtual const std::string networkObjectName() const { return "NetworkObject"; }
		/// Broadcast replication of this object over the network and start autoserialization
		virtual void construct();
		bool isConstructed() const { return constructed; }
		bool isRemote() const;
		/// Callback - called when construct() is called
		virtual void onConstruction() {}
		/// Callback - called at a change of ownership
		virtual void onOwnerChange() {}
		/// Set (or request if we're a client) the owner of this object
		virtual bool setOwner(Client *newOwner);
		/// Set cloaking (disabling serialization) of this object
		virtual void setCloaked(const bool value);
		bool isCloaked() const { return cloaked; }
		/// Set the interval at which this object is automatically serialized and replicated over the network
		void setSerializationInterval(const float seconds, const float fullseconds = 0);
		float getSerializationInterval() const { return (float)serializationInterval/1000.0f; }
		float getFullSerializationInterval() const { return (float)serializationInterval/1000.0f * (float)fullSerializeCountInterval; }
		
		/// Callback for serializing user data	
		virtual bool serialize(const bool full) { return true; }
		/// Callback for deserializing user data	
		virtual void deserialize(const bool full, const double timediff = 0) {}
		/// Callback for when the object changes visibility
		virtual void setVisibility(const bool visible) {}
		/// Query callback for object visibility
		virtual bool isVisibleToClient(Client *client) const;
		
		/// Broadcast a full serialization of the object ASAP
		virtual void broadcastFullSerialize();
		
		/// Implemented member of Replica2: This function encodes the identifier for this class, so the class factory can create it
		virtual bool SerializeConstruction(RakNet::BitStream *bitStream, RakNet::SerializationContext *serializationContext);
		/// Implemented member of Replica2: Write the data members of this class. ReplicaManager2 works with pointers as well as any other kind of data
		virtual bool Serialize(RakNet::BitStream *bitStream, RakNet::SerializationContext *serializationContext);
		/// Implemented member of Replica2: Read what I wrote in Serialize() immediately above
		virtual void Deserialize(RakNet::BitStream *bitStream, RakNet::SerializationType serializationType, SystemAddress sender, RakNetTime timestamp);
		virtual void DeserializeDestruction(RakNet::BitStream *bitStream, RakNet::SerializationType serializationType, SystemAddress sender, RakNetTime timestamp);
		
		/// Implemented member of Replica2: Should this object be visible to this connection? If not visible, Serialize() will not be sent to that system.
		virtual RakNet::BooleanQueryResult QueryVisibility(RakNet::Connection_RM2 *connection);
		/// Overriding so the client can decide wether to construct this object (yet)
		virtual RakNet::BooleanQueryResult QueryConstruction(RakNet::Connection_RM2 *connection);
		/// Implemented member of Replica2: Called when our visibility changes. While not visible, we will not get updates from Serialize() for affected connection(s)
		virtual void DeserializeVisibility(RakNet::BitStream *bitStream, RakNet::SerializationType serializationType, SystemAddress sender, RakNetTime timestamp);	
		/// Overriding so the client can delete this object. By default, only the server can.
		virtual bool QueryIsDestructionAuthority(void) const;
		/// Overriding so the client can control if this object is visible or not (for cloaking). By default, only the server control this
		virtual bool QueryIsVisibilityAuthority(void) const;
		/// Overriding so the client can send serialization changes for its own objects. By default, only the server can send serialization changes.
		virtual bool QueryIsSerializationAuthority(void) const;
		
		// for statistics:
		typedef std::map<const std::string, unsigned int> PacketStatsMap;
		static PacketStatsMap packetsize;
		static PacketStatsMap sendcount;
		static PacketStatsMap packettime;
		static PacketStatsMap recvcount;
		
	protected:
		RakNet::BitStream *bitstream;
		/// Get the average time difference from the last few deserializations
		double getAverageTimeDiff() { return averageTimeDiff; }
	private:
		bool changeOwnership(Client *newOwner, SystemAddress sender = UNASSIGNED_SYSTEM_ADDRESS);
		
		bool cloaked;
		Client *owner;
		bool dirtyOwner;
		Client *origOwner;
		bool constructed;
		int serializationInterval;
		int fullSerializeCountInterval, fullSerializeCount;
		bool forceFullSerialize;

		double averageTimeDiff;
		RakNetTime timeDiffs[10];
		int timeDiffIndex;
		
		friend class Connection;
		friend class NetworkManager;
	};
	
}

#endif
