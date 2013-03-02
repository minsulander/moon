#include "Configuration.h"
#include "XMLParser.h"
#include "ObjectFactory.h"
#include "PluginManager.h"
#include <mlog/Log.h>

using namespace mlog;

namespace moon {

	REGISTER_Object(moon, Configuration);
	
	Configuration::Configuration()
	:	FactoryProduct()
	{
	}
	
	Configuration::Configuration(const Configuration& source,  const osg::CopyOp& copyop)
	:	FactoryProduct(source)
	{
		scenarios = source.scenarios;
	}
	
	void Configuration::parseXML(const TiXmlElement *root)
	{
		//=== Configuration
		for (const TiXmlElement *element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {
			//=* repeatable element: scenario name="(string)" file="(string)" preload="true|false" (default false)
			std::string value = element->Value();
			if (value == "scenario") {
				ScenarioData data;
				data.name = XMLParser::parseStringAttribute(element, "name");
				data.filename = XMLParser::parseStringAttribute(element, "file");
				data.preload = XMLParser::parseBooleanAttribute(element, "preload", true, false);
				scenarios.push_back(data);
			} else if (value == "plugin") {
				std::string name = XMLParser::parseStringAttribute(element, "name");
				plugins.push_back(name);
				if (!PluginManager::instance().get(name)) {
					if (!PluginManager::instance().load(name))
						dout(ERROR) << "Failed to load plugin '" << name << "'\n";
				}
			} else if (value == "simfreq") {
				SimulationManager::instance().setTimeStep(1.0/XMLParser::parseDoubleAttribute(element, "value"));
			} else
				throw ParseException("Unknown configuration entry", element);
		}
	}
	
	void Configuration::writeXML(TiXmlElement *root) const
	{
		for (ScenarioDataList::const_iterator it = scenarios.begin(); it != scenarios.end(); it++) {
			const ScenarioData& data = *it;
			TiXmlElement *element = new TiXmlElement("scenario");
			element->SetAttribute("name", data.name);
			element->SetAttribute("file", data.filename);
			if (data.preload)
				element->SetAttribute("preload", "false");
			root->LinkEndChild(element);
		}
	}
	
	ScenarioData* Configuration::getScenario(const std::string& name)
	{
		for (ScenarioDataList::iterator it = scenarios.begin(); it != scenarios.end(); it++) {
			ScenarioData& data = *it;
			if (data.name == name)
				return &data;
		}
		return NULL;
	}
	
	ScenarioData* Configuration::getScenario(const unsigned int index)
	{
		if (index < 0 || index >= scenarios.size())
			return NULL;
		return &scenarios[index];
	}
	
	unsigned int Configuration::getNumScenarios() { return scenarios.size(); }
	
	void Configuration::addScenario(ScenarioData& data)
	{
		if (getScenario(data.name))
			return;
		scenarios.push_back(data);
	}

} // namespace
