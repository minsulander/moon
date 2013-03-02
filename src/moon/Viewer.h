#ifndef MOON_VIEWER_H
#define MOON_VIEWER_H

#include "ControlHandler.h"
#include "ConsoleHandler.h"
#include "objects/Interactive.h"
#include "mdraw/ConsoleWindow.h"
#include "Scenario.h"
#include "EditMode.h"
#include <osgViewer/Viewer>
#include <osg/Switch>
#include <osgText/Text>
#include <osg/Geode>
#include <osgGA/KeySwitchMatrixManipulator>
#include <string>

namespace moon {
	
	/// \addtogroup core
	/// @{

	/// Scenario viewer, producing the actual graphics
	class Viewer : public osg::Referenced {
	public:
		Viewer(osgViewer::Viewer *osgviewer);
		
		osgViewer::Viewer* getOsgViewer() { return osgviewer; }
		
		/// Set scenario to view
		void setScenario(Scenario *scenario);
		/// Get current viewing scenario
		Scenario* getScenario();
		/// Set status text shown in top right corner of screen
		void setStatusText(const std::string& text);
		/// Set banner text shown transparent across the screen
		void setBannerText(const std::string& text);
		
		void setEditMode(const bool value);
		bool isEditing() const;
		
		/// Advance one frame
		virtual void frame(double dt = USE_REFERENCE_TIME);
		
		/// Get the console window
		mdraw::ConsoleWindow* getConsoleWindow() { return consolewindow.get(); }
		void showConsoleWindow(const bool value = true);
		bool isConsoleWindowShown();
		/// Get the HUD switch node
		osg::Switch* getHUD() { return hud.get(); }
		/// Get the edit mode handler
		EditHandler* getEditHandler() { return edithandler.get(); }

		/// View a model file, emulating the functionality of the \c osgviewer application
		void viewModelFile(const std::string& filename);
		/// Returns true if the viewer is in model view mode
		bool isViewingModel() { return viewingModel; }
		osg::Switch *getModelSwitch() { return viewmodel_switch.get(); }
		
		/// Set a flag indicating frame() will be called continuously
		void setRunning(const bool value) { running = value; }
		bool isRunning() { return running; }
		
		virtual int run();
		
		virtual void setDefaultControlBindings();

                void setManipulator(const unsigned int index);
                unsigned int getManipulator() const;

	private:
		virtual void init();
		virtual void initNodes();
		virtual void initHandlers();
		
		osg::ref_ptr<osgViewer::Viewer> osgviewer;
		
		osg::ref_ptr<osg::Switch> root, hud;
		osg::ref_ptr<ControlHandler> controlhandler;
		osg::ref_ptr<mdraw::ConsoleWindow> consolewindow;
		osg::ref_ptr<ConsoleHandler> consolehandler;
		osg::ref_ptr<Scenario> scenario;
		osg::ref_ptr<EditHandler> edithandler;
		osg::ref_ptr<InteractionHandler> interactionhandler;

		osg::ref_ptr<osgText::Text> status_text;
		osg::ref_ptr<osg::Geode> status_geode;
		osg::ref_ptr<osgText::Text> banner_text;
		osg::ref_ptr<osg::Geode> banner_geode;
		osg::ref_ptr<osg::Switch> viewmodel_switch;

                osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
                unsigned int manipulatorIndex;
		
		bool running;
		bool viewingModel;
		
		OpenThreads::Mutex mutex;
	};

	/// @}
}

#endif
