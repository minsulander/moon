#ifndef MOON_SCRIPT_H
#define MOON_SCRIPT_H

#include "Component.h"

namespace moon {
	
	/// \brief Script component, useful for adding object behaviour etc
	/// \ingroup script components
	class Script : public Component {
	public:
		Script();
		Script(const Script& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Script);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void reset();
		virtual void update(const double dt);
		
		/// Run the script in the global interpreter
		void run();
		/// Get number of times this script has run
		unsigned int getRunCount() const { return runcount; }
		
		enum When { PARSE, INITIALIZE, REALIZE, UNREALIZE, RESET, UPDATE };
		When getWhen() const { return when; }
		void setWhen(const When nwhen) { when = nwhen; }
		
		double getInterval() const { return interval; }
		void setInterval(const double value) { interval = value; }
		
		void setSelf(void *data, const std::string& type);
		
	private:
		std::string filename;
		std::string text;
		unsigned int runcount;
		double interval;
		double time;
		When when;
		void *selfptr;
		std::string selftype;
	};
}

#endif
