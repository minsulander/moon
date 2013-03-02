#include "AudioManager.h"
#include "SingleSource.h"
#include "Stream.h"
#include "util.h"
#include <mlog/Log.h>
#include <moon/objects/Camera.h>
#include <osg/io_utils>
#include <mpg123.h>

using namespace mlog;
using namespace moon;

namespace maudio {
	
	void AudioManager::init()
	{
		if (initialized)
			return;
		dout(1, AUDIO) << "Initializing audio\n";
		device = alcOpenDevice(NULL); //"'((sampling-rate 44100) (device '(native))");
		if (device == NULL)
			throw AudioException("Unable to open audio device");
		context = alcCreateContext (device, NULL);
		if (context == NULL) {
			alcCloseDevice (device);
			throw AudioException("Unable to create audio context");
		}
		
		if (!alcMakeContextCurrent (context)) {
			shutdown();
			throw AudioException("Unable to make context current");
		}

		dout(2, AUDIO) << "  Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << "\n";
		dout(3, AUDIO) << "  Default device: " << alcGetString(device, ALC_DEFAULT_DEVICE_SPECIFIER) << "\n";
		initialized = active = true;

		// Figure out max pitch - it varies for different platforms
		ALuint sourceID;
		alGenSources(1, &sourceID);
		int high = -10000;
		for (int i = 0; i <= 10000; i++) {
		  alSourcef(sourceID, AL_PITCH, i/100.f);
		  ALenum error = alGetError();
		  if (error == AL_NO_ERROR && i > high)
		    high = i;
		}
		alDeleteSources(1, &sourceID);
		if (high < 10000) {
		  maxPitch = high/100.f;
		  dout(3, AUDIO) << "  Pitch maximum: " << maxPitch << "\n";
		}
		
		// Init the MP3 library
		int err = mpg123_init();
		if (err != MPG123_OK) {
			dout(ERROR, AUDIO) << "Trouble with mpg123: " << mpg123_plain_strerror(err) << "\n";
			mpg123_exit();
		}
		
		//Stream::useThread(false);
	}
	
	void AudioManager::shutdown()
	{
		dout(1, AUDIO) << "Shutting down audio\n";
		Stream::stopStreaming();
		alcDestroyContext (context);
		alcCloseDevice (device);
		mpg123_exit();
		initialized = active = false;
	}
	
	AudioManager::~AudioManager()
	{
		shutdown();
	}
	
	void AudioManager::setActive(const bool value)
	{
		active = value;
		if (active && !initialized)
			init();
	}
	
	bool AudioManager::isActive() { return active; }
	
	bool AudioManager::isInitialized() { return initialized; }
	
	Sound* AudioManager::play(const std::string& name, const float gain, const float pitch, const osg::Vec3& pos, const bool relative)
	{
		if (!initialized || !active) 
			return NULL;
		if (Sound *sound = getSound(name)) {
			dout(2, AUDIO) << "Playing " << sound->className() << " '" << name << "'.\n";
			sound->play();
			sound->setGain(gain);
			sound->setPitch(pitch);
			sound->setPosition(pos);
			sound->setRelative(relative);
			return sound;
		} else {
			dout(2, AUDIO) << "Playing file '" << name << "'.\n";
			playSource = new SingleSource(name);
			playSource->setGain(gain);
			playSource->setPitch(pitch);
			playSource->setPosition(pos);
			playSource->setRelative(relative);
			playSource->play();
			return playSource.get();
		}
		return NULL;
	}
	
	void AudioManager::addSound(Sound *sound)
	{
		if (sound) {
			sound->setRelative(true);
			sound->initialize();
			sound->realize();
			if (sound->isRealized())
				playSounds.push_back(sound);
		}
	}
	
	Sound *AudioManager::getSound(const std::string& name)
	{
		for (SoundList::iterator it = playSounds.begin(); it != playSounds.end(); it++) {
			if (it->valid() && (*it)->getName() == name) {
				return it->get();
			}
		}
		return NULL;
	}
	
	void AudioManager::setListenerPosition(const osg::Vec3& pos)
	{
		if (!initialized || !active) return;
		alListener3f(AL_POSITION, pos.x(), pos.y(), pos.z());
		CHECK_AL_ERROR(setListenerPosition);
	}
	
	osg::Vec3 AudioManager::getListenerPosition()
	{
		if (!initialized || !active) return osg::Vec3(0,0,0);
		osg::Vec3 pos;
		alGetListener3f(AL_POSITION, &pos.x(), &pos.y(), &pos.z());
		CHECK_AL_ERROR(getListenerPosition);
		return pos;
	}
	
	void AudioManager::setListenerOrientation(const osg::Vec3& forward, const osg::Vec3& up)
	{
		if (!initialized || !active) return;
		float v[6];
		v[0] = forward.x();
		v[1] = forward.y();
		v[2] = forward.z();
		v[3] = up.x();
		v[4] = up.y();
		v[5] = up.z();
		alListenerfv(AL_ORIENTATION, v);
		CHECK_AL_ERROR(setListenerOrientation);
	}
	
	void AudioManager::setListenerRotation(const osg::Quat& rot)
	{
		setListenerOrientation(rot * osg::Vec3(0,1,0), rot * osg::Vec3(0,0,1));
	}
	
	void AudioManager::getListenerOrientation(osg::Vec3& forward, osg::Vec3& up)
	{
		if (!initialized || !active) return;
		float v[6];
		alGetListenerfv(AL_ORIENTATION, v);
		CHECK_AL_ERROR(getListenerOrientation);
		forward = osg::Vec3(v[0], v[1], v[2]);
		up = osg::Vec3(v[3], v[4], v[5]);
	}
	
	void AudioManager::setListenerVelocity(const osg::Vec3& vel)
	{
		if (!initialized || !active) return;
		alListener3f(AL_VELOCITY, vel.x(), vel.y(), vel.z());
		CHECK_AL_ERROR(setListenerVelocity);
	}
	
	osg::Vec3 AudioManager::getListenerVelocity()
	{
		if (!initialized || !active) return osg::Vec3(0,0,0);
		osg::Vec3 vel;
		alGetListener3f(AL_VELOCITY, &vel.x(), &vel.y(), &vel.z());
		CHECK_AL_ERROR(getListenerVelocity);
		return vel;
	}
	
	void AudioManager::setListenerGain(const float value)
	{
		if (!initialized || !active) return;
		alListenerf(AL_GAIN, value);
		CHECK_AL_ERROR(setListenerGain);
	}
	
	float AudioManager::getListenerGain()
	{
		if (!initialized || !active) return 0.f;
		float f = 0.f;
		alGetListenerf(AL_GAIN, &f);
		CHECK_AL_ERROR(getListenerGain);
		return f;
	}
	
	void AudioManager::update(const double dt)
	{
		if (moon::CameraManipulator::instance().getActiveCamera()) {
			osg::Matrix WM = moon::CameraManipulator::instance().getActiveCamera()->getWorldTransformMatrix();
			osg::Vec3 Wv =  moon::CameraManipulator::instance().getActiveCamera()->getWorldVelocity();
			setListenerPosition(WM.getTrans());
			setListenerRotation(WM.getRotate());
			setListenerVelocity(Wv);
		}
	}
	
	AudioManager& AudioManager::instance()
	{
		if (! instancePtr)
			instancePtr = new AudioManager;
		return *instancePtr;
	}
	
	AudioManager::AudioManager()
	:	moon::SimulationListener(),
		initialized(false),
		active(false),
		maxPitch(FLT_MAX)
	{
	}

	AudioManager *AudioManager::instancePtr = NULL;
}
