#include "TransformObject.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include "mdraw/utils.h"

using namespace mlog;

namespace moon {
	
        TransformObject::TransformObject() : transform(new osg::MatrixTransform), geocentric(false) {}
	
	TransformObject::TransformObject(const TransformObject& other, const osg::CopyOp& copyop)
        : transform(new osg::MatrixTransform), geocentric(other.geocentric)
	{
		transform->setMatrix(other.transform->getMatrix());
	}
	
	void TransformObject::parseXML(const TiXmlElement *element)
        {
            //=TransformObject:
            XMLParser::parseBooleanAttribute(geocentric, element, "geocentric");
            //=* attribute: pos="(vector3)" [meters]
            //=. Position of this object in cartesian coordinates.
            //=* attribute: att="(vector3)" [degrees]
            //=. Attitude in Euler angles (heading, pitch, roll)
            osg::Vec3 v;

            double lat = 0.0, lon = 0.0, height = 0.0;
            if (XMLParser::parseDoubleAttribute(lat, element, "lat") && XMLParser::parseDoubleAttribute(lon, element, "lon")) {
                geocentric = true;
                XMLParser::parseDoubleAttribute(height, element, "height");
                setPositionLatLongHeight(lat*M_PI/180.0, lon*M_PI/180.0, height);
                setAttitude(0,0,0);
            }

            if (XMLParser::parseVector3Attribute(v, element, "pos"))
                setPosition(v);

            if (element->Attribute("att")) {
                osg::Vec3 att = XMLParser::parseVector3Attribute(element, "att");
                if (att.length() > 1e-5)
                    att *= (float)M_PI/180.f; // when specified as attribute, unit is degrees
                setAttitude(att);
            }
            //=* attribute: scale="(vector3)"
            if (XMLParser::parseVector3Attribute(v, element, "scale"))
                scale(v);
            //=* element: pos="(vector3)" [meters]
            //=. Position of this object in cartesian coordinates.
            //=* element: att="(vector3") [radian]
            //=. Attitude in Euler angles (heading, pitch, roll)
            if (XMLParser::parseVector3(v, element, "pos", "meter"))
                setPosition(v);
            if (XMLParser::parseVector3(v, element, "att", "radian"))
                setAttitude(v);
	}
	
	void TransformObject::writeXML(TiXmlElement *element, const TransformObject* templateObject) const
	{
		if (getPosition() != osg::Vec3(0,0,0) && (!templateObject || getPosition() != templateObject->getPosition())) {
                        if (geocentric) {
                            double lat, lon, height;
                            getPositionLatLongHeight(lat, lon, height);
                            element->SetDoubleAttribute("lat", lat*180.0/M_PI);
                            element->SetDoubleAttribute("lon", lon*180.0/M_PI);
                            element->SetDoubleAttribute("height", height);
                        } else {
                            osg::Vec3 pos = getPosition();
                            std::stringstream ss;
                            ss << pos.x() << ", " << pos.y() << ", " << pos.z();
                            element->SetAttribute("pos", ss.str());
                        }
		}
		if (getAttitude() != osg::Vec3(0,0,0) && (!templateObject || getAttitude() != templateObject->getAttitude())) {
			osg::Vec3 att = getAttitude()*180.f/(float)M_PI;
			std::stringstream ss;
			ss << att.x() << ", " << att.y() << ", " << att.z();
			element->SetAttribute("att", ss.str());
		}
	}
	
	void TransformObject::setPosition(const osg::Vec3& pos)
	{
		osg::Matrix M = getTransformMatrix();
		M.setTrans(pos);
		setTransformMatrix(M);
	}
	void TransformObject::setPosition(const double x, const double y, const double z)
	{ 
		setPosition(osg::Vec3(x, y, z));
	}
	
	osg::Vec3 TransformObject::getPosition() const { return getTransformMatrix().getTrans(); }
	
	void TransformObject::getPosition(double& x, double& y, double& z) const 
	{ 
		osg::Vec3 pos = getPosition(); 
		x = pos.x(); 
		y = pos.y(); 
		z = pos.z();
	}
	
	void TransformObject::setRotation(const osg::Quat& rotation) 
	{
		osg::Matrix M = getTransformMatrix();
		M.setRotate(rotation);
		setTransformMatrix(M);
	}
	
	osg::Quat TransformObject::getRotation() const { return getTransformMatrix().getRotate(); }
	
	void TransformObject::setAttitude(const osg::Vec3& attitude)
	{
            if (geocentric)
                setRotation(mdraw::getQuatFromEulerAngles(attitude) * getLocalToWorldMatrix().getRotate());
            else
                setRotation(mdraw::getQuatFromEulerAngles(attitude));
        }
	
	osg::Vec3 TransformObject::getAttitude() const
	{
            if (geocentric)
                return mdraw::getEulerAnglesFromQuat(getRotation() * getLocalToWorldMatrix().getRotate().inverse());
            else
                return mdraw::getEulerAnglesFromQuat(getRotation());
	}
	
	void TransformObject::setAttitude(const double heading, const double pitch, const double roll)
	{ 
		setAttitude(osg::Vec3(heading, pitch, roll));
	}
	
	void TransformObject::getAttitude(double& heading, double& pitch, double& roll) const
	{ 
		osg::Vec3 att = getAttitude();
		heading = att.x();
		pitch = att.y();
		roll = att.z();
	}
	
	osg::Vec3 TransformObject::forward()
	{
		return getRotation() * osg::Vec3(0,1,0);
	}
	
	osg::Vec3 TransformObject::right()
	{
		return getRotation() * osg::Vec3(1,0,0);
	}
	
	osg::Vec3 TransformObject::up()
	{
                return getRotation() * osg::Vec3(0,0,1);
	}
	
	void TransformObject::move(const double distance)
	{
		setTransformMatrix(osg::Matrix::translate(osg::Vec3(0,distance,0)) * getTransformMatrix());
	}
	
	void TransformObject::move(const osg::Vec3& relposition)
	{
        setTransformMatrix(osg::Matrix::translate(relposition) * getTransformMatrix());
	}
	
	void TransformObject::move(const double x, const double y, const double z) { move(osg::Vec3(x, y, z)); }
	
        void TransformObject::yaw(const double angle) { rotate(-angle, osg::Vec3(0, 0, 1)); }
	
	void TransformObject::pitch(const double angle) { rotate(angle, osg::Vec3(1, 0, 0)); }
	
	void TransformObject::roll(const double angle) { rotate(angle, osg::Vec3(0, 1, 0)); }
	
	void TransformObject::rotate(const double angle, const osg::Vec3& axis)
	{ 
		setTransformMatrix(osg::Matrix::rotate(angle,axis) * getTransformMatrix());
	}
	
	void TransformObject::rotateEuler(const osg::Vec3& angles)
	{
		setTransformMatrix(getMatrixFromEulerAngles(angles) * getTransformMatrix());
	}
	
	void TransformObject::rotateEuler(const double heading, const double pitch, const double roll)
	{ 
		rotateEuler(osg::Vec3(heading, pitch, roll));
	}
		
	void TransformObject::scale(const osg::Vec3& scale)
	{
		osg::Matrix M = transform->getMatrix();
		M.makeScale(scale);
		transform->setMatrix(M);
		//setTransformMatrix(osg::Matrix::scale(scale) * getTransformMatrix());
	}
	
	osg::Vec3 TransformObject::getEulerAnglesFromMatrix(const osg::Matrix& M)
	{
		return mdraw::getEulerAnglesFromQuat(M.getRotate());
	}
	
	osg::Matrix TransformObject::getMatrixFromEulerAngles(const osg::Vec3& angles)
	{
		osg::Matrix R(mdraw::getQuatFromEulerAngles(angles));
		return R;
	}
	
        osg::MatrixTransform* TransformObject::getTransform() { return transform.get(); }
	const osg::MatrixTransform* TransformObject::getTransform() const { return transform.get(); }
	
	void TransformObject::setTransformMatrix(const osg::Matrix& matrix)
	{ 
		preUpdateTransformation();
		transform->setMatrix(matrix);
		updateTransformation();
	}
	
	osg::Matrix TransformObject::getTransformMatrix() const { return transform->getMatrix(); }
	
        void TransformObject::setEllipsoidModel(osg::EllipsoidModel *model) {
            if (ellipsoidModel.valid())
                dout(WARN) << "Overriding ellipsoid model\n";
            ellipsoidModel = model;
        }

        osg::EllipsoidModel* TransformObject::getOrCreateEllipsoidModel() {
            if (!ellipsoidModel) {
                dout(2) << "Assuming WGS84 ellipsoid model\n";
                ellipsoidModel = new osg::EllipsoidModel;
            }
            return ellipsoidModel.get();
        }

        void TransformObject::setPositionLatLongHeight(const double latitude, const double longitude, const double height)
        {
            double x,y,z;
            getOrCreateEllipsoidModel()->convertLatLongHeightToXYZ(latitude, longitude, height, x, y, z);
            setPosition(x,y,z);
        }

        void TransformObject::setPositionLatLongHeight(const osg::Vec3d& llh)
        {
            setPositionLatLongHeight(llh.x(), llh.y(), llh.z());
        }

        osg::Matrix TransformObject::getLocalToWorldMatrix() const
        {
            osg::Matrixd M;
            osg::Vec3 pos = getPosition();
            getOrCreateEllipsoidModel()->computeLocalToWorldTransformFromXYZ(pos.x(), pos.y(), pos.z(), M);
            return M;
        }

        osg::Vec3 TransformObject::getLocalUpVector() const
        {
            if (geocentric) {
                osg::Vec3 pos = getPosition();
                return getOrCreateEllipsoidModel()->computeLocalUpVector(pos.x(), pos.y(), pos.z());
            }
            return osg::Vec3(0,0,1);
        }

        void TransformObject::getPositionLatLongHeight(double& latitude, double& longitude, double& height) const
        {
            osg::Vec3 pos = getPosition();
            getOrCreateEllipsoidModel()->convertXYZToLatLongHeight(pos.x(), pos.y(), pos.z(), latitude, longitude, height);
        }

        osg::Vec3d TransformObject::getPositionLatLongHeight() const
        {
            osg::Vec3d llh;
            getPositionLatLongHeight(llh.x(), llh.y(), llh.z());
            return llh;
        }

        osg::ref_ptr<osg::EllipsoidModel> TransformObject::ellipsoidModel = NULL;

        osg::Vec3d latLongHeight(const osg::Vec3d& xyz)
        {
            osg::Vec3d LLH;
            TransformObject::getOrCreateEllipsoidModel()->convertXYZToLatLongHeight(xyz.x(), xyz.y(), xyz.z(), LLH.x(), LLH.y(), LLH.z());
            return LLH;
        }

        osg::Vec3d latLongHeightDeg(const osg::Vec3d& xyz)
        {
            osg::Vec3d LLH = latLongHeight(xyz);
            LLH.x() *= 180.0/M_PI;
            LLH.y() *= 180.0/M_PI;
            return LLH;
        }

        osg::Vec3d xyz(const osg::Vec3d& llh)
        {
            osg::Vec3d XYZ;
            TransformObject::getOrCreateEllipsoidModel()->convertLatLongHeightToXYZ(llh.x(), llh.y(), llh.z(), XYZ.x(), XYZ.y(), XYZ.z());
            return XYZ;
        }
	
} // namespace
