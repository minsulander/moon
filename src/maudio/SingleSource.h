#ifndef MAUDIO_SINGLESOURCE_H
#define MAUDIO_SINGLESOURCE_H

#include "Source.h"
#include "Sample.h"
#include <moon/FactoryProduct.h>

namespace maudio {
	
	/// \addtogroup audio
	/// @{
	
	/// \brief Audio source that can play a single sample file
	/// \ingroup components
	class MAUDIO_EXPORT SingleSource : public Source {
	public:
		SingleSource(const std::string& filename = "");
		SingleSource(const SingleSource& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(maudio, SingleSource);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void realize();
		
		virtual void setSample(Sample *sample);
		virtual float getLength() const;
		
	protected:
		virtual ~SingleSource();
		
	private:
		osg::ref_ptr<Sample> sample;
		bool failed;
	};
	
	/// @}
}

#endif
