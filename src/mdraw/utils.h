#ifndef MDRAW_UTILS_H
#define MDRAW_UTILS_H

#include "Export.h"

#include <osg/Node>
#include <osg/Drawable>

#include <iostream>

namespace mdraw
{
	extern MDRAW_EXPORT void printDrawable(const osg::Drawable* drawable, const int indentlevel, std::ostream& outs);
        extern MDRAW_EXPORT void printNode(const osg::Node* node, const int verbosity, const int indentlevel, std::ostream& outs, const std::string& prepend = "");
        extern MDRAW_EXPORT std::string getNodeString(const osg::Node* node, const int verbosity = 0, const int indentlevel = 0);
	
	enum DebugDrawMode {
		NORMAL,
		TRANSPARENT,
		WIREFRAME,
		THICK_WIREFRAME
	};
	/// Modify stateset of subgraph according to a specified DebugDrawMode
	extern MDRAW_EXPORT void setDebugDrawMode(osg::Node* node, const DebugDrawMode mode);
	/// Get a debug node for visualising bounding sphere of a subgraph
	extern MDRAW_EXPORT osg::Node* getBoundingSphereNode(const osg::Node* node, const DebugDrawMode = WIREFRAME, const double scale=1.0, const osg::Vec4& color = osg::Vec4(1,1,1,0.5));
	/// Get a debug node for visualising bounding box of a subgraph
	extern MDRAW_EXPORT osg::Node* getBoundingBoxNode(const osg::Node* node, const DebugDrawMode = WIREFRAME, const double scale=1.0, const osg::Vec4& color = osg::Vec4(1,1,1,0.5));
	/// Calculate a bounding box for a node subgraph (including groups and transforms)
	extern MDRAW_EXPORT osg::BoundingBox getBoundingBox(const osg::Node* node);
	extern MDRAW_EXPORT osg::Node* getBoundingBoxGraph(const osg::Node* node, const DebugDrawMode = WIREFRAME, const double scale=1.0, const osg::Vec4& color = osg::Vec4(1,1,1,0.5));	
	extern MDRAW_EXPORT osg::Vec3 getEulerAnglesFromQuat(const osg::Quat& q);
	extern MDRAW_EXPORT osg::Quat getQuatFromEulerAngles(const osg::Vec3& angles);
}

#endif
