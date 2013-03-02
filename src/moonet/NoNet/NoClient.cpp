#include "NoClient.h"

namespace moonet {

	Client::Client()  : player(NULL)
	{
		if (!mine)
			mine = this;
	}

	bool Client::isStillAround(Client *client) 
	{ 
		if (client == mine) 
			return true;
		return false;
	}
	
	Client *Client::mine = NULL;
}