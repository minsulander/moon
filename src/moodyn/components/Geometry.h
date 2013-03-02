#ifndef MOODYN_GEOMETRY_H
#define MOODYN_GEOMETRY_H

#include "Body.h"
#include <moon/components/Component.h>
#include <osg/Matrix>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <ode/ode.h>

namespace moodyn {
	
	/// \addtogroup dynamics
	/// @{
	
	class ContactCallback;
	class ContactFeedbackCallback;
	class NearCallback;

	/// \brief Wrapper encapsulating physical geometry
	/// \ingroup components
	class MOODYN_EXPORT Geometry : public moon::Component {
	public:

		static osg::TessellationHints *default_hints;
		static const osg::Vec4 default_color;
		static const osg::Vec4 disabled_color;
		static const osg::Vec4 static_color;
		
		enum ShapeType { NONE, BOX, SPHERE, CAPSULE, CYLINDER, PLANE, MESH, HEIGHTFIELD };
		/// A shape, or sub-geometry if you will, representing a basic shape as a component of the geometry
		struct Shape {
			Shape() : type(NONE), p1(0), p2(0), p3(0), p4(0), M(osg::Matrix::identity()), mesh_id(0), heightfield_id(0) {}
			Shape(const ShapeType ntype, const double np1, const double np2 = 0, 
						const double np3 = 0, const double np4 = 0, const osg::Matrix& nM = osg::Matrix::identity()) 
			: type(ntype), p1(np1), p2(np2), p3(np3), p4(np4), M(nM), mesh_id(0), heightfield_id(0) {}
			ShapeType type;
			double p1, p2, p3, p4;
			osg::Matrix M;
			dTriMeshDataID mesh_id;
			osg::ref_ptr<osg::Node> mesh_node;
			dHeightfieldDataID heightfield_id;
			osg::ref_ptr<osg::HeightField> heightfield;
		};
		
		Geometry();
		Geometry(const Geometry& other, const osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Geometry);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Attach this geometry to a Body
		void setBody(Body *body, const osg::Matrix& offset = osg::Matrix::identity());
		/// Get the Body that this geometry is attached to
		Body* getBody();
		
		/// Add a geometry shape, with optional transformation
		void addShape(const Shape& shape);
		/// Add a geometry shape, with optional transformation
		void addShape(const ShapeType type, const double p1, const double p2 = 0, const double p3 = 0, const double p4 = 0, const osg::Matrix& M = osg::Matrix::identity());
		/// Add a mesh, derived from an osg::Node
		void addMesh(osg::Node *node, const osg::Matrix& M = osg::Matrix::identity());
		/// Add a height field from an osg::HeightField
		void addHeightField(osg::HeightField *grid, const osg::Matrix& M = osg::Matrix::identity());
		/// Add a height field from an image
		void addHeightField(osg::Image *img, const float vscale, const float hscale, const osg::Matrix& M = osg::Matrix::identity());
		/// Merge another geometry into this (i.e. add all its shapes to this)
		void merge(const Geometry *other, const osg::Matrix& M = osg::Matrix::identity());
		/// Get a geometry shape
		const Shape& getShape(const unsigned int index) const;
		/// Remove a geometry shape
		void removeShape(const unsigned int index);
		/// Get number of shapes in this geometry
		unsigned int getNumShapes() const;
		/// Set transformation matrix
		void setTransformation(const osg::Matrix& M);
		/// Get transformation matrix
		osg::Matrix getTransformation() const;
		/// Get ODE geom ID
		dGeomID id(const unsigned int shapeno = 0); 
		/// Get position of a shape
		osg::Vec3 getPosition(const unsigned int shapeno = 0);
		/// Transform all shapes
		void transform(const osg::Matrix& M);

		bool isEnabled() const;
		/// Enable collision for this geometry
		void enable();
		/// Disable collision for this geometry
		void disable();
		
		/// Create the actual geometry for the physics engine
		virtual void realize();
		/// Remove the actual geometry for the physics engine
		virtual void unrealize();
		virtual bool isRealized() const;
		
		/// Do a collision test (for one contact point)
		bool checkContact(const Geometry *other, const unsigned int shapeno = 0, const unsigned int othershapeno = 0) const;

		void setContactCallback(ContactCallback *cb) { callback = cb; }
		ContactCallback *getContactCallback() { return callback.get(); }
		void setContactFeedbackCallback(ContactFeedbackCallback *cb) { fb_callback = cb; }
		ContactFeedbackCallback *getContactFeedbackCallback() { return fb_callback.get(); }
		void setNearCallback(NearCallback *cb) { near_callback = cb; }
		NearCallback *getNearCallback() { return near_callback.get(); }
		
		void setMaterialID(const unsigned int id) { materialID = id; }
		unsigned int getMaterialID() const { return materialID; }
		
		void setContactConnected(const bool value) { contactConnected = value; }
		bool shouldContactConnected() const { return contactConnected; }
		
		/// Make a crude visual representation of this geometry
		osg::Node* createDebugNode();
	
		/// Add sphere shape from an osg bounding sphere
		void addBoundingSphere(const osg::BoundingSphere& bsphere, const osg::Matrix& M = osg::Matrix::identity());
		/// Add box shape from an osg bounding box
		void addBoundingBox(const osg::BoundingBox& bbox, const osg::Matrix& M = osg::Matrix::identity());
		/// Add shapes from osg node bounding boxes/spheres
		void addShapesFromBounds(osg::Node *node, const osg::Matrix& M = osg::Matrix::identity());
		
		void setUserData(osg::Referenced *data) { userdata = data; }
		osg::Referenced* getUserData() { return userdata; }
		
		const osg::Vec3& getContactForce();
		const osg::Vec3& getContactTorque();
		bool wantsContactFeedback() const { return feedback; }
		void setContactFeedback(const bool value) { feedback = value; }
		
		bool needsMesh() const { return needMesh; }
		
		void setColorMultiplier(const float value) { colorMultiplier = value; }
		float getColorMultiplier() const { return colorMultiplier; }

	protected:
		virtual ~Geometry();
		
		void setContactForce(const osg::Vec3& F) { contactF = F; }
		void setContactTorque(const osg::Vec3& Q) { contactQ = Q; }
		friend class World;

	private:
		osg::observer_ptr<Body> body;
		dSpaceID space;
		std::vector<dGeomID> geoms;
		std::vector<Shape> shapes;
		osg::Matrix bodyOffsetM;
		osg::ref_ptr<ContactCallback> callback;
		osg::ref_ptr<ContactFeedbackCallback> fb_callback;
		osg::ref_ptr<NearCallback> near_callback;
		unsigned int materialID;
		bool contactConnected;
		
		dGeomID createGeom(const Shape& shape);
		dTriMeshDataID buildTriMesh(osg::Node *node);
		osg::Node* buildTriMeshDebugNode(osg::Node *node);
		dHeightfieldDataID buildHeightField(osg::HeightField* grid);
		dHeightfieldDataID buildHeightField(osg::Image *img, const float vscale, const float hscale, unsigned int& cols);

		static dSpaceID default_space;			
		osg::Vec3 contactF, contactQ;
		bool feedback;
		bool needMesh;
		float colorMultiplier;
		
		osg::Referenced *userdata;
	};
	
	class MOODYN_EXPORT ContactCallback : public osg::Referenced
	{
	public:
		virtual bool operator()(Geometry *own, Geometry *other) = 0;
	};
	
	class MOODYN_EXPORT ContactFeedbackCallback : public osg::Referenced
	{
	public:
		virtual bool operator()(Geometry *own, Geometry *other) = 0;
	};
	
	class MOODYN_EXPORT NearCallback : public osg::Referenced
	{
	public:
		virtual bool operator()(Geometry *own, Geometry *other) = 0;
	};
	
	/// @}
}

#endif
