#ifndef MOON_VEGETATIONLAYER_H
#define MOON_VEGETATIONLAYER_H

#include "BaseObject.h"
#include <mdraw/DensityMap.h>
#ifndef MOON_NO_PHYSICS
/// \todo Move physics code into PhysicalVegetationLayer object
#include <moodyn/Geometry.h>
#endif
#include <OpenThreads/Thread>

namespace moon {

	class PopulateThread;

	/// \ingroup core objects
	/// @{

	/// Layer of objects placed with density maps
	class MOON_EXPORT VegetationLayer : public BaseObject {
	public:
		VegetationLayer();
		VegetationLayer(const VegetationLayer& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, VegetationLayer);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void addComponent(Component *component);
		
		virtual void realize();
		virtual void populate();
		
		virtual void update(const double dt);
		
	private:
		osg::ref_ptr<mdraw::DensityMap> densityMap;
		osg::ref_ptr<osg::Node> model[4];
		osg::ref_ptr<osg::Node> terrainNode;
		osg::ref_ptr<osg::HeightField> heightField;
		bool align[4];
		bool boundsSet;
		PopulateThread* popthread;

		double geoUpdateInterval, updateTime, lastUpdateTime;
#ifndef MOON_NO_PHYSICS
		osg::ref_ptr<moodyn::Geometry> geometry[4];
		std::vector< osg::ref_ptr<moodyn::Geometry> > geopool[4];
#endif
		float georange[4];
		osg::Vec3 lastrefpos;
		osg::ref_ptr<osg::Node> debugNode[4];
		osg::ref_ptr<osg::Switch> debugSwitch[4];
	};

	/// @}
	
	class PopulateThread : public OpenThreads::Thread {
	public:
		PopulateThread(VegetationLayer *veg) : vegetation(veg) {}
		virtual void run() {
			vegetation->populate();
		}
		osg::ref_ptr<VegetationLayer> vegetation;
	};
	
}

#endif
