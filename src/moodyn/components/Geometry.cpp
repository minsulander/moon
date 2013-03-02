#include "Geometry.h"
#include "Body.h"
#include "moodyn/World.h"
#include "moodyn/ode_osg.h"
#include <mlog/Log.h>
#include <moon/XMLParser.h>
#include <moon/ObjectFactory.h>
#include <moon/objects/TransformObject.h>
#include <mdraw/utils.h>
#include <mdraw/QuadGrid.h>
#include <mdraw/FollowCameraUpdateCallback.h>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/TriangleFunctor>
#include <osg/PolygonMode>
#include <osg/LightModel>
#include <osgDB/ReadFile>
#include <osg/io_utils>
#include <algorithm>

#ifdef _MSC_VER
#	pragma warning(disable:4800)
#endif

using namespace moon;
using namespace mlog;

namespace moodyn {
	
	REGISTER_Object_Alias(moodyn, Geometry, Geometry);
	
	osg::TessellationHints *Geometry::default_hints = NULL;
	const osg::Vec4 Geometry::default_color(1.0,1.0,1.0,0.5);
	const osg::Vec4 Geometry::disabled_color(0.4,0.4,0.8,0.5);
	const osg::Vec4 Geometry::static_color(0.4,0.8,0.4,0.5);
	
	/// Callback that changes color of geometry debug node depending on body enabled/disabled state and owner object health
	class GeometryDebugNodeCallback : public osg::NodeCallback {
	public:
		GeometryDebugNodeCallback(Geometry* geo, osg::ShapeDrawable* sd) : 
		osg::NodeCallback(),
		geometry(geo),
		shapedraw(sd),
		geostate(0),
		lastm(0.f),
		lastRealized(true) {}
		
		virtual void operator() (osg::Node *node, osg::NodeVisitor *nv) {
			if (!node)
				return;
			if (nv->getVisitorType() != osg::NodeVisitor::UPDATE_VISITOR || !nv->getFrameStamp())
				return;
			if (!geometry.valid())
				return;
			float m = geometry->getColorMultiplier();
			Body *body = geometry->getBody();
			if ((!body || !body->isRealized()) && (geostate != 0 || m != lastm)) { // static
				shapedraw->setColor(Geometry::static_color+osg::Vec4(0.5f*m,0,-m,0));
				geostate = 0; // static
				shapedraw->dirtyDisplayList();
			} else if (body && body->isEnabled() && (geostate != 1 || m != lastm)) { // enabled body
				shapedraw->setColor(Geometry::default_color+osg::Vec4(0.5f*m,-m,-m,0));
				geostate = 1; // enabled
				shapedraw->dirtyDisplayList();
			} else if (body && !body->isEnabled() && (geostate != 2 || m != lastm)) { // disabled body
				shapedraw->setColor(Geometry::disabled_color+osg::Vec4(0.5f*m,-m,-0.5f*m,0));
				shapedraw->dirtyDisplayList();
				geostate = 2; // disabled
			}
			if (!geometry->isRealized() && lastRealized)
				mdraw::setDebugDrawMode(node, mdraw::TRANSPARENT);
			else if (geometry->isRealized() && !lastRealized)
				mdraw::setDebugDrawMode(node, mdraw::NORMAL);
			lastRealized = geometry->isRealized();
			lastm = m;
		}
		
	protected:
		osg::observer_ptr<Geometry> geometry;
		osg::ShapeDrawable* shapedraw;
		int geostate;
		float lastm;
		bool lastRealized;
	};
	
	Geometry::Geometry()
	:	moon::Component(),
		materialID(0),
		contactConnected(true),
		feedback(false),
		needMesh(false),
		colorMultiplier(0.f),
		userdata(NULL)
	{
		space = World::instance().getDefaultSpace();
	}
	
	Geometry::Geometry(const Geometry& geo, const osg::CopyOp copyop)
	:	moon::Component(geo, copyop),
		space(geo.space),
		shapes(geo.shapes),
		materialID(geo.materialID),
		contactConnected(geo.contactConnected),
		feedback(false),
		needMesh(geo.needMesh),
		colorMultiplier(geo.colorMultiplier),
		userdata(NULL)
	{
	}
	
	void Geometry::parseXML(const TiXmlElement *element)
	{
		Component::parseXML(element);
		//=== Geometry
		//=* attribute: pos="(vector3)" [m] (default 0,0,0) att="(vector3)" [degrees] (default 0,0,0)
		//=. Offset position and attitude in Euler angles (heading, pitch, roll)
		
		//=* attribute: cc="true|false" (default true)
		//=. Specifies wether contact should be made with bodies connected to this object through a joint
		XMLParser::parseBooleanAttribute(contactConnected, element, "cc");
		
		//=* attribute: material="(name)"
		std::string material;
		if (XMLParser::parseStringAttribute(material, element, "material")) {
			materialID = World::instance().getMaterialID(material);
			if (materialID < 0) {
				materialID = 0;
				dout(WARN) << "Material " << material << " has not been specified in contacts section\n";
			} else
				dout(4) << "    material " << material << "\n";
		}
		
		//Physics geometry specification.
		for (const TiXmlElement* el = element->FirstChildElement(); el; el=el->NextSiblingElement()) {
			dout(4) << "    ";
			Shape shape;
			
			osg::Matrix M;
			osg::Vec3 pos = XMLParser::parseVector3String(XMLParser::parseStringAttribute(el,"pos",true,"0,0,0"));
			osg::Vec3 att = XMLParser::parseVector3String(XMLParser::parseStringAttribute(el,"att",true,"0,0,0"));
			att *= M_PI/180.0;
			M.setRotate(moon::TransformObject::getMatrixFromEulerAngles(att).getRotate());			
			M.setTrans(pos);
			shape.M = M;
			
			// Add geoms
			if (el->Value() == std::string("mesh")) {
				//=* repeatable element: mesh model="(filename)"
				shape.type = MESH;
				std::string model;
				if (XMLParser::parseStringAttribute(model, el, "model")) {
					osg::Node *node = osgDB::readNodeFile(model);
					if (node) {
						dout(4) << "mesh model='" << model << "'\n";
						addMesh(node, M);
					} else
						dout(ERROR) << "Failed to load mesh model '" << model << "'\n";
				} else
					needMesh = true;
			} else if (el->Value() == std::string("heightfield")) {
				//=* repeatable element: heightfield model="(filename)"
				std::string str;
				if (XMLParser::parseStringAttribute(str, el,"model")) {
					osg::Node *node = osgDB::readNodeFile(str);
					osg::Geode *geode = NULL;
					osg::ShapeDrawable *sd = NULL;
					osg::HeightField *hf = NULL;
					geode = dynamic_cast<osg::Geode*> (node);
					if (geode)
						sd = dynamic_cast<osg::ShapeDrawable*> (geode->getDrawable(0));
					if (sd)
						hf = dynamic_cast<osg::HeightField*> (sd->getShape());
					if (hf) {
						dout(4) << "heightfield model='" << str << "'\n";
						addHeightField(hf, M);
					} else
						dout(ERROR) << "Failed to load height field from model '" << str << "'\n";
				} else if (XMLParser::parseStringAttribute(str, el, "image")) {
					osg::Image *img = osgDB::readImageFile(str);
					if (img) {
						float vscale = XMLParser::parseDoubleAttribute(el, "vscale");
						float hscale = XMLParser::parseDoubleAttribute(el, "hscale");
						dout(4) << "heightfield image='" << str << "'\n";
						addHeightField(img, vscale, hscale, M);
					} else
						dout(ERROR) << "Failed to load height field from image '" << str << "'\n";
				} else if (XMLParser::parseStringAttribute(str, el, "file")) {
					osg::HeightField *hf = osgDB::readHeightFieldFile(str);
					if (hf) {
						dout(4) << "heightfield file=)'" << str << "'\n";
						addHeightField(hf, M);
					} else
						dout(ERROR) << "Failed to load height field from file '" << str << "'\n";
				}
			} else {
				if (el->Value() == std::string("box")) {
					//=* repeatable element: box sides="(vector3)" [m]
					shape.type = BOX;
					osg::Vec3 sides = XMLParser::parseVector3Attribute(el,"sides");
					shape.p1 = sides.x();
					shape.p2 = sides.y();
					shape.p3 = sides.z();
					dout(4) << "box sides=" << shape.p1 << "," << shape.p2 << "," << shape.p3;
				} else if (el->Value() == std::string("sphere")) {
					//=* repeatable element: sphere radius="(number)" [m]
					shape.type = SPHERE;
					shape.p1 = XMLParser::parseDoubleAttribute(el,"radius");
					dout(4) << "sphere radius=" << shape.p1;
				} else if (el->Value() == std::string("capsule")) {
					//=* repeatable element: capsule radius="(number)" length="(number)" [m]
					shape.type = CAPSULE;
					shape.p1 = XMLParser::parseDoubleAttribute(el,"radius");
					shape.p2 = XMLParser::parseDoubleAttribute(el,"length");
					dout(4) << "capsule radius=" << shape.p1 << " length=" << shape.p2;
				} else if (el->Value() == std::string("cylinder")) {
					//=* repeatable element: cylinder radius="(number)" length="(number)" [m]
					shape.type = CYLINDER;
					shape.p1 = XMLParser::parseDoubleAttribute(el,"radius");
					shape.p2 = XMLParser::parseDoubleAttribute(el,"length");
					dout(4) << "cylinder radius=" << shape.p1 << " length=" << shape.p2;
				} else if (el->Value() == std::string("plane")) {
					//=* repeatable element: plane normal="(vector3)" offset="(number)" [m]
					//=. Normal vector the the plane, and position of the plane along its normal.
					shape.type = PLANE;
					osg::Vec3 normal = XMLParser::parseVector3Attribute(el,"normal");
					double offset = XMLParser::parseDoubleAttribute(el,"offset",true,0);
					shape.p1 = normal.x(); shape.p2 = normal.y(); shape.p3 = normal.z(); shape.p4 = offset;
					dout(4) << "plane normal=" << normal.x() << "," << normal.y() << "," << normal.z() << " offset=" << offset;
				}
				if (pos.length() > 0)
					dout(4) << " at " << pos.x() << "," << pos.y() << "," << pos.z();
				dout(4) << "\n";
				
				shapes.push_back(shape);
			}
		}
	}
	
	void Geometry::writeXML(TiXmlElement *element) const
	{
		Component::writeXML(element);
		for (std::vector<Shape>::const_iterator it = shapes.begin(); it != shapes.end(); it++) {
			const Shape& shape = *it;
			TiXmlElement *shapeElement = NULL;
			switch (shape.type) {
				case BOX: {
					shapeElement = new TiXmlElement("box");
					std::stringstream ss;
					ss << shape.p1 << ", " << shape.p2 << ", " << shape.p3;
					shapeElement->SetAttribute("sides", ss.str());
					break;
				}
				case SPHERE: {
					shapeElement = new TiXmlElement("sphere");
					shapeElement->SetDoubleAttribute("radius", shape.p1);
					break;
				}
				case CAPSULE: {
					shapeElement = new TiXmlElement("capsule");
					shapeElement->SetDoubleAttribute("radius", shape.p1);
					shapeElement->SetDoubleAttribute("length", shape.p2);
					break;
				}
				case CYLINDER: {
					shapeElement = new TiXmlElement("cylinder");
					shapeElement->SetDoubleAttribute("radius", shape.p1);
					shapeElement->SetDoubleAttribute("length", shape.p2);
					break;
				}
				case PLANE: {
					shapeElement = new TiXmlElement("plane");
					std::stringstream ss;
					ss << shape.p1 << ", " << shape.p2 << ", " << shape.p3;
					shapeElement->SetAttribute("normal", ss.str());
					if (shape.p4 > 0)
						shapeElement->SetDoubleAttribute("offset", shape.p4);
					break;
				}
				case MESH: {
					if (needMesh)
						shapeElement = new TiXmlElement("mesh");
					else
						dout(ERROR) << "Mesh from model file not supported for XML write\n";
				}
				default:
					dout(WARN) << "Shape type " << shape.type << " unsupported for XML write\n";
					
			}
			if (shapeElement) {
				if (shape.M != osg::Matrix::identity()) {
					std::stringstream ss;
					osg::Vec3 pos = shape.M.getTrans();
					if (pos.length() > 1e-5) {
						ss << pos.x() << ", " << pos.y() << ", " << pos.z();
						shapeElement->SetAttribute("pos", ss.str());
					}
					osg::Vec3 att = moon::TransformObject::getEulerAnglesFromMatrix(shape.M) * 180.0/M_PI;
					if (att.length() > 1e-5) {
						ss.str("");
						ss << att.x() << ", " << att.y() << ", " << att.z();
						shapeElement->SetAttribute("att", ss.str());
					}
				}
				element->LinkEndChild(shapeElement);
			}
		}
	}
	
	void Geometry::setBody(Body *newbody, const osg::Matrix& offset)
	{
		body = newbody;
		bodyOffsetM = offset;
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		if (body.valid()) {
			for (std::vector<dGeomID>::iterator it = geoms.begin(); it != geoms.end(); it++) {
				dGeomSetBody(*it, body->id());
			}
		} else {
			for (std::vector<dGeomID>::iterator it = geoms.begin(); it != geoms.end(); it++) {
				dGeomSetBody(*it, 0);
			}
		}
	}
	
	Body* Geometry::getBody()
	{
		return body.get();
	}
	
	void Geometry::addShape(const Shape& shape)
	{
		shapes.push_back(shape);
	}
	
	void Geometry::addShape(const ShapeType type, const double p1, const double p2, const double p3, const double p4, const osg::Matrix& M)
	{
		addShape(Shape(type,p1,p2,p3,p4,M));
	}
	
	void Geometry::addMesh(osg::Node *node, const osg::Matrix& M)
	{
		if (!node)
			return;
		Shape shape;
		shape.type = MESH;
		shape.M = M;
		shape.mesh_id = buildTriMesh(node);
		shape.mesh_node = buildTriMeshDebugNode(node);
		//shape.mesh_node = node;
		shapes.push_back(shape);
	}
	
	void Geometry::addHeightField(osg::HeightField *grid, const osg::Matrix& M)
	{
		if (!grid)
			return;
		Shape shape;
		shape.type = HEIGHTFIELD;
		shape.M = M;
		shape.heightfield_id = buildHeightField(grid);
		shape.heightfield = grid;

		// Rotate coordinate system and center it
		osg::Quat rot;
		rot.makeRotate(osg::Vec3(0,1,0),osg::Vec3(0,0,1));
		shape.M.setRotate(rot);
		unsigned int cols = grid->getNumColumns();
		unsigned int rows = grid->getNumRows();
		float xi = grid->getXInterval();
		float yi = grid->getYInterval();
		shape.M.setTrans(osg::Vec3(xi*cols/2.f,yi*rows/2.f,0));
		shape.M = M * shape.M;
		
		shapes.push_back(shape);
	}
	
	void Geometry::addHeightField(osg::Image *img, const float vscale, const float hscale, const osg::Matrix& M)
	{
		if (!img)
			return;
		Shape shape;
		shape.type = HEIGHTFIELD;
		shape.M = M;
		unsigned int cols = 0;
		shape.heightfield_id = buildHeightField(img, vscale, hscale, cols);
		shape.heightfield = NULL;
		
		// Rotate coordinate system and center it
		osg::Quat rot;
		rot.makeRotate(osg::Vec3(0,1,0),osg::Vec3(0,0,1));
		shape.M.setRotate(rot);
		shape.M.setTrans(osg::Vec3(hscale*cols/2.f,hscale*cols/2.f,0));
		shape.M = M * shape.M;
		
		shapes.push_back(shape);
	}
	
	void Geometry::merge(const Geometry *other, const osg::Matrix& M)
	{
		for (unsigned int i = 0; i < other->getNumShapes(); i++) {
			Shape shape = other->getShape(i);
			shape.M = shape.M * M;
			addShape(shape);
		}
	}
	
	const Geometry::Shape& Geometry::getShape(unsigned int index) const
	{
		return shapes[index];
	}
	
	void Geometry::removeShape(unsigned int index)
	{
		if (index < 0 || index >= shapes.size())
			return;
		shapes.erase(shapes.begin()+index);
	}
	
	unsigned int Geometry::getNumShapes() const { return shapes.size(); }
	
	void Geometry::setTransformation(const osg::Matrix& M) {
		if (body.valid()) {
			body->setTransformation(M);
			return;
		}
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		osg::Vec3 pos = M.getTrans();
		osg::Quat rot = M.getRotate();
		dQuaternion q; q[0] = rot.w(); q[1] = rot.x(); q[2] = rot.y(); q[3] = rot.z();
		for (std::vector<dGeomID>::iterator i = geoms.begin(); i != geoms.end(); i++) {
			if (dGeomGetClass(*i) == dPlaneClass) {
				int idx=i-geoms.begin();
				osg::Vec3 normal (shapes[idx].p1,shapes[idx].p2,shapes[idx].p3);
				shapes[idx].p4 = normal*pos;
				dGeomPlaneSetParams(*i,normal.x(),normal.y(),normal.z(),normal*pos);
				continue;
			}
			dGeomSetPosition(*i,pos.x(),pos.y(),pos.z());
			dGeomSetQuaternion(*i,q);
		}
	}
	
	osg::Matrix Geometry::getTransformation() const
	{
		if (geoms.size() == 0)
			return osg::Matrix::identity();
		// Check if geom is placeable - really whish there was an ODE function for this
		if (dGeomGetClass(geoms[0]) == dPlaneClass)
			return osg::Matrix::identity();
		osg::Matrix M = osg::Matrix::identity();
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		const dReal* p = dGeomGetPosition(geoms[0]);
		dQuaternion q;
		dGeomGetQuaternion(geoms[0], q);
		M.setRotate(osg::Quat(q[1],q[2],q[3],q[0]));
		M.setTrans(osg::Vec3(p[0],p[1],p[2]));
		return M;
	}
	
	dGeomID Geometry::id(const unsigned int shapeno) {
		if (shapeno >= geoms.size())
			return geoms[shapeno];
		return 0;
	}
	
	osg::Vec3 Geometry::getPosition(const unsigned int shapeno) {
		if (shapeno >= geoms.size())
			return osg::Vec3(0,0,0);
		// Check if geom is placeable - really whish there was an ODE function for this
		if (dGeomGetClass(geoms[shapeno]) == dPlaneClass)
			return osg::Vec3(0,0,0);
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		const dReal *p = dGeomGetPosition(geoms[shapeno]);
		return osg::Vec3(p[0], p[1], p[2]);
	}
	
	void Geometry::transform(const osg::Matrix& M) {
		for (unsigned int i = 0; i < shapes.size(); i++)
			shapes[i].M = M * shapes[i].M;
	}
	
	bool Geometry::isEnabled() const {
		if (geoms.size() == 0)
			return false;
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		// Assume that we have total control - if one is enabled/disabled that goes for the rest...
		return dGeomIsEnabled(geoms[0]);
	}
	
	void Geometry::enable() {
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		for (unsigned int i = 0; i < geoms.size(); i++)
			dGeomEnable(geoms[i]);
	}
	
	void Geometry::disable() {
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		for (unsigned int i = 0; i < geoms.size(); i++)
			dGeomDisable(geoms[i]);
	}
	
	/// \see BaseObject::realize(), Scenario::realize()
	void Geometry::realize()
	{
		if (geoms.size() > 0)
			unrealize();
		for (std::vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); it++) {
			dGeomID g = createGeom(*it);
			if (!g)
				continue;
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
			if (body.valid() && body->id())
				dGeomSetBody(g, body->id());
			geoms.push_back(g);
		}
		Component::realize();
	}
	
	/// \see BaseObject::unrealize(), Scenario::unrealize()
	void Geometry::unrealize()
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		for (std::vector<dGeomID>::iterator it = geoms.begin(); it != geoms.end(); it++) {
			dGeomDestroy(*it);
		}
		geoms.clear();
		Component::unrealize();
	}
	
	bool Geometry::isRealized() const
	{
		return (geoms.size() > 0 && geoms[0] != 0);
	}
	
	/// \param shapeno Shape index of this geometry to test (default 0)
	/// \param othershapeno Shape index of other geometry to test (default 0)
	/// \return True if the geoms are in contact
	bool Geometry::checkContact(const Geometry *other, const unsigned int shapeno, const unsigned int othershapeno) const
	{
		//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		if (shapeno >= geoms.size() || othershapeno >= other->geoms.size())
			return false;
		dContact contact;
		int num = dCollide(geoms[shapeno], other->geoms[othershapeno], 1, &contact.geom, sizeof(dContact));
		return (num == 1);
	}

	osg::Node* Geometry::createDebugNode() {
		if (shapes.size() == 0)
			return NULL;
		osg::Geode* geode = new osg::Geode;
		osg::CompositeShape* cshape = new osg::CompositeShape;
		osg::ShapeDrawable* shapedraw = new osg::ShapeDrawable(cshape,default_hints);
		osg::Vec4 color = default_color;
		if (!body)
			color = static_color;
		shapedraw->setColor(color);
		geode->addDrawable(shapedraw);
		geode->setUpdateCallback(new GeometryDebugNodeCallback(this,shapedraw));
		osg::Group *meshgroup = NULL;
		for (std::vector<Shape>::const_iterator i = shapes.begin(); i != shapes.end(); i++) {
			const Shape& shape = *i;
			if (shape.type == BOX) {
				osg::Box* box = new osg::Box(shape.M.getTrans(),shape.p1,shape.p2,shape.p3);
				box->setRotation(shape.M.getRotate());
				cshape->addChild(box);
			} else if (shape.type == SPHERE) {
				osg::Sphere* sphere = new osg::Sphere(shape.M.getTrans(),shape.p1);
				cshape->addChild(sphere);
			} else if (shape.type == CAPSULE) {
				osg::Capsule* capsule = new osg::Capsule(shape.M.getTrans(),shape.p1,shape.p2);
				capsule->setRotation(shape.M.getRotate());
				cshape->addChild(capsule);
			} else if (shape.type == CYLINDER) {
				osg::Cylinder* cylinder = new osg::Cylinder(shape.M.getTrans(),shape.p1,shape.p2);
				cylinder->setRotation(shape.M.getRotate());
				cshape->addChild(cylinder);
			} else if (shape.type == PLANE) {
				geode->addDrawable(new mdraw::QuadGrid(osg::Vec4(shape.p1,shape.p2,shape.p3,0),100,10));
				geode->setUpdateCallback(NULL);
				geode->removeDrawable(shapedraw);
				osg::MatrixTransform *transform = new osg::MatrixTransform;
				transform->addChild(geode);
				mdraw::FollowCameraUpdateCallback *follow = new mdraw::FollowCameraUpdateCallback();
				follow->setStep(20);
				follow->setDirection(osg::Vec3(1,1,1)-osg::Vec3(shape.p1,shape.p2,shape.p3));
				transform->setCullCallback(follow);
				return transform;
			} else if (shape.type == MESH) {
				if (!meshgroup) {
					meshgroup = new osg::Group;
					osg::StateSet* state = meshgroup->getOrCreateStateSet(); 
					osg::LightModel *lightm = new osg::LightModel;
					lightm->setAmbientIntensity(osg::Vec4(0.5f,0.5f,0.5f,1.0f));
					state->setAttribute(lightm);
					/*
					osg::PolygonMode* pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE ); 
					state->setAttributeAndModes( pm, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE ); 
					 */
				}
				if (shape.M != osg::Matrix::identity()) {
					osg::MatrixTransform *xform = new osg::MatrixTransform;
					xform->setMatrix(shape.M);
					xform->addChild(shape.mesh_node.get());
					meshgroup->addChild(xform);
				} else 
					meshgroup->addChild(shape.mesh_node.get());
			} else if (shape.type == HEIGHTFIELD) {
				if (shape.heightfield.valid()) {
					cshape->addChild(shape.heightfield.get());
					osg::StateSet* state = geode->getOrCreateStateSet(); 
					osg::PolygonMode* pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE ); 
					state->setAttributeAndModes( pm, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE ); 
				}
			} else {
				dout(ERROR) << "No debug node implemented for geometry type " << shape.type << "\n";
			}		
		}
		if (meshgroup) {
			if (cshape->getNumChildren() > 0) {
				osg::Group *group = new osg::Group;
				group->addChild(meshgroup);
				group->addChild(geode);
				return group;
			}
			return meshgroup;
		} else
			return geode;
	}
	
	// internal utility function
	/// \todo Move
	double max3(const double v1, const double v2, const double v3) {
		double v;
		v = v1;
		if (v2 > v)
			v = v2;
		if (v3 > v)
			v = v3;
		return v;
	}
	
	void Geometry::addBoundingSphere(const osg::BoundingSphere& bsphere, const osg::Matrix& M) {
		Shape shape;
		shape.type = SPHERE;
		shape.M = osg::Matrix::translate(bsphere.center()) * M;
		shape.p1 = bsphere.radius();
		if (shape.p1 < 0.01)
			dout(WARN) << "Bounding sphere radius close to zero - ignored\n";
		else
			addShape(shape);
	}

	void Geometry::addBoundingBox(const osg::BoundingBox& bbox, const osg::Matrix& M) {
		Shape shape;
		shape.type = BOX;
		shape.M = osg::Matrix::translate(bbox.center()) * M;
		shape.p1 = bbox.xMax()-bbox.xMin();
		if (shape.p1 < 0.01) {
			dout(WARN) << "Bounding box x thickness close to zero - set to 0.01\n";
			shape.p1 = 0.01;
		}
		shape.p2 = bbox.yMax()-bbox.yMin();
		if (shape.p2 < 0.01) {
			dout(WARN) << "Bounding box y thickness close to zero - set to 0.01\n";
			shape.p2 = 0.01;
		}
		shape.p3 = bbox.zMax()-bbox.zMin();
		if (shape.p3 < 0.01) {
			dout(WARN) << "Bounding box z thickness close to zero - set to 0.01\n";
			shape.p3 = 0.01;
		}
		addShape(shape);
	}
	
	void Geometry::addShapesFromBounds(osg::Node* node, const osg::Matrix& M) {
		if (!node)
			return;

		std::string name = node->getName();
		if (name.length() == 0 && node->getNumParents() > 0)
			name = node->getParent(0)->getName();

		if (name.find(":nogeo") != std::string::npos) {
			return;
		}
		
		if (name.find(":mesh") != std::string::npos)
			addMesh(node, M);
		else if (node->asTransform() && node->asTransform()->asMatrixTransform()) {
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
				addShapesFromBounds(node->asGroup()->getChild(i),node->asTransform()->asMatrixTransform()->getMatrix() * M);
			return;
		} else if (node->asGroup()) {
			for (unsigned int i = 0; i < node->asGroup()->getNumChildren(); i++)
				addShapesFromBounds(node->asGroup()->getChild(i),M);
			return;
		} else {
			osg::Geode* geode = dynamic_cast<osg::Geode*> (node);
			if (!geode || name.find(":bsphere") != std::string::npos) {
				osg::BoundingSphere bsphere = node->getBound();
				addBoundingSphere(bsphere, M);
			} else if (name.find("sphere") != std::string::npos) {
				osg::BoundingBox bbox = geode->getBoundingBox();
				Shape shape;
				shape.type = SPHERE;
				shape.M = osg::Matrix::translate(bbox.center()) * M;
				shape.p1 = max3(bbox.xMax()-bbox.xMin(), bbox.yMax()-bbox.yMin(), shape.p3 = bbox.zMax()-bbox.zMin())/2.0;
				addShape(shape);
			} else if (name.find(":bbox") != std::string::npos) {
				// Use bounding box of entire geode
				osg::BoundingBox bbox = geode->getBoundingBox();
				// ... but shaped as a cylinder or capsule?
				bool cyl = name.find(":cylinder") != std::string::npos;
				bool caps = name.find(":capsule") != std::string::npos;
				if (cyl || caps) {
					Shape shape;
					if (cyl)
						shape.type = CYLINDER;
					else
						shape.type = CAPSULE;
					if (name.find(":x") != std::string::npos) {
						shape.M = osg::Matrix::rotate(osg::Vec3(0,0,1), osg::Vec3(1,0,0)) * osg::Matrix::translate(bbox.center()) * M;
						shape.p1 = std::max(bbox.yMax()-bbox.yMin(), bbox.zMax()-bbox.zMin())/2.0;
						shape.p2 = bbox.xMax()-bbox.xMin();
					} else if (name.find(":y") != std::string::npos) {
						shape.M = osg::Matrix::rotate(osg::Vec3(0,0,1), osg::Vec3(0,1,0)) * osg::Matrix::translate(bbox.center()) * M;
						shape.p1 = std::max(bbox.xMax()-bbox.xMin(), bbox.zMax()-bbox.zMin())/2.0;
						shape.p2 = bbox.yMax()-bbox.yMin();
					} else {
						shape.M = osg::Matrix::translate(bbox.center()) * M;
						shape.p1 = std::max(bbox.xMax()-bbox.xMin(), bbox.yMax()-bbox.yMin())/2.0;
						shape.p2 = bbox.zMax()-bbox.zMin();
					}
					addShape(shape);
				} else
					addBoundingBox(bbox,M);
			} else {
				// Traverse drawables
				for (unsigned int i = 0; i < geode->getNumDrawables(); i++) {
					osg::BoundingBox bbox = geode->getDrawable(i)->getBound();
					addBoundingBox(bbox,M);
				}
			}
		}
	}
	
	const osg::Vec3& Geometry::getContactForce()
	{
		if (!feedback) {
			feedback = true;
			contactF = osg::Vec3(0,0,0);
		}
		return contactF;
	}
	
	const osg::Vec3& Geometry::getContactTorque()
	{
		if (!feedback) {
			feedback = true;
			contactQ = osg::Vec3(0,0,0);
		}
		return contactQ;
	}
	
	Geometry::~Geometry()
	{
		unrealize();
	}
	
	
	dGeomID Geometry::createGeom(const Shape& shape) {
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(World::mutex);
		// Create the Geom in the ODE space
		dGeomID geom;
		switch(shape.type) {
			case BOX:
				geom = dCreateBox(space,shape.p1,shape.p2,shape.p3); // p1,p2,p3 = side of the box
				break;
			case SPHERE:
				geom = dCreateSphere(space,shape.p1); // p1 = radius of the sphere
				break;
			case CAPSULE:
				geom = dCreateCapsule(space,shape.p1,shape.p2); // p1 = radius, p2 = length
				break;
			case CYLINDER:
				geom = dCreateCylinder(space,shape.p1,shape.p2); // p1 = radius, p2 = length
				break;
			case PLANE:
				geom = dCreatePlane(space,shape.p1,shape.p2,shape.p3,shape.p4);
				break;
			case MESH:
				if (shape.mesh_id) {
					geom = dCreateTriMesh(space, shape.mesh_id, 0, 0, 0);
				} else {
					dout(ERROR) << "Cannot create mesh geometry for object with no mesh data\n";
					return 0;
				}
				break;
			case HEIGHTFIELD:
				if (shape.heightfield_id) {
					geom = dCreateHeightfield(space,shape.heightfield_id,1);
				} else {
					dout(ERROR) << "Cannot create heightfield for object with no height data\n";
					return 0;
				}
				break;
			default:
				dout(ERROR) << "No Geom defined for shape " << shape.type << "\n";
				return 0;
		}
		dGeomSetData(geom,(void*)this);
		// Make a transform geom if needed
		if (shape.M != osg::Matrix::identity() || bodyOffsetM != osg::Matrix::identity()) {
			dGeomID trans = dCreateGeomTransform(space);
			dGeomSetData(trans,(void*)this);
			dGeomTransformSetCleanup(trans,1);
			dGeomTransformSetGeom(trans,geom);
			dSpaceRemove(space,geom);
			// Set the original geom's position and rotation
			dMatrix3 r;
			odeMatrixFromOsg(bodyOffsetM * shape.M,r);
			dGeomSetRotation(geom,r);
			osg::Vec3 p = (bodyOffsetM * shape.M).getTrans();
			dGeomSetPosition(geom,p.x(),p.y(),p.z());
			// Set our new geom to the transform
			geom = trans;
		}
		return geom;
	}
	
	// DrawableVisitor and TriangleRecorder copied from Delta3D 2.0.0. Thanks Delta3D team!
	
	/**
	 * A visitor that determines the parameters associated
	 * with a node.
	 */
	template< class T >
	class DrawableVisitor : public osg::NodeVisitor {
	public:
		
		osg::TriangleFunctor<T> mFunctor;
		
		/**
		 * Constructor.
		 */
		DrawableVisitor()
		: osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
		{}
		
		/**
		 * Applies this visitor to a geode.
		 *
		 * @param node the geode to visit
		 */
		virtual void apply(osg::Geode& node)
		{
			for(unsigned int i=0;i<node.getNumDrawables();i++)
			{
				osg::Drawable* d = node.getDrawable(i);
				
				if(d->supports(mFunctor))
				{
					osg::NodePath nodePath = getNodePath();
					mFunctor.mMatrix = osg::computeLocalToWorld(nodePath);					
					d->accept(mFunctor);
				}
			}
		}
	};
	
	
	/**
	 * A strided vertex for the ODE triangle mesh collision geometry.
	 */
	struct StridedVertex {
		dVector3 Vertex;
	};
	
	/**
	 * A strided triangle for the ODE triangle mesh collision geometry.
	 */
	struct StridedTriangle {
		int Indices[3];
	};
	
	/**
	 * Records visited triangles into an array suitable for passing
	 * into ODE's triangle mesh collision detection class.
	 */
	class TriangleRecorder {
	public:
		
		std::vector<StridedVertex> mVertices;
		
		std::vector<StridedTriangle> mTriangles;
		
		osg::Matrix mMatrix;
		
		/**
		 * Called once for each visited triangle.
		 *
		 * @param v1 the triangle's first vertex
		 * @param v2 the triangle's second vertex
		 * @param v3 the triangle's third vertex
		 * @param treatVertexDataAsTemporary whether or not to treat the vertex data
		 * as temporary
		 */
		void operator()(const osg::Vec3& v1,
						const osg::Vec3& v2,
						const osg::Vec3& v3,
						bool treatVertexDataAsTemporary)
		{
			osg::Vec3 tv1 = v1*mMatrix,
			tv2 = v2*mMatrix,
			tv3 = v3*mMatrix;
			
			StridedVertex sv1, sv2, sv3;
			StridedTriangle t;
			
			t.Indices[0] = mVertices.size();
			t.Indices[1] = mVertices.size() + 1;
			t.Indices[2] = mVertices.size() + 2;
			
			mTriangles.push_back(t);
			
			sv1.Vertex[0] = tv1[0];
			sv1.Vertex[1] = tv1[1];
			sv1.Vertex[2] = tv1[2];
			
			sv2.Vertex[0] = tv2[0];
			sv2.Vertex[1] = tv2[1];
			sv2.Vertex[2] = tv2[2];
			
			sv3.Vertex[0] = tv3[0];
			sv3.Vertex[1] = tv3[1];
			sv3.Vertex[2] = tv3[2];
			
			mVertices.push_back(sv1);
			mVertices.push_back(sv2);
			mVertices.push_back(sv3);
		}
	};
	
	class DebugShapeTriangleRecorder {
	public:
		DebugShapeTriangleRecorder()
		{
			mVertices = new osg::Vec3Array;
			mIndices = new osg::UIntArray;
		}
		
		void operator()(const osg::Vec3& v1,
						const osg::Vec3& v2,
						const osg::Vec3& v3,
						bool treatVertexDataAsTemporary)
		{
			osg::Vec3 tv1 = v1*mMatrix,
			tv2 = v2*mMatrix,
			tv3 = v3*mMatrix;
			mVertices->push_back(osg::Vec3(tv1[0],tv1[1],tv1[2]));
			mIndices->push_back(mVertices->size());
			mVertices->push_back(osg::Vec3(tv2[0],tv2[1],tv2[2]));
			mIndices->push_back(mVertices->size());
			mVertices->push_back(osg::Vec3(tv3[0],tv3[1],tv3[2]));
			mIndices->push_back(mVertices->size());
		}
		
		osg::Vec3Array* mVertices;
		osg::UIntArray* mIndices;
		osg::Matrix mMatrix;
	};
	
	
	dTriMeshDataID Geometry::buildTriMesh(osg::Node *node)
	{
		if (!node)
			return 0;
		
		DrawableVisitor<TriangleRecorder> mv;	
		node->accept(mv);
		
		/*
		if(meshvertices != 0) {
			delete[] meshvertices;
			delete[] meshindices;
		}
		*/
		/// \todo do we need to keep references to these?
		dVector3 *meshvertices = new dVector3[mv.mFunctor.mVertices.size()];
		dTriIndex *meshindices = new dTriIndex[mv.mFunctor.mTriangles.size()*3];
		
		if( !mv.mFunctor.mVertices.empty() ) {
			memcpy(  meshvertices,
				   &mv.mFunctor.mVertices[0],
				   mv.mFunctor.mVertices.size()*sizeof(StridedVertex) );
		}
		
		if( !mv.mFunctor.mTriangles.empty() ) {
			memcpy(  meshindices,
				   &mv.mFunctor.mTriangles[0],
				   mv.mFunctor.mTriangles.size()*sizeof(StridedTriangle) );
		}
		
		dTriMeshDataID mesh_id = dGeomTriMeshDataCreate();
		
		dout(4) << "Building trimesh with " << mv.mFunctor.mTriangles.size() << " triangles\n";
		dGeomTriMeshDataBuildSimple(mesh_id,
									(dReal*)meshvertices,
									mv.mFunctor.mVertices.size(),
									meshindices,
									mv.mFunctor.mTriangles.size()*3);
		
		return mesh_id;
	}
	
	osg::Node* Geometry::buildTriMeshDebugNode(osg::Node *node)
	{
		if (!node)
			return NULL;
		DrawableVisitor<DebugShapeTriangleRecorder> dv;
		node->accept(dv);
		
		osg::Geometry *geometry = new osg::Geometry;
		geometry->setVertexArray(dv.mFunctor.mVertices);
		osg::Vec4Array *colors = new osg::Vec4Array;
		for (std::size_t i = 0; i < dv.mFunctor.mVertices->size()/3; i++)
			colors->push_back(osg::Vec4(0.5f, 1.f - (i % 100)/200.f, 1.f - (i % 100)/200.f, 1.f));
		geometry->setColorArray(colors);
		geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, dv.mFunctor.mVertices->size()));
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(geometry);
		return geode;
	}
	
	dHeightfieldDataID Geometry::buildHeightField(osg::HeightField* grid)
	{
		
		if (!grid) return false;
		unsigned int cols = grid->getNumColumns();
		unsigned int rows = grid->getNumRows();
		if (cols != rows) {
			dout(ERROR) << "Non-square height field\n";
			return false;
		}
		bool finite = true;
		float xi = grid->getXInterval();
		float yi = grid->getYInterval();
		float scale = 1.0;
		std::vector<dReal> dheights;
		dout(2) << "  HeightField cols=" << cols << " rows=" << rows << " xi=" << xi << " yi=" << grid->getYInterval() << "\n";
		osg::HeightField::HeightList heights = grid->getHeightList();
		for (unsigned int r = 0; r < grid->getNumRows(); r++) {
			for (unsigned int c = 0; c < grid->getNumColumns(); c++) {
				dheights.push_back(grid->getHeight(c,grid->getNumRows()-r-1)*scale);
			}
		}
		dout(2) << "  min " << *(min_element(dheights.begin(), dheights.end())) << " max " <<  *(max_element(dheights.begin(), dheights.end())) << "\n";
		// Build ODE heightfield
		dout(2) << "  building height field data\n";
		dHeightfieldDataID data = dGeomHeightfieldDataCreate();
		dGeomHeightfieldDataBuildSingle(data,&dheights[0],1,xi*cols,yi*rows,cols,rows,1,0,10,(int)(!finite));
		return data;
	}
	
	dHeightfieldDataID Geometry::buildHeightField(osg::Image *img, const float vscale, const float hscale, unsigned int& cols)
	{
		bool finite = true;
		if (!img) return false;
		dout(1) << "Geometry::buildHeightField(image)\n";
		dout(2) << "  size " << img->getImageSizeInBytes() << "\n";
		dout(2) << "  pixelformat " << img->getPixelFormat() << "\n";
		dout(2) << "  datatype " << img->getDataType() << "\n";
		dout(2) << "  pixelsize " << img->getPixelSizeInBits() << "\n";
		dout(2) << "  s " << img->s() << " t " << img->t() << "\n";
		dout(2) << "  r " << img->r() << "\n";
		std::vector<dReal> dheights;
		cols = img->s();
		for (unsigned int y = 0; y < cols; y++) {
			for (unsigned int x = 0; x < cols; x++) {
				osg::Vec4 color = img->getColor(x,y);
				dheights.push_back(color.r() * vscale);
			}
		}
		/*
		if (img->getPixelSizeInBits() == 8) {
			cols = ::sqrt(img->getImageSizeInBytes());
			for (unsigned char* u = img->data(); (u - img->data()) < img->getImageSizeInBytes(); u++) {
				dheights.push_back((dReal) *u * scale);
			}
		} else if (img->getPixelSizeInBits() == 16) {
			cols = ::sqrt(img->getImageSizeInBytes()/2);
			for (unsigned char* u = img->data(); (u - img->data()) < img->getImageSizeInBytes(); u += 2) {
				unsigned int* u2 = (unsigned int*) u;
				dheights.push_back((dReal) *u2 * scale);
			}
		} else if (img->getPixelSizeInBits() == 32) {
			cols = ::sqrt(img->getImageSizeInBytes()/4);
			for (unsigned char* u = img->data(); (u - img->data()) < img->getImageSizeInBytes(); u += 4) {
				float* f = (float*) u;
				dheights.push_back((dReal) *f * scale);
			}
		} else {
			dout(ERROR) << "Unsupported height field image format\n";
			cols = 0;
			return 0;
		}
		 */
		dout(2) << "  cols " << cols << "\n";
		dout(2) << "  min " << *(min_element(dheights.begin(), dheights.end())) << " max " <<  *(max_element(dheights.begin(), dheights.end())) << "\n";
		// Build ODE heightfield
		dout(2) << "  building height field data\n";
		dHeightfieldDataID data = dGeomHeightfieldDataCreate();
		dGeomHeightfieldDataBuildSingle(data,&dheights[0],1,hscale*cols,hscale*cols,cols,cols,1,0,10,(int)(!finite));
		return data;
	}
	
	dSpaceID Geometry::default_space = 0;
	
} // namespace
