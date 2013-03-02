#ifndef MDRAW_VALUATOR_H
#define MDRAW_VALUATOR_H

#include "Export.h"
#include <osg/Node>

namespace mdraw {
	
	/// \brief Interface class for a valuator
	/// \ingroup draw
	/// A valuator in this sense is a visual object that changes its appearance
	/// depending on one or more values.
	class MDRAW_EXPORT Valuator {
	public:
		virtual void setValue(const float value, const unsigned int index = 0) = 0;
		virtual float getValue(const unsigned int index = 0) const = 0;
		virtual void setValuePtr(const float* valuePtr, const unsigned int index = 0) = 0;
		
		virtual osg::Node* asNode() = 0;
		virtual int getIndex(const std::string& name) { return -1; }
		virtual ~Valuator() {}
	};
	
}

#endif
