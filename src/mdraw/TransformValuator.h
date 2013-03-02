#ifndef MDRAW_TRANSFORMVALUATOR_H
#define MDRAW_TRANSFORMVALUATOR_H

#include "Valuator.h"
#include <osg/MatrixTransform>

namespace mdraw {
	
	/// \brief An osg::MatrixTransform that matches its matrix to set values
	/// \ingroup draw
	class MDRAW_EXPORT TransformValuator : public osg::MatrixTransform, public Valuator {
	public:
		TransformValuator();
		TransformValuator(const TransformValuator& source, const osg::CopyOp& copyop);
		META_Node(mdraw, TransformValuator);
		
		virtual void setValue(const float value, const unsigned int index = 0);
		virtual float getValue(const unsigned int index = 0) const;
		virtual void setValuePtr(const float* valuePtr, const unsigned int index = 0);
		virtual int getIndex(const std::string& name);
		virtual osg::Node* asNode() { return this; }

		virtual void traverse(osg::NodeVisitor& nv);
		
		enum ValueIndex {
			TRANS_X, TRANS_Y, TRANS_Z,
			EULER_H, EULER_P, EULER_R,
			SCALE_X, SCALE_Y, SCALE_Z,
			SCALE
		};

	private:
		std::vector< const float* > valueptrs;
	};
	
}

#endif
