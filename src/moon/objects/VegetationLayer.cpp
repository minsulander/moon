#include "VegetationLayer.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include "Camera.h"
#include <mdraw/utils.h>
#include <osgDB/ReadFile>
#include <osg/io_utils>
#include <osg/ShapeDrawable>
#include <osgSim/Impostor>
#include <osg/Timer>

using namespace mlog;

namespace moon {
	
	REGISTER_Object(moon, VegetationLayer);
	
	VegetationLayer::VegetationLayer()
	:	BaseObject(),
		boundsSet(false),
		popthread(NULL),
		geoUpdateInterval(0.5),
		updateTime(0.0),
		lastUpdateTime(0.0)
	{
		densityMap = new mdraw::DensityMap;
		for (int i = 0; i < 4; i++) {
			align[i] = false;
			georange[i] = 0;
		}
	}
	
	VegetationLayer::VegetationLayer(const VegetationLayer& source, const osg::CopyOp& copyop)
	:	BaseObject(source, copyop),
		terrainNode(source.terrainNode.get()),
		heightField(source.heightField.get()),
		boundsSet(source.boundsSet),
		popthread(NULL),
		geoUpdateInterval(source.geoUpdateInterval),
		updateTime(0.0),
		lastUpdateTime(0.0)
	{
		densityMap = new mdraw::DensityMap(*source.densityMap.get());
		for (int i = 0; i < 4; i++) {
			model[i] = source.model[i];
			align[i] = source.align[i];
#ifndef MOON_NO_PHYSICS
			geometry[i] = source.geometry[i];
#endif
			georange[i] = source.georange[i];
		}
	}
	
	void VegetationLayer::parseXML(const TiXmlElement *element)
	{
		BaseObject::parseXML(element);
		//=== VegetationLayer
		//=* component: Geometry - up to four can be specified, one for each layer of the density map
		//=See superclass BaseObject for more parameters.
		//=* attribute: image="(filename)"
		std::string imagefile = XMLParser::parseStringAttribute(element, "image");
		osg::Image *image = osgDB::readImageFile(imagefile);
		if (!image) {
			dout(ERROR) << "Failed to read density map '" << imagefile << "'\n";
			return;
		}
		densityMap->setImage(image);
		//=* attribute: terrainmodel="(filename)"
		//=. Use specified model for determining bounds and height (if unspecified, use parent if it exists)
		std::string str;
		if (XMLParser::parseStringAttribute(str, element, "terrainmodel")) {
			terrainNode = osgDB::readNodeFile(str);
			osg::Node *node = osgDB::readNodeFile(str);
			osg::Geode *geode = NULL;
			osg::ShapeDrawable *sd = NULL;
			geode = dynamic_cast<osg::Geode*> (node);
			if (geode)
				sd = dynamic_cast<osg::ShapeDrawable*> (geode->getDrawable(0));
			if (sd)
				heightField = dynamic_cast<osg::HeightField*> (sd->getShape());
		}
		//=* attribute: geoupdate="(number)" [seconds]
		//=. Interval between geometry updates (default 0.5).
		XMLParser::parseDoubleAttribute(geoUpdateInterval, element, "geoupdate");
		//=* element: bounds xmin="(number)" xmax="(number)" ymin="(number)" ymax="(number)" [meter]
		if (element->FirstChildElement("bounds")) {
			float xmin, xmax, ymin, ymax;
			densityMap->getBounds(xmin, xmax, ymin, ymax);
			xmin = (float) XMLParser::parseDouble(element, "bounds", "meter", true, xmin, "xmin");
			xmax = (float) XMLParser::parseDouble(element, "bounds", "meter", true, xmax, "xmax");
			ymin = (float) XMLParser::parseDouble(element, "bounds", "meter", true, ymin, "ymin");
			ymax = (float) XMLParser::parseDouble(element, "bounds", "meter", true, ymax, "ymax");
			densityMap->setBounds(xmin, xmax, ymin, ymax);
		}
		//=* repeatable element: layer channel="r|g|b|a" density="(number)" model="(filename)" align="true|false"
		for (const TiXmlElement *el = element->FirstChildElement("layer"); el; el = el->NextSiblingElement("layer")) {
			std::string chstr = XMLParser::parseStringAttribute(el, "channel", true, "r");
			mdraw::DensityMap::Channel channel;
			if (chstr == "r")
				channel = mdraw::DensityMap::CH_R;
			else if (chstr == "g")
				channel = mdraw::DensityMap::CH_G;
			else if (chstr == "b")
				channel = mdraw::DensityMap::CH_B;
			else if (chstr == "a")
				channel = mdraw::DensityMap::CH_A;
			else
				throw ParseException("Invalid density map channel '" + chstr + "'", el);
			float density = (float) XMLParser::parseDoubleAttribute(el, "density", true, 1);
			densityMap->setDensity(density, channel);
			std::string modelfile = XMLParser::parseStringAttribute(el, "model");
			//=** attribute: range="(number)"
			float range = (float) XMLParser::parseDoubleAttribute(el, "range", true, 3000);
			//=** attribute: impostor="(number)"
			float impostor_range = (float) XMLParser::parseDoubleAttribute(el, "impostor", true, 0);
			osg::Node *vegnode = osgDB::readNodeFile(modelfile);
			if (vegnode) {
				if (impostor_range > 1e-5) {
					dout(5) << "Creating impostor for vegetation node " << vegnode->getName() << "\n";
					osgSim::Impostor *impostor = new osgSim::Impostor;
					impostor->addChild(vegnode);
					impostor->setRange(0, 0, range);
					impostor->setImpostorThreshold(impostor_range);
					osg::BoundingSphere bs = vegnode->getBound();
					osg::BoundingSphere bs2 = impostor->getBound();
					if (!bs.valid() || !bs2.valid())
						dout(ERROR) << "Bounds for vegetation layer node are not valid! " << bs.valid() << " " << bs2.valid() << "\n";
					else
						model[channel] = impostor;
				} else if (range > 1e-5) {
					dout(5) << "Creating LOD for vegetation node " << vegnode->getName() << "\n";
					osg::LOD *lod = new osg::LOD;
					lod->addChild(vegnode);
					lod->setRange(0, 0, range);
					model[channel] = lod;
				} else {
					dout(5) << "Using vegetation node as is\n";
					model[channel] = vegnode;
				}
			} else
				dout(ERROR) << "Failed to read model '" << modelfile << "' for vegetation layer " << getName() << "\n";
			
			//=** attribute: align="true|false"
			align[channel] = XMLParser::parseBooleanAttribute(el, "align", true, false);
			//=** attribute: georange="(number)"
			//=. Range to reference object (usually active camera) to use for placing geometry
			georange[channel] = XMLParser::parseDoubleAttribute(el, "georange", true, 0);
		}
	}
	
	void VegetationLayer::writeXML(TiXmlElement *element) const
	{
		BaseObject::writeXML(element);
	}
	
	void VegetationLayer::addComponent(Component *component)
	{
#ifndef MOON_NO_PHYSICS
		if (moodyn::Geometry* geo = dynamic_cast<moodyn::Geometry*> (component)) {
			for (int ch = 0; ch < 4; ch++)
				if (!geometry[ch])
					geometry[ch] = geo;
		} else {
			dout(ERROR) << "VegetationLayer does not support component '" << component->getName() << "'\n";
		}
#endif
		BaseObject::addComponent(component);
	}
	
	void VegetationLayer::realize()
	{
		if (isRealized())
			return;
		
		// need some node to prevent debug geometry from showing up
		/*
		for (int chi = 0; chi < 4; chi++) {
			if (model[chi].valid())
				addNode(model[chi].get());
		}
		 */
		
		BaseObject::realize();
		
		if (!terrainNode.valid() && getParent() && getParent()->getNode()) {
			terrainNode = getParent()->getNode();
			dout(4) << "  using parent as terrain node\n";
		}
		if (!boundsSet) {
			if (terrainNode.valid()) {
				osg::BoundingBox bbox = mdraw::getBoundingBox(terrainNode.get());
				densityMap->setBounds(bbox);
				dout(4) << "  bounds from terrain: " << bbox.xMin() << " " << bbox.xMax() << " " << bbox.yMin() << " " << bbox.yMax() << "\n";
			} else
				dout(WARN) << "No bounds set for VegetationLayer '" << getName() << "'\n";
		}
		popthread = new PopulateThread(this);
		popthread->start();
		//populate();
	}
	
	void VegetationLayer::populate()
	{
		for (int chi = 0; chi < 4; chi++) {
			if (!model[chi].valid())
				continue;
			mdraw::DensityMap::Channel channel = (mdraw::DensityMap::Channel) chi;
			densityMap->generate(channel);
			dout(4) << "Populating vegetation layer " << getName() << " channel " << channel << " density " << densityMap->getDensity(channel) << " model " 
					<< model[channel]->getName() << ": " << densityMap->getNumPositions(channel) << " objects\n";
			if (heightField.valid()) {
				dout(4) << "  setting heights to height field\n";
				densityMap->setHeights(channel, heightField.get(), align[channel]);
			} else if (terrainNode.valid()) {
				dout(4) << "  settings heights to terrain\n";
				densityMap->setHeights(channel, terrainNode.get(), align[channel]);
			}
			dout(4) << "  creating nodes\n";
			addNode(densityMap->createNode(channel, model[channel].get()));
			show();
			// remove temporary node
			//if (osg::Switch* modelswitch = dynamic_cast<osg::Switch*> (getNode()))
			//	modelswitch->removeChild(model[chi].get());

			// Setup geometry
#ifndef MOON_NO_PHYSICS
			if (!geometry[chi].valid()) {
				geometry[chi] = new moodyn::Geometry;
				geometry[chi]->addBoundingBox(mdraw::getBoundingBox(model[chi].get()));
			}
#endif
		}
	}
	
	void VegetationLayer::update(const double dt)
	{
		BaseObject::update(dt);
#ifndef MOON_NO_PHYSICS
		updateTime += dt;
		if (updateTime - lastUpdateTime < geoUpdateInterval)
			return;
		
		// Figure out a reference position to use for ranges to nodes
		osg::Vec3 refpos;
		moon::Camera *cam = CameraManipulator::instance().getActiveCamera();
		if (cam)
			refpos = cam->getWorldTransformMatrix().getTrans() - getWorldTransformMatrix().getTrans();
		
		for (int ch = 0; ch < 4; ch++) {
			if (georange[ch] < 1e-5 || !model[ch].valid())
				continue;
			// Skip updating geometry if channel has none or reference position hasn't moved enough
			if ((refpos-lastrefpos).length() < georange[ch]/4.0)
				continue;
			
			// Create debug nodes if needed
			if (getDisplayMode() & DISPLAY_DEBUG && geometry[ch].valid()) {
				if (!debugNode[ch].valid()) {
					debugNode[ch] = geometry[ch]->createDebugNode();
					debugSwitch[ch] = new osg::Switch;
					addDebugNode(debugSwitch[ch].get());
				}
			}

			mdraw::DensityMap::Channel channel = (mdraw::DensityMap::Channel) ch;
			// Create a new pool of geometries
			//geopool[ch].clear();
			unsigned int gpi = 0;
			for (unsigned int i = 0; i < densityMap->getNumPositions(channel); i++) {
				osg::Vec3 pos = densityMap->getPosition(i, channel);
				if ((pos-refpos).length() < georange[ch]) {
					// either reuse geometries or create new ones
					if (geopool[ch].size() >= gpi) {
						geopool[ch].resize(gpi+1);
						geopool[ch][gpi] = new moodyn::Geometry(*geometry[ch].get());
					}
					moodyn::Geometry *geo = geopool[ch][gpi].get();
					// set transformation and realize
					osg::Matrix M = osg::Matrix::translate(getWorldTransformMatrix().getTrans() + pos);
					if (align[channel])
						M = osg::Matrix::rotate(osg::Vec3(0,0,1), densityMap->getNormal(i, channel)) * M;
					if (!geo->isRealized())
						geo->realize();
					geo->setTransformation(M);
					// update debug node if needed
					if (getDisplayMode() & DISPLAY_DEBUG && debugSwitch[ch].valid()) {
						if (debugSwitch[ch]->getNumChildren() < gpi+1) {
							osg::MatrixTransform *xform = new osg::MatrixTransform;
							xform->addChild(debugNode[ch].get());
							debugSwitch[ch]->addChild(xform);
						}
						osg::MatrixTransform *xform = (osg::MatrixTransform*) debugSwitch[ch]->getChild(gpi);
						if (align[channel])
							xform->setMatrix(osg::Matrix::rotate(osg::Vec3(0,0,1), densityMap->getNormal(i, channel))
											 * osg::Matrix::translate(pos));
						else
							xform->setMatrix(osg::Matrix::translate(pos));
						debugSwitch[ch]->setValue(gpi, true);
					}
					gpi++;
				}
			}
			// unrealize geometries in the pool but not within range
			while (gpi < geopool[ch].size()) {
				geopool[ch][gpi]->unrealize();
				if (getDisplayMode() & DISPLAY_DEBUG && debugSwitch[ch].valid()) {
					debugSwitch[ch]->setValue(gpi, false);
				}
				gpi++;
			}
			// And even cooler would be if, within a specific range, we could switch to BaseObjects instead,
			// so they could be animated on collisions etc etc... sometime in the future that is.

			lastrefpos = refpos;
		}
#endif
	}
	
}
