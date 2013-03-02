#include "Camera.h"
#include "moon/XMLParser.h"
#include "moon/ObjectFactory.h"
#include "moon/SimulationManager.h"
#include "moon/Interpreter.h"
#include <moonet/SerializeMacros.h>
#include <moonet/NetworkManager.h>
#include <osg/ShapeDrawable>
#include <osg/io_utils>
#include <iomanip>

using namespace mlog;
using namespace moon;

void CameraManipulator::setViewer(osgViewer::Viewer *nviewer) {
    viewer = nviewer;
	if (defaultAspect < 0) {
		double foo;
		if (viewer->getCamera()->getProjectionMatrixAsPerspective(foo, defaultAspect, foo, foo))
			dout(5) << "Camera default aspect ratio: " << defaultAspect << "\n";
	}
}

void CameraManipulator::setByMatrix(const osg::Matrix& M) {
/*
    if (activecamera)
		activecamera->setByMatrix(M);
		*/
}

void CameraManipulator::setByInverseMatrix(const osg::Matrix& M) {
/*
    if (activecamera)
		activecamera->setByInverseMatrix(M);
		*/
}

osg::Matrix CameraManipulator::getMatrix() const {
    if (activecamera.valid())
		return activecamera->getWorldTransformMatrix() * osg::Matrixd::rotate(-M_PI/2.0, osg::Vec3(1,0,0));
    else
		return osg::Matrix::identity();
}

osg::Matrix CameraManipulator::getInverseMatrix() const {
    if (activecamera.valid())
		return osg::Matrix::inverse(activecamera->getWorldTransformMatrix()) * osg::Matrixd::rotate(-M_PI/2.0, osg::Vec3(1,0,0) );
    else
		return osg::Matrix::identity();
}

bool CameraManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa) {
	if (ea.getEventType() != osgGA::GUIEventAdapter::FRAME)
		return false;
    if (!activecamera)
		return false;
	if (!viewer && dynamic_cast<osgViewer::Viewer*> (&aa))
		setViewer((osgViewer::Viewer*) &aa);
	if (activecamera->dirtyPerspective && viewer.valid()) {
		double fov, aspect, near, far;
		activecamera->getPerspective(fov,aspect,near,far);
		if (near > 0 && far > 0) {
			viewer->getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
			viewer->getCamera()->setProjectionMatrixAsPerspective(fov,aspect,near,far);
		} else {
			viewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES);
			viewer->getCamera()->setProjectionMatrixAsPerspective(fov,aspect,1,1000);
		}
		activecamera->dirtyPerspective = false;
	}
	return true;
}

Camera* CameraManipulator::getActiveCamera() {
    return activecamera.get();
}

void CameraManipulator::setNoActiveCamera() {
	if (activecamera.valid())
		activecamera->deactivate();
}

CameraManipulator& CameraManipulator::instance() {
	if (!instanceptr)
		instanceptr = new CameraManipulator();
	return *instanceptr;
}

CameraManipulator::CameraManipulator()
:	activecamera(NULL),
	viewer(NULL),
	hudroot(new osg::Group)
{
    /// \todo don't use this as a singleton or figure out how an osg::Referenced can be singleton
    this->ref();
}

CameraManipulator::~CameraManipulator()
{
    dout(ERROR) << "~CameraManipulator()\n";
}

void CameraManipulator::setActiveCamera(Camera *cam) {
	if (activecamera.valid())
		activecamera->active = false;
    activecamera = cam;
	if (!cam)
		return;
	activecamera->active = true;
    if (viewer.valid()) {
		double fov, aspect, near, far;
		activecamera->getPerspective(fov,aspect,near,far);
                if (viewer->getCameraManipulator() == this) {
                    if (near > 0 && far > 0) {
                        viewer->getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
                        viewer->getCamera()->setProjectionMatrixAsPerspective(fov,aspect,near,far);
                    } else {
                        viewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES);
                        viewer->getCamera()->setProjectionMatrixAsPerspective(fov,aspect,1,1000);
                    }
                }
                activecamera->dirtyPerspective = false;
	} else
		activecamera->dirtyPerspective = true;
}

CameraManipulator* CameraManipulator::instanceptr = NULL;


/********************************** Camera **********************************/


REGISTER_Object(moon, Camera);

Camera::Camera(const std::string& name) : KinematicObject(),
	active(false),
	free(true), // default to a free camera when created programatically
	speed(10.f),
	rollangle(0),
	dirtyPerspective(true),
	fovy(30),
	aspect(1.6),
	nearclip(-1),
	farclip(-1), /// \todo check default perpsective
	trackmode(NONE),
	trackspeed(0),
	trackacc(10),
	trackdistance(0),
	trackazimuth(0),
	trackelevation(0),
	ignorePause(false),
	hideWhenActive(true),
	move2D(false),
	hud(new osg::Switch),
	hudtransform(new osg::MatrixTransform),
	infolevel(0),
	hudmode(NORMALIZED)
{
	setName(name);
	setNormallyVisible(false);
	rollcontrol = new ListenerControl("RollView",Control::AXIS,this);
	yawcontrol = new ListenerControl("YawView",Control::AXIS,this);
	pitchcontrol = new ListenerControl("PitchView",Control::AXIS,this);
	forwardcontrol = new ListenerControl("MoveView",Control::AXIS,this);
	rightcontrol = new ListenerControl("StrafeView",Control::AXIS,this);
	upcontrol = new ListenerControl("RiseView",Control::AXIS,this);
	resetcontrol = new ListenerControl("ResetView",Control::MOMENTARY,this);
	for (int i = 0; i < 12; i++)
		limits[i] = 0;
	setPerspective(fovy, aspect, nearclip, farclip);
	hudtransform->addChild(hud.get());
}

Camera::Camera(const Camera& cam,const osg::CopyOp& copyop) : KinematicObject(cam,copyop),
	rollcontrol(NULL),
	pitchcontrol(NULL),
	yawcontrol(NULL),
	forwardcontrol(NULL),
	rightcontrol(NULL),
	upcontrol(NULL),
	resetcontrol(NULL),
	active(false),
	free(cam.free),
	speed(cam.speed),
	dirtyPerspective(true),
	fovy(cam.fovy),
	aspect(cam.aspect),
	nearclip(cam.nearclip),
	farclip(cam.farclip),
	trackmode(cam.trackmode),
	trackspeed(cam.trackspeed),
	trackacc(cam.trackacc),
	trackdistance(cam.trackdistance),
	trackazimuth(cam.trackazimuth),
	trackelevation(cam.trackelevation),
	ignorePause(cam.ignorePause),
	hideWhenActive(cam.hideWhenActive),
	move2D(cam.move2D),
	hud(new osg::Switch(*cam.hud.get())),
	hudtransform(new osg::MatrixTransform),
	infolevel(cam.infolevel),
	hudmode(cam.hudmode)
{
	for (int i = 0; i < 12; i++)
		limits[i] = cam.limits[i];
	if (free || limits[0] != 0 || limits[1] != 0)
		rollcontrol = new ListenerControl("RollView",Control::AXIS,this);
	if (free || limits[2] != 0 || limits[3] != 0)
		pitchcontrol = new ListenerControl("PitchView",Control::AXIS,this);
	if (free || limits[4] != 0 || limits[5] != 0)
		yawcontrol = new ListenerControl("YawView",Control::AXIS,this);
	if (free || limits[6] != 0 || limits[7] != 0)
		forwardcontrol = new ListenerControl("MoveView",Control::AXIS,this);
	if (free || limits[8] != 0 || limits[9] != 0)
		rightcontrol = new ListenerControl("StrafeView",Control::AXIS,this);
	if (free || limits[10] != 0 || limits[11] != 0)
		upcontrol = new ListenerControl("RiseView",Control::AXIS,this);
	resetcontrol = new ListenerControl("ResetView",Control::MOMENTARY,this);
	origPosition = getPosition();
	origAttitude = getAttitude();
	rollangle = origAttitude.z();
	setPerspective(fovy, aspect, nearclip, farclip);
	hudtransform->addChild(hud.get());
}

void Camera::parseXML(const TiXmlElement* element)
{
	//=== Camera
	//=see superclass KinematicObject for more parameters
	KinematicObject::parseXML(element);
	//=* attribute: free="true|false"
	XMLParser::parseBooleanAttribute(free,element,"free");
	//=* attribute: speed="(number)"
	XMLParser::parseValueAttribute(speed, element, "speed");
	//=* attribute: fov value="(number)" [degree]
	//=. Vertical field of view
	XMLParser::parseValueAttribute(fovy, element, "fov");
	//=* attribute: aspect value="(number)"
	//=. Aspect ratio
	XMLParser::parseValueAttribute(aspect, element, "aspect");
	//=* attribute: nearclip="(number)" farclip="(number)" [meter]
	//=. Clip distances
	XMLParser::parseValueAttribute(nearclip, element, "nearclip");
	XMLParser::parseValueAttribute(farclip, element, "farclip");
	//=* attribute: hideactive="true|false"
	//=. Hide visual model when camera is active
	XMLParser::parseBooleanAttribute(hideWhenActive, element, "hideactive");
	//=* attribute: infolevel="(integer)"
	//=. HUD info level
	XMLParser::parseIntAttribute(infolevel, element, "infolevel");
	//=* attribute: hudcoord="normalized|deg|rad"
	//=. HUD coordinate system (normalized default)
	std::string str;
	if (XMLParser::parseStringAttribute(str, element, "hudcoord")) {
		if (str == "normalized")
			hudmode = NORMALIZED;
		else if (str == "deg")
			hudmode = FOV_DEGREES;
		else if (str == "rad")
			hudmode = FOV_RADIANS;
		else
			throw ParseException("Invalid 'hudcoord' specification", element);
	}
	//=* element: roll min="(number)" max="(number)" [radian]
	//=. Roll limitation
	limits[0] = XMLParser::parseDouble(element,"roll","radian",true,limits[0],"min");
	limits[1] = XMLParser::parseDouble(element,"roll","radian",true,limits[1],"max");
	//=* element: pitch min="(number)" max="(number)" [radian]
	//=. Pitch limitation
	limits[2] = XMLParser::parseDouble(element,"pitch","radian",true,limits[2],"min");
	limits[3] = XMLParser::parseDouble(element,"pitch","radian",true,limits[3],"max");
	//=* element: yaw min="(number)" max="(number)" [radian]
	//=. Yaw limitation
	limits[4] = XMLParser::parseDouble(element,"yaw","radian",true,limits[4],"min");
	limits[5] = XMLParser::parseDouble(element,"yaw","radian",true,limits[5],"max");
	//=* element: forward min="(number)" max="(number)" [meter]
	//=. Forward/back (y-axis) limitation
	limits[6] = XMLParser::parseDouble(element,"forward","meter",true,limits[6],"min");
	limits[7] = XMLParser::parseDouble(element,"forward","meter",true,limits[7],"max");
	//=* element: right min="(number)" max="(number)" [meter]
	//=. Right/left (x-axis) limitation
	limits[8] = XMLParser::parseDouble(element,"right","meter",true,limits[8],"min");
	limits[9] = XMLParser::parseDouble(element,"right","meter",true,limits[9],"max");
	//=* element: up min="(number)" max="(number)" [meter]
	//=. Up/down (z-axis) limitation
	limits[10] = XMLParser::parseDouble(element,"up","meter",true,limits[10],"min");
	limits[11] = XMLParser::parseDouble(element,"up","meter",true,limits[11],"max");

	setPerspective(fovy, aspect, nearclip, farclip);
}

void Camera::writeXML(TiXmlElement *element) const
{
	KinematicObject::writeXML(element);
	const Camera *temp = dynamic_cast<const Camera*> (getTemplate());
	if (free && (!temp || !temp->free))
		element->SetAttribute("free", true);
	if (!temp || fovy != temp->fovy)
		element->SetDoubleAttribute("fov", fovy);
	if (!temp || aspect != temp->aspect)
		element->SetDoubleAttribute("aspect", aspect);
	if (nearclip >= 0 && (!temp || nearclip != temp->nearclip))
		element->SetDoubleAttribute("nearclip", nearclip);
	if (farclip >= 0 && (!temp || farclip != temp->farclip))
		element->SetDoubleAttribute("farclip", farclip);
	if (!hideWhenActive && (!temp || temp->hideWhenActive))
		element->SetAttribute("hideactive", false);
	if (infolevel > 0 && (!temp || temp->infolevel != infolevel))
		element->SetAttribute("infolevel", infolevel);
	if (!free) {
		if (!temp || limits[0] != temp->limits[0])
			XMLParser::setDouble(element, "roll", limits[0], "min");
		if (!temp || limits[1] != temp->limits[1])
			XMLParser::setDouble(element, "roll", limits[1], "max");
		if (!temp || limits[2] != temp->limits[2])
			XMLParser::setDouble(element, "pitch", limits[2], "min");
		if (!temp || limits[3] != temp->limits[3])
			XMLParser::setDouble(element, "pitch", limits[3], "max");
		if (!temp || limits[4] != temp->limits[4])
			XMLParser::setDouble(element, "yaw", limits[4], "min");
		if (!temp || limits[5] != temp->limits[5])
			XMLParser::setDouble(element, "yaw", limits[5], "max");
		if (!temp || limits[6] != temp->limits[6])
			XMLParser::setDouble(element, "forward", limits[6], "min");
		if (!temp || limits[7] != temp->limits[7])
			XMLParser::setDouble(element, "forward", limits[7], "max");
		if (!temp || limits[8] != temp->limits[8])
			XMLParser::setDouble(element, "right", limits[8], "min");
		if (!temp || limits[9] != temp->limits[9])
			XMLParser::setDouble(element, "right", limits[9], "max");
		if (!temp || limits[10] != temp->limits[10])
			XMLParser::setDouble(element, "up", limits[10], "min");
		if (!temp || limits[11] != temp->limits[11])
			XMLParser::setDouble(element, "up", limits[11], "max");
	}
}

void Camera::reset()
{
	KinematicObject::reset();
	rollangle = getAttitude().z();
}

void Camera::setResetState()
{
	KinematicObject::setResetState();
	origPosition = getPosition();
	origAttitude = getAttitude();
}

void Camera::activate()
{
	if (CameraManipulator::instance().getActiveCamera() == this)
		return;
	else if (CameraManipulator::instance().getActiveCamera())
		CameraManipulator::instance().getActiveCamera()->deactivate();
	CameraManipulator::instance().setActiveCamera(this);
	dout(5) << "Camera::activate " << getName() << "\n";
	bindControls();
	if (hideWhenActive)
		hide();
	if (hudtransform.valid())
		CameraManipulator::instance().getHUDRoot()->addChild(hudtransform.get());
	// Export active camera to Lua interpreter
	Interpreter::instance().pushGlobal("objects");
	Interpreter::instance().setTable("cam", this, "moon::Camera");
}

void Camera::setPerspective(const double fovy, const double aspect, const double nearclip, const double farclip) {
	this->fovy = fovy;
	this->aspect = aspect;
	this->nearclip = nearclip;
	this->farclip = farclip;
	dirtyPerspective = true;
	hudtransform->setMatrix(osg::Matrix::scale(getHUDScale()));
}

void Camera::getPerspective(double& fovy, double& aspect, double& nearclip, double& farclip) const {
	fovy = this->fovy;
	aspect = this->aspect;
	nearclip = this->nearclip;
	farclip = this->farclip;
}

void Camera::setLimit(CameraLimit limit, const double value) {
	limits[limit] = value;
}

double Camera::getLimit(CameraLimit limit) const {
	return limits[limit];
}

void Camera::track(BaseObject *target) {
	if (trackmode == NONE)
		trackmode = POINT;
	if (trackdistance < 1e-5 && target && !tracktarget) {
		if (target == getParent()) {
			trackdistance = getPosition().length();
			trackazimuth = getAzimuth(target, true);
			trackelevation = getElevation(target, true);
		} else {
			trackdistance = (getWorldTransformMatrix().getTrans() - target->getWorldTransformMatrix().getTrans()).length();
			trackazimuth = getAzimuth(target, false);
			trackelevation = getElevation(target, false);
		}
	}
	tracktarget = target;
	if (tracktarget.valid()) {
		osg::Vec3 o = tracktarget->getAttitude();
		if (trackmode == CHASE || trackmode == CHASE_HEADING)
			trackazimuth -= o.x();
		if (trackmode == CHASE || trackmode == CHASE_HEADING)
			trackazimuth += o.x();
		dout(5) << "Camera " << getName() << " tracking " << tracktarget->getName() << "\n";
		dout(6) << "  distance " << trackdistance << " azimuth " << trackazimuth << " elevation " << trackelevation << "\n";
	} else
		trackmode = NONE;
}

void Camera::track(BaseObject *target, TrackMode mode)
{
	trackmode = mode;
	track(target);
}

void Camera::setTrackParameters(const double distance, const double azimuth, const double elevation)
{
	trackdistance = distance;
	trackazimuth = azimuth;
	trackelevation = elevation;
}


void Camera::controlUpdate(Control* control) {
	if (!control)
		return;
	double value = control->getValue();
	osg::Vec3 position = getPosition();
	osg::Vec3 attitude = getAttitude();
	if (getMotionModel())
		attitude = getMotionModel()->getTargetAttitude();
	
	if (trackmode != NONE && trackmode != POINT) {
		if (control == pitchcontrol)
			trackelevation += value*0.1;
		else if (control == upcontrol)
			trackelevation -= value*0.01;
		else if (control == yawcontrol)
			trackazimuth += value*0.1;
		else if (control == rightcontrol)
			trackazimuth -= value*0.01;
		else if (control == forwardcontrol)
			trackdistance -= value*0.1;
		if (trackazimuth > M_PI) trackazimuth -= M_PI*2;
		if (trackazimuth < -M_PI) trackazimuth += M_PI*2;
		if (trackelevation > M_PI) trackelevation -= M_PI*2;
		if (trackelevation < -M_PI) trackelevation += M_PI*2;
		return;
	}
	
	if (SimulationManager::instance().isPaused() && !ignorePause)
		return;
	
	osg::Vec3 v = getVelocity(true);
	
	// Use heading values ranging from -pi to pi
	if (origAttitude.x() > M_PI)
		origAttitude.x() -= 2.0*M_PI;
	if (attitude.x() > M_PI)
		attitude.x() -= 2.0*M_PI;

        if (fabs(attitude.z()) > M_PI/2.0 && (control == pitchcontrol || control == yawcontrol))
            value = -value;
	
	if (control == forwardcontrol && (((value > 0 || position.y() > limits[6]+origPosition.y()) && (value < 0 || position.y() < limits[7]+origPosition.y())) || free))
		v.y() = value*speed;
	else if (control == rightcontrol)
		v.x() = value*speed;
	else if (control == upcontrol)
		v.z() = value*speed;
	else if (move2D && control == yawcontrol)
		v.x() = value*speed*100.f;
	else if (move2D && control == pitchcontrol)
		v.z() = value*speed*100.f;
	else if (control == rollcontrol && (((value > 0 || attitude.z() > limits[0]+origAttitude.z()) && (value < 0 || attitude.z() < limits[1]+origAttitude.z())) || free))
                rollangle += value*0.1;
	else if (control == pitchcontrol && (((value > 0 || attitude.y() > limits[2]+origAttitude.y()) && (value < 0 || attitude.y() < limits[3]+origAttitude.y())) || free)) {
		if (pivot.y() > 1e-5)
			move(0, (1.0-cos(value*0.1))*pivot.y(), -sin(value*0.1)*pivot.y());
		attitude.y() += (value*0.1);
	} else if (control == yawcontrol && (((value > 0 || attitude.x() > limits[4]+origAttitude.x()) && (value < 0 || attitude.x() < limits[5]+origAttitude.x())) || free)) {
		if (pivot.y() > 1e-5)
			move(-sin(value*0.1)*pivot.y(), (1.0-cos(value*0.1))*pivot.y(), 0);
		attitude.x() += (value*0.1);
	} else if (control == resetcontrol && value)
		reset();
        if (fabs(attitude.y()) > M_PI/2.0) {
            rollangle -= M_PI;
            attitude.x() -= M_PI;
            attitude.y() = -M_PI - attitude.y();
        }
        attitude.z() = rollangle;
	
	/// \todo pivot around more than y-axis to pivot point

	if (SimulationManager::instance().isPaused()) {
		setAttitude(attitude);
		move(v * SimulationManager::instance().getTimeStep());
	} else {
		requestAttitude(attitude);
		requestVelocity(v, true);
	}
        /*
	osg::Matrix M = transform->getMatrix();
	if (fabs(M(2,2)) > 0.1) {
		if (M(2,2) > 0)
			roll(asin(M(0,2))+rollangle);
		else
			roll(-asin(M(0,2))+rollangle);
	}
        */
}

double sign(double val) {
	if (val > 0)
		return 1;
	if (val < 0)
		return -1;
	return 0;
}

void Camera::update(const double dt) {
	if (!active)
		return;

        if (isGeocentric()) {
            osg::Vec3 attitude = getAttitude();
            attitude.z() = rollangle;
            setAttitude(attitude);
        }

	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(updateMutex);
	
	osg::Matrix WM = getWorldTransformMatrix();
	
	// Limit movement
	if (!free) {
		osg::Vec3 position = getPosition();
		osg::Vec3 vel = getVelocity(true);
		if (position.y() < limits[6]+origPosition.y()) {
			position.y() = limits[6]+origPosition.y();
			vel.y() = 0;
		} else if (position.y() > limits[7]+origPosition.y()) {
			position.y() = limits[7]+origPosition.y();
			vel.y() = 0;
		}
		if (position.x() < limits[8]+origPosition.x()) {
			position.x() = limits[8]+origPosition.x();
			vel.x() = 0;
		} else if (position.x() > limits[9]+origPosition.x()) {
			position.x() = limits[9]+origPosition.x();
			vel.x() = 0;
		}
		if (position.z() < limits[10]+origPosition.z()) {
			position.z() = limits[10]+origPosition.z();
			vel.z() = 0;
		} else if (position.z() > limits[11]+origPosition.z()) {
			position.z() = limits[11]+origPosition.z();
			vel.z() = 0;
		}
		requestPosition(position);
		requestVelocity(vel,true);
	}
	
	if (tracktarget.valid()) {
		osg::Vec3 trackPos = getPosition();
		if (trackmode == FOLLOW) {
			osg::Vec3 offset =  osg::Matrix::rotate(trackazimuth,0,0,1) * osg::Matrix::rotate(-trackelevation,1,0,0) * osg::Vec3(0,trackdistance,0);
			trackPos = tracktarget->getPosition() - offset;
		} else if (trackmode == CHASE) {
			osg::Vec3 o = tracktarget->getAttitude();
			osg::Vec3 offset = osg::Matrix::rotate(o.x()+trackazimuth,0,0,1) * osg::Matrix::rotate(-o.y()-trackelevation,1,0,0) * osg::Vec3(0,trackdistance,0);
			trackPos = tracktarget->getPosition() - offset;
		} else if (trackmode == CHASE_HEADING) {
			osg::Vec3 o = tracktarget->getAttitude();
			osg::Vec3 offset = osg::Matrix::rotate(o.x()+trackazimuth,0,0,1) * osg::Matrix::rotate(-trackelevation,1,0,0) * osg::Vec3(0,trackdistance,0);
			trackPos = tracktarget->getPosition() - offset;
		} else if (trackmode == CHASE_VELOCITY && tracktarget->asKinematic()) {
			osg::Vec3 vel = tracktarget->asKinematic()->getVelocity();
			osg::Vec3 offset = osg::Matrix::rotate(trackazimuth,0,0,1) * osg::Matrix::rotate(-trackelevation,1,0,0) * osg::Vec3(0, trackdistance, 0);
			if (vel.length() > 0.01f)
				offset = osg::Matrix::rotate(vel,osg::Vec3(0,1,0)) * offset;
			trackPos = tracktarget->getPosition() - offset;
		} else if (trackmode == CHASE_HORIZONTAL_VELOCITY && tracktarget->asKinematic()) {
			osg::Vec3 vel = tracktarget->asKinematic()->getVelocity();
			vel.z() = 0;
			osg::Vec3 offset = osg::Matrix::rotate(trackazimuth,0,0,1) * osg::Matrix::rotate(-trackelevation,1,0,0) * osg::Vec3(0, trackdistance, 0);
			if (vel.length() > 0.01f)
				offset = osg::Matrix::rotate(vel,osg::Vec3(0,1,0)) * offset;
			trackPos = tracktarget->getPosition() - offset;
		}
		if (trackmode != NONE && trackmode != POINT) {
			requestPosition(trackPos);
		}
		pointAt(tracktarget.get());
	}
	if (infolevel > 0)
		createInfoText();
	if (infotext.valid()) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0);
		ss << getName() << "\n";
		if (trackmode != NONE && tracktarget.valid()) {
			ss << "track: " << tracktarget->getName();
			switch (trackmode) {
				case POINT: ss << " point"; break;
				case FOLLOW: ss << " follow"; break;
				case CHASE: ss << " chase"; break;
				case CHASE_HEADING: ss << " chase heading"; break;
				case CHASE_VELOCITY: ss << " chase velocity"; break;
				case CHASE_HORIZONTAL_VELOCITY: ss << " chase horizontal velocity"; break;
				default: ss << " ???";
			}
			if (infolevel > 1) {
				ss << " attitude " << tracktarget->getAttitude() * 180.0/M_PI;
				ss << " position " << tracktarget->getPosition();
				if (tracktarget->asKinematic())
					ss << " speed " << tracktarget->asKinematic()->getVelocity().length();
			}
			ss << "\n";
		}
		if (getParent()) {
			ss << "root: " << getRoot()->getName();
			if (infolevel > 1) {
				ss << " attitude " << getRoot()->getAttitude() * 180.0/M_PI;
				ss << " position " << getRoot()->getPosition();
				if (getRoot()->asKinematic())
					ss << " speed " << getRoot()->asKinematic()->getVelocity().length();
			}
			ss << "\n";
		}
		if ((infolevel > 2 && (getParent() || tracktarget.valid())) || (infolevel > 1 && !getParent() && !tracktarget)) {
			if (getParent() || tracktarget.valid())
				ss << "local: ";
			ss << "attitude " << getAttitude() * 180.0/M_PI;
			ss << " position " << getPosition();
			ss << " speed " << getVelocity().length();
			ss << "\n";
		}
		infotext->setText(ss.str());
	}
	KinematicObject::update(dt);
}

bool Camera::serialize(const bool full)
{
	if (full) {
		SERIALIZE_Bit(free);
		if (!free) {
			for (int i = 0; i < 12; i++)
				SERIALIZE(limits[i]);
		}
		SERIALIZEf(fovy);
		SERIALIZEf(aspect);
		SERIALIZEf(nearclip);
		SERIALIZEf(farclip);
		SERIALIZEf(rollangle);
		if (tracktarget.valid()) {
			SERIALIZE_1();
			SERIALIZE(tracktarget->GetNetworkID());
			SERIALIZE(trackmode);
			SERIALIZEf(trackspeed);
			SERIALIZEf(trackacc);
			SERIALIZEf(trackdistance);
			SERIALIZEf(trackazimuth);
			SERIALIZEf(trackelevation);
		} else
			SERIALIZE_0();
	}
	return KinematicObject::serialize(full);
}

void Camera::deserialize(const bool full, const double timediff)
{
	if (full) {
		free = DESERIALIZE_Bit();
		if (!free) {
			for (int i = 0; i < 12; i++)
				DESERIALIZE(limits[i]);
		}
		DESERIALIZEf(fovy);
		DESERIALIZEf(aspect);
		DESERIALIZEf(nearclip);
		DESERIALIZEf(farclip);
		DESERIALIZEf(rollangle);
		if (DESERIALIZE_Bit()) {
			NetworkID trackTargetID;
			DESERIALIZE(trackTargetID);
			tracktarget = (BaseObject*) moonet::NetworkManager::instance().getObject(trackTargetID);
			DESERIALIZE(trackmode);
			DESERIALIZEf(trackspeed);
			DESERIALIZEf(trackacc);
			DESERIALIZEf(trackdistance);
			DESERIALIZEf(trackazimuth);
			DESERIALIZEf(trackelevation);
		}
	}
	KinematicObject::deserialize(full, timediff);
}

osg::Vec3 Camera::getVelocity(const bool relative) const
{
	if (tracktarget.valid() && tracktarget->asKinematic() && trackmode != NONE && trackmode != POINT)
		return tracktarget->asKinematic()->getVelocity(relative);
	return KinematicObject::getVelocity(relative);
}

void Camera::setDisplayMode(const unsigned int mode)
{
	if (mode == DISPLAY_DEBUG) {
		if (isActive())
			return;
		if (!debugnode.valid()) {
			osg::Geode* geode = new osg::Geode;
			osg::CompositeShape* cshape = new osg::CompositeShape;
			osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(cshape);
			shapedraw->setColor(osg::Vec4(0.5,0.5,0.5,0.5));
			geode->addDrawable(shapedraw);
			osg::Box *box = new osg::Box(osg::Vec3(0,-1,0), 0.5, 1, 0.5);
			cshape->addChild(box);
			osg::Cone *cone = new osg::Cone(osg::Vec3(0,0,0), 0.25, 1);
			osg::Quat rot;
			rot.makeRotate(osg::Vec3(0,0,1), osg::Vec3(0,-1,0));
			cone->setRotation(rot);
			cshape->addChild(cone);
			osg::Cylinder *cylinder = new osg::Cylinder(osg::Vec3(0,-0.55,-0.5), 0.05, 0.5);
			cshape->addChild(cylinder);
			debugnode = geode;
		}
		addDebugNode(debugnode.get());
	}
	KinematicObject::setDisplayMode(mode);
}

void Camera::setInfoLevel(const int level)
{
	if (level <= 0) {
		if (hud.valid() && infogeode.valid()) {
			hud->removeChild(infogeode.get());
			infogeode = NULL;
			infotext = NULL;
		}
		return;
	} else
		createInfoText();
	infolevel = level;
}

osg::Vec3 Camera::getHUDScale() const
{
	switch (hudmode) {
		case NORMALIZED:
			return osg::Vec3(1,1,1);
		case FOV_DEGREES:
			return osg::Vec3(1.0/(aspect*fovy), 1.0/fovy, 1);
		case FOV_RADIANS:
			return osg::Vec3(1.0/(aspect*fovy*M_PI/180.0), 1.0/(fovy*M_PI/180.0), 1);
	}
	return osg::Vec3(1,1,1);
}

osg::Vec3 Camera::scaleNormalizedCoordinates(const osg::Vec3& vec) const
{
	osg::Vec3 scale = getHUDScale();
	return osg::Vec3(vec.x()/scale.x(), vec.y()/scale.y(), vec.z()/scale.z());
}

void Camera::addComponent(Component *component)
{
	KinematicObject::addComponent(component);	
	if (VisualModel *model = dynamic_cast<VisualModel*> (component)) {
		if (model->hasTag("hud") && model->getNode()) {
			osg::Node *node = model->getNode();
			if (node) {
				if (model->hasTag("normalized")) {
					osg::Vec3 scale = getHUDScale();
					osg::MatrixTransform *transform = dynamic_cast<osg::MatrixTransform*> (node);
					if (transform) {
						transform->setMatrix(osg::Matrix::scale(1.0/scale.x(), 1.0/scale.y(), 1.0/scale.z()) * transform->getMatrix());
					} else {
						transform = new osg::MatrixTransform;
						transform->setMatrix(osg::Matrix::scale(1.0/scale.x(), 1.0/scale.y(), 1.0/scale.z()));
						transform->addChild(node);
						node = transform;
					}
				}
				getHUD()->addChild(node);
				if (model->isInitiallyHidden())
					getHUD()->setChildValue(model->getNode(), false);
				getModelSwitch()->removeChild(model->getNode());
			}
		}
	}
}

void Camera::showAllModels()
{
	getHUD()->setAllChildrenOn();
	KinematicObject::showAllModels();
}

void Camera::hideAllModels()
{
	getHUD()->setAllChildrenOff();
	KinematicObject::hideAllModels();
}

/// Overridden to allow tracked object to be included (with \c tracktarget)
Parameter* Camera::findParameter(const std::string& name)
{
	std::string objectname, param = name;
	std::size_t sepindex = param.find_first_of(" :.,");
	if (sepindex != std::string::npos) {
		objectname = param.substr(0, sepindex);
		param = param.substr(sepindex+1);
	}
	/// \todo Find parameters in components derived from ParameterContainer.
	if (objectname == "tracktarget") {
		if (tracktarget.valid())
			return tracktarget->findParameter(param);
		return NULL;
	}
	return KinematicObject::findParameter(name);
}

Camera::~Camera()
{
	if (isActive())
		deactivate();
}


void Camera::deactivate() {
	dout(5) << "Camera::deactivate " << getName() << "\n";
	if (CameraManipulator::instance().getActiveCamera() == this)
		CameraManipulator::instance().setActiveCamera(NULL);
	unbindControls();
	if (hideWhenActive)
		show(); // show visual node if we have one
	if (hudtransform.valid() && CameraManipulator::instance().getHUDRoot())
		CameraManipulator::instance().getHUDRoot()->removeChild(hudtransform.get());
	// Export active camera to Lua interpreter
	Interpreter::instance().pushGlobal("objects");
	Interpreter::instance().setTable("cam", NULL, "nil");
}

void Camera::createInfoText()
{
	if (infogeode.valid() && infotext.valid())
		return;
	
	infogeode = new osg::Geode;
	
	infotext = new osgText::Text;
	infotext->setText(getName());
	infotext->setCharacterSize(0.03/getHUDScale().x(), 1.5);
	infotext->setPosition(scaleNormalizedCoordinates(osg::Vec3(-0.97,-0.93,0)));
	infotext->setFont("fonts/arial.ttf");
	
	infogeode->addDrawable(infotext.get());
	hud->addChild(infogeode.get());
}

void Camera::switchModel(VisualModel* model, const bool value)
{
	if (!model)
		return;
	getHUD()->setChildValue(model->getNode(), value);
	KinematicObject::switchModel(model, value);
}

osg::ref_ptr<osg::Node> Camera::debugnode = NULL;
