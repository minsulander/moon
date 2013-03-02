#include "EditMode.h"
#include "Viewer.h"
#include "SimulationManager.h"
#include "Interpreter.h"
#include "ObjectFactory.h"
#include "Destructible.h"
#include "mdraw/utils.h"
#include "mdraw/FadeText.h"
#include "mdraw/AnimationPathNode.h"
#include "mdraw/GridPlane.h"
#include <osgManipulator/TabBoxDragger>
#include <osgManipulator/TabPlaneDragger>
#include <osgManipulator/TabPlaneTrackballDragger>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osg/io_utils>
#include <iomanip>

using namespace mlog;

namespace moon
{
	
#ifdef WIN32
double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
#endif

	osg::Node* createMarkerNode()
	{
		osg::Geode *geode = new osg::Geode;
		osg::Geometry *geometry = new osg::Geometry;

		osg::Vec3Array *vertices = new osg::Vec3Array;
		vertices->push_back(osg::Vec3( -1, 0, 0 ));
		vertices->push_back(osg::Vec3( 1, 0, 0 ));
		vertices->push_back(osg::Vec3( 1, 0, 0 ));
		vertices->push_back(osg::Vec3( 0.8, 0.1, 0 ));
		vertices->push_back(osg::Vec3( 1, 0, 0 ));
		vertices->push_back(osg::Vec3( 0.8, -0.1, 0 ));
		vertices->push_back(osg::Vec3( 0, -1, 0 ));
		vertices->push_back(osg::Vec3( 0, 1, 0 ));
		vertices->push_back(osg::Vec3( 0, 1, 0 ));
		vertices->push_back(osg::Vec3( 0.1, 0.8, 0 ));
		vertices->push_back(osg::Vec3( 0, 1, 0 ));
		vertices->push_back(osg::Vec3( -0.1, 0.8, 0 ));
		vertices->push_back(osg::Vec3( 0, 0, -1 ));
		vertices->push_back(osg::Vec3( 0, 0, 1 ));
		vertices->push_back(osg::Vec3( 0, 0, 1 ));
		vertices->push_back(osg::Vec3( 0.1, 0, 0.8 ));
		vertices->push_back(osg::Vec3( 0, 0, 1 ));
		vertices->push_back(osg::Vec3( -0.1, 0, 0.8 ));
		vertices->push_back(osg::Vec3( 0, 0, -1 ));
		vertices->push_back(osg::Vec3( 0, 0, -1000 ));
		geometry->setVertexArray(vertices);

        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
        colors->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
        colors->push_back(osg::Vec4(0.5f,0.5f,0.5f,1.0f));
        geometry->setColorArray(colors);
        geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,vertices->size()));
        geode->addDrawable(geometry);

		osg::StateSet *stateset = geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

		return geode;
	}
	
	osg::Node *createPlaneAxesNode(float gridbounds, EditHandler::PlaneType plane)
	{
		osg::Geode *geode = new osg::Geode;
		osg::Geometry *geometry = new osg::Geometry;
		
		osg::Vec3Array *vertices = new osg::Vec3Array;
		switch (plane) {
			case EditHandler::XY_PLANE:
				vertices->push_back(osg::Vec3( gridbounds, 0, 0 ));
				vertices->push_back(osg::Vec3( gridbounds*1.5, 0, 0 ));
				vertices->push_back(osg::Vec3( 0, gridbounds, 0 ));
				vertices->push_back(osg::Vec3( 0, gridbounds*1.5, 0 ));
				break;
			case EditHandler::XZ_PLANE:
				vertices->push_back(osg::Vec3( gridbounds, 0, 0 ));
				vertices->push_back(osg::Vec3( gridbounds*1.5, 0, 0 ));
				vertices->push_back(osg::Vec3( 0, 0, gridbounds ));
				vertices->push_back(osg::Vec3( 0, 0, gridbounds*1.5 ));
				break;
			case EditHandler::YZ_PLANE:
				vertices->push_back(osg::Vec3( 0, gridbounds, 0 ));
				vertices->push_back(osg::Vec3( 0, gridbounds*1.5, 0 ));
				vertices->push_back(osg::Vec3( 0, 0, gridbounds ));
				vertices->push_back(osg::Vec3( 0, 0, gridbounds*1.5 ));
				break;
		}
		geometry->setVertexArray(vertices);
		
        osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
        geometry->setColorArray(colors);
        geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
		
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,vertices->size()));
        geode->addDrawable(geometry);
		
		osg::StateSet *stateset = geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		
		return geode;
	}
	
	osg::Node *createFallLineNode()
	{
		osg::Geode *geode = new osg::Geode;
		osg::Geometry *geometry = new osg::Geometry;
		
		osg::Vec3Array *vertices = new osg::Vec3Array;
		vertices->push_back(osg::Vec3( 0, 0, 0 ));
		vertices->push_back(osg::Vec3( 0, 0, -1000 ));
		geometry->setVertexArray(vertices);
		
        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(0.5f,0.5f,0.5f,1.0f));
        geometry->setColorArray(colors);
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,vertices->size()));
        geode->addDrawable(geometry);
		
		osg::StateSet *stateset = geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		return geode;
	}
	
	osg::Vec3 snapToGrid(const osg::Vec3& pos, const osg::Vec3& origo, const float gsize)
	{
		osg::Vec3 ret;
		ret.x() = round((pos.x()-origo.x())/gsize)*gsize + origo.x();
		ret.y() = round((pos.y()-origo.y())/gsize)*gsize + origo.y();
		ret.z() = round((pos.z()-origo.z())/gsize)*gsize + origo.z();
		return ret;
	}
	
	EditHandler::EditHandler(Viewer *nviewer)
	:	togglekey(0),
		pausekey(0),
		lastButtonPressed(-1),
		editmode(false),
		current_dragger(NONE),
		current_plane(XY_PLANE),
		altplane(false),
		world_coord(true),
		grid(false),
		clamp(false),
		align(false),
		dragging(false),
		gridsize(1.f),
		template_index(0),
		marker_distance(50.0),
		viewer(nviewer)
	{
		commandmanager = new osgManipulator::CommandManager;
		
		status_text = new osgText::Text;
		status_text->setColor(osg::Vec4(1, 1, 1, 0.8));
		status_text->setPosition(osg::Vec3(-1,0.95,0));
		status_text->setCharacterSize(0.04,1.5);
		status_text->setFont("fonts/Vera.ttf");
		if (status_text->getFont() == NULL)
			status_text->setFont("Arial.ttf");
		//status_text->setAlignment(osgText::Text::RIGHT_TOP);
		status_text->setBackdropType(osgText::Text::OUTLINE);
		status_geode = new osg::Geode;
		status_geode->addDrawable(status_text.get());
		status_geode->setName("Edit mode status text");
		
		help_text = new osgText::Text;
		help_text->setColor(osg::Vec4(1, 1, 1, 0.8));
		help_text->setPosition(osg::Vec3(-0.98,0.98,0));
		help_text->setCharacterSize(0.05,1.5);
		help_text->setFont("fonts/VeraMono.ttf");
		help_text->setAlignment(osgText::Text::LEFT_TOP);
		help_text->setBackdropType(osgText::Text::OUTLINE);
		help_text->setText(helpText);
		help_geode = new osg::Geode;
		help_geode->addDrawable(help_text.get());
		help_geode->setName("Edit mode help text");

		// Create a background box for the help text
		osg::Vec3Array* boxvecs = new osg::Vec3Array(4);
		(*boxvecs)[0] = osg::Vec3(-1,-1,0);
		(*boxvecs)[1] = osg::Vec3(-1,1,0);
		(*boxvecs)[2] = osg::Vec3(1,1,0);
		(*boxvecs)[3] = osg::Vec3(1,-1,0);
		osg::Geometry* boxgeometry = new osg::Geometry;
		boxgeometry->setVertexArray(boxvecs);
		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(0,0,0,0.5));
		boxgeometry->setColorArray(colors);
		boxgeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		boxgeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
		help_geode->addDrawable(boxgeometry);
		
		nodes_switch = new osg::Switch;
		fall_line_transform = new osg::MatrixTransform;
		fall_line_transform->addChild(createFallLineNode());
		nodes_switch->addChild(fall_line_transform.get());
		
		marker_transform = new osg::MatrixTransform;
		marker_transform->addChild(createMarkerNode());
		nodes_switch->addChild(marker_transform.get());
		
		gridplane_transform = new osg::MatrixTransform;
		nodes_switch->addChild(gridplane_transform.get());
	}
	
	bool EditHandler::handle (const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
	{
		if (viewer->isViewingModel())
			return false;
		
		if (ea.getHandled())
			return false;
		
		if (editmode && ea.getEventType() == osgGA::GUIEventAdapter::FRAME) {
			if (selected_object.valid() && selected_object->getRemoveTime() > 1e-5 
				&& SimulationManager::instance().getTime() >= selected_object->getRemoveTime()) {
					select(NULL);
			}
			updateVisuals();
			if (dragging)
				updateMouseDrag();
                        if (editcam.valid() && viewer->getManipulator() != 0) {
                            osg::Matrix M = viewer->getOsgViewer()->getCamera()->getInverseViewMatrix();
                            editcam->setTransformMatrix(osg::Matrix::rotate(-M_PI/2, osg::Vec3(1,0,0)) * M);
                            //viewer->setManipulator(0);
                        }
                        return true;
		}

		if (pausekey && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN && ea.getKey() == pausekey) {
			bool paused = !SimulationManager::instance().isPaused();
			SimulationManager::instance().setPaused(paused);
			return true;
		} else if (togglekey && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN && ea.getKey() == togglekey) {
			setEditMode(!editmode);
			return true;
		}
		
		if (!editmode)
			return false;
		
		// Need to remember last mouse button pushed since ea.getButton() doesn't work for DRAG events
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
			lastButtonPressed = ea.getButton();
		
		// Alt - switch plane
		if (altplane && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP
			&& !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_ALT)) {
			switch (current_plane) {
				case XZ_PLANE: current_plane = XY_PLANE; break;
				case YZ_PLANE: current_plane = XZ_PLANE; break;
				case XY_PLANE: current_plane = YZ_PLANE; break;
			}
			altplane = false;
			gridplane_transform->removeChildren(0, gridplane_transform->getNumChildren());
		}
		
		// Setup direction for gridded arrow key movement based on selected plane
		float direction = 1;
		osg::Vec3 right, up;
		switch (current_plane) {
			case XY_PLANE: right = osg::Vec3(1,0,0); up = osg::Vec3(0,1,0); break;
			case XZ_PLANE: right = osg::Vec3(1,0,0); up = osg::Vec3(0,0,1); break;
			case YZ_PLANE: right = osg::Vec3(0,1,0); up = osg::Vec3(0,0,1); break;
		}
		if (world_coord) {
                    /*
                    if (selected_object.valid() && selected_object->isGeocentric()) {
                        osg::Matrix LWM = selected_object->getLocalToWorldMatrix();
                        right = LWM.getRotate().inverse() * right;
                        up = LWM.getRotate().inverse() * up;
                    }
                    */
                    right = osg::Matrix::rotate(editcam->getAttitude().x(), osg::Vec3(0,0,1)) * right;
                    up = osg::Matrix::rotate(editcam->getAttitude().x(), osg::Vec3(0,0,1)) * up;
		}
		if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
			
			// Alt - switch plane
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Alt_L || ea.getKey() == osgGA::GUIEventAdapter::KEY_Alt_R) {
				switch (current_plane) {
					case XY_PLANE: current_plane = XZ_PLANE; break;
					case XZ_PLANE: current_plane = YZ_PLANE; break;
					case YZ_PLANE: current_plane = XY_PLANE; break;
				}
				altplane = true;
				gridplane_transform->removeChildren(0, gridplane_transform->getNumChildren());
			}
			
			if ((ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL
				|| ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_META
				|| ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SUPER)
				&& !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT)) {
				if (ea.getKey() == 'r' || ea.getKey()+'a'-1 == 'r') {
					// Ctrl-R or Cmd-R: Reset scenario
					reset();
					return true;
				} else if (ea.getKey() == 's' || ea.getKey()+'a'-1 == 's') {
					// Ctrl-S or Cmd-S: Save
					if (Interpreter::instance().pushNamed("event.editorSave")) {
						if (Interpreter::instance().pCall(0,0) != 0)
							dout(ERROR, SCRIPT) << Interpreter::instance().getError() << "\n";
					} else
						dout(ERROR, SCRIPT) << "No event.editorSave() script\n";
					return true;
				} else if (ea.getKey() == 'h' || ea.getKey()+'a'-1 == 'h') {
					editcam->getHUD()->setChildValue(help_geode.get(), !editcam->getHUD()->getChildValue(help_geode.get()));
					return true;
				} else if (ea.getKey() == 'p' || ea.getKey()+'a'-1 == 'p') {
					// Ctrl-T or Cmd-T: Print out current object to terminal
					if (selected_object.valid()) {
						BaseObject *writeObject = selected_object.get();
						if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_ALT)
							writeObject = (BaseObject*) selected_object->getTemplate();
						if (writeObject) {
							TiXmlElement *element;
							if (writeObject->getTemplate())
								element = new TiXmlElement(writeObject->getTemplate()->getName());
							else
								element = new TiXmlElement(writeObject->libraryName() + std::string("_") + writeObject->className());
							writeObject->writeXML(element);
							element->Print(stdout, 0);
							std::cout << "\n";
							delete element;
						}
					}
					return true;
				} else if (ea.getKey() == 'c' || ea.getKey()+'a'-1 == 'c') {
					// Ctrl-C or Cmd-C: Copy
					if (selected_object.valid()) {
						dout(5) << "copy " << selected_object->getName() << "\n";
						paste_object = selected_object.get();
					}
					return true;
				} else if (ea.getKey() == 'x' || ea.getKey()+'a'-1 == 'x') {
					// Ctrl-X or Cmd-X: Cut
					if (selected_object.valid()) {
						dout(5) << "cut " << selected_object->getName() << "\n";
						paste_object = selected_object.get();
						scenario->removeComponent(selected_object.get());
						select(NULL);
					}
					return true;
				} else if (ea.getKey() == 'v' || ea.getKey()+'a'-1 == 'v') {
					// Ctrl-V or Cmd-V: Cut
					if (paste_object.valid()) {
						BaseObject *object = dynamic_cast<BaseObject*> (paste_object->clone(osg::CopyOp::SHALLOW_COPY));
						if (object) {
							object->setName(object->getName() + " copy");
							object->setPosition(markerpos);
							object->setResetState();
							scenario->addComponent(object, true);
							dout(5) << "paste " << object->getName() << "\n";
							select(object);
							if (align)
								object->alignToTerrain();
							if (clamp)
								object->clampToTerrain();
							object->setResetState();
						}
					}
					return true;
				} else if (ea.getKey() == 't' || ea.getKey()+'a'-1 == 't') {
					// Ctrl-T: Copy transform
					if (selected_object.valid())
						pastematrix = selected_object->getTransformMatrix();
					return true;
				} else if (ea.getKey() == 'y' || ea.getKey()+'a'-1 == 'y') {
					// Ctrl-Y: Paste transform
					if (selected_object.valid()) {
						selected_object->setTransformMatrix(pastematrix);
						commitChanges();
					}
					return true;
				} else if (ea.getKey() == 'u' || ea.getKey()+'a'-1 == 'u') {
					// Ctrl-U: Paste transform rotation
					if (selected_object.valid()) {
						selected_object->setRotation(pastematrix.getRotate());
						commitChanges();
					}
					return true;
				}
			}
			
			switch (ea.getKey()) {
					
				case 't': // Cycle template
					template_index++;
					if (!ObjectFactory::instance().getTemplate(template_index))
						template_index = 0;
					updateStatusText();
					return true;
				case 'T': // Cycle template (reverse)
					template_index--;
					if (!ObjectFactory::instance().getTemplate(template_index))
						template_index = ObjectFactory::instance().getNumTemplates()-1;
					updateStatusText();
					return true;
					
				case 'n': { // New instance of selected/template object
					const FactoryProduct *templateObject = ObjectFactory::instance().getTemplate(template_index);
					FactoryProduct *product = ObjectFactory::instance().createInstance(templateObject);
					scenario->addComponent(dynamic_cast<Component*> (product), true);
					BaseObject *object = dynamic_cast<BaseObject*> (product);
					if (object) {
						object->setPosition(markerpos);
						select(object);
						if (align)
							object->alignToTerrain();
						if (clamp)
							object->clampToTerrain();
						object->setResetState();
					}
					updateStatusText();
					return true;
				}
				case 'p': { // Cycle plane for editing
					switch (current_plane) {
						case XY_PLANE: current_plane = XZ_PLANE; break;
						case XZ_PLANE: current_plane = YZ_PLANE; break;
						default: current_plane = XY_PLANE; break;
					}
					if (current_dragger == TRANSLATE2D)
						setDragger(current_dragger); // reset it
					updateStatusText();
					return true;
				}
				case 'g': // Toggle grid
					grid = !grid;
					if (dragger.valid())
						setDragger(current_dragger); // reset it
					updateStatusText();
					return true;
				case 'h': // Increase grid size
                                    if (grid) {
                                        if (gridsize < 1)
                                            gridsize = 1;
                                        else {
                                            int gridi = round(gridsize);
                                            gridi *= 10;
                                            gridsize = gridi;
                                        }
                                        if (dragger.valid())
                                            setDragger(current_dragger); // reset it
                                    }
                                    gridplane_transform->removeChildren(0, gridplane_transform->getNumChildren());
                                    return true;
				case 'H': // Decrease grid size
					if (grid) {
                                            if (gridsize > 1) {
                                                int gridi = round(gridsize);
                                                gridi /= 10;
                                                gridsize = gridi;
                                            } else if (gridsize > 0.1)
                                                gridsize = 0.1;
						if (dragger.valid())
							setDragger(current_dragger); // reset it						
					}
					gridplane_transform->removeChildren(0, gridplane_transform->getNumChildren());
					return true;
				case 'b': // Toggle world/body coordinate editing
					world_coord = !world_coord;
					if (dragger.valid())
						setDragger(current_dragger); // reset it
					updateStatusText();
					return true;
					
				case 'V': // Cycle global visual display mode
					if (scenario->getDisplayMode() == BaseObject::DISPLAY_NORMAL)
						scenario->setDisplayMode(BaseObject::DISPLAY_DEBUG);
					else
						scenario->setDisplayMode(BaseObject::DISPLAY_NORMAL);
					editcam->hide();
					return true;
				case 'C': // Set clamp flag
					clamp = !clamp;
					return true;
				case 'X': // Set align flag
					align = !align;
					return true;
				case 'P': { // Visualize animation path
					if (animationPathNode.valid()) {
						animationPathNode->getParent(0)->removeChild(animationPathNode.get());
						if (animationPathIndex >= 0) {
							selected_object->asKinematic()->setTransformationUpdatesControlPoint(-1);
							selected_object->asKinematic()->setAnimationPaused(false);
						}
					} else if (selected_object.valid()) {
						KinematicObject *kinematic = selected_object->asKinematic();
						if (kinematic)
							visualizeAnimationPath(kinematic);
					}
					return true;
				}
				case '1': { // Pivot camera around marker
					if (editcam->getPivot().length() < 1e-5) {
						editcam->setPivot(osg::Vec3(0,marker_distance,0));
					} else
						editcam->setPivot(osg::Vec3(0,0,0));
					return true;
				}
				case '2': { // 2D editing mode
					if (!editcam->getMove2D()) {
						if (editcam->getTrackMode() == Camera::POINT)
							editcam->track(editcam->getTrackTarget(), Camera::FOLLOW);
						editcam->setPosition(markerpos+osg::Vec3(0,0,marker_distance));
						editcam->setTrackParameters(marker_distance,0,-M_PI/2.0);
						editcam->setAttitude(0,-M_PI/2.0,0);
						editcam->setMove2D(true);
					} else {
						// Reset to 3D view at 45 degree azimuth and elevation
						double s45 = sin(M_PI/4.0);
						editcam->setPosition(markerpos+osg::Vec3(marker_distance*s45*s45,-marker_distance*s45*s45,marker_distance*s45));
						editcam->setTrackParameters(marker_distance,-M_PI/4.0,-M_PI/4.0);
						editcam->setAttitude(-M_PI/4.0,-M_PI/4.0,0);
						editcam->setMove2D(false);
					}
					return true;
				}
				case osgGA::GUIEventAdapter::KEY_Down:
				case osgGA::GUIEventAdapter::KEY_Left:
					direction = -1;
				case osgGA::GUIEventAdapter::KEY_Up:
				case osgGA::GUIEventAdapter::KEY_Right: { // Gridded marker/cam movement
					if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT) {
						osg::Vec3 vec;
						if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up || ea.getKey() == osgGA::GUIEventAdapter::KEY_Down)
							vec = up;
						else
							vec = right;
						direction *= gridsize;
						osg::Vec3 pos = editcam->getPosition() + vec*direction;
						// snap to grid
						if (grid)
							editcam->setPosition(snapToGrid(pos, osg::Vec3(0,0,0), gridsize));
						else
							editcam->setPosition(pos);
						return true;
					}
				}
			}
		}
			
		// Manipulator handling - inspired by osgmanipulator example
		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
		if (!view) return false;
		
		switch (ea.getEventType())
		{
			case osgGA::GUIEventAdapter::PUSH:
			{
				osgUtil::LineSegmentIntersector::Intersections intersections;
				
				pointer.reset();
				
				if (view->computeIntersections(ea.getX(),ea.getY(),intersections))
				{
					pointer.setCamera(view->getCamera());
					pointer.setMousePosition(ea.getX(), ea.getY());
					
					for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
						hitr != intersections.end();
						++hitr)
					{
						pointer.addIntersection(hitr->nodePath, hitr->getLocalIntersectPoint());
					}
					for (osg::NodePath::iterator itr = pointer._hitList.front().first.begin();
						 itr != pointer._hitList.front().first.end();
						 ++itr)
					{
						osgManipulator::Dragger* thedragger = dynamic_cast<osgManipulator::Dragger*>(*itr);
						if (thedragger)
						{
							if (thedragger->handle(pointer, ea, aa)) {
								return true;
							}
							break;
						}                   
					}
				}
			}
			case osgGA::GUIEventAdapter::DRAG:
			case osgGA::GUIEventAdapter::RELEASE:
			{
				if (dragger.valid()) {
					pointer._hitIter = pointer._hitList.begin();
					pointer.setCamera(view->getCamera());
					pointer.setMousePosition(ea.getX(), ea.getY());
					
					if (dragger->handle(pointer, ea, aa)) {
						if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
							commitChanges();
						return true;
					}
					break;
				}
				break;
			}
			default:
				break;
		}
		
		if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
		{
			//dragger = 0;
			pointer.reset();
		}
		// End manipulator handling
		
		// Editing key strokes
		if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN && selected_object.valid()) {
			switch (ea.getKey()) {
					
				case osgGA::GUIEventAdapter::KEY_Delete:
				case osgGA::GUIEventAdapter::KEY_BackSpace:
					// Delete object
					dout(5) << "delete " << selected_object->getName() << "\n";
					scenario->removeComponent(selected_object.get());
					select(NULL);
					break;
					
				case 'u': // Undo
					selected_object->getTransform()->setMatrix(undomatrix);
					if (selection.valid())
						selection->setMatrix(osg::Matrix::identity());
					setDragger(current_dragger);
					commitChanges();
					updateStatusText();
					return true;
					
					// Gridded movement
				case osgGA::GUIEventAdapter::KEY_Down:
				case osgGA::GUIEventAdapter::KEY_Left:
					direction = -1;
				case osgGA::GUIEventAdapter::KEY_Up:
				case osgGA::GUIEventAdapter::KEY_Right: {
					osg::Vec3 vec, rvec;
                                        if (world_coord) {
                                            osg::Matrix WM = selected_object->getWorldTransformMatrix();
                                            osg::Quat rot = WM.getRotate().inverse();
                                            right = rot*right;
                                            up = rot*up;
                                        }
					if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up || ea.getKey() == osgGA::GUIEventAdapter::KEY_Down) {
						vec = up;
						rvec = right;
					} else {
						vec = right;
						rvec = up ^ right;
					}
					if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
						selected_object->rotate(M_PI/12.0*direction,rvec);
					else
						selected_object->move(vec*direction*gridsize);
					// snap to grid
					if (grid && world_coord) {
						if (selected_object->getParent()) {
							osg::Vec3 pos = snapToGrid(selected_object->getWorldTransformMatrix().getTrans(), osg::Vec3(0,0,0), gridsize);
							osg::Matrix pWM = selected_object->getParent()->getWorldTransformMatrix();
							pos = pWM.getRotate().inverse() * (pos - pWM.getTrans());
							selected_object->setPosition(pos);
						} else 
							selected_object->setPosition(snapToGrid(selected_object->getPosition(), osg::Vec3(0,0,0), gridsize));
					}
					// align & clamp if needed
					if (align)
						selected_object->alignToTerrain();
					if (clamp)
						selected_object->clampToTerrain();
					commitChanges();
					return true;
				}
					
				case osgGA::GUIEventAdapter::KEY_Tab: { // Select manipulator
					switch (current_dragger) {
						case NONE: setDragger(TRANSLATEAXIS); break;
						case TRANSLATEAXIS: setDragger(TRANSLATE2D); break;
						case TRANSLATE2D: setDragger(TRACKBALL); break;
						case TRACKBALL: setDragger(TABBOX); break;
						default: setDragger(NONE); break;					
					}
					updateStatusText();
					return true;
				}
					
				case 'f': // "Fall" - place object on nearest surface below it
					selected_object->clampToTerrain();
					commitChanges();
					break;
				case 'F': // Fall and align to ground normal
					selected_object->alignToTerrain();
					selected_object->clampToTerrain();
					commitChanges();
					break;
				case 'G': // Align to ground (like F but without the fall)
					selected_object->alignToTerrain();
					commitChanges();
					break;
				case 'm': // Move selected object to marker
					selected_object->setPosition(markerpos);
					commitChanges();
					return true;
				case 'M': // Copy camera matrix
					selected_object->setTransformMatrix(editcam->getTransformMatrix());
					commitChanges();
					return true;
				case 'k': { // Cycle camera track mode
					if (!editcam->getTrackTarget())
						editcam->track(selected_object.get(), moon::Camera::FOLLOW);
					else if (editcam->getTrackMode() == moon::Camera::FOLLOW && !editcam->getMove2D())
						editcam->track(selected_object.get(), moon::Camera::POINT);
					else {
						editcam->track(NULL);
						if (editcam->getMove2D()) {
							editcam->setAttitude(0,-M_PI/2.0,0);
							editcam->setPosition(selected_object->getPosition()+osg::Vec3(0,0,editcam->getTrackDistance()));
						}
					}
					return true;
				}
				case ' ' : { // Move marker to object
					osg::Vec3 dpos = selected_object->getPosition() - markerpos;
					editcam->setPosition(editcam->getPosition() + dpos);
					return true;
				}
				case 'r': { // Replace selected object with new instance of template
					const FactoryProduct *templateObject = ObjectFactory::instance().getTemplate(template_index);
					FactoryProduct *product = ObjectFactory::instance().createInstance(templateObject);
					scenario->addComponent(dynamic_cast<Component*> (product));
					BaseObject *object = dynamic_cast<BaseObject*> (product);
					if (object) {
						object->setPosition(selected_object->getPosition());
						object->setAttitude(selected_object->getAttitude());
						scenario->removeComponent(selected_object.get());
						select(object);
					}
					return true;
				}
				case 'v': { // Change visual display mode
					if (selected_object->getDisplayMode() == BaseObject::DISPLAY_DEBUG)
						selected_object->setDisplayMode(BaseObject::DISPLAY_NORMAL);
					else
						selected_object->setDisplayMode(BaseObject::DISPLAY_DEBUG);
					return true;
				}
				case 'U': // Unselect
					select(NULL);
					return true;
				case '=': { // Unselect animation control point
					if (selected_object->asKinematic() && selected_object->asKinematic()->getAnimationPath()) {
						animationPathIndex = -1;
						selected_object->asKinematic()->setTransformationUpdatesControlPoint(animationPathIndex);
						selected_object->asKinematic()->setAnimationPaused(false);
					}
					return true;
				}
				case '+': { // Next animation control point
					if (selected_object->asKinematic() && selected_object->asKinematic()->getAnimationPath()) {
						osg::AnimationPath::TimeControlPointMap& cpmap = selected_object->asKinematic()->getAnimationPath()->getTimeControlPointMap();
						animationPathIndex++;
						if (animationPathIndex >= (int)cpmap.size())
							animationPathIndex = 0;
						selected_object->asKinematic()->setAnimationPaused(true, animationPathIndex);
						selected_object->asKinematic()->setTransformationUpdatesControlPoint(animationPathIndex);
					}
					return true;
				}
				case '-': { // Previous animation control point
					if (selected_object->asKinematic() && selected_object->asKinematic()->getAnimationPath()) {
						osg::AnimationPath::TimeControlPointMap& cpmap = selected_object->asKinematic()->getAnimationPath()->getTimeControlPointMap();
						animationPathIndex--;
						if (animationPathIndex < 0)
							animationPathIndex = cpmap.size()-1;
						selected_object->asKinematic()->setAnimationPaused(true, animationPathIndex);
						selected_object->asKinematic()->setTransformationUpdatesControlPoint(animationPathIndex);
					}
					return true;
				}
				case '!': { // Destroy selected object
					if (moon::Destructible *destructible = dynamic_cast<Destructible*> (selected_object.get())) {
						destructible->destroy();
					}
					return true;
				}

			}

		} else if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH && ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			// Select object
                        moon::BaseObject *picked_object = ControlHandler::instance().pick(ea.getX(), ea.getY());
                        moon::BaseObject *prev_selected = selected_object.get();
                        if (picked_object && (picked_object->hasTag("noselect") || picked_object->getRoot()->hasTag("noselect")))
				select(NULL);
			else
				select(picked_object, (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL) != 0);
			updateStatusText();
                        if (selected_object != prev_selected)
                            return true;
			return false;

		} else if (ea.getEventType() == osgGA::GUIEventAdapter::DRAG && lastButtonPressed == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && selected_object.valid()) {
			// Drag object
			dragging = true;
			drag_x = ea.getXnormalized();
			drag_y = ea.getYnormalized();
			commitChanges();
                        return true;
		} else if (dragging && ea.getEventType() == osgGA::GUIEventAdapter::SCROLL && selected_object.valid()) {
			// Drag-scroll (move forward/back) object
			float magnitude = gridsize;
			osg::Vec3 savepos = selected_object->getPosition();
			osg::Vec3 v = selected_object->getPosition() - editcam->getPosition();
			v.normalize();
			float x = ea.getScrollingDeltaX(), y = ea.getScrollingDeltaY();
			switch (ea.getScrollingMotion()) {
				case osgGA::GUIEventAdapter::SCROLL_LEFT: x = -1; break;
				case osgGA::GUIEventAdapter::SCROLL_RIGHT: x = 1; break;
				case osgGA::GUIEventAdapter::SCROLL_UP: y = 1; break;
				case osgGA::GUIEventAdapter::SCROLL_DOWN: y = -1; break;
				default: break;
			}
			osg::Vec3 pos = selected_object->getPosition() + v * y * magnitude;
			// snap to grid
			if (grid) {
				if (!world_coord) {
					osg::Vec3 dpos = pos - selected_object->getPosition();
					osg::Vec3 dposB = selected_object->getWorldTransformMatrix().getRotate().inverse()*dpos;
					selected_object->move(snapToGrid(dposB, osg::Vec3(0,0,0), gridsize));
				} else
					selected_object->setPosition(snapToGrid(pos, osg::Vec3(0,0,0), gridsize));
			} else
				selected_object->setPosition(pos);
			osg::Vec3 newv = selected_object->getPosition() - editcam->getPosition();
			newv.normalize();
			// Horizontal scrolling gives rotation
			selected_object->rotate(x * M_PI/180.0*magnitude,editcam->up());
			if (newv * editcam->forward() < 0) // is in front of camera?
				selected_object->setPosition(savepos);
			if (align)
				selected_object->alignToTerrain();
			if (clamp)
				selected_object->clampToTerrain();
			commitChanges();
                        return true;
		} else if (dragging && ea.getEventType() == osgGA::GUIEventAdapter::RELEASE) {
			// Release from dragging
			dragging = false;
			commitChanges();
			// "unstop" dynamic objects (which were stopped in updateMouseDrag())
			selected_object->setPosition(selected_object->getPosition());
                        return true;
		} else if (ea.getEventType() == osgGA::GUIEventAdapter::SCROLL && ea.getModKeyMask() & (osgGA::GUIEventAdapter::MODKEY_CTRL | osgGA::GUIEventAdapter::MODKEY_SUPER)) {
			// Shift-scroll - move marker in/out
			float y = ea.getScrollingDeltaY();
			switch (ea.getScrollingMotion()) {
				case osgGA::GUIEventAdapter::SCROLL_UP: y = 1; break;
				case osgGA::GUIEventAdapter::SCROLL_DOWN: y = -1; break;
				default: break;
			}
			float old_distance = marker_distance;
			marker_distance += y;
			if (marker_distance < 1)
				marker_distance = 1;
			if (marker_distance > 1000)
				marker_distance = 1000;
			if (editcam->getPivot().length() > 1e-5) {
				editcam->move(0,old_distance-marker_distance,0);
				editcam->setPivot(osg::Vec3(0,marker_distance,0));
			}
			updateVisuals();
                        return true;
		}
			
		return false;
	}
	
	void EditHandler::setEditMode(const bool value)
	{
		scenario = viewer->getScenario();
		if (!scenario) {
			scenario = new Scenario;
			scenario->setName("NewScenario");
			viewer->setScenario(scenario.get());
		}
		editmode = value;
		osg::Group *root = scenario->getRootNode();
		if (editmode) {
			ControlHandler::instance().setGrabInhibited(true);
			prevcam = CameraManipulator::instance().getActiveCamera();
			if (!editcam.valid()) {
				// First time...
				editcam = new Camera("EditCam");
				if (prevcam.valid()) {
					editcam->setPosition(prevcam->getWorldTransformMatrix().getTrans());
					editcam->setRotation(prevcam->getWorldTransformMatrix().getRotate());
				} else if (scenario->getRootNode()) {
					osg::BoundingSphere bound = scenario->getRootNode()->getBound();
					editcam->setPosition(0, -bound.radius()*2, bound.radius()/2);
					editcam->pointAt(bound.center());
				}
                                editcam->setIgnorePause(true);
				editcam->getHUD()->addChild(status_geode.get());
				editcam->getHUD()->addChild(help_geode.get());
				editcam->getHUD()->setChildValue(help_geode.get(), false);
			}
			scenario->addComponent(editcam.get());
			editcam->activate();
			root->addChild(nodes_switch.get());
			editcam->hide();
			editcam->setResetState();
		} else {
			ControlHandler::instance().setGrabInhibited(false);
			select(NULL);
			visualizeAnimationPath(NULL);
			root->removeChild(nodes_switch.get());
			if (prevcam.valid())
				prevcam->activate();
			else
				CameraManipulator::instance().setNoActiveCamera();
			scenario->removeComponent(editcam.get());
			scenario = NULL; // release our reference to the scenario
		}
		updateStatusText();
	}
	
	void EditHandler::select(moon::BaseObject *object, const bool childSelect)
	{
		// Select only top-parent object
		if (object && !childSelect)
			object = object->getRoot();
		Camera::TrackMode savedTrackMode = Camera::NONE;
		if (object != selected_object.get() && selected_object.valid()) {
			dout(3) << "unselect " << selected_object->getName() << "\n";
			bool changes = false;
			if (selection.valid() && selection->getMatrix() != osg::Matrix::identity())
				changes = true;
			setDragger(NONE);
			if (changes)
				commitChanges();
			selected_object->getRoot()->highlight(false);
			if (animationPathIndex >= 0 && selected_object->asKinematic()) {
				selected_object->asKinematic()->setAnimationPaused(false);
				selected_object->asKinematic()->setTransformationUpdatesControlPoint(-1);
				animationPathIndex = -1;
			}
			visualizeAnimationPath(NULL);
			selected_object = NULL;
			undomatrix = osg::Matrix::identity();
			savedTrackMode = editcam->getTrackMode();
			editcam->track(NULL);
			fall_line_offset = osg::Vec3(0,0,0);
		}
		if (object && object != selected_object.get()) {
			selected_object = object;
			dout(2) << "select " << selected_object->getName() << "\n";
			setDragger(current_dragger);
			
			undomatrix = selected_object->getTransform()->getMatrix();
			selected_object->setOwner(moonet::Client::me());
			//selected_object->realize();
			if (savedTrackMode != Camera::NONE)
				editcam->track(selected_object.get(), savedTrackMode);
		}
		// Export to Lua interpreter
		Interpreter::instance().pushGlobal("objects");
		Interpreter::instance().setTable("sel", selected_object.get(), "moon::BaseObject");
		// Highlight object
		if (selected_object.valid()) {
			// Set color based on static/dynamic object and simulation state
			osg::Vec4 color(1,1,1,1);
			if (selected_object->getRoot()->asKinematic() && selected_object->getRoot()->asKinematic()->isDynamic()) {
				if (SimulationManager::instance().getTime() > 0)
					color.set(1,0,0,1);
			}
			BaseObject::HighLightMode highlightMode1 = BaseObject::BBOX;
			BaseObject::HighLightMode highlightMode2 = BaseObject::THICK_BBOX;
			selected_object->getRoot()->highlight(true, highlightMode1, color);
			// Special color for selected child
			if (selected_object->getParent())
				selected_object->highlight(true, highlightMode2, osg::Vec4(1,1,0,1));
			selected_object->getRoot()->highlight(true, highlightMode2, color, false);			
		}
		// Reset grid visualization
		gridplane_transform->removeChildren(0, gridplane_transform->getNumChildren());
	}
	
	void EditHandler::setGrid(const float size)
	{
		if (size > 0) {
			grid = true;
			gridsize = size;
			if (dragger.valid())
				setDragger(current_dragger); // reset it
			updateStatusText();			
		} else {
			grid = false;
			gridsize = 1;
		}
	}
	
	void EditHandler::reset()
	{
		if (selected_object.valid() && animationPathIndex >= 0 && selected_object->asKinematic()) {
			selected_object->asKinematic()->setAnimationPaused(false);
			selected_object->asKinematic()->setTransformationUpdatesControlPoint(-1);
			animationPathIndex = -1;
		}
		if (editcam.valid())
			editcam->setResetState();
		SimulationManager::instance().setTime(0);
		scenario->reset();
		if (selected_object.valid())
			select(selected_object.get()); // reset highlight
	}
	
	osgManipulator::Dragger* EditHandler::createDragger(DraggerType type)
	{
		osgManipulator::Dragger* dragger = 0;
		switch (type) {
			case TABBOX: {
				osgManipulator::TabBoxDragger* d = new osgManipulator::TabBoxDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break; 
			}
			case TABPLANE: {
				osgManipulator::TabPlaneDragger* d = new osgManipulator::TabPlaneDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			case TABPLANE_TRACKBALL: {
				osgManipulator::TabPlaneTrackballDragger* d = new osgManipulator::TabPlaneTrackballDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			case TRACKBALL: {
				osgManipulator::TrackballDragger* d = new osgManipulator::TrackballDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			case TRANSLATE1D: {
				osgManipulator::Translate1DDragger* d = new osgManipulator::Translate1DDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			case TRANSLATE2D: {
				osgManipulator::Translate2DDragger* d = new osgManipulator::Translate2DDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			case TRANSLATEAXIS: {
				osgManipulator::TranslateAxisDragger* d = new osgManipulator::TranslateAxisDragger();
				d->setupDefaultGeometry();
				dragger = d;
				break;
			}
			default: break;
		}	
		return dragger;
	}
	
	void EditHandler::setDragger(DraggerType type)
	{
		if (!selected_object.valid())
			return;
		if (dragger_group.valid()) {
			// Commit current change
			for (unsigned int i = 0; i < selection->getNumChildren(); i++)
				selected_object->getTransform()->addChild(selection->getChild(i));
			selected_object->getTransform()->removeChild(dragger_group.get());
			selected_object->setTransformMatrix(selection->getMatrix() * selected_object->getTransformMatrix());
			if (align)
				selected_object->alignToTerrain();
			if (clamp)
				selected_object->clampToTerrain();
			commandmanager->disconnect(*dragger);
			selection = NULL;
			dragger = NULL;
			dragger_group = NULL;
		}
		current_dragger = type;
		if (type != NONE) {
			selection = new osgManipulator::Selection;
			for (unsigned int i = 0; i < selected_object->getTransform()->getNumChildren(); i++)
				selection->addChild(selected_object->getTransform()->getChild(i));
			dragger = createDragger(type);
			dragger_group = new osg::Group;
			dragger_group->addChild(dragger.get());
			dragger_group->addChild(selection.get());

			float scale = selected_object->getTransform()->getBound().radius();//scene->getBound().radius();
			osg::Matrix M;
			switch (current_dragger) {
				case TRANSLATE2D:
					switch (current_plane) {
						case XY_PLANE: M *= osg::Matrix::rotate(M_PI/2, osg::Vec3(1,0,0)); break;
						case YZ_PLANE: M *= osg::Matrix::rotate(M_PI/2, osg::Vec3(0,0,1)); break;
						default: break;
					}
					scale *= 2.0;
					break;
				default:
					scale *= 1.5;
			}
			if (world_coord) {
				osg::Matrix WM = selected_object->getWorldTransformMatrix();
				M *= osg::Matrix::inverse(osg::Matrix::rotate(WM.getRotate()));
			}
			M *= osg::Matrix::scale(scale, scale, scale);
			//M *= osg::Matrix::translate(scene->getBound().center());
			dragger->setMatrix(M);
			dout(5) << "dragger translation " << M.getTrans() << "\n";
			
			commandmanager->connect(*dragger, *selection);
			if (grid) {
				//gridconstraint = new osgManipulator::GridConstraint(*selected_object->getTransform(), dragger->getMatrix().getTrans(), osg::Vec3(1,1,1));
				gridconstraint = new osgManipulator::GridConstraint(*dragger, osg::Vec3(0,0,0), osg::Vec3(1,1,1)/scale*gridsize);
				commandmanager->connect(*dragger, *gridconstraint);
			} else
				gridconstraint = NULL;
			selected_object->getTransform()->removeChildren(0, selected_object->getTransform()->getNumChildren());
			selected_object->getTransform()->addChild(dragger_group.get());
		}
	}
	
	void EditHandler::updateStatusText()
	{
		if (!editmode || editcam->getHUD()->getChildValue(help_geode.get())) {
			status_text->setText("");
			return;
		}
		std::stringstream ss;
		ss << std::setiosflags(std::ios::fixed);
		if (SimulationManager::instance().isPaused())
			ss << "PAUSED\n";
		ss << "Scenario: " << scenario->getName() << "\n";

		// Mode
		ss << "Mode: ";
		switch (current_plane) {
			case XY_PLANE: ss << "XY"; break;
			case XZ_PLANE: ss << "XZ"; break;
			case YZ_PLANE: ss << "YZ"; break;
		}
		if (grid) {
			ss << " Grid ";
			if (gridsize > 0.99)
				ss << (int)gridsize;
			else
				ss << std::setprecision(1) << gridsize;
		}
		if (world_coord)
			ss << " World";
		else {
			ss << " Body";
		}
		if (clamp)
			ss << " Clamp";
		if (align)
			ss << " Align";
		ss << "\n\n";
		
                if (viewer->getManipulator() == 0) {
                    ss << "Cam:";
                    if (editcam->getMove2D())
                        ss << " 2D";
                    if (editcam->getPivot().length() > 1e-5)
                        ss << " Pivot";
                    if (editcam->getTrackTarget()) {
                        if (editcam->getTrackMode() == Camera::FOLLOW)
                            ss << " Follow\n";
                        else if (editcam->getTrackMode() == Camera::POINT)
                            ss << " Point\n";
                    }
                    ss << "\n";
                    ss << "  pos " << std::setprecision(1) << editcam->getPosition() << "\n";
                    ss << "  att " << std::setprecision(0) << editcam->getAttitude()*180.0/M_PI << "\n";
                    ss << "\n";
                }

		const FactoryProduct *templateObject = ObjectFactory::instance().getTemplate(template_index);
		if (templateObject) {
			ss << "Template: ";
			ss << templateObject->getName();
			ss << " (" << ObjectFactory::instance().getTemplateUsage(templateObject) << ")";
			ss << "\n";
		}
		if (paste_object.valid()) {
			ss << "Paste: " << paste_object->getName();
			if (paste_object->getTemplate())
				ss << " (" << paste_object->getTemplate()->getName() << ")";
			ss << " (" << paste_object->libraryName() << "::" << paste_object->className() << ")\n";
		}			
		
		// Editing
		if (selected_object.valid()) {
			ss << "Object: " << selected_object->getName();
			if (selected_object->getTemplate())
				ss << " (" << selected_object->getTemplate()->getName() << ")";
			ss << " (" << selected_object->libraryName() << "::" << selected_object->className() << ")";
			ss << "\n";
                        if (selected_object->isGeocentric()) {
                            double lat, lon, height;
                            selected_object->getPositionLatLongHeight(lat, lon, height);
                            ss << "  lat " << std::setprecision(4) << lat*180.0/M_PI
                                    << " lon " << lon*180.0/M_PI << std::setprecision(1)
                                    << " height " << height << "\n";
                        }
                        ss << "  pos " << std::setprecision(1) << selected_object->getPosition() << "\n";
			ss << "  att " << std::setprecision(0) << selected_object->getAttitude()*180.0/M_PI << "\n";
			
			if (selected_object->asKinematic() && selected_object->asKinematic()->getAnimationPath()) {
				osg::AnimationPath *ap = selected_object->asKinematic()->getAnimationPath();
				ss << "\nAnim";
				switch (ap->getLoopMode()) {
					case osg::AnimationPath::SWING: ss << " swing"; break;
					case osg::AnimationPath::LOOP: ss << " loop"; break;
					default: break;
				}
				ss << " " << ap->getPeriod() << "s\n";
				if (animationPathIndex >= 0)
					ss << "pt " << animationPathIndex << " time " << selected_object->asKinematic()->getAnimationTime() << "\n";
			}
		} else
			ss << "Marker: " << std::setprecision(1) << markerpos << "\n";
		
		ss << "\n";
		ss << "Sim time " << std::setprecision(0) << SimulationManager::instance().getTime();
		ss << "\n";
		status_text->setText(ss.str());
	}
	
	/// Update visual helper nodes (markers etc)
	void EditHandler::updateVisuals()
	{		
		// Marker
		markerpos = editcam->getPosition() + editcam->forward()*marker_distance;
		if (grid) {
			if (world_coord || !selected_object.valid())
				markerpos = snapToGrid(markerpos, osg::Vec3(0,0,0), gridsize);
			else {
				osg::Vec3 dpos = markerpos - selected_object->getPosition();
				osg::Vec3 dposB = selected_object->getWorldTransformMatrix().getRotate().inverse()*dpos;
				markerpos = selected_object->getPosition() + selected_object->getWorldTransformMatrix().getRotate()*snapToGrid(dposB, osg::Vec3(0,0,0), gridsize);
			}
		}
		marker_transform->setMatrix(osg::Matrix::translate(markerpos));
		
		// Grid plane
		if (grid) {
			if (gridplane_transform->getNumChildren() == 0) {
				mdraw::GridPlane *gridplane = new mdraw::GridPlane(4, osg::Vec4(0,0,1,0), 1.f, osg::Vec4(0.5,0.5,0.5,0.5));
				osg::Geode *geode = new osg::Geode;
				geode->addDrawable(gridplane);
				gridplane_transform->addChild(geode);
				switch (current_plane) {
					case XY_PLANE: gridplane->setParams(osg::Vec4(0,0,1,0)); break;
					case XZ_PLANE: gridplane->setParams(osg::Vec4(0,1,0,0)); break;
					case YZ_PLANE: gridplane->setParams(osg::Vec4(1,0,0,0)); break;
				}
				gridplane->setGridSize(gridsize);
				gridplane_transform->addChild(createPlaneAxesNode(gridsize*4, current_plane));
			}
			nodes_switch->setChildValue(gridplane_transform.get(), true);
		} else 
			nodes_switch->setChildValue(gridplane_transform.get(), false);
		
		if (selected_object.valid()) {
			osg::Vec3 pos = selected_object->getPosition();
			if (selected_object->getParent()) {
				osg::Matrix pWM = selected_object->getParent()->getWorldTransformMatrix();
				pos = pWM.getRotate() * pos + pWM.getTrans();
			}

			// Fall line
			fall_line_offset = selected_object->getBottomCenter();
			osg::Matrix fallM = osg::Matrix::translate(pos + fall_line_offset);
			nodes_switch->setChildValue(fall_line_transform.get(), true);
			fall_line_transform->setMatrix( fallM );
			
			// Grid plane at object
			if (grid) {
				if (world_coord) {
					pos = snapToGrid(pos, osg::Vec3(0,0,0), gridsize);
                                        /*
                                        if (selected_object->isGeocentric()) {
                                            osg::Matrix LWM = selected_object->getLocalToWorldMatrix();
                                            gridplane_transform->setMatrix(osg::Matrix::rotate(LWM.getRotate()) * osg::Matrix::translate(pos));
                                        } else
                                        */
                                            gridplane_transform->setMatrix(osg::Matrix::translate(pos));
                                    } else
					gridplane_transform->setMatrix( selected_object->getWorldTransformMatrix() );
			}
		} else {
			nodes_switch->setChildValue(fall_line_transform.get(), false);
			gridplane_transform->setMatrix( marker_transform->getMatrix() );
		}
		
		updateStatusText();
	}
	
	void EditHandler::updateHelperNodes()
	{
		if (animationPathNode.valid() && selected_object.valid())
			visualizeAnimationPath(selected_object->asKinematic());
	}
	
	void EditHandler::updateMouseDrag()
	{
		if (!selected_object)
			return;
		double fov = editcam->getFOV();
		double aspect = editcam->getAspect();
		double distance = (selected_object->getWorldTransformMatrix().getTrans()-editcam->getPosition()) * editcam->forward();
		osg::Vec3 camObjPlaneCenter = editcam->getPosition() + editcam->forward() * distance;
		osg::Vec3 pos = camObjPlaneCenter
			+ editcam->right()*drag_x*distance*tan(fov*M_PI/360.0)*aspect 
			+ editcam->up()*drag_y*distance*tan(fov*M_PI/360.0);
		
		// snap to grid
		if (grid && world_coord)
			pos = snapToGrid(pos, osg::Vec3(0,0,0), gridsize);
		if (selected_object->getParent()) {
			osg::Matrix pWM = selected_object->getParent()->getWorldTransformMatrix();
			pos = pWM.getRotate().inverse() * (pos - pWM.getTrans());
		}
		if (grid && !world_coord) {
			osg::Vec3 dpos = pos - selected_object->getPosition();
			osg::Vec3 dposB = selected_object->getWorldTransformMatrix().getRotate().inverse()*dpos;
			selected_object->move(snapToGrid(dposB, osg::Vec3(0,0,0), gridsize));
			pos = selected_object->getPosition();
		} else
			selected_object->setPosition(pos);
		
		if (align)
			selected_object->alignToTerrain();
		if (clamp)
			selected_object->clampToTerrain();
		if (!SimulationManager::instance().isPaused() && selected_object->asKinematic())
			selected_object->asKinematic()->stop();
	}
	
	void EditHandler::visualizeAnimationPath(KinematicObject *object) {
		if (animationPathNode.valid())
			animationPathNode->getParent(0)->removeChild(animationPathNode.get());
		if (!object)
			return;
		osg::Node *node = mdraw::createAnimationPathNode(object->getAnimationPath(), osg::Vec4(0.5,0.5,1,1));
		if (node && object->getTransform()->getNumParents() > 0) {
			osg::MatrixTransform *xform = new osg::MatrixTransform;
			osg::Matrix M;
			if (object->getParent())
				M = object->getParent()->getWorldTransformMatrix();
			xform->setMatrix(object->getAnimationOriginMatrix() * M);
			xform->addChild(node);
			object->getTransform()->getParent(0)->addChild(xform);
			animationPathNode = xform;
		}
	}
	
	void EditHandler::commitChanges()
	{
		if (!selected_object)
			return;
		setDragger(current_dragger);
		if ( (!selected_object->asKinematic() || !selected_object->asKinematic()->isDynamic() || SimulationManager::instance().getTime() == 0) && animationPathIndex == -1)
			selected_object->setResetState();
		updateStatusText();
		updateHelperNodes();
	}
	
	
} // namespace

const char* moon::EditHandler::helpText = "\
EDIT MODE HELP\n\
\n\
View/selection:\n\
  click       Select an object                     ^-click      Select a child object\n\
  1           Toggle camera pivot around marker    2            Toggle camera 2D top-view\n\
  k           Cycle camera track mode              ^-scroll     Move marker in/out\n\
  space       Move marker to selected object       S-arrow keys Gridded plane marker movement\n\
\n\
Editing:\n\
  drag        Move object in camera plane          scroll       Move object in/out of camera plane\n\
  arrow keys  Gridded plane movement               ^-arrow keys Stepped rotation\n\
  f           Fall to ground\n\
  F           Fall to ground and align             G            Align with surface normal\n\
  m           Move object to marker                M            Move/rotate object as camera\n\
  u           Undo all movements                   U            Unselect object\n\
  ^t          Copy transformation                  ^y, ^u       Paste transformation, rotation\n\
\n\
Animation path editing:\n\
  P           View/edit animation path             =            Unselect control point\n\
  +           Next control point                   -            Previous control point\n\
\n\
Mode selection:\n\
  tab         Cycle manipulator                    b            Toggle body/world coordinate frame\n\
  p           Cycle editing plane                  alt          Hold for alternate plane\n\
  C           Toggle ground clamping               X            Toggle ground alignment\n\
  g           Toggle grid                          h, H         Cycle grid size\n\
  v           Cycle display mode of selected       V            Cycle global display mode\n\
\n\
Creation and deletion:\n\
  Del/BackSp. Delete object                        ^x ^c ^v     Cut, copy, paste\n\
  t, T        Cycle template object                n            Create new instance of template\n\
  r           Replace selected with template\n\
\n\
Scenario:\n\
  ^s          Save                                ^r            Reset\n\
\n\
When an object is selected, it is available in the console as 'objects.sel'.\n\
Current camera is always available as 'objects.cam'.";
