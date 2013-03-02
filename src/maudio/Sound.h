#ifndef MAUDIO_SOUND_H
#define MAUDIO_SOUND_H

#include "Export.h"
#include <moon/Modifier.h>
#include <moon/components/Component.h>
#include <moon/objects/BaseObject.h>
#include <osg/Vec3>
#include <osg/Quat>
#include <vector>

namespace maudio {
	
	/// \addtogroup audio
	/// @{

	/// \brief Interface class for audible objects (i.e. a sound source)
	/// \ingroup components
	class MAUDIO_EXPORT Sound : public moon::Component, public moon::ModifierContainer {
	public:
		Sound();
		Sound(const Sound& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Play the sound
		virtual void play()=0;
		/// Pause the sound
		virtual void pause()=0;
		/// Rewind (set sample positon to zero)
		virtual void rewind()=0;
		/// Stop the sound
		virtual void stop()=0;
		
		/// Returns true if the sound is playing
		virtual bool isPlaying() const = 0;
		/// Returns true if the sound is paused
		virtual bool isPaused() const = 0;
		
		/// Get gain (volume) of the sound
		virtual float getGain() const = 0;
		/// Set gain (volume) of the sound
		virtual void setGain(const float value)=0;
		/// Get pitch of the sound ("normal" pitch is 1)
		virtual float getPitch() const = 0;
		/// Set pitch of the sound ("normal" pitch is 1)
		virtual void setPitch(const float value)=0;
		/// Returns true if this sound object is looping
		virtual bool isLooping() const = 0;
		/// Set wether this sound object is looping
		virtual void setLooping(const bool value)=0;
		/// Set position of sound in world coordinates
		virtual void setPosition(const osg::Vec3& pos) = 0;
		/// Set orientation of the sound by specifiying forward
		virtual void setDirection(const osg::Vec3& forward) = 0;
		/// Set orientation of the sound by specifying rotation
		virtual void setRotation(const osg::Quat& rot) = 0;
		// Get rotation of the sound
		virtual osg::Quat getRotation() const = 0;
		/// Get orientation of the sound
		virtual osg::Vec3 getDirection() const = 0;
		/// Get position of sound in world coordinates
		virtual osg::Vec3 getPosition() const = 0;
		/// Set velocity of sound in world coordinates
		virtual void setVelocity(const osg::Vec3& vel) = 0;
		/// Get velocity of sound in world coordinates
		virtual osg::Vec3 getVelocity() const = 0;
		/// Set wether position, orientation and velocity is relative listener
		virtual void setRelative(const bool value) = 0;
		/// Get wether position, orientation and velocity is relative listener
		virtual bool isRelative() const = 0;
		/// Get length in seconds
		virtual float getLength() const = 0;
		
		/// Return wether the sound should automatically start playing
		virtual bool shouldAutoPlay() const;
		/// Set wether the sound should automatically start playing
		virtual void setAutoPlay(const bool value);
		
		enum AudioModifierTarget {
			TARGET_NONE,
			TARGET_GAIN,
			TARGET_PITCH
		};
				
		enum TriggerMode {
			NO_TRIGGER,
			PLAY,
			PAUSE,
			STOP,
			PLAY_STOP,
			PLAY_PAUSE
		};
		/// Set the trigger mode used to start/pause/stop the sound automatically when 
		/// gain/pitch is set above or below the trigger threshold
		void setTriggerMode(TriggerMode mode) { triggermode = mode; }
		/// Get the trigger mode
		TriggerMode getTriggerMode() const { return triggermode; }
		/// Set threshold value for triggering the sound
		/// \see setTriggerMode()
		void setTriggerThreshold(const float value) { triggerThreshold = value; }
		/// Get the trigger threshold value
		float getTriggerThreshold() const { return triggerThreshold; }
		
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void update(const double dt);
		virtual void updateModifiers();
		virtual void icMessage(const unsigned int id, void *data = NULL);
		
	protected:
		float basegain, basepitch;
		osg::Vec3 positionOffset;
		osg::Quat rotationOffset;
		
	private:
		osg::observer_ptr< moon::BaseObject > object;
		TriggerMode triggermode;
		float triggerThreshold;
		bool autoplay;
		float lastTriggerValue;
	};
	
	/// @}
}

#endif
