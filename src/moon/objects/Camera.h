#ifndef MOON_CAMERA_H
#define MOON_CAMERA_H

#include "mlog/Log.h"
#include "moon/Control.h"
#include "KinematicObject.h"

#include <osg/Vec3>
#include <osg/Switch>
#include <osgGA/CameraManipulator>
#include <osg/Transform>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osgText/Text>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
    class Camera;
    class CameraManipulator;
	
	/// OpenSceneGraph matrix manipulator for tying the active Camera to the Viewer
    class MOON_EXPORT CameraManipulator : public osgGA::CameraManipulator {
	public:
		
		META_Object(moon,CameraManipulator);
		CameraManipulator(const CameraManipulator& cam,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY) :
			activecamera(cam.activecamera),
			viewer(cam.viewer),
			defaultAspect(-1)
		{}
		void setViewer(osgViewer::Viewer *viewer);
		virtual void setByMatrix(const osg::Matrix& M);
		virtual void setByInverseMatrix(const osg::Matrix& M);
		virtual osg::Matrix getMatrix() const;
		virtual osg::Matrix getInverseMatrix() const;
		bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
		
		Camera* getActiveCamera();
		void setNoActiveCamera();
		
		osg::Group* getHUDRoot() { return hudroot.get(); }
		
		static CameraManipulator& instance();
		
	protected:			
		CameraManipulator();
                ~CameraManipulator();
		void setActiveCamera(Camera *cam);
		
		static CameraManipulator* instanceptr;
		osg::observer_ptr<Camera> activecamera;
		osg::ref_ptr<osgViewer::Viewer> viewer;
		osg::ref_ptr<osg::Group> hudroot;
		
		double defaultAspect;
		
		friend class Camera;
    };
	
	/// \brief A simulation object that is a controllable camera 
	/// \ingroup objects
    class MOON_EXPORT Camera : public KinematicObject, public ControlListener {
	public:
		
		enum CameraLimit {
			MIN_ROLL,
			MAX_ROLL,
			MIN_PITCH,
			MAX_PITCH,
			MIN_YAW,
			MAX_YAW,
			MIN_FORWARD,
			MAX_FORWARD,
			MIN_RIGHT,
			MAX_RIGHT,
			MIN_UP,
			MAX_UP
		};
		
		enum TrackMode {
			NONE,
			POINT,
			FOLLOW,
			CHASE,
			CHASE_HEADING,
			CHASE_VELOCITY,
			CHASE_HORIZONTAL_VELOCITY
		};
		
		Camera(const std::string& name = "");
		Camera(const Camera& cam,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Camera);
		
		virtual void parseXML(const TiXmlElement* element);
		virtual void writeXML(TiXmlElement* element) const;
		virtual void reset();
		virtual void setResetState();
		
		bool isActive() const { return active; }
		void activate();
		
		void setPerspective(const double fovy, const double aspect, const double nearclip=-1, const double farclip=-1);
		void getPerspective(double& fovy, double& aspect, double& nearclip, double& farclip) const;
		double getFOV() const { return fovy; }
		double getAspect() const { return aspect; }
		double getNearClip() const { return nearclip; }
		double getFarClip() const { return farclip; }
		
		void setFree(const bool flag) { free = flag; }
		bool isFree() const { return free; }
		void setLimit(CameraLimit limit, const double value);
		double getLimit(CameraLimit limit) const;
		void track(BaseObject *target);
		void track(BaseObject *target, TrackMode mode);
		BaseObject* getTrackTarget() { return tracktarget.get(); }
		TrackMode getTrackMode() const { return trackmode; }
		void setTrackParameters(const double distance, const double azimuth, const double elevation);
		double getTrackDistance() const { return trackdistance; }
		double getTrackAzimuth() const { return trackazimuth; }
		double getTrackElevation() const { return trackelevation; }
		void setIgnorePause(const bool flag) { ignorePause = flag; }
		bool ignoresPause() const { return ignorePause; }
		void setHideWhenActive(const bool flag) { hideWhenActive = flag; }
		bool hidesWhenActive() const { return hideWhenActive; }
		void setMove2D(const bool flag) { move2D = flag; }
		bool getMove2D() const { return move2D; }
		void setPivot(const osg::Vec3& newpivot) { pivot = newpivot; }
		const osg::Vec3& getPivot() const { return pivot; }
		
		virtual void controlUpdate(Control* control);
		virtual void update(const double dt);
		
		// Overloaded network methods
		virtual bool serialize(const bool full);
		virtual void deserialize(const bool full, const double timediff);
		
		/// Get velocity, overloaded for correct velocity reading also when tracking an object
		virtual osg::Vec3 getVelocity(const bool relative = false) const;
		
		virtual void setDisplayMode(const unsigned int mode);
		osg::Switch *getHUD() { return hud.get(); }
		void setInfoLevel(const int level);
		int getInfoLevel() const { return infolevel; }
		osg::Vec3 getHUDScale() const;
		osg::Vec3 scaleNormalizedCoordinates(const osg::Vec3& vec) const;
		enum HUDCoordinateMode { NORMALIZED, FOV_DEGREES, FOV_RADIANS };
		void setHUDCoordinateMode(const HUDCoordinateMode mode) { hudmode = mode; }
		HUDCoordinateMode getHUDCoordinateMode() const { return hudmode; }
		
		virtual void addComponent(Component *component);
		virtual void showAllModels();
		virtual void hideAllModels();

		virtual Parameter* findParameter(const std::string& name);

	protected:
		virtual ~Camera();
		void deactivate();
		void createInfoText();
		virtual void switchModel(VisualModel *model, const bool value);
		
	private:
		ListenerControl* rollcontrol;
		ListenerControl* pitchcontrol;
		ListenerControl* yawcontrol;
		ListenerControl* forwardcontrol;
		ListenerControl* rightcontrol;
		ListenerControl* upcontrol;
		ListenerControl* resetcontrol;
		
		bool active;
		bool free;
		float speed;
		float limits[12];
		double rollangle;
		osg::Vec3 origPosition, origAttitude;
		osg::Vec3 pivot;
		
		bool dirtyPerspective;
		double fovy, aspect, nearclip, farclip;
		
		osg::ref_ptr<BaseObject> tracktarget;
		TrackMode trackmode;
		double trackspeed;
		double trackacc;
		double trackdistance;
		double trackazimuth, trackelevation;
		bool ignorePause;
		bool hideWhenActive;
		bool move2D;
		
		static osg::ref_ptr<osg::Node> debugnode;
		osg::ref_ptr<osg::Switch> hud;
		osg::ref_ptr<osg::MatrixTransform> hudtransform;
		osg::ref_ptr<osg::Geode> infogeode;
		osg::ref_ptr<osgText::Text> infotext;
		int infolevel;
		HUDCoordinateMode hudmode;
		
		friend class CameraManipulator;
    };
	
	/// @}
}

#endif
