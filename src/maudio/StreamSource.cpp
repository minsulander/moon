#include "StreamSource.h"
#include "AudioManager.h"
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <mlog/Log.h>

using namespace moon;
using namespace mlog;

namespace maudio {

	REGISTER_Object_Alias(maudio, StreamSource, Stream);
	
	StreamSource::StreamSource(const std::string& filename)
	:	Source()
	{
		if (filename.length() > 0)
			setStream(Stream::get(filename));
	}
	
	StreamSource::StreamSource(const StreamSource& other, const osg::CopyOp& copyop)
	:	Source(other, copyop)
	{
		setStream(other.stream.get());
	}
	
	void StreamSource::parseXML(const TiXmlElement *element)
	{
		//=== Stream
		//=* attribute: file="(string)"
		std::string filename;
		if (XMLParser::parseStringAttribute(filename, element, "file"))
			setStream(Stream::get(filename));
		Source::parseXML(element);
	}
	
	void StreamSource::writeXML(TiXmlElement *element) const
	{
		Source::writeXML(element);
		if (stream.valid())
			element->SetAttribute("file", stream->getFileName());
	}
	
	void StreamSource::setStream(Stream *newstream)
	{
		if (isRealized())
			unrealize();
		stream = newstream;
	}
	
	float StreamSource::getLength() const
	{
		if (stream.valid())
			return stream->getLength();
		return 0.0f;
	}
	
	void StreamSource::initialize()
	{
		if (stream.valid())
			Source::initialize();
	}

	void StreamSource::realize()
	{
		if (stream.valid()) {
			Source::realize();
			stream->setSource(sourceID);
			if (shouldAutoPlay())
				play();
		}
	}
	
	void StreamSource::unrealize()
	{
		if (stream.valid())
			stream->setSource(AL_NONE);
		Source::unrealize();
		if (stream.valid())
			stream->stop();
	}
	
	void StreamSource::play()
	{
		if (sourceID == AL_NONE)
			realize();
		if (stream.valid() && sourceID != AL_NONE) {
			stream->setSource(sourceID);
			stream->start();
		}
		Source::play();
	}
	
	void StreamSource::stop()
	{
		Source::stop();
		if (stream.valid())
			stream->stop();
	}
	
	void StreamSource::rewind()
	{
		bool replay = isPlaying();
		stop();
		if (stream.valid())
			stream->rewind();
		Source::rewind();
		if (replay)
			play();
	}
	
	void StreamSource::setLooping(const bool value)
	{
		/// \todo imlement looping streams
	}
	
	bool StreamSource::isLooping() const
	{
		return false;
	}
	
	void StreamSource::update(const double dt)
	{
		if (stream.valid() && !Stream::usingThread())
			stream->update();
		Source::update(dt);
	}
	
	StreamSource::~StreamSource()
	{
		if (stream.valid())
			stream->stop();
	}
	
}
