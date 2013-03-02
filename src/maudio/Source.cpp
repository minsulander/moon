#include "Source.h"
#include "AudioManager.h"
#include <moon/XMLParser.h>
#include <mlog/Log.h>
#include <float.h>

#ifdef _MSC_VER
#	pragma warning(disable:4800)
#endif

using namespace moon;
using namespace mlog;

namespace maudio {
	
	OpenALSourceState::OpenALSourceState()
	: gain(1.f), pitch(1.f), looping(false), direction(0,1,0),
	  sec_offset(0.f), cone_inner_angle(360.f), cone_outer_angle(360.f),
	  cone_outer_gain(0.f), reference_distance(1.f), max_distance(FLT_MAX), rolloff_factor(1.f),
	  min_gain(0.f), max_gain(1.f), relative(false)
	{
	}
	
	OpenALSourceState::OpenALSourceState(ALuint sourceID)
	{
		if (sourceID == AL_NONE)
			return;
		alGetError();
		alGetSourcef(sourceID, AL_GAIN, &gain);
		alGetSourcef(sourceID, AL_PITCH, &pitch);
		int i;
		alGetSourcei(sourceID, AL_LOOPING, &i);
		looping = (i == AL_TRUE);
		alGetSource3f(sourceID, AL_POSITION, &position.x(), &position.y(), &position.z());
		alGetSource3f(sourceID, AL_DIRECTION, &direction.x(), &direction.y(), &direction.z());
		alGetSource3f(sourceID, AL_VELOCITY, &velocity.x(), &velocity.y(), &velocity.z());
		alGetSourcei(sourceID, AL_SOURCE_RELATIVE, &i);
		relative = (i == AL_TRUE);
#ifndef __linux__
		alGetSourcef(sourceID, AL_SEC_OFFSET, &sec_offset);
#endif
		alGetSourcef(sourceID, AL_CONE_INNER_ANGLE, &cone_inner_angle);
		alGetSourcef(sourceID, AL_CONE_OUTER_ANGLE, &cone_outer_angle);
		alGetSourcef(sourceID, AL_CONE_OUTER_GAIN, &cone_outer_gain);
		alGetSourcef(sourceID, AL_REFERENCE_DISTANCE, &reference_distance);
		alGetSourcef(sourceID, AL_MAX_DISTANCE, &max_distance);
		alGetSourcef(sourceID, AL_ROLLOFF_FACTOR, &rolloff_factor);
		alGetSourcef(sourceID, AL_MIN_GAIN, &min_gain);
		alGetSourcef(sourceID, AL_MAX_GAIN, &max_gain);
		CHECK_AL_ERROR_SOURCE(getState);
	}
	
	void OpenALSourceState::apply(ALuint sourceID)
	{
		if (sourceID == AL_NONE)
			return;
		alSourcef(sourceID, AL_GAIN, gain);
		alSourcef(sourceID, AL_PITCH, pitch);
		int i = looping;
		alSourcei(sourceID, AL_LOOPING, i);
		alSource3f(sourceID, AL_POSITION, position.x(), position.y(), position.z());
		alSource3f(sourceID, AL_DIRECTION, direction.x(), direction.y(), direction.z());
		alSource3f(sourceID, AL_VELOCITY, velocity.x(), velocity.y(), velocity.z());
		i = relative;
		alSourcei(sourceID, AL_SOURCE_RELATIVE, i);
#ifndef __linux__
		alSourcef(sourceID, AL_SEC_OFFSET, sec_offset);
#endif
		alSourcef(sourceID, AL_CONE_INNER_ANGLE, cone_inner_angle);
		alSourcef(sourceID, AL_CONE_OUTER_ANGLE, cone_outer_angle);
		alSourcef(sourceID, AL_CONE_OUTER_GAIN, cone_outer_gain);
		alSourcef(sourceID, AL_REFERENCE_DISTANCE, reference_distance);
		alSourcef(sourceID, AL_MAX_DISTANCE, max_distance);
		alSourcef(sourceID, AL_ROLLOFF_FACTOR, rolloff_factor);
		alSourcef(sourceID, AL_MIN_GAIN, min_gain);
		alSourcef(sourceID, AL_MAX_GAIN, max_gain);
		CHECK_AL_ERROR_SOURCE(applyState);
	}

	/// \throw AudioException on OpenAL errors
	Source::Source()
	:	Sound(),
		sourceID(AL_NONE),
		state(new OpenALSourceState)
	{
	}
	
	Source::Source(const Source& other, const osg::CopyOp& copyop)
	:	Sound(other, copyop),
		sourceID(AL_NONE)
	{
		if (other.state)
			state = new OpenALSourceState(*other.state);
		else
			state = new OpenALSourceState(other.sourceID);
	}
	
	void Source::parseXML(const TiXmlElement *element)
	{
		//=== Source
		//=An audio source
		//=see superclass Sound
		double value;
		Sound::parseXML(element);
		//=* attribute: offset="(number)" [seconds]
		//=. Sample start offset.
		if (XMLParser::parseDoubleAttribute(value, element, "offset"))
			state->sec_offset = value;
		//=* attribute: refdistance="(number)" [meter]
		if (XMLParser::parseDoubleAttribute(value, element, "refdistance"))
			state->reference_distance = value;
		
		//=* element: cone direction="(vector3)" inner="(number)" outer="(number)" outgain="(number)"
		if (const TiXmlElement *coneElement = element->FirstChildElement("cone")) {
			osg::Vec3 v;
			if (XMLParser::parseVector3Attribute(v, coneElement, "direction")) {
				setDirection(v);
			}
			if (XMLParser::parseDoubleAttribute(value, coneElement, "inner"))
				state->cone_inner_angle = value;
			if (XMLParser::parseDoubleAttribute(value, coneElement, "outer"))
				state->cone_outer_angle = value;
			if (XMLParser::parseDoubleAttribute(value, coneElement, "outgain"))
				state->cone_outer_gain = value;
		}
		
		//=* element: distance ref="(number)" max="(number)" [meter] rolloff="(number)"
		if (XMLParser::parseDouble(value, element, "distance", "meter", "ref")) {
			state->reference_distance = value;
		}
		if (XMLParser::parseDouble(value, element, "distance", "meter", "max")) {
			state->max_distance = value;
		}
		if (XMLParser::parseDouble(value, element, "distance", "meter", "rolloff")) {
			state->rolloff_factor = value;
		}
		
		//=* element: gain min="(number)" max="(number)"
		if (XMLParser::parseDouble(value, element, "gain", "", "min")) {
			state->min_gain = value;
		}
		if (XMLParser::parseDouble(value, element, "gain", "", "max")) {
			state->max_gain = value;
		}
		
	}
	
	void Source::writeXML(TiXmlElement *element) const
	{
		Sound::writeXML(element);
		/// \todo Implement
	}
	
	void Source::realize()
	{
		if (isRealized() || !AudioManager::instance().isActive())
			return;
		dout(5, AUDIO) << "Allocating source #" << numSources << " " << getName();
		alGenSources(1, &sourceID);
		if (sourceID != AL_NONE) {
			dout(5, AUDIO) << " id " << sourceID << "\n";
			numSources++;
			state->apply(sourceID);
			delete state;
			state = NULL;
		} else {
			dout(5, AUDIO) << " failed\n";
			dout(WARN, AUDIO) << "Failed to allocate source #" << numSources+1 << " " << getName() << "\n";
			return;
		}
		CHECK_AL_ERROR_SOURCE(realize);
		
		Sound::realize();
	}
	
	void Source::unrealize()
	{
		if (!isRealized())
			return;
		if (sourceID != AL_NONE) {
			dout(5, AUDIO) << "Deallocating source id " << sourceID << "\n";
			Sound::unrealize();
			state = new OpenALSourceState(sourceID);
			alDeleteSources(1, &sourceID);
			sourceID = AL_NONE;
			numSources--;
			CHECK_AL_ERROR_SOURCE(unrealize);
		}
	}
	
	bool Source::isRealized() const
	{
		return (sourceID != AL_NONE);
	}
	
	/// \throw AudioException on OpenAL errors
	Source::~Source()
	{
		CHECK_AL_ERROR_SOURCE(Source destructor PRE);
		if (state) {
			delete state;
			state = NULL;
		}
		if (sourceID != AL_NONE) {
			alSourceStop(sourceID);
			dout(5, AUDIO) << "Deallocating source id " << sourceID << "\n";
			alDeleteSources(1, &sourceID);
			CHECK_AL_ERROR_SOURCE(Source destructor);
			numSources--;
		}
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setGain(const float value)
	{
	  float gain = value;
	  if (gain < 0)
	    gain = 0;
	  if (state)
	    state->gain = gain;
	  if (sourceID == AL_NONE) return;
	  alSourcef(sourceID, AL_GAIN, gain);
	  CHECK_AL_ERROR_SOURCE(setGain);
	}
	
	/// \throw AudioException on OpenAL errors
	float Source::getGain() const
	{
		if (sourceID == AL_NONE) return state->gain;
		float g;
		alGetSourcef(sourceID, AL_GAIN, &g);
		CHECK_AL_ERROR_SOURCE(getGain);
		return g;
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setPitch(const float value)
	{
	  float pitch = value;
	  if (pitch < 0)
	    pitch = 0;
	  else if (pitch > AudioManager::instance().getMaxPitch())
	    pitch = AudioManager::instance().getMaxPitch();
	  if (state)
	    state->pitch = pitch;
	  if (sourceID == AL_NONE) return;
	  alSourcef(sourceID, AL_PITCH, pitch);
	  CHECK_AL_ERROR_SOURCE(setPitch);
	}
	
	/// \throw AudioException on OpenAL errors
	float Source::getPitch() const
	{
		if (sourceID == AL_NONE) return state->pitch;
		float p;
		alGetSourcef(sourceID, AL_PITCH, &p);
		CHECK_AL_ERROR_SOURCE(getPitch);
		return p;
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setLooping(const bool value)
	{
		if (state)
			state->looping = value;
		if (sourceID == AL_NONE) return;
		if (value)
			alSourcei(sourceID, AL_LOOPING, AL_TRUE);
		else
			alSourcei(sourceID, AL_LOOPING, AL_FALSE);
		CHECK_AL_ERROR_SOURCE(setLooping);
	}
	
	/// \throw AudioException on OpenAL errors
	bool Source::isLooping() const
	{
		if (sourceID == AL_NONE) return state->looping;
		int i;
		alGetSourcei(sourceID, AL_LOOPING, &i);
		CHECK_AL_ERROR_SOURCE(isLooping);
		return (i == AL_TRUE);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setPosition(const osg::Vec3& newpos)
	{
		osg::Vec3 pos = newpos;
		if (state)
			state->position = pos;
		if (sourceID == AL_NONE) return;
		alSource3f(sourceID, AL_POSITION, pos.x(), pos.y(), pos.z());
		CHECK_AL_ERROR_SOURCE(setPosition);
	}
	
	/// \throw AudioException on OpenAL errors
	osg::Vec3 Source::getPosition() const
	{
		if (sourceID == AL_NONE) return state->position;
		float x,y,z;
		alGetSource3f(sourceID, AL_POSITION, &x, &y, &z);
		CHECK_AL_ERROR_SOURCE(getPosition);
		return osg::Vec3(x,y,z);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setDirection(const osg::Vec3& direction)
	{
		if (state)
			state->direction = direction;
		if (sourceID == AL_NONE) return;
		alSource3f(sourceID, AL_DIRECTION, direction.x(), direction.y(), direction.z());
		CHECK_AL_ERROR_SOURCE(setDirection);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setRotation(const osg::Quat& rot)
	{
		setDirection(rot * rotationOffset * osg::Vec3(0,1,0));
	}
	
	/// \throw AudioException on OpenAL errors
	osg::Quat Source::getRotation() const
	{
		osg::Quat rot;
		rot.makeRotate(osg::Vec3(0,1,0), getDirection());
		return rot;
	}
	
	/// \throw AudioException on OpenAL errors
	osg::Vec3 Source::getDirection() const
	{
		if (sourceID == AL_NONE) return state->direction;
		float x,y,z;
		alGetSource3f(sourceID, AL_DIRECTION, &x, &y, &z);
		CHECK_AL_ERROR_SOURCE(getDirection);
		return osg::Vec3(x,y,z);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::setVelocity(const osg::Vec3& vel)
	{
		if (state)
			state->velocity = vel;
		if (sourceID == AL_NONE) return;
		alSource3f(sourceID, AL_VELOCITY, vel.x(), vel.y(), vel.z());
		CHECK_AL_ERROR_SOURCE(setVelocity);
	}
	
	/// \throw AudioException on OpenAL errors
	osg::Vec3 Source::getVelocity() const
	{
		if (sourceID == AL_NONE) return state->velocity;
		float x,y,z;
		alGetSource3f(sourceID, AL_VELOCITY, &x, &y, &z);
		CHECK_AL_ERROR_SOURCE(getVelocity);
		return osg::Vec3(x,y,z);
	}
	
	void Source::setRelative(const bool value)
	{
		if (state)
			state->relative = value;
		if (sourceID == AL_NONE) return;
		alSourcei(sourceID, AL_SOURCE_RELATIVE, value);
		CHECK_AL_ERROR(setRelative);
	}
	
	bool Source::isRelative() const
	{
		if (sourceID == AL_NONE) return state->relative;
		int i;
		alGetSourcei(sourceID, AL_SOURCE_RELATIVE, &i);
		CHECK_AL_ERROR_SOURCE(isRelative);
		return (bool)i;
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::play()
	{
		dout(8, AUDIO) << "Play source " << getName() << "\n";
		if (sourceID == AL_NONE)
			realize();
		if (sourceID == AL_NONE) return;
		alSourcePlay(sourceID);
		CHECK_AL_ERROR_SOURCE(play);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::pause()
	{
		dout(8, AUDIO) << "Pause source " << getName() << "\n";
		if (sourceID == AL_NONE) return;
		alSourcePause(sourceID);
		CHECK_AL_ERROR_SOURCE(pause);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::rewind()
	{
		if (sourceID == AL_NONE) return;
		alSourceRewind(sourceID);
		CHECK_AL_ERROR_SOURCE(rewind);
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::stop()
	{
		dout(8, AUDIO) << "Stop source " << getName() << "\n";
		if (sourceID == AL_NONE) return;
		alSourceStop(sourceID);
		CHECK_AL_ERROR_SOURCE(stop);
		unrealize();
	}
	
	/// \throw AudioException on OpenAL errors
	void Source::seek(const float secs)
	{
		if (sourceID == AL_NONE) return;
		alSourcef(sourceID, AL_SEC_OFFSET, secs);
		CHECK_AL_ERROR_SOURCE(seek);
	}
	
	/// \throw AudioException on OpenAL errors
	bool Source::isPlaying() const
	{
		if (sourceID == AL_NONE) return false;
		ALint state;
		alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
		CHECK_AL_ERROR_SOURCE(isPlaying);
		return (state == AL_PLAYING);
	}
	
	/// \throw AudioException on OpenAL errors
	bool Source::isPaused() const
	{
		if (sourceID == AL_NONE) return true;
		ALint state;
		alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
		CHECK_AL_ERROR_SOURCE(isPaused);
		return (state == AL_PAUSED);
	}
	
	/// \throw AudioException on OpenAL errors
	float Source::tell() const
	{
		if (sourceID == AL_NONE) return 0.f;
		float secs;
		ALint state;
		alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
		if (state == AL_INITIAL || state == AL_STOPPED)
			return 0;
		alGetSourcef(sourceID, AL_SEC_OFFSET, &secs);
		CHECK_AL_ERROR_SOURCE(tell);
		return secs;
	}
	
	unsigned int Source::numSources = 0;

}

