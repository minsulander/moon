#ifndef MOONET_PLAYER_H
#define MOONET_PLAYER_H

#include "PositionedNetworkObject.h"
#include "Export.h"
#include <string>

namespace moonet {

class Client;

/// \brief A human network game participant
/// \ingroup net
class MOONET_EXPORT Player : public PositionedNetworkObject {
public:
	Player(const std::string& name = "new");
	virtual ~Player();
	
	void setName(const std::string& newname) { name = newname; }
	const std::string& getName() const { return name; }
	const std::string networkObjectName() const { return "Player"; }
	virtual void onConstruction();
	
	/// Static accessor for our own player
	static Player* me();
	/// Static accessor for our own player's name
	static const std::string myName();
	
	/// Set the position of the player, used to determine visibility of PositionedNetworkObject 
	virtual void setPosition(const double x, const double y, const double z);
	/// Get the position of the player
	virtual void getPosition(double& x, double& y, double& z) const;
	virtual bool serialize(const bool full);
	virtual void deserialize(const bool full, const double timediff = 0);

protected:
	std::string name;
	double pos_x, pos_y, pos_z;
	static Player *myPlayer;
	friend class NetworkManager;
};

}

#endif
