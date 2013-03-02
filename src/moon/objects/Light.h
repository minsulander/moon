#ifndef MOON_LIGHT_H
#define MOON_LIGHT_H

#include "BaseObject.h"
#include "moon/Environment.h"
#include <osg/Light>
#include <osg/LightSource>

namespace moon {
	
	/// \ingroup core objects
	/// @{
	
	class MOON_EXPORT Light : public BaseObject {
	public:
		Light();
		Light(const Light& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Light);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void realize();
		virtual void unrealize();
		
		virtual void setDisplayMode(const unsigned int mode);
		
		static void setLightNumUsed(const int num, const bool value = true);
		
		void setLocal(const bool value);
		bool isLocal() const;
		
		virtual void update(const double dt);
		
	protected:		
		osg::StateSet* getStateSet();
		
		static osg::observer_ptr<osg::StateSet> globalLightStateSet;
		typedef std::map<int, bool> LightNumUseMap;
		static LightNumUseMap lightUsed;
		friend class Environment;

	private:
		osg::ref_ptr<osg::Light> light;
		osg::ref_ptr<osg::LightSource> lightsource;
		bool local;
		osg::Vec4 ambient, diffuse, specular;
		float fadeRangeIn, fadeRangeOut;
	};
	
	/// @}
}

#endif
