#include "util.h"
#include <sstream>

namespace maudio {
	
	std::string OpenALErrorString(ALenum error, ALuint id)
	{
		std::stringstream ss;
		switch (error) {
			case AL_NO_ERROR: ss << "AL_NO_ERROR"; break;
			case AL_INVALID_NAME: ss << "AL_INVALID_NAME"; break;
			case AL_INVALID_ENUM: ss << "AL_INVALID_ENUM"; break;
			case AL_INVALID_VALUE: ss << "AL_INVALID_VALUE"; break;
			case AL_INVALID_OPERATION: ss << "AL_INVALID_OPERATION"; break;
			case AL_OUT_OF_MEMORY: ss << "AL_OUT_OF_MEMORY"; break;
			default: ss << "??? " << error; break;
		}
		if (id != AL_NONE)
			ss << " id " << id;
		return ss.str();
	}
	
}
