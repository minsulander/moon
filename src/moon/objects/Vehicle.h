#ifndef MOON_VEHICLE_H
#define MOON_VEHICLE_H

#include <moon/Export.h>
#include <moonet/Player.h>

namespace moon {
	
	/// \ingroup core objects
	/// @{
	
	/// Interface class for vehicles
	class MOON_EXPORT Vehicle  {
	public:
		Vehicle();
		virtual void enter();
		virtual void exit();
		
		bool isOccupied() const;
		
		static Vehicle *current();
		
	protected:
		virtual ~Vehicle();
		static Vehicle* currentVehicle;
		moonet::Player *player;
	};
	
	/// @}
	
}

#endif
