#ifndef MOON_SCRIPTEVENTFACTORYCALLBACK_H
#define MOON_SCRIPTEVENTFACTORYCALLBACK_H

#include "ObjectFactory.h"

namespace moon {
	
	/// \ingroup script
	class ScriptEventFactoryCallback : public FactoryCallback {
	public:
		virtual void onParseObject(const FactoryProduct *object);
		virtual void onLoadStart(const std::string& filename);
		virtual void onLoadFinish(const std::string& filename);
	};
		
}

#endif
