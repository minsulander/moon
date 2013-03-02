// In order to make usage of RakNet optional, the Client class can be
// replaced with a dummy class by not defining MOONET_USE_RAKNET..

#ifdef MOONET_USE_RAKNET
	#include "RakNet/RakClient.h"
#else
	#include "NoNet/NoClient.h"
#endif
