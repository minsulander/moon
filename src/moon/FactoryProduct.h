#ifndef MOON_FACTORYPRODUCT_H
#define MOON_FACTORYPRODUCT_H

#include "Export.h"
#include "Parsable.h"
#include <osg/Object>

namespace moon {

	/// \addtogroup core
	/// @{
	
	/// An object that can be serialized, deserialized, instantiated, cloned etc by the ObjectFactory
	class MOON_EXPORT FactoryProduct : public osg::Object, virtual public Parsable {
	public:
		FactoryProduct() : osg::Object(), temporary(false) {}
		FactoryProduct(const FactoryProduct& other, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
			: osg::Object(other, copyop), templateObject(other.templateObject), temporary(other.temporary) {}
		
		const FactoryProduct *getTemplate() const { return templateObject.get(); }

		/// Setting a product as temporary indicates that it is not persistent and should generally not be written to file
		void setTemporary(const bool value) { temporary = value; }
		bool isTemporary() const { return temporary; }
		
	private:
		osg::ref_ptr<const FactoryProduct> templateObject;
		friend class ObjectFactory;
		bool temporary;
	};
	
	/// @}

}

#endif
