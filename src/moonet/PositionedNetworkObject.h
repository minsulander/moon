#ifndef MOONET_POSITIONEDNETWORKOBJECT_H
#define MOONET_POSITIONEDNETWORKOBJECT_H

#include "NetworkObject.h"
#include "Export.h"

namespace moonet {

/// \brief A positioned network object that can be shown/hidden depending on distance to a Player
/// \ingroup net
class MOONET_EXPORT PositionedNetworkObject : public NetworkObject {
public:
	PositionedNetworkObject();
	PositionedNetworkObject(const PositionedNetworkObject& source);
	
	virtual const std::string networkObjectName() const { return "PositionedNetworkObject"; }
	
	/// Interface method for setting position of this object
	virtual void setPosition(const double x, const double y, const double z) = 0;
	/// Interface method for getting position of this object
	virtual void getPosition(double& x, double& y, double& z) const = 0;
	/// Set the maximum range between this object and player for the object to be visible to that player
	void setVisibleRange(const double range);
	/// Get the maximum range between this object and player for the object to be visible to that player
	double getVisibleRange() const { return visible_range; }

	virtual bool serialize(const bool full);
	virtual void deserialize(const bool full, const double timediff = 0);
	/// Compares player/object position to the visible range
	virtual bool isVisibleToClient(Client *client) const;

private:
	double visible_range;
	double last_x, last_y, last_z;
};

}

#endif
