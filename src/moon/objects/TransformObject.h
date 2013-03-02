#ifndef MOON_TRANSFORMOBJECT_H
#define MOON_TRANSFORMOBJECT_H

#include "moon/PositionedObject.h"
#include "moon/Parsable.h"
#include <osg/MatrixTransform>
#include <osg/CoordinateSystemNode>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// An object with a position/attitude that is reflected in an osg::MatrixTransform
	class MOON_EXPORT TransformObject : public PositionedObject, virtual public Parsable {
	public:
		TransformObject();
		TransformObject(const TransformObject& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		
		virtual void parseXML(const TiXmlElement *element);
		//virtual void writeXML(TiXmlElement *element) const;
		virtual void writeXML(TiXmlElement *element, const TransformObject* templateObject = NULL) const;
		
		virtual void setPosition(const osg::Vec3& position);
		virtual void setPosition(const double x, const double y, const double z);
		virtual osg::Vec3 getPosition() const;
		virtual void getPosition(double& x, double& y, double& z) const;
		
		virtual void setRotation(const osg::Quat& rotation);
		virtual osg::Quat getRotation() const;
		virtual void setAttitude(const osg::Vec3& attitude);
		virtual osg::Vec3 getAttitude() const;
		virtual void setAttitude(const double heading, const double pitch, const double roll);
                virtual void getAttitude(double& heading, double& pitch, double& roll) const;
		virtual osg::Vec3 forward();
		virtual osg::Vec3 right();
		virtual osg::Vec3 up();
		
		virtual void move(const double distance);
		virtual void move(const osg::Vec3& relposition);
		virtual void move(const double x, const double y, const double z);
		virtual void rotate(const double angle, const osg::Vec3& axis);
		virtual void rotateEuler(const osg::Vec3& angles);
		virtual void rotateEuler(const double heading, const double pitch, const double roll);
		virtual void yaw(const double angle);
		virtual void pitch(const double angle);
		virtual void roll(const double angle);
		
		virtual void scale(const osg::Vec3& scale);
		void scale(const double amount) { scale(osg::Vec3(amount, amount, amount)); }
		
		osg::MatrixTransform* getTransform();
		const osg::MatrixTransform* getTransform() const;
		virtual void setTransformMatrix(const osg::Matrix& matrix);
		virtual osg::Matrix getTransformMatrix() const;
		static osg::Vec3 getEulerAnglesFromMatrix(const osg::Matrix& M);
		static osg::Matrix getMatrixFromEulerAngles(const osg::Vec3& angles);
	
		/// This is called before the transform of an object has changed by using any of the methods above.
		virtual void preUpdateTransformation(const bool parentUpdate = false) {}
		/// This is called after the transform of an object has changed by using any of the methods above.
		virtual void updateTransformation(const bool parentUpdate = false) {}

                static void setEllipsoidModel(osg::EllipsoidModel *model);
                static osg::EllipsoidModel* getOrCreateEllipsoidModel();

                virtual osg::Matrix getLocalToWorldMatrix() const;
                virtual osg::Vec3 getLocalUpVector() const;
                virtual void setPositionLatLongHeight(const double latitude, const double longitude, const double height);
                void setPositionLatLongHeight(const osg::Vec3d& llh);
                void getPositionLatLongHeight(double& latitude, double& longitude, double& height) const;
                osg::Vec3d getPositionLatLongHeight() const;
                bool isGeocentric() { return geocentric; }

        protected:
		osg::ref_ptr<osg::MatrixTransform> transform;
                static osg::ref_ptr<osg::EllipsoidModel> ellipsoidModel;
                bool geocentric;
	};

        /// Get latitude/longitude/height in radians from x/y/z coordinates
        extern MOON_EXPORT osg::Vec3d latLongHeight(const osg::Vec3d& xyz);
        /// Get latitude/longitude/height in degrees from x/y/z coordinates
        extern MOON_EXPORT osg::Vec3d latLongHeightDeg(const osg::Vec3d& xyz);
        /// Get x/y/z from latitude/longitude/height in radians
        extern MOON_EXPORT osg::Vec3d xyz(const osg::Vec3d& llh);
	
	/// @}
}

#endif
