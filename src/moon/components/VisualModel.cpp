#include "VisualModel.h"
#include "moon/ObjectFactory.h"
#include "moon/XMLParser.h"
#include "mlog/Log.h"
#include "moon/objects/TransformObject.h"
#include <osgDB/ReadFile>
#include <osgSim/LightPointNode>
#include <osg/io_utils>

using namespace mlog;

namespace moon {
	
	REGISTER_Object_Alias(moon, VisualModel, Model);
	
	VisualModel::VisualModel()
	:	Component(),
		initHidden(false)
	{
	}
	
	VisualModel::VisualModel(const std::string& modelfile, const osg::Matrix& M, const bool load)
	:	Component(),
		filename(modelfile),
		initHidden(false)
	{
		if (load) {
			dout(3) << "Loading model " << filename << "\n";
			model = osgDB::readNodeFile(filename);
			if (!model)
				dout(ERROR) << "Failed to open model " << filename << "\n";
		}
		if (M != osg::Matrix::identity() && model.get()) {
			transform = new osg::MatrixTransform;
			if (model.valid())
				transform->addChild(model.get());
			transform->setMatrix(M);
		}
	}
	
	VisualModel::VisualModel(const VisualModel& source, const osg::CopyOp& copyop)
	:	Component(source, copyop),
		filename(source.filename),
		model(source.model),
		transform(source.transform),
		initHidden(source.initHidden)
	{
	}

	void VisualModel::parseXML(const TiXmlElement *element)
	{
		//=== VisualModel
		//=see superclass Component
		Component::parseXML(element);
		if (XMLParser::parseStringAttribute(filename, element, "file")) {
			dout(3) << "Loading model " << filename << "\n";
			model = osgDB::readNodeFile(filename);
			if (!model)
				dout(ERROR) << "Failed to open model " << filename << "\n";
		}
		osg::Vec3 v;
		osg::Matrix M;

		//=* attribute: yup="true|false"
		//=. Rotate model from x-left, y-up, z-back coordinate system.
		if (XMLParser::parseBooleanAttribute(element, "yup", true, false)) {
			M = osg::Matrix::rotate(M_PI/2.0,osg::Vec3(1,0,0))
			* osg::Matrix::rotate(M_PI,osg::Vec3(0,0,1));
		}
		//=* attribute: xforward="true|false"
		//=. Rotate model from x-forward, y-right, z-up coordinate system.
		if (XMLParser::parseBooleanAttribute(element, "xforward", true, false)) {
			M = osg::Matrix::rotate(M_PI/2.0, 0, 0, 1);
		}
		
		//=* attribute: att="(vector3)" [degrees]
		//=. Euler rotation (attitude) of the visual model
		if (XMLParser::parseVector3Attribute(v, element, "att")) {
			M *= moon::TransformObject::getMatrixFromEulerAngles(v*M_PI/180.0);
		}
		//=* attribute: scale="(vector3)"
		if (XMLParser::parseVector3Attribute(v, element, "scale"))
			M.makeScale(v);
		
		//=* attribute: pos="(vector3)"
		//=. Offset translation of the visual model
		if (XMLParser::parseVector3Attribute(v, element, "pos"))
			M.setTrans(v);

		//=* attribute: hidden="true|false"
		//=. If set, the model is hidden at scenario start
		XMLParser::parseBooleanAttribute(initHidden, element, "hidden");
		
		if (M != osg::Matrix::identity()) {
			if (!transform.valid()) {
				transform = new osg::MatrixTransform;
				if (model.valid())
					transform->addChild(model.get());
			}
			transform->setMatrix(M);
		}

		//=* attribute: extract="true|false"
		//=. If set, tagged nodes are replaced with other eyecandy
		if (XMLParser::parseBooleanAttribute(element, "extract", true, false))
			extractSpecialNodes();
		
	}
	
	void VisualModel::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		if (filename.length() > 0)
			element->SetAttribute("file", filename);
		if (transform.valid()) {
			osg::Matrix M = transform->getMatrix();
			osg::Vec3 pos = M.getTrans();
			if (pos.length() > 1e-5) {
				std::stringstream ss;
				ss << pos;
				element->SetAttribute("pos", ss.str());
			}
			osg::Vec3 att = moon::TransformObject::getEulerAnglesFromMatrix(M) * 180.0/M_PI;
			if (att.length() > 1e-5) {
				std::stringstream ss;
				ss << att;
				element->SetAttribute("att", ss.str());
			}
			osg::Vec3 scale = M.getScale();
			if ((scale-osg::Vec3(1,1,1)).length() > 1e-5) {
				std::stringstream ss;
				ss << scale;
				element->SetAttribute("scale", ss.str());
			}
		}
	}
	
	osg::Node *VisualModel::getNode()
	{
		if (transform.valid())
			return transform.get();
		return model.get();
	}
	

	
	bool extractStringValue(const std::string& str, const std::string& sub, float& value) {
		size_t index = str.find(sub);
		if (index != std::string::npos) {
			std::stringstream ss;
			ss.str(str.substr(index+sub.length()));
			ss >> value;
			return true;
		}
		return false;
	}
	
	osg::Node* addNodeToNode(osg::Node *addnode, osg::Node *tonode) {
		if (!addnode) {
		} else if (!tonode) {
			tonode = addnode;
		} else if (tonode->asGroup()) {
			tonode->asGroup()->addChild(addnode);
		} else {
			osg::Node *tempnode = tonode;
			tonode = new osg::Group;
			tonode->asGroup()->addChild(tempnode);
			tonode->asGroup()->addChild(addnode);
		}
		return tonode;
	}
	
	osgSim::LightPoint extractLightPoint(osg::Node *node, const osg::Vec3 trans, osgSim::LightPoint* templateLP = NULL) {
		std::string name = node->getName();
		if (name.length() == 0 && node->getNumParents() > 0)
			name = node->getParent(0)->getName();

		osgSim::LightPoint lp;
		if (templateLP)
			lp = *templateLP;
		lp._position = node->getBound().center() + trans;
		osg::Geode* geode = dynamic_cast<osg::Geode*> (node);
		while (!geode && node->asGroup() && node->asGroup()->getNumChildren() > 0) {
			node = node->asGroup()->getChild(0);
			geode = dynamic_cast<osg::Geode*> (node);
		}
		if (geode && geode->getDrawable(0) && geode->getDrawable(0)->asGeometry()) {
			osg::Array* colors = geode->getDrawable(0)->asGeometry()->getColorArray();
			if (colors) {
				if (colors->getType() == osg::Array::Vec4ArrayType) {
					osg::Vec4Array *v4colors = (osg::Vec4Array*) colors;
					if (v4colors->size() > 0)
						lp._color = (*v4colors)[0];
				} else
					dout(WARN) << "Unknown array type " << colors->getType() << "for :lp special node tag\n";
			}
		}
		float value;
		if (extractStringValue(name, ":intensity", value))
			lp._intensity = value;
		if (extractStringValue(name, ":radius", value))
			lp._radius = value;
		else
			lp._radius = node->getBound().radius();
		if (name.find(":add") != std::string::npos)
			lp._blendingMode = osgSim::LightPoint::ADDITIVE;
		if (extractStringValue(name, ":blink", value)) {
			osgSim::BlinkSequence *blink = new osgSim::BlinkSequence;
			blink->addPulse(value, lp._color);
			blink->addPulse(value, osg::Vec4(0,0,0,0));
			lp._blinkSequence = blink;
		}
		return lp;
	}
	
	osg::Node *VisualModel::extractSpecialNodes(osg::Node *node, const osg::Matrix& M, bool *premoved) {
		if (!node)
			return NULL;
		dout(4) << "extract " << node->getName() << "\n";
		osg::Node *retnode = NULL;
		
		std::string name = node->getName();
		if (name.length() == 0 && node->getNumParents() > 0)
			name = node->getParent(0)->getName();
		
		if (name.find(":skip") != std::string::npos)
			return NULL;
		if (node->asTransform() && node->asTransform()->asMatrixTransform()) {
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++) {
				bool removed = false;
				retnode = addNodeToNode(extractSpecialNodes(node->asGroup()->getChild(i),node->asTransform()->asMatrixTransform()->getMatrix() * M, &removed), retnode);
				if (removed)
					i--;
			}
		} else if (node->asGroup()) {
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++) {
				bool removed = false;
				retnode = addNodeToNode(extractSpecialNodes(node->asGroup()->getChild(i),M, &removed), retnode);
				if (removed)
					i--;
			}
		}
		
		if (name.find(":lp") != std::string::npos) {
			osgSim::LightPointNode *lpn = new osgSim::LightPointNode;
			float value;
			if (extractStringValue(name, ":min", value))
				lpn->setMinPixelSize(value);
			if (extractStringValue(name, ":max", value))
				lpn->setMaxPixelSize(value);
			if (extractStringValue(name, ":distance", value))
				lpn->setMaxVisibleDistance2(value*value);
			if (node->asGroup()) {
				osgSim::LightPoint templateLP = extractLightPoint(node, M.getTrans());
				for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
					lpn->addLightPoint(extractLightPoint(node->asGroup()->getChild(i), M.getTrans(), &templateLP));
			} else
				lpn->addLightPoint(extractLightPoint(node, M.getTrans()));
			dout(4) << lpn->getNumLightPoints() << " lightpoints\n";
			retnode = addNodeToNode(lpn, retnode);
			if (node->getNumParents() > 0) {
				node->getParent(0)->removeChild(node);
				if (premoved) 
					*premoved = true;
			}
		}
		
		return retnode;	
	}
	
	void VisualModel::extractSpecialNodes()
	{ 
		if (!model.valid())
			return;
		osg::Node *specnode = extractSpecialNodes(model.get());
		if (specnode) {
			specnode->setName(getName() + ":special:nogeo");
			if (!transform.valid()) {
				transform = new osg::MatrixTransform;
				transform->addChild(model.get());
			}
			transform->addChild(specnode);
		}
	}
	
}
