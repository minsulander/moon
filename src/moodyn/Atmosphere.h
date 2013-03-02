#ifndef MOODYN_ATMOSPHERE_H
#define MOODYN_ATMOSPHERE_H

#include "Export.h"
#include <moon/components/Component.h>
#include <osg/Vec3>
#include <osg/observer_ptr>

namespace moodyn {
	
	/// \addtogroup dynamics
	/// @{

	struct MOODYN_EXPORT AtmosphericProperties {
		AtmosphericProperties() : p(101.325e3), rho(1.225), T(288.16), c(343), mu(1.78e-5), h(0) {}
		double
		p,		///< Air pressure [Pa]
		rho,	///< Air density [kg/m^3]
		T,		///< Temperature [K]
		c,		///< Speed of sound [m/s]
		mu,		///< Viscosity [kg/ms]
		h;		///< Geopotential altitude [m]
		osg::Vec3 wind;
	};
	
	/// \ingroup components
	/// \brief Atmosphere simulation component
	class MOODYN_EXPORT Atmosphere : public moon::Component {
	public:
		Atmosphere();
		Atmosphere(const Atmosphere& source, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
		META_Object(moodyn, Atmosphere);
		
		virtual void realize();
		virtual void unrealize();
		
		/// Calculate atmospheric properties at a given location
		void calculate(AtmosphericProperties& atmo, const osg::Vec3& pos);
		
		/// Get current atmosphere - set by realize() and unset by unrealize()
		static Atmosphere* current() { return currentPtr.get(); }
		
	private:
		double
		p0,		///< Sea level pressure			Pa
		rho0,	///< Sea level density			kg/m^3
		T0,		///< Sea level temperature		K
		R,		///< ?							J/(kg*K)
		g0,		///< Gravitational acceleration	m/s^2
		a,		///< Temperature lapse rate		K/m
		r,		///< Planet radius				m
		mu0,	///< Sea level viscosity		kg/(m*s)
		S,		///< ?							K
		gamma;	///< ?							cp/cv
		osg::Vec3 globalwind;
		
		static osg::observer_ptr<Atmosphere> currentPtr;
	};
	
	/// @}
}

#endif
