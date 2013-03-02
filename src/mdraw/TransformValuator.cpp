#include "TransformValuator.h"
#include "utils.h"

namespace mdraw {
	
	TransformValuator::TransformValuator() 
	: osg::MatrixTransform()
	{
	}
	
	TransformValuator::TransformValuator(const TransformValuator& source, const osg::CopyOp& copyop)
	: osg::MatrixTransform(source, copyop)
	{
	}
	
	void TransformValuator::setValue(const float value, const unsigned int index)
	{
		switch (index) {
			case TRANS_X: {
				osg::Matrix M = getMatrix();
				osg::Vec3 trans = M.getTrans();
				trans.x() = value;
				M.setTrans(trans);
				setMatrix(M);
				break;
			}
			case TRANS_Y: {
				osg::Matrix M = getMatrix();
				osg::Vec3 trans = M.getTrans();
				trans.x() = value;
				M.setTrans(trans);
				setMatrix(M);
				break;
			}
			case TRANS_Z: {
				osg::Matrix M = getMatrix();
				osg::Vec3 trans = M.getTrans();
				trans.x() = value;
				M.setTrans(trans);
				setMatrix(M);
				break;
			}
			case EULER_H: {
				osg::Matrix M = getMatrix();
				osg::Vec3 att = getEulerAnglesFromQuat(M.getRotate());
				att.x() = value;
				M.setRotate(getQuatFromEulerAngles(att));
				setMatrix(M);
				break;
			}
			case EULER_P: {
				osg::Matrix M = getMatrix();
				osg::Vec3 att = getEulerAnglesFromQuat(M.getRotate());
				att.y() = value;
				M.setRotate(getQuatFromEulerAngles(att));
				setMatrix(M);
				break;
			}
			case EULER_R: {
				osg::Matrix M = getMatrix();
				osg::Vec3 att = getEulerAnglesFromQuat(M.getRotate());
				att.z() = value;
				M.setRotate(getQuatFromEulerAngles(att));
				setMatrix(M);
				break;
			}
			case SCALE_X: {
				osg::Matrix M = getMatrix();
				osg::Vec3 pos, scale;
				osg::Quat rot, so;
				M.decompose(pos, rot, scale, so);
				M = osg::Matrix::rotate(rot) * osg::Matrix::translate(pos) * osg::Matrix::scale(value, scale.y(), scale.z());
				setMatrix(M);
				break;
			}
			case SCALE_Y: {
				osg::Matrix M = getMatrix();
				osg::Vec3 pos, scale;
				osg::Quat rot, so;
				M.decompose(pos, rot, scale, so);
				M = osg::Matrix::rotate(rot) * osg::Matrix::translate(pos) * osg::Matrix::scale(scale.x(), value, scale.z());
				setMatrix(M);
				break;
			}
			case SCALE_Z: {
				osg::Matrix M = getMatrix();
				osg::Vec3 pos, scale;
				osg::Quat rot, so;
				M.decompose(pos, rot, scale, so);
				M = osg::Matrix::rotate(rot) * osg::Matrix::translate(pos) * osg::Matrix::scale(scale.x(), scale.y(), value);
				setMatrix(M);
				break;
			}
			case SCALE: {
				osg::Matrix M = getMatrix();
				osg::Vec3 pos, scale;
				osg::Quat rot, so;
				M.decompose(pos, rot, scale, so);
				M = osg::Matrix::rotate(rot) * osg::Matrix::translate(pos) * osg::Matrix::scale(value, value, value);
				setMatrix(M);
				break;
			}
		}
	}
	
	float TransformValuator::getValue(const unsigned int index) const
	{
		osg::Matrix M = getMatrix();
		switch (index) {
			case TRANS_X: return M.getTrans().x();
			case TRANS_Y: return M.getTrans().y();
			case TRANS_Z: return M.getTrans().z();
			case EULER_H: {
				osg::Vec3 att = getEulerAnglesFromQuat(getMatrix().getRotate());
				return att.x();
			}
			case EULER_P: {
				osg::Vec3 att = getEulerAnglesFromQuat(getMatrix().getRotate());
				return att.y();
			}
			case EULER_R: {
				osg::Vec3 att = getEulerAnglesFromQuat(getMatrix().getRotate());
				return att.z();
			}
			case SCALE_X: return M.getScale().x();
			case SCALE_Y: return M.getScale().y();
			case SCALE_Z: return M.getScale().z();
			case SCALE: return M.getScale().length();
			default:
				return 0.f;
		}
	}

	void TransformValuator::setValuePtr(const float *ptr, const unsigned int index)
	{
		if (index >= valueptrs.size())
			valueptrs.resize(index+1);
		valueptrs[index] = ptr;
	}
	
	int TransformValuator::getIndex(const std::string& name)
	{
		if (name == "posx")
			return TRANS_X;
		else if (name == "posy")
			return TRANS_Y;
		else if (name == "posz")
			return TRANS_Z;
		else if (name == "heading")
			return EULER_H;
		else if (name == "pitch")
			return EULER_P;
		else if (name == "roll")
			return EULER_R;
		else if (name == "scalex")
			return SCALE_X;
		else if (name == "scaley")
			return SCALE_Y;
		else if (name == "scalez")
			return SCALE_Z;
		else if (name == "scale")
			return SCALE;
		else
			return -1;
	}
	
	void TransformValuator::traverse(osg::NodeVisitor& nv)
	{
		if (nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR) {
			for (std::size_t i = 0; i < valueptrs.size(); i++) {
				if (valueptrs[i])
					setValue(*valueptrs[i], i);
			}
		}
		osg::MatrixTransform::traverse(nv);
	}
	
} // namespace
