#ifndef MOON_PARAMETER_H
#define MOON_PARAMETER_H

#include "Export.h"
#include <osg/Object>
#include <osg/observer_ptr>
#include <vector>

namespace moon {
	
	class ParameterContainer;
	
	/// \brief Placeholder for a parameter value that can be tied to a Modifier
	/// \ingroup core
	class MOON_EXPORT Parameter : public osg::Object {
	public:
		Parameter(const std::string& name = "", ParameterContainer *container = NULL, const float def = 0);
		Parameter(const Parameter& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Parameter);
		
		/// Set parameter value
		void set(const float value);
		/// Get the value
		float get() { return value; }
		/// Return wether this parameter is connected to any modifier
		bool isConnected() const;
	protected:
		void connect();
		void disconnect();
		friend class Modifier;
	private:
		float value;
		unsigned int connectCount;
	};
	
	/// \brief Interface class for objects that hold parameters
	/// \ingroup core
	class MOON_EXPORT ParameterContainer {
	public:
		ParameterContainer();
		ParameterContainer(const ParameterContainer& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		virtual ~ParameterContainer() {}

		unsigned int getNumParameters() const;
		Parameter* getParameter(const unsigned int index);
		const Parameter* getParameter(const unsigned int index) const;
		virtual Parameter* getParameter(const std::string& name);
		
	protected:
		void addParameter(Parameter *parameter);
		void removeParameter(Parameter *parameter);
		friend class Parameter;
		
	private:
		typedef std::vector< osg::observer_ptr<moon::Parameter> > ParameterList;
		ParameterList parameters;
	};
	
}

#endif
