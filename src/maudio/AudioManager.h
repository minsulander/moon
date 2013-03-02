#ifndef MAUDIO_AUDIOMANAGER_H
#define MAUDIO_AUDIOMANAGER_H

#include "OpenALHeaders.h"
#include "SingleSource.h"
#include "Export.h"
#include <moon/SimulationManager.h>
#include <string>
#include <exception>
#include <vector>
#include <osg/Vec3>
#include <osg/Quat>

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	/// Singleton manager for things like initializing OpenAL, shutting down etc
	class MAUDIO_EXPORT AudioManager : public moon::SimulationListener {
	public:
		void init();
		void shutdown();
		virtual ~AudioManager();
		void setActive(const bool value);
		bool isActive();
		bool isInitialized();
		
		/// Play a single-shot sample/sound
		Sound* play(const std::string& name, const float gain = 1.0, const float pitch = 1.0, const osg::Vec3& pos = osg::Vec3(0,0,0), const bool relative = true);
		/// Add a sound to list of single-shot sounds
		void addSound(Sound *sound);
		/// Get a single-shot sound by name from the list
		Sound *getSound(const std::string& name);
		
		void setListenerPosition(const osg::Vec3& pos);
		osg::Vec3 getListenerPosition();
		void setListenerOrientation(const osg::Vec3& forward, const osg::Vec3& up);
		void getListenerOrientation(osg::Vec3& forward, osg::Vec3& up);
		void setListenerRotation(const osg::Quat& rot);
		void setListenerVelocity(const osg::Vec3& vel);
		osg::Vec3 getListenerVelocity();
		void setListenerGain(const float value);
		float getListenerGain();

		float getMaxPitch() { return maxPitch; }
		
		virtual void update(const double dt);
		
		static AudioManager& instance();
		
	private:
		AudioManager();
		
		bool initialized, active;
		ALCdevice *device;
		ALCcontext *context;
		osg::ref_ptr<SingleSource> playSource;
		typedef std::vector< osg::ref_ptr<Sound> > SoundList;
		SoundList playSounds;
		float maxPitch;

		static AudioManager *instancePtr;
	};
	
	/// General audio exception
	class MAUDIO_EXPORT AudioException : public std::exception {
	public:
		AudioException(const std::string& nmessage) { message = nmessage; }
		~AudioException() throw() {}
		virtual const char* what() const throw() { return message.c_str(); }
	private:
		std::string message;
	};
	
	/// @}
}

#endif
