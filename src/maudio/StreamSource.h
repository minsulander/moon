#ifndef MAUDIO_STREAMSOURCE_H
#define MAUDIO_STREAMSOURCE_H

#include "Source.h"
#include "Stream.h"
#include <moon/FactoryProduct.h>

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	/// \brief Audio source that can play a stream
	/// \ingroup components
	class MAUDIO_EXPORT StreamSource : public Source {
	public:
		StreamSource(const std::string& filename = "");
		StreamSource(const StreamSource& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(maudio, StreamSource);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void setStream(Stream *stream);
		virtual float getLength() const;
		
		virtual void initialize();
		virtual void realize();
		virtual void unrealize();
		virtual void play();
		virtual void stop();
		virtual void rewind();
		
		virtual void setLooping(const bool value);
		virtual bool isLooping() const;
		
		virtual void update(const double dt);
		
	protected:
		virtual ~StreamSource();
		
	private:
		osg::ref_ptr<Stream> stream;
	};
	
	/// @}
}

#endif
