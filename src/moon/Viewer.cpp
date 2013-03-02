#include "Viewer.h"
#include "objects/Camera.h"
#include "Version.h"
#include "SimulationManager.h"
#include "mdraw/FadeText.h"
#include "mdraw/utils.h"
#include "components/VisualModel.h"
//#include "moodyn/Geometry.h"
#include <mlog/Log.h>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <sstream>
#include <osg/io_utils>

using namespace mlog;

namespace moon {

	class ModelViewerHandler : public osgGA::GUIEventHandler {
	public:
		ModelViewerHandler(Viewer *nviewer) : osgGA::GUIEventHandler(), viewer(nviewer), currentModel(0), viewmode(0)
		{
			update();
		}

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
		{
			if (!viewer) return false;
			osg::Switch *modelswitch = viewer->getModelSwitch();
			if (!modelswitch) return false;
			if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
				if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right) {
					currentModel++;
					if (currentModel*2 >= modelswitch->getNumChildren())
						currentModel = 0;
					update();
					return true;
				} else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left) {
					if (currentModel == 0)
						currentModel = modelswitch->getNumChildren()/2;
					currentModel--;
					update();
					return true;
				} else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Tab) {
					viewmode++;
					if (viewmode > 3)
						viewmode = 0;
					update();
					return true;
				}
			}
			return false;
		}

	private:

		void update()
		{
			if (!viewer) return;
			osg::Switch *modelswitch = viewer->getModelSwitch();
			if (!modelswitch) return;
			if (modelswitch->getNumChildren() == 0) return;
			std::stringstream status;
			status << modelswitch->getChild(currentModel*2)->getName() << "\n";
			switch (viewmode) {
				case 0: // visual model
					modelswitch->setSingleChildOn(currentModel*2);
					mdraw::setDebugDrawMode(modelswitch->getChild(currentModel*2), mdraw::NORMAL);
					break;
				case 1: // geometry
					modelswitch->setSingleChildOn(currentModel*2+1);
					mdraw::setDebugDrawMode(modelswitch->getChild(currentModel*2+1), mdraw::NORMAL);
					status << "geometry";
					break;
				case 2: // both
					modelswitch->setSingleChildOn(currentModel*2);
					modelswitch->setValue(currentModel*2+1, true);
					mdraw::setDebugDrawMode(modelswitch->getChild(currentModel*2+1), mdraw::TRANSPARENT);
					status << "normal + geometry";
					break;
				case 3: // wireframe and geometry
					modelswitch->setSingleChildOn(currentModel*2);
					modelswitch->setValue(currentModel*2+1, true);
					mdraw::setDebugDrawMode(modelswitch->getChild(currentModel*2), mdraw::WIREFRAME);
					mdraw::setDebugDrawMode(modelswitch->getChild(currentModel*2+1), mdraw::TRANSPARENT);
					status << "wireframe + geometry";
					break;
			}
			if (modelswitch->getNumChildren() > 2)
				status << " (" << currentModel+1 << " of " << modelswitch->getNumChildren()/2 << ")";
			viewer->setStatusText(status.str());
		}

		osg::observer_ptr<Viewer> viewer;
		unsigned int currentModel;
		unsigned int viewmode;
	};

        class TerrainCoordinatesHandler : public osgGA::GUIEventHandler {
        public:
            TerrainCoordinatesHandler(Viewer *nviewer) : osgGA::GUIEventHandler(), viewer(nviewer) {}

            virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *) {
                if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE) {
                    osgUtil::LineSegmentIntersector::Intersections ixns;
                    viewer->getOsgViewer()->computeIntersections(ea.getX(), ea.getY(), ixns);
                    if (ixns.size() > 0) {
                        osgUtil::LineSegmentIntersector::Intersection ixn = *ixns.begin();
                        osg::Vec3 pos = latLongHeightDeg(ixn.getWorldIntersectPoint());
                        std::stringstream ss;
                        ss << pos;
                        viewer->setStatusText(ss.str());
                    } else
                        viewer->setStatusText("");
                }
            }

            osg::observer_ptr<Viewer> viewer;

        };

	Viewer::Viewer(osgViewer::Viewer *nosgviewer)
	:	osgviewer(nosgviewer),
		running(false),
                viewingModel(false),
                manipulatorIndex(0)
	{
		init();
	}

	void Viewer::setScenario(Scenario *newscenario)
	{
                if (newscenario && viewingModel) {
			dout(ERROR) << "Cannot set scenario when viewing model\n";
			return;
		}
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
		if (scenario.valid())
			root->removeChild(scenario->getRootNode());
		scenario = newscenario;
		osg::ref_ptr<Environment> nullenvironment = new Environment;
		if (scenario.valid()) {
			root->addChild(scenario->getRootNode());
                        unsigned int manipulator = scenario->getManipulator();
                        setManipulator(manipulator);
                        if (manipulator == 0) {
                            if (scenario->getFirstCamera())
                                scenario->getFirstCamera()->activate();
                        } else {
                            osg::Matrixd M = scenario->getViewMatrix();
                            if (M != osg::Matrixd::identity()) {
                                osgviewer->getCameraManipulator()->setByMatrix(osg::Matrix::inverse(M));
                                osg::Vec3 eye, center, up;
                                M.getLookAt(eye, center, up);
                                osgviewer->getCameraManipulator()->setHomePosition(eye,center,up,false);
                            }
                        }
			if (scenario->getEnvironment())
				scenario->getEnvironment()->apply(osgviewer->getCamera());
			else
				nullenvironment->apply(osgviewer->getCamera());
		} else
			nullenvironment->apply(osgviewer->getCamera());
	}

	Scenario* Viewer::getScenario() { return scenario.get(); }

	void Viewer::setStatusText(const std::string& text)
	{
		if (!running && osgviewer->getThreadingModel() != osgViewer::Viewer::SingleThreaded)
			return;
		if (!status_text)
			return;
		if (text.length() == 0)
			hud->setChildValue(status_geode.get(), false);
		else {
			status_text->setText(text);
			hud->setChildValue(status_geode.get(), true);
		}
		if (!running)
			osgviewer->frame(0);
	}

	void Viewer::setBannerText(const std::string& text)
	{
		if (!running && osgviewer->getThreadingModel() != osgViewer::Viewer::SingleThreaded)
			return;
		if (!banner_text)
			return;
		if (text.length() == 0)
			hud->setChildValue(banner_geode.get(), false);
		else {
			banner_text->setText(text);
			hud->setChildValue(banner_geode.get(), true);
		}
		if (!running)
			osgviewer->frame(0);
	}

	void Viewer::setEditMode(const bool value)
	{
		if (!edithandler.valid())
			return;
		edithandler->setEditMode(value);
	}

	bool Viewer::isEditing() const
	{
		if (!edithandler.valid())
			return false;
		return edithandler->isEditing();
	}

	void Viewer::frame(double dt)
	{
	  if (!running && osgviewer->getThreadingModel() != osgViewer::Viewer::SingleThreaded)
	    return;
	  OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
	  osgviewer->frame(dt);
	}

	void Viewer::showConsoleWindow(const bool value)
	{
		hud->setChildValue(consolewindow.get(), value);
	}

	bool Viewer::isConsoleWindowShown()
	{
		return hud->getChildValue(consolewindow.get());
	}

	/**
	 This method "taints" the viewer and renders it unusable for viewing scenarios.
	 Calling setScenario() will fail once this is called.
	 */
	void Viewer::viewModelFile(const std::string& filename)
	{
		ControlHandler::instance().disable();
		osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filename);
		if (!loadedModel)
		{
			dout(ERROR) << "Unknown file type: " << filename << "\n";
			return;
		}
		if (scenario.valid()) {
			dout(ERROR) << "Can't view model file " << filename << " with scenario loaded\n";
			return;
		}
		if (!viewingModel) {
			viewmodel_switch = new osg::Switch;
			viewmodel_switch->setNewChildDefaultValue(false);
			root->addChild(viewmodel_switch.get());
			viewingModel = true;
		}

		// Setup node with special visual nodes extracted and geometry from bounds visualized
		osg::Group *group = new osg::Group;
		group->setName(filename);
		group->addChild(loadedModel.get());
		viewmodel_switch->addChild(group);

		osg::Node *special = VisualModel::extractSpecialNodes(loadedModel.get());
		if (special)
			group->addChild(special);
		/*
		osg::ref_ptr<moodyn::Geometry> geo = new moodyn::Geometry;
		geo->addShapesFromBounds(loadedModel.get());
		osg::Node *geonode = geo->createDebugNode();
		if (geonode)
			viewmodel_switch->addChild(geonode);
		else
			viewmodel_switch->addChild(new osg::Node);
		 */
	}

	int Viewer::run()
	{
		if (viewingModel) {
			osgviewer->addEventHandler(new ModelViewerHandler(this));
			// The following is (almost) copy-paste from osgviewer.cpp
			// set up the camera manipulators.
			{
				osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
				keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
				keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
				keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
				keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );
				osgviewer->setCameraManipulator( keyswitchManipulator.get() );
			}
			// add the state manipulator
			osgviewer->addEventHandler( new osgGA::StateSetManipulator(osgviewer->getCamera()->getOrCreateStateSet()) );
			// add the LOD Scale handler
			osgviewer->addEventHandler(new osgViewer::LODScaleHandler);
			// add the screen capture handler
			osgviewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
			// End osgviewer.cpp code
		}
		running = true;
		int ret = osgviewer->run();
		running = false;
		return ret;
	}

	void Viewer::setDefaultControlBindings()
	{
		ControlBinding pan(Event(Event::MOUSE_MOVE, 0, 0x14), "YawView");
		pan.grab = true;
		pan.resetonrelease = true;
		pan.gain = 3;
		controlhandler->bind(pan);

		ControlBinding tilt(Event(Event::MOUSE_MOVE, 0, 0x24), "PitchView");
		tilt.grab = true;
		tilt.resetonrelease = true;
		tilt.gain = 3;
		controlhandler->bind(tilt);

		controlhandler->bind('w', 's', "MoveView", 1);
		controlhandler->bind('W', 'S', "MoveView", 10);
		controlhandler->bind('d', 'a', "StrafeView", 1);
		controlhandler->bind('D', 'A', "StrafeView", 10);
		controlhandler->bind('q', 'z', "RiseView", 1);
		controlhandler->bind('Q', 'Z', "RiseView", 10);

		controlhandler->bind('e', "Action");
		controlhandler->bind(Event(Event::MOUSE_BUTTON, 0, 1), "Action");
		controlhandler->bind('x', "Exit");
	}

        void Viewer::setManipulator(const unsigned int index)
        {
            if (index) {
                Camera *camera = CameraManipulator::instance().getActiveCamera();
                if (camera)
                    camera->unbindControls();
                if (!keyswitchManipulator) {
                    keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
                    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
                    keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
                    keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
                    keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );
                    osgviewer->addEventHandler(new TerrainCoordinatesHandler(this));
                }
                keyswitchManipulator->selectMatrixManipulator(index-1);
                // This forces the osg viewer to re-interpret coordinate system node
                osgviewer->setSceneData(NULL);
                osgviewer->setSceneData(root.get());

                osgviewer->setCameraManipulator(keyswitchManipulator.get());
            } else {
                osgviewer->setCameraManipulator(&CameraManipulator::instance());
                Camera *camera = CameraManipulator::instance().getActiveCamera();
                if (camera)
                    camera->bindControls();
            }
            manipulatorIndex = index;
        }

        unsigned int Viewer::getManipulator() const
        {
            return manipulatorIndex;
        }

	void Viewer::init()
	{
		running = false;
		initNodes();
		initHandlers();
	}

	void Viewer::initNodes()
	{
		// Create the root node
		root = new osg::Switch();
		root->setName("Root");
		osgviewer->setSceneData(root.get());

		// Setup HUD
		hud = new osg::Switch();
		hud->setName("HUD");
		// Setup HUD camera
		osg::ref_ptr<osg::Camera> hudcamera = new osg::Camera;
		hudcamera->setProjectionMatrix(osg::Matrix::ortho2D(-1,1,-1,1));
		hudcamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		hudcamera->setViewMatrix(osg::Matrix::identity());
		hudcamera->setClearMask(GL_DEPTH_BUFFER_BIT);
		hudcamera->setRenderOrder(osg::Camera::POST_RENDER);
		hudcamera->addChild(hud.get());
		hudcamera->setName("HUD Camera");
		root->addChild(hudcamera.get());
		// Setup HUD states
		osg::StateSet *stateset = hud->getOrCreateStateSet();
		stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHTING, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT0, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT1, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT2, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT3, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT4, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT5, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT6, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_LIGHT7, osg::StateAttribute::PROTECTED | osg::StateAttribute::OFF);
		stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
		stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		//stateset->setAttribute(new osg::PolygonOffset(1.0f,1.0f),osg::StateAttribute::ON);

		// Setup console window
		consolewindow = new mdraw::ConsoleWindow();
		//consolewindow->loadHistory(getSettingsPath() + "/console_history.txt");
		consolehandler = new ConsoleHandler(consolewindow.get());
		consolewindow->setPrompt(">");
		consolewindow->setName("Console");
		hud->addChild(consolewindow.get());
		*consolewindow << MOON_VERSION_STRING << "\n";
		hud->setChildValue(consolewindow.get(), false);

		// Setup status text
		status_text = new osgText::Text;
		status_text->setColor(osg::Vec4(1, 1, 1, 0.8));
		status_text->setPosition(osg::Vec3(0.95,0.95,0));
		status_text->setCharacterSize(0.05,1.5);
		status_text->setFont("fonts/Vera.ttf");
		if (status_text->getFont() == NULL)
			status_text->setFont("Arial.ttf");
		status_text->setAlignment(osgText::Text::RIGHT_CENTER);
		status_text->setText("Initializing...");
		status_geode = new osg::Geode;
		status_geode->addDrawable(status_text.get());
		hud->addChild(status_geode.get());

		// Setup large banner text
		banner_text = new osgText::Text;
		banner_text->setColor(osg::Vec4(0.5, 0.5, 0.5, 0.5));
		banner_text->setFontResolution(96, 96);
		banner_text->setPosition(osg::Vec3(0,0,0));
		banner_text->setCharacterSize(0.2,1);
		banner_text->setFont("fonts/Vera.ttf");
		if (banner_text->getFont() == NULL)
			banner_text->setFont("Arial.ttf");
		banner_text->setAlignment(osgText::Text::CENTER_CENTER);
		banner_geode = new osg::Geode;
		banner_geode->addDrawable(banner_text.get());
		hud->addChild(banner_geode.get());
		hud->setChildValue(banner_geode.get(), false);

		// Setup notify geode (see mdraw::notify())
		osg::Geode *notify_geode = new osg::Geode;
		hud->addChild(notify_geode);
		mdraw::setNotifyGeode(notify_geode);
	}

	void Viewer::initHandlers()
	{
		// Setup camera manipulator
                osgviewer->setCameraManipulator(&CameraManipulator::instance());
		if (hud.valid())
			hud->addChild(CameraManipulator::instance().getHUDRoot());

		// Add event handlers
		osgviewer->addEventHandler(consolehandler.get());

		edithandler = new EditHandler(this);
                osgviewer->addEventHandler(edithandler.get());

		controlhandler = new ControlHandler();
		controlhandler->setViewer(osgviewer);
		controlhandler->initJoysticks();
                osgviewer->addEventHandler(controlhandler.get());

		osg::ref_ptr<osgViewer::StatsHandler> statshandler = new osgViewer::StatsHandler;
		osgviewer->addEventHandler(statshandler.get());
		osg::ref_ptr<osgViewer::WindowSizeHandler> wshandler = new osgViewer::WindowSizeHandler;
		osgviewer->addEventHandler(wshandler.get());
		osg::ref_ptr<osgViewer::ThreadingHandler> thandler = new osgViewer::ThreadingHandler;
		osgviewer->addEventHandler(thandler.get());

		interactionhandler = new InteractionHandler();
                osgviewer->addEventHandler(interactionhandler.get());

		// Set keys for special handlers
		/// \todo Remove these handlers and rewrite with Lua bindings
		statshandler->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F4);
		statshandler->setKeyEventPrintsOutStats(0);
		wshandler->setKeyEventToggleFullscreen(osgGA::GUIEventAdapter::KEY_F5);
		wshandler->setKeyEventWindowedResolutionDown(osgGA::GUIEventAdapter::KEY_F6);
		wshandler->setKeyEventWindowedResolutionUp(osgGA::GUIEventAdapter::KEY_F7);
		thandler->setKeyEventChangeThreadingModel(osgGA::GUIEventAdapter::KEY_F8);
		thandler->setKeyEventChangeEndBarrierPosition(osgGA::GUIEventAdapter::KEY_F9);

	}
} // namespace
