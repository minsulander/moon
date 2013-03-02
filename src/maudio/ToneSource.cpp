#include "ToneSource.h"
#include "ToneGenerator.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>

using namespace moon;
using namespace mlog;

namespace maudio {
	
	REGISTER_Object_Alias(maudio, ToneSource, ToneSource);

	ToneSource::ToneSource() : SingleSource()
	{
	}
	
	ToneSource::ToneSource(const ToneSource& source, const osg::CopyOp& copyop) : SingleSource(source, copyop)
	{
	}
	
	void ToneSource::parseXML(const TiXmlElement *element)
	{
		//=== ToneSource
		//=See superclass Source
		SingleSource::parseXML(element);
		ToneGenerator generator;
		bool didGenerate = false;
		//=* repeatable element: tone waveform="sine|square|saw|noise|impulse|silence"
		for (const TiXmlElement *toneEl = element->FirstChildElement("tone"); toneEl; toneEl = toneEl->NextSiblingElement("tone")) {
			std::string str = "sine";
			XMLParser::parseStringAttribute(str, toneEl, "waveform");
			Waveform waveform;
			if (str == "sine")
				waveform = SINE;
			else if (str == "square")
				waveform = SQUARE;
			else if (str == "saw")
				waveform = SAW;
			else if (str == "noise")
				waveform = NOISE;
			else if (str == "impulse")
				waveform = IMPULSE;
			else if (str == "silence")
				waveform = SILENCE;
			else {
				dout(ERROR) << "Unknown tone waveform '" + str + "'\n";
				continue;
			}
			double freq = 1000, gain = 1, duration = 1, start = 0, phase = 0, prf = 0;
			//=** attribute: freq="(number)" [Hz] default 1000
			XMLParser::parseDoubleAttribute(freq, toneEl, "freq");
			//=** attribute: gain="(number)" 0-1
			XMLParser::parseDoubleAttribute(gain, toneEl, "gain");
			//=** attribute: length="(number)" [seconds] default 1
			XMLParser::parseDoubleAttribute(duration, toneEl, "length");
			//=** attribute: start="(number)" [seconds] default 0
			XMLParser::parseDoubleAttribute(start, toneEl, "start");
			//=** attribute: phase="(number)"
			XMLParser::parseDoubleAttribute(phase, toneEl, "phase");
			//=** attribute: prf="(number)" [Hz]
			//=. Pulse repetition frequency
			XMLParser::parseDoubleAttribute(prf, toneEl, "prf");
			generator.generate(waveform, freq, gain, duration, start, phase, prf);
			didGenerate = true;				
		}
		//=* element: prf freq="(number)" [Hz]
		//=. Pulse repetition frequency for entire sample
		if (const TiXmlElement *prfEl = element->FirstChildElement("prf")) {
			double freq = XMLParser::parseDoubleAttribute(prfEl, "freq");
			generator.prf(freq);
		}
		if (didGenerate)
			setSample(new Sample(generator.getBuffer()));
		// Save generated sample to file - just for testing...
		std::string savestr;
		if (XMLParser::parseString(savestr, element, "save", "file"))
			saveSampleBuffer(savestr, generator.getBuffer());
	}
	
	void ToneSource::writeXML(TiXmlElement *element) const
	{
		dout(WARN) << "Writing tone generated audio sources is not implemented\n";
		SingleSource::writeXML(element);
	}
	
	
}
