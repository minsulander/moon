#ifndef MOON_EDITMODE_H
#define MOON_EDITMODE_H

#include "Export.h"
#include "objects/Camera.h"
#include "Scenario.h"
#include <osgGA/GUIEventHandler>
#include <osgManipulator/CommandManager>
#include <osgManipulator/Dragger>
#include <osgManipulator/Selection>
#include <osgManipulator/Constraint>
#include <osgText/Text>
#include <osg/Switch>

namespace moon
{
	/// \addtogroup core
	/// @{
	
	class Viewer; // forward declaration (cyclic dependency)
	
	/// OSG event handler for the Edit mode
	class MOON_EXPORT EditHandler : public osgGA::GUIEventHandler {
	public:
		EditHandler(Viewer *viewer);
		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
		void setKeyEventToggleEditMode(int key) { togglekey = key; }
		void setKeyEventTogglePause(int key) { pausekey = key; }
		void setEditMode(const bool value);
		bool isEditing() { return editmode; }
		moon::BaseObject *getSelectedObject() { return selected_object.get(); }
		void select(moon::BaseObject *object, const bool childSelect = false);
		void setGrid(const float size = 1.f);
		void reset();
		
		enum PlaneType {
			XY_PLANE,
			XZ_PLANE,
			YZ_PLANE
		};

	private:

		enum DraggerType {
			NONE,
			TABBOX,
			TABPLANE,
			TABPLANE_TRACKBALL,
			TRACKBALL,
			TRANSLATE1D,
			TRANSLATE2D,
			TRANSLATEAXIS,
			NUM_DRAGGER_TYPES
		};
		
		osgManipulator::Dragger* createDragger(DraggerType type);
		void setDragger(DraggerType type);
		void updateStatusText();
		void updateVisuals();
		void updateHelperNodes();
		void updateMouseDrag();
		void visualizeAnimationPath(KinematicObject *object);
		void commitChanges();
		
		int togglekey, pausekey;
		int lastButtonPressed;
		bool editmode;
		DraggerType current_dragger;
		PlaneType current_plane;
		bool altplane;
		bool world_coord, grid, clamp, align, dragging;
		float gridsize;
		float drag_x, drag_y;
		unsigned int template_index;
		
		osg::ref_ptr<Camera> prevcam, editcam;
		osg::ref_ptr<moon::BaseObject> selected_object, paste_object;
		osg::ref_ptr<osgManipulator::CommandManager> commandmanager;
		osg::ref_ptr<osgManipulator::Dragger> dragger;
		osg::ref_ptr<osgManipulator::Selection> selection;
		osg::ref_ptr<osg::Group> dragger_group;
        osgManipulator::PointerInfo pointer;
		osg::ref_ptr<osgManipulator::GridConstraint> gridconstraint;
		osg::ref_ptr<osg::Geode> status_geode;
		osg::ref_ptr<osgText::Text> status_text;
		osg::ref_ptr<osg::Geode> help_geode;
		osg::ref_ptr<osgText::Text> help_text;
		osg::ref_ptr<osg::Switch> nodes_switch;
		osg::ref_ptr<osg::MatrixTransform> fall_line_transform;
		osg::Vec3 fall_line_offset;
		osg::ref_ptr<osg::MatrixTransform> marker_transform;
		osg::ref_ptr<osg::MatrixTransform> gridplane_transform;
		osg::Vec3 markerpos;
		float marker_distance;
		osg::observer_ptr<osg::Node> animationPathNode;
		int animationPathIndex;
		
		osg::ref_ptr<Scenario> scenario;
		osg::ref_ptr<Viewer> viewer;
		
		osg::Matrix undomatrix, pastematrix;
				
		static const char* helpText;
	};

	/// @}
}

#endif
