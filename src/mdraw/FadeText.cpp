#include "FadeText.h"

namespace mdraw {
	
	osg::ref_ptr<osgText::Text> templateText;
	osg::ref_ptr<osg::Geode> notifyGeode;
	
	void TextFaderCallback::update(osg::NodeVisitor *nv, osg::Drawable *drawable) {
		if (!nv->getFrameStamp() || !drawable || done)
			return;
		osgText::Text *text = (osgText::Text*) drawable;
		double reftime = nv->getFrameStamp()->getReferenceTime();
		if (!firsttime) {
			firsttime = reftime;
			origalpha = text->getColor().w();
			origbackdropalpha = text->getBackdropColor().w();
			return;
		}
		// fade linearly from start time to end time
		if (reftime > firsttime+starttime) {
			osg::Vec4 color = text->getColor();
			color.w() = origalpha*(1.0-(reftime-starttime-firsttime)/(endtime-starttime));
			text->setColor(color);
			color = text->getBackdropColor();
			color.w() = origbackdropalpha*(1.0-(reftime-starttime-firsttime)/(endtime-starttime));
			text->setBackdropColor(color);
		}
		if (reftime > firsttime+endtime) {
			done = true;
		}
	}
	
	void TextFaderCleanerCallback::operator()(osg::Node *node, osg::NodeVisitor *nv) {
		if (nv->getVisitorType() != osg::NodeVisitor::UPDATE_VISITOR)
			return;
		osg::Geode *geode = (osg::Geode*) node;
		for (unsigned int i = 0; i < geode->getNumDrawables(); i++) {
			osg::Drawable *drawable = geode->getDrawable(i);
			TextFaderCallback *callback = (TextFaderCallback*) drawable->getUpdateCallback();
			if (callback && callback->isDone()) {
				geode->removeDrawable(drawable);
				i--;
			}
		}
	}
	
	void createFadeText(osg::Geode *geode, const std::string& string, const osg::Vec4& color, const double start, const double length) {
		if (!geode->getUpdateCallback())
			geode->setUpdateCallback(new TextFaderCleanerCallback);
		// Create template if it's not set
		if (!templateText.valid()) {
			templateText = new osgText::Text;
			templateText->setPosition(osg::Vec3(0,-0.8,0));
			templateText->setCharacterSize(0.04,1.6);
			templateText->setFont("fonts/Vera.ttf");
			templateText->setAlignment(osgText::Text::CENTER_CENTER);
			templateText->setBackdropType(osgText::Text::OUTLINE);
		}
		// Create new text
		osgText::Text *text = new osgText::Text(*templateText);
		text->setText(string);
		text->setColor(color);
		text->setUpdateCallback(new TextFaderCallback(start,length));
		// Move previous messages up
		for (unsigned int i = 0; i < geode->getNumDrawables(); i++) {
			osgText::Text *prevtext = (osgText::Text*) geode->getDrawable(i);
			double height = text->getBound().yMax() - text->getBound().yMin();
			prevtext->setPosition(prevtext->getPosition()+osg::Vec3(0, height*1.3, 0));
		}

		geode->addDrawable(text);
	}
	
	void setFadeTextTemplate(osgText::Text *text) {
		templateText = text;
	}
	
	void setNotifyGeode(osg::Geode *geode) {
		notifyGeode = geode;
	}
	
	void notify(const std::string& message, const osg::Vec4& color, const double start, const double length) {
		if (!notifyGeode)
			return;
		createFadeText(notifyGeode.get(), message, color, start, length);
	}
	
} // namespace ogeDraw
