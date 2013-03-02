#ifndef MOON_PARSABLE_H
#define MOON_PARSABLE_H

#include "Export.h"
#include <tinyxml.h>

namespace moon {
	
	/// \addtogroup core
	/// @{
	
	/// Interface class for an object that is parsable/writable with TinyXML
	class MOON_EXPORT Parsable {
	public:
		virtual void parseXML(const TiXmlElement *element) = 0;
		virtual void writeXML(TiXmlElement *element) const = 0;
		virtual ~Parsable() {}
	};
	
	/// @}
}

#endif
