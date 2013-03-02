#include "Vehicle.h"
#include <moon/ObjectFactory.h>
#include <moon/Scenario.h>
#include <moon/Interpreter.h>

namespace moon {
	
	Vehicle::Vehicle()
	: player(NULL)
	{
	}
	
	void Vehicle::enter()
	{
		if (currentVehicle)
			currentVehicle->exit();
		currentVehicle = this;
		player = moonet::Player::me();
	}
	
	void Vehicle::exit()
	{
		if (currentVehicle == this)
			currentVehicle = NULL;
		player = NULL;
	}
	
	bool Vehicle::isOccupied() const
	{
		return (currentVehicle == this || player != NULL);
	}
	
	Vehicle* Vehicle::current()
	{
		return currentVehicle;
	}
	
	Vehicle::~Vehicle()
	{
		Vehicle::exit();
	}
	
	Vehicle* Vehicle::currentVehicle = NULL;
	
} // namespace
