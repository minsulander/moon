#include "TextValuator.h"
#include <sstream>
#include <iostream>
#include <cstdio>

#ifdef WIN32
#	define snprintf _snprintf
#endif

namespace mdraw {
	
	TextValuator::TextValuator(const TextValuator& source, const osg::CopyOp& copyop)
	:	osg::Geode(source, copyop),
		formatstrings(source.formatstrings)
	{
		for (unsigned int i = 0; i < getNumDrawables(); i++) {
			if (osgText::TextBase *text = dynamic_cast<osgText::TextBase*> (getDrawable(i)))
				texts.push_back(text);
		}
	}
	
	void TextValuator::addText(osgText::TextBase *text)
	{
		std::string format = text->getText().createUTF8EncodedString();
		bool expectvalue = true;
		if (format.find_first_of("%") == std::string::npos) {
			format += "%f";
			expectvalue = false;
		}
		formatstrings.push_back(format);
		texts.push_back(text);
		addDrawable(text);
		if (expectvalue)
			setValueAndText(0, getNumDrawables()-1);
	}
	
	void TextValuator::setValue(const float value, const unsigned int index)
	{
		if (index >= values.size())
			values.resize(index+1);
		if (value == values[index])
			return;
		setValueAndText(value, index);
	}
	
	float TextValuator::getValue(const unsigned int index) const
	{
		if (index >= values.size())
			return 0.f;
		return values[index];
	}
	
	void TextValuator::setValuePtr(const float *ptr, const unsigned int index)
	{
		if (index >= texts.size())
			return;
		if (index >= valueptrs.size())
			valueptrs.resize(index+1);
		valueptrs[index] = ptr;
		setValue(*ptr, index);
	}
	
	void TextValuator::traverse(osg::NodeVisitor& nv)
	{
		if (nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR) {
			for (std::size_t i = 0; i < valueptrs.size(); i++) {
				if (valueptrs[i])
					setValue(*valueptrs[i], i);
			}
		}
	}
	
	void TextValuator::setValueAndText(const float value, const unsigned int index)
	{
		if (index >= texts.size())
			return;
		if (index >= values.size())
			values.resize(index+1);
		values[index] = value;
		/// set text by format string
		if (texts[index].valid()) {
			char buf[1024];
			snprintf(buf, sizeof(buf), formatstrings[index].c_str(), value);
			texts[index]->setText(buf);
		}
	}
	
} // namespace
