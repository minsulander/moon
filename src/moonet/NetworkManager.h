// In order to make usage of RakNet optional, the NetworkManager class can be
// replaced with a dummy class by not defining MOONET_USE_RAKNET..

#ifdef MOONET_USE_RAKNET
	#include "RakNet/RakNetworkManager.h"
#else
	#include "NoNet/NoNetworkManager.h"
#endif
