#ifndef MOON_POSITIONEDOBJECT_H
#define MOON_POSITIONEDOBJECT_H

#include "Export.h"
#include <osg/Vec3>
#include <osg/Quat>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// Interface class for an object that has a position and attitude
	class MOON_EXPORT PositionedObject {
	public:
		/// Set position of the object
		virtual void setPosition(const osg::Vec3& position) = 0;
		/// Set position of the object
		virtual void setPosition(const double x, const double y, const double z) = 0;
		/// Get position of the object
		virtual osg::Vec3 getPosition() const = 0;
		/// Get position of the object
		virtual void getPosition(double& x, double& y, double& z) const = 0;
		
		/// Set attitude using quaternion notation
		virtual void setRotation(const osg::Quat& rotation) = 0;
		/// Get attitude using quaternion notation
		virtual osg::Quat getRotation() const = 0;
		/// Set attitude using Euler angle notation, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual void setAttitude(const osg::Vec3& attitude) = 0;
		/// Set attitude using Euler angle notation, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual void setAttitude(const double heading, const double pitch, const double roll) = 0;
		/// Get attitude using Euler angle notation, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual osg::Vec3 getAttitude() const = 0;
		/// Get attitude using Euler angle notation, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual void getAttitude(double& heading, double& pitch, double& roll) const = 0;
		
		// Relative position modifiers
		
		/// Move specified \a distance in the direction of the current attitude
		virtual void move(const double distance) = 0;
		/// Add the specified vector to current position
		virtual void move(const osg::Vec3& relposition) = 0;
		/// Add the specified x, y, z components to current position
		virtual void move(const double x, const double y, const double z) = 0;
		/// Rotate the specified \a angle [rad] about an \a axis
		virtual void rotate(const double angle, const osg::Vec3& axis) = 0;
		/// Rotate around the negative z-axis
		virtual void yaw(const double angle) = 0;
		/// Rotate around the x-axis
		virtual void pitch(const double angle) = 0;
		/// Rotate around the y-axis
		virtual void roll(const double angle) = 0;
		/// Rotate the specified Euler angles, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual void rotateEuler(const osg::Vec3& angles) = 0;
		/// Rotate the specified Euler angles, assuming OpenFlight coordinates: X east/right, Y north/forward, Z up
		virtual void rotateEuler(const double heading, const double pitch, const double roll) = 0;
		
		virtual ~PositionedObject() {}
	};
	
	/// @}
}

#endif
