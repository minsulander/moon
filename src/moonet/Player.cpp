#include "Player.h"
#include "Client.h"
#include "NetworkManager.h"
#include <mlog/Log.h>
#include <iostream>

namespace moonet {

Player::Player(const std::string& myname)
:	PositionedNetworkObject(), 
	name(myname),
	pos_x(0),
	pos_y(0),
	pos_z(0)
{
}

Player::~Player()
{
	if (getOwner() != Client::me())
		NetworkManager::instance().unregisterPlayer(this);
	if (getOwner())
		getOwner()->setPlayer(NULL);
}

Player* Player::me()
{
	//if (Client::me())
	//	return Client::me()->getPlayer();
	//return NULL;
	return myPlayer;
}

const std::string Player::myName()
{
	if (me())
		return me()->getName();
	if (NetworkManager::instance().isServer())
		return "server";
	return "";
}

void Player::onConstruction()
{
	if (getOwner() != Client::me())
		NetworkManager::instance().registerPlayer(this);
}

void Player::setPosition(const double x, const double y, const double z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

void Player::getPosition(double& x, double& y, double& z) const
{
	x = pos_x;
	y = pos_y;
	z = pos_z;
}

bool Player::serialize(const bool full)
{
	if (!PositionedNetworkObject::serialize(full))
		return false;
#ifdef MOONET_USE_RAKNET
	StringCompressor::Instance()->EncodeString(name.c_str(),name.size()+1,bitstream);
#endif	
	return true;
}

void Player::deserialize(const bool full, const double timediff)
{
	PositionedNetworkObject::deserialize(full, timediff);
#ifdef MOONET_USE_RAKNET
	char str[128];
	StringCompressor::Instance()->DecodeString(str,sizeof(str),bitstream);
	name = str;
#endif

	if (getOwner())
		getOwner()->setPlayer(this);
}
	
Player *Player::myPlayer = NULL;

} // namespace moonet
