#ifndef MOON_ENVIRONMENT_H
#define MOON_ENVIRONMENT_H

#include "Export.h"
#include "components/Component.h"
#include <osg/Camera>
#include <osg/View>
#include <osgShadow/ShadowedScene>

namespace moon {
	
	/// \brief Scenario-level component for lighting, shadows etc
	/// \ingroup core components
	class MOON_EXPORT Environment : public Component {
	public:
		Environment();
		Environment(const Environment& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Environment);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;

		void apply(osg::Group *group);
		void apply(osg::Camera *camera);
		
		osgShadow::ShadowedScene* getShadowedScene() { return shadowedScene.get(); }

	private:
		osg::Vec4 clearcolor;
		osg::View::LightingMode lightingmode;
		osg::Vec4 global_light_ambient, global_light_diffuse, global_light_specular;
		osg::ref_ptr<osg::StateSet> states;
		osg::ref_ptr<osgShadow::ShadowedScene> shadowedScene;
	};
}

#endif
