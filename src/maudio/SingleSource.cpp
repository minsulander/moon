#include "SingleSource.h"
#include "AudioManager.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>

using namespace moon;
using namespace mlog;

namespace maudio {

	REGISTER_Object_Alias(maudio, SingleSource, Source);
	
	SingleSource::SingleSource(const std::string& filename)
	:	Source(), failed(false)
	{
		if (filename.length() > 0)
			setSample(Sample::get(filename));
	}
	
	SingleSource::SingleSource(const SingleSource& other, const osg::CopyOp& copyop)
	:	Source(other, copyop), failed(false)
	{
		setSample(other.sample.get());
	}
	
	void SingleSource::parseXML(const TiXmlElement *element)
	{
		//=* attribute: file="(string)"
		std::string filename;
		if (XMLParser::parseStringAttribute(filename, element, "file"))
			setSample(Sample::get(filename));
		Source::parseXML(element);
	}
	
	void SingleSource::writeXML(TiXmlElement *element) const
	{
		Source::writeXML(element);
		if (sample.valid())
			element->SetAttribute("file", sample->getFileName());
	}
	
	void SingleSource::initialize()
	{
		if (sample.valid())
			Source::initialize();
	}
	
	void SingleSource::realize()
	{
		if (sample.valid() && AudioManager::instance().isActive()) {
			Source::realize();
			if (sourceID == AL_NONE)
				return;
			try {
				alSourcei(sourceID, AL_BUFFER, sample->getBufferID());
				CHECK_AL_ERROR_SOURCE(set sample);
				if (shouldAutoPlay())
					play();
				failed = false;
			} catch (AudioException& e) {
				if (!failed)
					dout(ERROR, AUDIO) << "Source " << getName() << ": " << e.what() << "\n";
				Source::unrealize();
				failed = true;
			}
		}
	}
	
	void SingleSource::setSample(Sample *newsample)
	{
		if (isRealized())
			unrealize();
		sample = newsample;
	}
	
	float SingleSource::getLength() const
	{
		if (sample.valid())
			return sample->getLength();
		return 0.0f;
	}

	SingleSource::~SingleSource()
	{
		if (sourceID != AL_NONE) {
			alSourceStop(sourceID);
			alSourcei(sourceID, AL_BUFFER, AL_NONE);
			CHECK_AL_ERROR_SOURCE(SingleSource destructor);
		}
	}
	
}
