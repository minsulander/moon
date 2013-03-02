#include "Parameter.h"

namespace moon {
	
	Parameter::Parameter(const std::string& name, ParameterContainer *container, const float def)
	: osg::Object(), value(def), connectCount(0)
	{
		setName(name);
		if (container)
			container->addParameter(this);
	}
	
	Parameter::Parameter(const Parameter& other, const osg::CopyOp& copyop)
	: osg::Object(other, copyop), value(other.value), connectCount(0)
	{
		setName(other.getName());
	}
	
	void Parameter::set(const float nvalue) { value = nvalue; }	
	bool Parameter::isConnected() const	{ return connectCount > 0; }	
	void Parameter::connect() { connectCount++; }
	void Parameter::disconnect()
	{
		if (connectCount > 0)
			connectCount--;
	}
	
	ParameterContainer::ParameterContainer()
	{
	}
	
	ParameterContainer::ParameterContainer(const ParameterContainer& source, const osg::CopyOp& copyop)
	{
	}
	
	unsigned int ParameterContainer::getNumParameters() const { return parameters.size(); }
	
	Parameter* ParameterContainer::getParameter(const unsigned int index)
	{
		if (index >= parameters.size())
			return NULL;
		return parameters[index].get();
	}
	
	const Parameter* ParameterContainer::getParameter(const unsigned int index) const
	{
		if (index >= parameters.size())
			return NULL;
		return parameters[index].get();
	}
	
	Parameter* ParameterContainer::getParameter(const std::string& name)
	{
		for (ParameterList::iterator it = parameters.begin(); it != parameters.end(); it++) {
			if (it->valid() && (*it)->getName() == name)
				return it->get();
		}
		return NULL;
	}
	
	void ParameterContainer::addParameter(Parameter *parameter)
	{
		if (!parameter)
			return;
		parameters.push_back(parameter);
	}

	void ParameterContainer::removeParameter(Parameter *parameter)
	{
		for (ParameterList::iterator it = parameters.begin(); it != parameters.end(); it++) {
			if (parameter == it->get()) {
				parameters.erase(it);
				return;
			}
		}
	}
	
}
