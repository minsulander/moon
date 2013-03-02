#ifndef MDRAW_FADETEXT_H
#define MDRAW_FADETEXT_H

#include "Export.h"
#include <osg/Drawable>
#include <osg/Geode>
#include <osgText/Text>

namespace mdraw {
	
	class MDRAW_EXPORT TextFaderCallback : public osg::Drawable::UpdateCallback
	{
	public:
		TextFaderCallback(double start, double length) : firsttime(0), starttime(start), endtime(start+length), done(false) {}
		
		virtual void update(osg::NodeVisitor *nv, osg::Drawable *drawable);
		const bool isDone() { return done; }
		
	protected:	
		double firsttime, starttime, endtime;
		double origalpha, origbackdropalpha;
		bool done;
	};
	
	class MDRAW_EXPORT TextFaderCleanerCallback : public osg::NodeCallback
	{
	public:
		virtual void operator()(osg::Node *node, osg::NodeVisitor *nv);
	};

	/// Create an osgText::Text and a TextFaderCallback and add them to the geode
	extern MDRAW_EXPORT void createFadeText(osg::Geode *geode, const std::string& string, const osg::Vec4& color = osg::Vec4(1,1,1,1), const double start = 5, const double length = 1);
	/// Set an osgText::Text to use as a template for createFadeText() and notify()
	extern MDRAW_EXPORT void setFadeTextTemplate(osgText::Text *text);
	/// Pre-select a geode for fading text messages
	extern MDRAW_EXPORT void setNotifyGeode(osg::Geode *geode);
	/// Create a fading text message on the geode previously set with setNotifyGeode()
	extern MDRAW_EXPORT void notify(const std::string& message, const osg::Vec4& color = osg::Vec4(1,1,1,1), const double start = 5, const double length = 1);
};

#endif
