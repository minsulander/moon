#ifndef MDRAW_VALUATORTEXT_H
#define MDRAW_VALUATORTEXT_H

#include "Valuator.h"
#include <osg/Geode>
#include <osgText/Text>
#include <string>

namespace mdraw {
	
	/// \brief Text node that varies its text content depending on set values
	/// \ingroup draw
	class MDRAW_EXPORT TextValuator : public osg::Geode, public Valuator {
	public:
		TextValuator()
			: osg::Geode() {}
		TextValuator(const TextValuator& source, const osg::CopyOp& copyop = osg::CopyOp::DEEP_COPY_ALL);
		META_Node(mdraw, TextValuator);
		
		void addText(osgText::TextBase* text);
		
		virtual void setValue(const float value, const unsigned int index = 0);
		virtual float getValue(const unsigned int index = 0) const;
		virtual void setValuePtr(const float* valuePtr, const unsigned int index = 0);
		virtual osg::Node* asNode() { return this; }
		
		virtual void traverse(osg::NodeVisitor& nv);
		
	private:
		void setValueAndText(const float value, const unsigned int index = 0);
		
		std::vector< osg::observer_ptr<osgText::TextBase> > texts;
		std::vector<std::string> formatstrings;
		std::vector<float> values;
		std::vector< const float* > valueptrs;
	};
	
}

#endif
