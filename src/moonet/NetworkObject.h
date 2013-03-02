// In order to make usage of RakNet optional, the NetworkObject class can be
// replaced with a dummy class by not defining MOONET_USE_RAKNET..

#ifdef MOONET_USE_RAKNET
	#include "RakNet/RakNetworkObject.h"
#else
	#include "NoNet/NoNetworkObject.h"
#endif
