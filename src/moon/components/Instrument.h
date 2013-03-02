#ifndef MOON_INSTRUMENT_H
#define MOON_INSTRUMENT_H

#include "VisualModel.h"
#include "moon/Modifier.h"
#include <vector>
#include <osg/Group>
#include <mdraw/Bar.h>
#include <mdraw/TextValuator.h>

namespace moon {
	
	/// \brief An instrument model - displaying content based on Parameter/Modifier values
	/// \ingroup core components
	class MOON_EXPORT Instrument : public VisualModel, public ModifierContainer {
	public:
		Instrument();
		Instrument(const Instrument& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Instrument);

		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		virtual void initialize();
		virtual void update(const double dt);
		
		osgText::Text* getLabel(const std::string& name);
		
	protected:
		osgText::Text* parseText(const TiXmlElement *element);

		std::vector<mdraw::Valuator*> valuators;
		osg::ref_ptr<osg::Group> group;
		osg::observer_ptr<osg::Geode> labelGeode;
	};
	
	class MOON_EXPORT BarGraph : public Instrument {
	public:
		BarGraph() {}
		BarGraph(const BarGraph& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
		: Instrument(source, copyop) {}
		META_Object(moon, BarGraph);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
	protected:
		mdraw::Bar* parseBar(const TiXmlElement *element);
	};
	
}

#endif
