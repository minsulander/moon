#ifndef MOODYN_WORLD_H
#define MOODYN_WORLD_H

#include "Export.h"
#include <moon/FactoryProduct.h>
#include <moon/SimulationManager.h>
#include <osg/Vec3>
#include <osg/ShapeDrawable>
#include <ode/ode.h>
#include <map>
#include <string>
#include <OpenThreads/ReadWriteMutex>

namespace moodyn {
	
	/// \addtogroup dynamics
	/// @{
	
	/// Dynamics (ODE) world wrapper class. Pure singleton.
	class MOODYN_EXPORT World : public moon::SimulationListener, public moon::Parsable {
	public:
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
		
		void setGravity(const osg::Vec3& gravity);
		osg::Vec3 getGravity();
		
		enum Stepper { QUICK, ACCURATE };
		/// Set stepper algorithm to use in step() method
		void setStepper(const Stepper stepper);
		Stepper getStepper();
		
		dContact& getContact(const unsigned int material_id1, const unsigned int material_id2);
		void setContact(const unsigned int material_id1, const unsigned int material_id2, dContact& contact);
		const unsigned int getMaterialID(const std::string& name);
		const unsigned int getOrCreateMaterialID(const std::string& name);
		
		/// Advance the dynamics simulation by the time step set with setTimeStep()
		virtual void update(const double dt);
		
		dWorldID id();
		dSpaceID getDefaultSpace() const;
		dJointGroupID getContactGroup();
		inline float getReferenceMass() const { return referenceMass; }
		
		static World& instance();
		static OpenThreads::Mutex mutex;

	protected:
		World();
		virtual ~World();
		
	private:
		dWorldID worldID;
		dSpaceID defaultSpace;
		dJointGroupID contactGroup;
		Stepper stepper;

		typedef std::map<unsigned int, dContact> ContactTable;
		ContactTable contacts;
		typedef std::map<std::string, unsigned int> MaterialTable;
		MaterialTable materials;
		osg::ref_ptr<osg::TessellationHints> hints;
		float referenceMass;
		
		static World *instancePtr;
	};
	
	class MOODYN_EXPORT DynamicsConfiguration : public moon::FactoryProduct {
	public:
		DynamicsConfiguration();
		DynamicsConfiguration(const DynamicsConfiguration& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, DynamicsConfiguration);
		
		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;
	};

	class MOODYN_EXPORT DynamicsException : public std::exception {
	public:
		DynamicsException(const std::string& message = "") { this->message = std::string("DynamicsException: ") + message; }
		~DynamicsException() throw() {}
		virtual const char* what() const throw()
		{
			return message.c_str();
		}
		std::string message;
	};
	
	/// @}

}

#endif
