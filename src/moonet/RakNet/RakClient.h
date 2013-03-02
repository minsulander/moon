#ifndef MOONET_RAKCLIENT_H
#define MOONET_RAKCLIENT_H

#undef __BITSTREAM_NATIVE_END
#ifdef _MSC_VER
#	pragma warning(disable:4275)
#endif

#include "../Player.h"
#include "../Export.h"

#include <RakNet/ReplicaManager2.h>
#include <vector>

namespace moonet {

	enum ClientState {
		CLIENT_INITIAL,
		CLIENT_READY,
		NUM_CLIENT_STATES
	};
	
	/// \brief A network participant
	/// \ingroup net
	class MOONET_EXPORT Client : public RakNet::Replica2
	{
	public:
		Client();
		virtual ~Client();
		
		/// Get the player that is associated with this client
		Player *getPlayer() { return player; }
		/// Set the player that is associated with this client
		void setPlayer(Player *newplayer) { player = newplayer; }
		const SystemAddress& getSystemAddress() const { return systemAddress; }
		std::string toString() const;
		void setConnected(const bool value);
		bool isConnected() const { return connected; }
		void setState(const ClientState newstate) { state = newstate; }
		ClientState getState() const { return state; }
		
		/// Static accessor for our own client
		static Client *me() { return mine; }
		static Client *getClientByAddress(const SystemAddress& systemAddress);
		static unsigned int getNumClients() { return clients.size(); }
		static Client *getClient(unsigned int index) { return clients[index]; }
		static bool isStillAround(Client *client);
		static ClientState getMinimumClientState();
		
		/// Implemented member of Replica2: This function encodes the identifier for this class, so the class factory can create it
		virtual bool SerializeConstruction(RakNet::BitStream *bitStream, RakNet::SerializationContext *serializationContext);
		/// Implemented member of Replica2: Write the data members of this class. ReplicaManager2 works with pointers as well as any other kind of data
		virtual bool Serialize(RakNet::BitStream *bitStream, RakNet::SerializationContext *serializationContext);
		/// Implemented member of Replica2: Read what I wrote in Serialize() immediately above
		virtual void Deserialize(RakNet::BitStream *bitStream, RakNet::SerializationType serializationType, SystemAddress sender, RakNetTime timestamp);
		
	protected:
		void setSystemAddress(const SystemAddress& address) { systemAddress = address; }
		static void deleteClientByAddress(const SystemAddress& systemAddress);
		
		Player *player;
		SystemAddress systemAddress;
		bool registered;
		bool connected;
		bool downloadComplete;
		ClientState state;
		
		typedef std::vector<Client*> ClientList;
		static ClientList clients;
		static Client *mine;
		
		friend class NetworkManager;
	};
	
}

#endif

