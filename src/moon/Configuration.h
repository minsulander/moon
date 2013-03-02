#ifndef MOON_CONFIGURATION_H
#define MOON_CONFIGURATION_H

#include "Scenario.h"
#include <vector>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// Index data for a scenario
	struct ScenarioData {
		std::string name;
		std::string filename;
		bool preload;
		osg::ref_ptr<Scenario> ptr;
		ScenarioData() : preload(false) {}
	};
	
	/// A game configuration which hold an index of available scenarios, files to load etc
	class MOON_EXPORT Configuration : public FactoryProduct {
	public:
		Configuration();
		Configuration(const Configuration& group,  const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Configuration);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		ScenarioData* getScenario(const std::string& name);
		ScenarioData* getScenario(const unsigned int index);
		unsigned int getNumScenarios();
		void addScenario(ScenarioData& data);
		
		inline const std::string& get(const unsigned int index) { return plugins[index]; }
		inline unsigned int getNumPlugins() const { return plugins.size(); }
	private:
		typedef std::vector<ScenarioData> ScenarioDataList;
		ScenarioDataList scenarios;
		std::vector<std::string> plugins;
	};
	
	/// @}
}

#endif
