#ifndef MAUDIO_UTIL_H
#define MAUDIO_UTIL_H

#include "OpenALHeaders.h"
#include <string>

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	extern std::string OpenALErrorString(ALenum error, ALuint id = AL_NONE);
	
#define CHECK_AL_ERROR(message) \
{\
ALenum error = alGetError(); \
if (error != AL_NO_ERROR) \
throw AudioException(std::string(#message) + ": " + OpenALErrorString(error));\
}
	
#define CHECK_AL_ERROR_SOURCE(message) \
{\
ALenum error = alGetError(); \
if (error != AL_NO_ERROR) \
throw AudioException(std::string(#message) + ": " + OpenALErrorString(error, sourceID));\
}
	
	/// @}
	
}

#endif
