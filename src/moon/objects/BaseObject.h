#ifndef MOON_BASEOBJECT_H
#define MOON_BASEOBJECT_H

#include "TransformObject.h"
#include "moon/Export.h"
#include "moon/components/Component.h"
#include "moon/Parameter.h"
#include "moon/NodeMask.h"
#include <moonet/PositionedNetworkObject.h>
#include <osg/observer_ptr>
#include <vector>

class TiXmlElement;

namespace moon {
	
	class KinematicObject;
	
	/// \ingroup core objects
	/// @{
	
	/// Base class for static visible objects in the scenario, supporting hierarchies of objects
	class MOON_EXPORT BaseObject 
	:	public TransformObject, 
		public moonet::PositionedNetworkObject, 
		public ComponentContainer,
		public ParameterContainer
	{
	public:
		BaseObject();
		BaseObject(const BaseObject& object, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moon,BaseObject);
		virtual const std::string networkObjectName() const;
		
		/// Get number of children beneath this node in the hierarchy
		unsigned int getNumChildren() const;
		/// Add a child to this object
		virtual void addChild(BaseObject *child);
		/// Remove a child from this object
		void removeChild(BaseObject *child);
		/// Remove a child from this object
		inline void removeChild(const unsigned int index) { removeChildren(index, 1); }
		/// Remove a set of children from this object
		void removeChildren(const unsigned int index, const unsigned int num);
		/// Remove a child from this object and add it to the current scenario as an independent object
		virtual void separateChild(BaseObject *child);
		/// Remove a child from this object and add it to the current scenario as an independent object
		inline void separateChild(const unsigned int index) { separateChild(getChild(index)); }
		/// Get a child of this object
		BaseObject* getChild(const unsigned int index);
		/// Get index of a child
		unsigned int getChildIndex(const BaseObject *child) const;
		/// Get the parent of this object
		BaseObject* getParent() const;
		/// Get the root (top-most parent) of this object
		BaseObject* getRoot();
		/// Find a named object in the same object hierarchy as this one
		BaseObject* findRelated(const std::string& name, const bool childrenOnly = false);
		/// Find an object in the same object hierarchy as this one by its template object
		BaseObject* findRelatedByTemplate(const BaseObject* templateObject, const bool childrenOnly = false);
		/// Find an object in the same object hierarchy as this one with a tag
		BaseObject* findRelatedByTag(const std::string& tag, const bool childrenOnly = false);
		
		/// Deserialize object from an XML element
		virtual void parseXML(const TiXmlElement *element);
		/// Serialize object to an XML element
		virtual void writeXML(TiXmlElement *element) const;
		
		/// Add another object as a component to this object
		virtual void addComponent(Component* component);
		
		/// Initialize components and parsed parameters
		virtual void initialize();
		/// Reset state of this object
		virtual void reset();
		/// Set the reset point (record current state which will be returned to by calling reset())
		virtual void setResetState();
		/// Called when scenario is activated - for creating geometry etc
		virtual void realize();
		/// Called when scenario is deactivated - for removing/disabling geometry
		virtual void unrealize();

		void setRealizeRange(const float range) { realizeRange = range; }
		float getRealizeRange() const { return realizeRange; }
		
		virtual void show();
		virtual void hide();
		bool isHidden() { return hidden; }
		
		virtual void addNode(osg::Node *node);
		virtual void removeNode(osg::Node *node);
		virtual void addDebugNode(osg::Node *node);
		virtual void removeDebugNode(osg::Node *node);
		osg::Node *getNode() const;
		osg::Node *getDebugNode() const;
		
		enum HighLightMode { BBOX, THICK_BBOX, TRANSPARENT_BBOX, SCRIBE, THICK_SCRIBE };
		virtual void highlight(const bool on, const HighLightMode mode = THICK_SCRIBE, const osg::Vec4& color = osg::Vec4(1,1,1,1), const bool recursive = true);

		enum DisplayMode { DISPLAY_NORMAL = 0x01, DISPLAY_DEBUG = 0x02 };
		virtual void setDisplayMode(const unsigned int mode);
		unsigned int getDisplayMode() const { return displayMode; }
		
		/// Set wether this object should normally be visible (i.e. it represents a visible object in real life)
		void setNormallyVisible(const bool flag) { normallyVisible = flag; }
		/// Get wether this object should normally be visible (false for lights, cameras etc)
		bool isNormallyVisible() const { return normallyVisible; }

		// Overloaded (unneccesarily) from osg::Object to avoid Lua binding confusion
		void setName(const std::string& name) { osg::Object::setName(name); }
		std::string getName() const { return osg::Object::getName(); }

		/// Used to compare object references in Lua
		long id() const { return (long) this; }
		
		/// Get accumulated world transform matrix of this object
		osg::Matrix getWorldTransformMatrix() const;
		/// Get inverse accumulated world transform matrix of this object
		osg::Matrix getInverseWorldTransformMatrix();
		
		/// Set attitude so that this object points toward a specific world coordinate
		void pointAt(const osg::Vec3& pos);
		/// Set attitude so that this object points toward a specific world coordinate
		void pointAt(const double x, const double y, const double z) { pointAt(osg::Vec3(0,0,0)); }
		/// Set attitude so that this object points towards the other object
		void pointAt(BaseObject *other);
		/// Get range to another object
		float getRange(const BaseObject *object);
		/// Get azimuth (bearing) angle to another object
		float getAzimuth(const BaseObject *object, const bool rel = true);
		/// Get elevation angle relative to another object
		float getElevation(const BaseObject *object, const bool rel = true);
		/// Get spherical coordinates to another object (more effectively than separate methods above)
		void getSpherical(float& range, float& azimuth, float& elevation, const BaseObject *object, const bool rel = true);
		
		/// Get height of this object above objects directly below
		bool getHeightAboveTerrain(float &height, const bool boundscenter = true, const double below = 10000.0, const double above = 1000.0, const osg::Node::NodeMask mask = NodeMask::INTERSECT);
		/// Set object position on top of objects directly below
		bool clampToTerrain(const bool boundscenter = true, const double below = 10000.0, const double above = 1000.0, const osg::Node::NodeMask mask = NodeMask::INTERSECT);
		/// Set object attitude parallel to normal of objects directly below
		bool alignToTerrain(const bool boundscenter = true, const double below = 10000.0, const double above = 1000.0, const osg::Node::NodeMask mask = NodeMask::INTERSECT);
		/// Get bottom center of total bounding box in parent coordinates
		virtual osg::Vec3 getBottomCenter();
		
		// These are ambiguous between TransformObject and PositionedNetworkObject
		using TransformObject::setPosition;
		using TransformObject::getPosition;
		virtual void setPosition(const double x, const double y, const double z) { TransformObject::setPosition(x, y, z); }
		virtual void getPosition(double& x, double& y, double& z) const { TransformObject::getPosition(x, y, z); }

		// Overloaded network methods
		virtual void onConstruction();
		virtual void onOwnerChange();
		virtual bool serialize(const bool full);
		virtual void deserialize(const bool full, const double timediff);
		/// Set (or request if we're a client) the owner of this object and its children
		virtual bool setOwner(moonet::Client *newOwner);
		virtual void setVisibility(const bool visible);
		
		virtual KinematicObject* asKinematic();
		virtual void preUpdateTransformation(const bool parentUpdate = false);
		virtual void updateTransformation(const bool parentUpdate = false);
		
		BaseObject* getChildByTag(const std::string& tag);
		
		bool serializesChildren() { return serializeChildren; }
		bool serializesAsChild() { return serializeAsChild; }
		
		osg::Matrix getResetMatrix() const { return resetMatrix; }
		osg::Matrix getWorldResetMatrix() const;
		
		void setScriptUpdateInterval(const double interval) { scriptUpdateInterval = interval; }
		double getScriptUpdateInterval() const { return scriptUpdateInterval; }
		
		void remove(const double timeFromNow = 0.0);
		void setRemoveTime(const double time) { removeTime = time; }
		double getRemoveTime() const { return removeTime; }
		
		OpenThreads::Mutex& getUpdateMutex() { return updateMutex; }
		
		virtual void update(const double dt);
		
		virtual Parameter* findParameter(const std::string& name);

	protected:
		void setDirtyInverseWorldMatrix() { dirtyInverseWorldMatrix = true; }
		virtual ~BaseObject(); // protected destructor - forces use of ref_ptr
		
		osg::Matrix resetMatrix;
		bool resetHidden;
		OpenThreads::Mutex updateMutex;
		bool serializeChildren, serializeAsChild;

	private:
		typedef std::vector< osg::observer_ptr<BaseObject> > ChildList;
		ChildList children;
		BaseObject *parent;
		
		osg::Quat lastRot;
		osg::Matrix inverseWorldMatrix;
		bool dirtyInverseWorldMatrix;
		
		osg::ref_ptr<osg::Node> highlightnode;
		osg::ref_ptr<osg::Group> nodeGroup;
		osg::ref_ptr<osg::Group> debugGroup;
		bool normallyVisible;
		bool hidden;
		unsigned int displayMode;

		bool wasRealizedInRange, wasHiddenInRange;
		float realizeRange, realizeAzimuth, realizeElevation, realizeExemptRange;
		
		double scriptUpdateInterval, scriptTimeStamp;
		double removeTime;

		osg::ref_ptr<Parameter> headingParam, pitchParam, rollParam;		
		typedef std::map<std::string, std::string> ScriptParamMap;
		ScriptParamMap scriptParams;
		
	};

	/// @}

}


#endif
