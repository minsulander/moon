#include "Sound.h"
#include <moon/objects/KinematicObject.h>
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <mlog/Log.h>
#include <osg/io_utils>

using namespace moon;
using namespace mlog;

namespace maudio {
	
	Sound::Sound()
	:	Component(),
		ModifierContainer(),
		basegain(1),
		basepitch(1),
		triggermode(NO_TRIGGER),
		triggerThreshold(0.01f),
		autoplay(false),
		lastTriggerValue(0)
	{
	}
	
	Sound::Sound(const Sound& other, const osg::CopyOp& copyop)
	:	Component(other, copyop),
		ModifierContainer(other, copyop),
		basegain(other.basegain),
		basepitch(other.basepitch),
		positionOffset(other.positionOffset),
		rotationOffset(other.rotationOffset),
		triggermode(other.triggermode),
		triggerThreshold(other.triggerThreshold),
		autoplay(other.autoplay),
		lastTriggerValue(0)
	{
	}

	void Sound::parseXML(const TiXmlElement *element)
	{
		//=== Sound
		//=A sound object
		double value;
		if (XMLParser::parseDoubleAttribute(value, element, "gain")) {
			//=* attribute: gain="(number)"
			//=. Gain (volume), between 0 and 1.
			basegain = value;
			setGain((float)value);
		} else if (XMLParser::parseDoubleAttribute(value, element, "gaindb")) {
			//=* attribute: gaindb="(number)"
			//=. Gain (volume), specified in decibel (dB).
			value = pow(10,value/20.0);
			basegain = value;
			setGain((float)value);
		}
		//=* attribute: pitch="(number)"
		//=. Pitch, where 1 is normal.
		if (XMLParser::parseDoubleAttribute(value, element, "pitch")) {
			basepitch = value;
			setPitch((float)value);
		}
		//=* attribute: loop="true|false"
		bool loop;
		if (XMLParser::parseBooleanAttribute(loop, element, "loop"))
			setLooping(loop);
		//=* attribute: pos="(vector3)"
		osg::Vec3 v;
		if (XMLParser::parseVector3Attribute(v, element, "pos"))
			positionOffset = v;
		//=* attribute: dir="(vector3)"
		if (XMLParser::parseVector3Attribute(v, element, "dir"))
			rotationOffset.makeRotate(osg::Vec3(0,1,0), v);
		//=* attribute: play="true|false"
		//=. If set, the sound plays automatically when the object is realized
		XMLParser::parseBooleanAttribute(autoplay, element, "play");
		
		//=* attribute: trigger="play|pause|stop|play/pause|play/stop"
		std::string str;
		if (XMLParser::parseStringAttribute(str, element, "trigger")) {
			if (str == "play")
				triggermode = PLAY;
			else if (str == "pause")
				triggermode = PAUSE;
			else if (str == "stop")
				triggermode = STOP;
			else if (str == "play/pause")
				triggermode = PLAY_PAUSE;
			else if (str == "play/stop")
				triggermode = PLAY_STOP;
			else if (str == "none")
				triggermode = NO_TRIGGER;
			else
				throw ParseException("Unknown modifier trigger mode '" + str + "'", element);
		}
		//=* attribute: threshold="(number)"
		//=. Gain/pitch threshold value for trigger
		if (XMLParser::parseDoubleAttribute(value, element, "threshold"))
			triggerThreshold = value;
		
		// Parse modifiers
		//=* modifier targets: gain pitch
		ModifierContainer::parseXML(element);
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			std::string target = mod->getTargetName();
			if (target == "gain")
				mod->setTargetIndex(TARGET_GAIN);
			else if (target == "pitch")
				mod->setTargetIndex(TARGET_PITCH);
		}
	}		
	
	void Sound::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		if (basegain != 1)
			element->SetDoubleAttribute("gain", basegain);
		if (basepitch != 1)
			element->SetDoubleAttribute("pitch", basepitch);
		if (isLooping())
			element->SetAttribute("loop", true);
		if (positionOffset.length() > 1e-5) {
			std::stringstream ss;
			ss << positionOffset.x() << ", " << positionOffset.y() << ", " << positionOffset.z();
			element->SetAttribute("pos", ss.str());
		}
		if (!rotationOffset.zeroRotation()) {
			std::stringstream ss;
			osg::Vec3 dir = rotationOffset*osg::Vec3(0,1,0);
			ss << dir.x() << ", " << dir.y() << ", " << dir.z();
			element->SetAttribute("dir", ss.str());
		}
		std::string str;
		switch (triggermode) {
			case PLAY: str = "play"; break;
			case PAUSE: str = "pause"; break;
			case STOP: str = "stop"; break;
			case PLAY_PAUSE: str = "play/pause"; break;
			case PLAY_STOP: str = "play/stop"; break;
			default: break;
		}
		if (str.length() > 0)
			element->SetAttribute("trigger", str);
		if (triggerThreshold > 1e-5)
			element->SetDoubleAttribute("threshold", triggerThreshold);
		
		ModifierContainer::writeXML(element);
	}
	
	bool Sound::shouldAutoPlay() const { return autoplay; }
	void Sound::setAutoPlay(const bool value) { autoplay = value; }
	
	void Sound::initialize()
	{
		
		Component::initialize();
		object = dynamic_cast<BaseObject*> (getContainer());
		if (!object && getContainer()) {
			dout(ERROR) << "Container for sound '" << getName() << "' is not a BaseObject\n";
			return;
		}
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			if (Parameter *param = object->findParameter(mod->getName())) {
				mod->setParameter(param);
				dout(3, AUDIO) << "Modifer " << object->getName() << ":" << mod->getName() << " connected\n";
			} else {
				dout(3, AUDIO) << "No connection for modifier " << object->getName() << ":" << mod->getName() << "\n";
				dout(4, AUDIO) << "  Candidates are:\n";
				for (unsigned int i = 0; i < object->getNumParameters(); i++) {
					dout(4, AUDIO) << "    " << object->getParameter(i)->getName() << "\n";
				}
			}
		}
	}
	
	void Sound::realize()
	{
		Component::realize();
		setGain(basegain);
		setPitch(basepitch);
	}
	
	void Sound::unrealize()
	{
		Component::unrealize();
	}
	
	void Sound::update(const double dt)
	{
		if (dt > 0)
			updateModifiers();
		if (!object)
			return;
		osg::Matrix M;
		M.setTrans(positionOffset);
		M.setRotate(rotationOffset);
		osg::Matrix WM = object->getWorldTransformMatrix();
		M = M * WM;
		setPosition(M.getTrans());
		setRotation(M.getRotate());
		if (object->asKinematic())
			setVelocity(object->asKinematic()->getWorldVelocity());
	}
	
	void Sound::updateModifiers()
	{
		float gain = basegain;
		float pitch = basepitch;
		for (unsigned int i = 0; i < getNumModifiers(); i++) {
			Modifier *mod = getModifier(i);
			switch (mod->getTargetIndex()) {
				case TARGET_GAIN:
					gain *= mod->get();
					break;
				case TARGET_PITCH:
					pitch *= mod->get();
					break;
			}
		}

		if (gain > triggerThreshold || triggermode == NO_TRIGGER)
			setGain(gain);
		if (pitch > triggerThreshold || triggermode == NO_TRIGGER)
			setPitch(pitch);
		
		// Use trigger mode for the lowest of gain/pitch. If either of them get close
		// to zero the sound will be inaudible anyway.
		float value = std::min(gain,pitch);
		switch (triggermode) {
			case PLAY:
				if (value >= triggerThreshold && lastTriggerValue < triggerThreshold && !isPlaying())
					play();
				break;
			case PAUSE:
				if (value < triggerThreshold && lastTriggerValue >= triggerThreshold && isPlaying())
					pause();
				break;
			case STOP:
				if (value < triggerThreshold && lastTriggerValue >= triggerThreshold && isPlaying())
					stop();
				break;
			case PLAY_PAUSE:
				if (value >= triggerThreshold && lastTriggerValue < triggerThreshold && !isPlaying())
					play();
				else if (value < triggerThreshold && lastTriggerValue >= triggerThreshold && isPlaying())
					pause();
				break;
			case PLAY_STOP:
				if (value >= triggerThreshold && lastTriggerValue < triggerThreshold && !isPlaying())
					play();
				else if (value < triggerThreshold && lastTriggerValue >= triggerThreshold && isPlaying())
					stop();
				break;
			default: break;
		}
		lastTriggerValue = value;

	}
	
	void Sound::icMessage(const unsigned int id, void *data)
	{
		if (id == IC_MSG_UPDATE_TRANSFORMATION)
			update(0);
	}
	
}
