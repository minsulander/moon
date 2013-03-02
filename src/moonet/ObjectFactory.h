#ifndef MOONET_OBJECTFACTORY_H
#define MOONET_OBJECTFACTORY_H

#include "NetworkObject.h"
#include "Export.h"
#include <string>

namespace moonet {

/// Template class for a user-supplied object factory, to be registered with the NetworkManager
class MOONET_EXPORT ObjectFactory {
public:
	/// Called by the NetworkManager, based on NetworkObject::networkObjectName() when the object is constructed
	/// \return the approriate derivative of NetworkObject based on its object name
	virtual NetworkObject* createNetworkObject(const std::string& objectName) { return NULL; }
	virtual ~ObjectFactory() {}
};

}

#endif
