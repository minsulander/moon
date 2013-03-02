/** \file alinfo.cpp

 This is a small test application for figuring out some things about the OpenAL implementation.
 Implementations vary quite a bit on different platforms, so this is useful for figuring out
 how they differ.
 
 */

#include "maudio/OpenALHeaders.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>

std::string alErrStr(ALenum error, ALuint id = AL_NONE)
{
	if (error == AL_NO_ERROR)
		return "";
	std::stringstream ss;
	switch (error) {
		case AL_INVALID_NAME: ss << "AL_INVALID_NAME"; break;
		case AL_INVALID_ENUM: ss << "AL_INVALID_ENUM"; break;
		case AL_INVALID_VALUE: ss << "AL_INVALID_VALUE"; break;
		case AL_INVALID_OPERATION: ss << "AL_INVALID_OPERATION"; break;
		case AL_OUT_OF_MEMORY: ss << "AL_OUT_OF_MEMORY"; break;
		default: ss << "??? " << error; break;
	}
	if (id != AL_NONE)
		ss << " id " << id;
	ss << "\n";
	return ss.str();
}

int main(int argc, char *argv[])
{
	ALCdevice *device;
	ALCcontext *context;
	device = alcOpenDevice(NULL); //"'((sampling-rate 44100) (device '(native))");
	if (device == NULL) {
		std::cerr << "Unable to open audio device\n";
		exit(1);
	}
	context = alcCreateContext (device, NULL);
	if (context == NULL) {
		std::cerr << "Unable to create audio context\n";
		alcCloseDevice (device);
		exit(1);
	}
	
	if (!alcMakeContextCurrent (context)) {
		std::cerr << "Unable to make context current\n";
		alcDestroyContext (context);
		alcCloseDevice (device);
		exit(1);
	}
	
	std::cout << " AL version: " << alGetString(AL_VERSION) << "\n";
	ALCint majorver, minorver;
	alcGetIntegerv(NULL, ALC_MAJOR_VERSION, 1, &majorver);
	alcGetIntegerv(NULL, ALC_MINOR_VERSION, 1, &minorver);
	std::cout << " ALC version: " << majorver << "." << minorver << "\n";

	std::cout << " Renderer: " << alGetString(AL_RENDERER) << "\n";
	std::cout << " Vendor: " << alGetString(AL_VENDOR) << "\n";

	std::cout << "\n";

	const ALCchar *devs = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	std::cout << " Devices: ";
	while (devs[0] != 0) {
		std::cout << devs;
		devs += strlen(devs)+1;
		if (devs[0] != 0)
			std::cout << ", ";
	}
	std::cout << "\n";
	devs = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	std::cout << " Capture devices: ";
	while (devs[0] != 0) {
		std::cout << devs;
		devs += strlen(devs)+1;
		if (devs[0] != 0)
			std::cout << ", ";
	}
	std::cout << "\n";

	std::cout << " Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << "\n";
	std::cout << " Default device: " << alcGetString(device, ALC_DEFAULT_DEVICE_SPECIFIER) << "\n";
	std::cout << " Capture Device: " << alcGetString(device, ALC_CAPTURE_DEVICE_SPECIFIER) << "\n";
	std::cout << " Default Capture device: " << alcGetString(device, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER) << "\n";
	
	std::cout << "\n";
	
	std::cout << " Extensions: " << alGetString(AL_EXTENSIONS) << "\n";
	std::cout << " ALC Extensions: " << alcGetString(device, ALC_EXTENSIONS) << "\n";
	
	std::cerr << alErrStr(alGetError());
	
	std::cout << "\n";
	
	// Generate a source
	ALuint sourceID;
	alGenSources(1, &sourceID);
	std::cerr << alErrStr(alGetError());
	
	// Figure out limits for gain
	int low = 10000, high = -10000;
	for (int i = -10000; i <= 10000; i++) {
		alSourcef(sourceID, AL_GAIN, i/100.f);
		ALenum error = alGetError();
		if (error == AL_NO_ERROR && i < low)
			low = i;
		if (error == AL_NO_ERROR && i > high)
			high = i;
	}
	std::cout << " Lowest gain: " << low/100.f << (low == -10000 ? "+" : "") << "\n";
	std::cout << " Highest gain: " << high/100.f << (high == 10000 ? "+" : "") << "\n";
	
	// Figure out limits for pitch
	low = 10000; high = -10000;
	for (int i = -10000; i <= 10000; i++) {
		alSourcef(sourceID, AL_PITCH, i/100.f);
		ALenum error = alGetError();
		if (error == AL_NO_ERROR && i < low)
			low = i;
		if (error == AL_NO_ERROR && i > high)
			high = i;
	}
	std::cout << " Lowest pitch: " << low/100.f << (low == -10000 ? "+" : "") << "\n";
	std::cout << " Highest pitch: " << high/100.f << (high == 10000 ? "+" : "") << "\n";
	
	alDeleteSources(1,&sourceID);
	
	// Figure out how many sources we can have
	unsigned int num = 0;
	std::vector<ALuint> sources;
	while (num < 1000) {
		ALuint id = AL_NONE;
		alGenSources(1, &id);
		ALuint error = alGetError();
		if (id != AL_NONE && error == AL_NO_ERROR) {
			sources.push_back(id);
			num++;
		} else {
			//std::cout << " Last source error: " << alErrStr(error);
			break;
		}
	}
	std::cout << " Max sources: " << num << (num == 1000 ? "+" : "") << "\n";
	for (size_t i = 0; i < sources.size(); i++) {
		ALuint id = sources[i];
		alDeleteSources(1,&id);
	}
	sources.clear();

	// Figure out how many buffers we can have
	num = 0;
	std::vector<ALuint> buffers;
	while (num < 1000) {
		ALuint id = AL_NONE;
		alGenBuffers(1, &id);
		ALuint error = alGetError();
		if (id != AL_NONE && error == AL_NO_ERROR) {
			buffers.push_back(id);
			num++;
		} else {
			//std::cout << " Last buffer error: " << alErrStr(error);
			break;
		}
	}
	std::cout << " Max buffers: " << num << (num == 1000 ? "+" : "") << "\n";
	for (size_t i = 0; i < buffers.size(); i++) {
		ALuint id = buffers[i];
		alDeleteBuffers(1,&id);
	}
	sources.clear();

	alcDestroyContext (context);
	alcCloseDevice (device);

}
