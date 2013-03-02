#ifndef MAUDIO_SOURCE_H
#define MAUDIO_SOURCE_H

#include "Sound.h"
#include "OpenALHeaders.h"
#include "util.h"
#include <moon/Parsable.h>
#include <osg/Vec3>
#include <osg/Quat>

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	/// Temporary state storage for unrealized sound sources
	struct OpenALSourceState {
		float gain, pitch;
		bool looping;
		osg::Vec3 position, direction, velocity;
		float sec_offset;
		float cone_inner_angle;
		float cone_outer_angle;
		float cone_outer_gain;
		float reference_distance;
		float max_distance;
		float rolloff_factor;
		float min_gain;
		float max_gain;
		bool relative;
		
		OpenALSourceState();
		OpenALSourceState(ALuint sourceID);
		void apply(ALuint sourceID);
	};
	
	/// An OpenAL sound source
	class MAUDIO_EXPORT Source : public Sound {
	public:
		Source();
		Source(const Source& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void realize();
		virtual void unrealize();
		virtual bool isRealized() const;
		
		virtual void setGain(const float value);
		virtual float getGain() const;
		virtual void setPitch(const float value);
		virtual float getPitch() const;
		virtual void setLooping(const bool value);
		virtual bool isLooping() const;
		virtual void setPosition(const osg::Vec3& pos);
		virtual osg::Vec3 getPosition() const;
		virtual void setDirection(const osg::Vec3& forward);
		virtual void setRotation(const osg::Quat& rot);
		virtual osg::Quat getRotation() const;
		virtual osg::Vec3 getDirection() const;
		virtual void setVelocity(const osg::Vec3& pos);
		virtual osg::Vec3 getVelocity() const;
		virtual void setRelative(const bool value);
		virtual bool isRelative() const;
		virtual float getLength() const = 0;

		// State modifiers
		virtual void play();
		virtual void pause();
		virtual void rewind();
		virtual void stop();
		virtual void seek(const float secs);
		
		// State getters
		virtual bool isPlaying() const;
		virtual bool isPaused() const;
		virtual float tell() const;

	protected:
		virtual ~Source();
		ALuint sourceID;
		OpenALSourceState *state;

		static unsigned int numSources;
	};
	
	/// @}

}

#endif
