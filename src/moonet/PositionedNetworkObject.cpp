#include "PositionedNetworkObject.h"
#include "Client.h"
#include "SerializeMacros.h"
#include <mlog/Log.h>
#include <iostream>
#include <math.h>

using namespace mlog;

namespace moonet {

PositionedNetworkObject::PositionedNetworkObject()
:	NetworkObject(),
	visible_range(0),
	last_x(0),
	last_y(0),
	last_z(0)
{
}

PositionedNetworkObject::PositionedNetworkObject(const PositionedNetworkObject& source)
:	NetworkObject(source),
	visible_range(source.visible_range),
	last_x(0),
	last_y(0),
	last_z(0)
{
}

void PositionedNetworkObject::setVisibleRange(const double range) { visible_range = range; }

bool PositionedNetworkObject::serialize(const bool full)
{
	double pos_x, pos_y, pos_z;
	getPosition(pos_x, pos_y, pos_z);
	if (!full && pos_x == last_x && pos_y == last_y && pos_z == last_z)
		SERIALIZE_0();
	else {
		SERIALIZE_1();
		SERIALIZE_Vector3(pos_x, pos_y, pos_z);
	}
	last_x = pos_x;
	last_y = pos_y;
	last_z = pos_z;
	return true;
}

void PositionedNetworkObject::deserialize(const bool full, const double timediff)
{
	if (DESERIALIZE_Bit()) {
		float pos_x, pos_y, pos_z;
		DESERIALIZE_Vector3(pos_x, pos_y, pos_z);
		setPosition(pos_x, pos_y, pos_z);
	}
}

/// Used by NetworkObject::QueryVisibility() to determine visibility
bool PositionedNetworkObject::isVisibleToClient(Client *client) const
{
	if (!client)
		return false;
	if (getOwner() == client)
		return true;
	if (visible_range > 0 && client->getPlayer()) {
		double pos_x, pos_y, pos_z;
		double player_x, player_y, player_z;
		getPosition(pos_x, pos_y, pos_z);
		Player *player = client->getPlayer();
		player->getPosition(player_x, player_y, player_z);
		double distance = sqrt( (pos_x - player_x)*(pos_x - player_x) +
								(pos_y - player_y)*(pos_y - player_y) +
								(pos_z - player_z)*(pos_z - player_z) );
		/*
		dout(3, NETWORK) << "isvisible? " << networkObjectName() << " #" << GetAllocationNumber() 
			<< " pos " << pos_x << " " << pos_y << " " << pos_z
			<< " player " << player_x << " " << player_y << " " << player_z
			<< " distance " << distance << " visrange " << visible_range << "\n";
		 */
		if (distance > visible_range)
			return false;
	}
	return true;
}

} // namespace moonet
