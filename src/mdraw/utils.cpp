#include "utils.h"

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/BlendFunc>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/MatrixTransform>
#include <osg/Switch>
#include <osg/CoordinateSystemNode>

#include <string>
#include <sstream>
#include <osg/io_utils>

namespace mdraw
{
	
	std::string indent(int num) {
		std::string s;
		for (int i = 0; i < num; i++) s += "  ";
		return s;
	}
		
	void printDrawable(const osg::Drawable* drawable, const int indentlevel, std::ostream& outs) {
		outs << indent(indentlevel) << drawable->libraryName() << "::" << drawable->className();
		if (drawable->getName().length() > 0)
			outs << " '" << drawable->getName() << "'";
		if (drawable->getShape())
			outs << " shape " << drawable->getShape()->className();
		const osg::Geometry* geo = drawable->asGeometry();
		if (geo) {
			if (geo->getVertexArray())
				outs << " " << geo->getVertexArray()->getNumElements() << " vertices";
		}
		outs << "\n";
	}
	
        void printNode(const osg::Node* node, const int verbosity, const int indentlevel, std::ostream& outs, const std::string& prepend) {
		if (!node)
			return;
		outs << indent(indentlevel) << prepend << node->libraryName() << "::" << node->className();
		if (node->getName().length() > 0)
			outs << " '" << node->getName() << "'";
		outs << "\n";
		for (unsigned int i = 0; i < node->getNumDescriptions(); i++) {
			outs << indent(indentlevel+1) << "description #" << i << ": " << node->getDescription(i) << "\n";
		}
                if (verbosity > 0) {
                    const osg::CoordinateSystemNode *csNode = dynamic_cast<const osg::CoordinateSystemNode*> (node);
                    if (csNode) {
                        outs << indent(indentlevel+1) << "format " << csNode->getFormat() << "\n";
                        outs << indent(indentlevel+1) << "system " << csNode->getCoordinateSystem() << "\n";
                    }
                }
                if (node->asGroup()) {
			const osg::Switch *sw = dynamic_cast<const osg::Switch*> (node);
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++) {
				std::string swprepend = "";
				if (sw && !sw->getChildValue(node->asGroup()->getChild(i)))
					swprepend = "(off) ";
                                printNode(node->asGroup()->getChild(i), verbosity, indentlevel+1, outs, swprepend);
			}
		}
		const osg::Geode* geode = dynamic_cast<const osg::Geode*> (node);
		if (geode) {
			for (unsigned int i = 0; i < geode->getNumDrawables(); i++)
				printDrawable(geode->getDrawable(i),indentlevel+1,outs);
		}
	}
	
        std::string getNodeString(const osg::Node* node, const int verbosity, const int indentlevel) {
		if (!node)
			return "";
		std::stringstream ss;
                printNode(node, verbosity, indentlevel, ss);
		return ss.str();
	}
	
	void setDebugDrawMode(osg::Node* node, const DebugDrawMode mode) {
		if (!node)
			return;
		osg::StateSet* ss = node->getOrCreateStateSet();
		if (mode == NORMAL) {
			ss->setMode(GL_BLEND,osg::StateAttribute::OFF);
			osg::PolygonMode *pm = new osg::PolygonMode;
			ss->setAttributeAndModes( pm ) ;
			ss->setMode(GL_LIGHTING,osg::StateAttribute::ON);
		} else if (mode == TRANSPARENT) {
			osg::BlendFunc *bf = new osg::BlendFunc();
			bf->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
			ss->setAttributeAndModes(bf,osg::StateAttribute::OFF);
			ss->setMode(GL_BLEND,osg::StateAttribute::ON);
			ss->setRenderBinDetails(20,"DepthSortedBin");
		} else if (mode == WIREFRAME) {
			osg::PolygonMode *pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE) ;
			ss->setAttributeAndModes( pm ) ;
			ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		} else if (mode == THICK_WIREFRAME) {
			osg::PolygonMode *pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE) ;
			ss->setAttributeAndModes( pm ) ;
			osg::LineWidth *lw = new osg::LineWidth(3.f) ;
			ss->setAttribute( lw ) ; 
			ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		}
	}
	
	osg::Node* getBoundingSphereNode(const osg::Node* node, const DebugDrawMode mode, const double scale, const osg::Vec4& color) {
		if (!node)
			return NULL;
		const osg::BoundingSphere& bsphere = node->getBound();
		osg::Sphere* sphere = new osg::Sphere(bsphere.center(),bsphere.radius()*scale);
		osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(sphere);
		shapedraw->setColor(color);
		osg::Geode* geode = new osg::Geode;
		geode->addDrawable(shapedraw);
		setDebugDrawMode(geode,mode);
		return geode;
	}
	
	osg::Node* getBoundingBoxNode(const osg::Node* node, const DebugDrawMode mode, const double scale, const osg::Vec4& color) {
		if (!node)
			return NULL;
		osg::BoundingBox bbox = getBoundingBox(node);
		if (bbox.radius() <= 0)
			return NULL;
		osg::Box* box = new osg::Box(bbox.center(),(bbox.xMax()-bbox.xMin())*scale,(bbox.yMax()-bbox.yMin())*scale,(bbox.zMax()-bbox.zMin())*scale);
		osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(box);
		shapedraw->setColor(color);
		osg::Geode* geode = new osg::Geode;
		geode->addDrawable(shapedraw);
		setDebugDrawMode(geode,mode);
		return geode;
	}
	
	/// Expand a bounding box by a node graph (handles groups and transforms)
	void expandBoundingBox(osg::BoundingBox& bbox, const osg::Node* node) {
		if (!node)
			return;
		if (node->asTransform()) {
			if (node->asTransform()->asMatrixTransform()) {
				// Rotate and translate bounding box according to transform and continue traversing
				osg::Matrix M = node->asTransform()->asMatrixTransform()->getMatrix();
				osg::BoundingBox tempbox;
				tempbox.set(osg::Vec3(0,0,0), osg::Vec3(0,0,0));
				for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
					expandBoundingBox(tempbox,node->asGroup()->getChild(i));
				osg::Vec3 scale = M.getScale();
				osg::Vec3 min(scale.x()*tempbox.xMin(),scale.y()*tempbox.yMin(),scale.z()*tempbox.zMin());
				osg::Vec3 max(scale.x()*tempbox.xMax(),scale.y()*tempbox.yMax(),scale.z()*tempbox.zMax());
				min = M.getRotate()*min;
				max = M.getRotate()*max;
				osg::Vec3 lengths(fabs(max.x()-min.x()),fabs(max.y()-min.y()),fabs(max.z()-min.z()));
				osg::Vec3 center(scale.x()*tempbox.center().x(), scale.y()*tempbox.center().y(), scale.z()*tempbox.center().z());
				center = M.getRotate()*center + M.getTrans();
				tempbox.set(center-lengths/2.0,center+lengths/2.0);
				bbox.expandBy(tempbox);
			} else 
				bbox.expandBy(node->getBound());
			return;
		}
		const osg::Geode* geode = dynamic_cast<const osg::Geode*> (node);
		if (geode)
			bbox.expandBy(geode->getBoundingBox());
		else if (node->asGroup()) {
			// Expand by child nodes
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
				expandBoundingBox(bbox,node->asGroup()->getChild(i));
		}
	}
	
	osg::BoundingBox getBoundingBox(const osg::Node* node) {
		osg::BoundingBox bbox;
		bbox.set(osg::Vec3(0,0,0), osg::Vec3(0,0,0));
		expandBoundingBox(bbox,node);
		return bbox;
	}
	
	osg::Node* getBoundingBoxGraph(const osg::Node* node, const DebugDrawMode mode, const double scale, const osg::Vec4& color) {
		if (!node)
			return NULL;
		if (node->asTransform() && node->asTransform()->asMatrixTransform()) {
			osg::MatrixTransform* xform = new osg::MatrixTransform;
			xform->setMatrix(node->asTransform()->asMatrixTransform()->getMatrix());
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
				xform->addChild(getBoundingBoxGraph(node->asGroup()->getChild(i),mode,scale,color));
			return xform;
		} else if (node->asGroup()) {
			osg::Group* group = new osg::Group;
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
				group->addChild(getBoundingBoxGraph(node->asGroup()->getChild(i),mode,scale,color));
			return group;
		} else
			return getBoundingBoxNode(node,mode,scale,color);
	}

	/// \return Euler angles (heading, pitch, roll)
	osg::Vec3 getEulerAnglesFromQuat(const osg::Quat& q)
	{
		double heading, pitch, roll;
		double test = q.y()*q.z() + q.x()*q.w();
                if (test-0.5 > -1e-8) { // singularity at north pole
			heading = -2 * atan2(q.y(),q.w());
			pitch = M_PI/2;
			roll = 0;
                } else if (test+0.5 < 1e-8) { // singularity at south pole
			heading = 2 * atan2(q.y(),q.w());
			pitch = -M_PI/2;
			roll = 0;
		} else {	
			heading = -atan2(2*q.z()*q.w()-2*q.y()*q.x() , 1 - 2*q.z()*q.z() - 2*q.x()*q.x());
			pitch = asin(2*test);
			roll = atan2(2*q.y()*q.w()-2*q.z()*q.x() , 1 - 2*q.y()*q.y() - 2*q.x()*q.x());
		}
		if (heading < 0)
			heading += M_PI*2.0;
		return osg::Vec3(heading, pitch, roll);
	}
	
	/// \param angles Euler angles (heading, pitch, roll)
	osg::Quat getQuatFromEulerAngles(const osg::Vec3& angles)
	{
		osg::Quat R =
	    osg::Quat(angles.z(),osg::Vec3(0.0,1.0,0.0))*
    	osg::Quat(angles.y(),osg::Vec3(1.0,0.0,0.0))*
    	osg::Quat(-angles.x(),osg::Vec3(0.0,0.0,1.0));
		return R;
	}
	
} // namespace
