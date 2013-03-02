#ifndef MOON_VISUALMODEL_H
#define MOON_VISUALMODEL_H

#include "Component.h"
#include <osg/MatrixTransform>

namespace moon {

	/// \brief Visual model component
	/// \ingroup core components
	class MOON_EXPORT VisualModel : public Component {
	public:
		VisualModel();
		VisualModel(const std::string& filename, const osg::Matrix& M = osg::Matrix::identity(), const bool load = true);
		VisualModel(const VisualModel& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, VisualModel);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;

		virtual osg::Node* getNode();
		
		bool isInitiallyHidden() const { return initHidden; }
		
		/// Traverse a node and extract nodes from "specially tagged" names
		static osg::Node* extractSpecialNodes(osg::Node *node, const osg::Matrix& M = osg::Matrix::identity(), bool *premoved = NULL);
		void extractSpecialNodes();
		
	protected:
		std::string filename;
		osg::ref_ptr<osg::Node> model;
		osg::ref_ptr<osg::MatrixTransform> transform;
		bool initHidden;
	};
	
}

#endif
