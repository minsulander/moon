#include "Atmosphere.h"

namespace moodyn {
	
	Atmosphere::Atmosphere()
	: moon::Component()
	, p0(101.325e3)   // Pa
	, rho0(1.225)     // kg/m^3
	, T0(288.16)      // K
	, R(287.04)       // J/(kg*K)
	, g0(9.80665)     // m/s^2
	, a(-0.0065)      // K/m
	, r(6.356766e6)   // m
	, mu0(1.780e-5)   // kg/(m*s)
	, S(110.6)        // K
	, gamma(1.4)      // cp/cv
	{
	}
	
	Atmosphere::Atmosphere(const Atmosphere& source, const osg::CopyOp& copyop)
	: moon::Component(source, copyop)
	, p0(source.p0)
	, rho0(source.rho0)
	, T0(source.T0)
	, R(source.R)
	, g0(source.g0)
	, a(source.a)
	, r(source.r)
	, mu0(source.mu0)
	, S(source.S)
	, gamma(source.gamma)
	{
	}
	
	void Atmosphere::realize()
	{
		Component::realize();
		if (currentPtr.valid() && currentPtr.get() != this)
			currentPtr->unrealize();
		currentPtr = this;
	}
	
	void Atmosphere::unrealize()
	{
		Component::unrealize();
		if (currentPtr.get() == this)
			currentPtr = NULL;
	}
	
	void Atmosphere::calculate(AtmosphericProperties& atmo, const osg::Vec3& pos)
	{
		double z = pos.z();
		double p, rho, T;
		double h=r/(r+z)*z;
		double T11=T0+a*11000.0; //temperature at h=11000m
		if (h>11000.0) {
			// Treat temperature differently in stratosphere
			T=T11;
			p=p0*0.22336*exp((-g0/R/T11)*(h-11000.0));
			rho=rho0*0.29707*exp(-(g0/R/T11)*(h-11000.0));
		} else {
			// Troposphere temperature from standard lapse rate
			T=T0+a*h;
			p=p0*pow(T/T0,-g0/(a*R));
			rho=rho0*pow(T/T0,-g0/(a*R)+1.0);
		}
		atmo.p = p;
		atmo.rho = rho;
		atmo.T = T;
		atmo.c = sqrt(gamma*R*T);
		atmo.mu = pow(mu0*(T/T0),1.5*(T0+S)/(T+S));
		atmo.h = h;
		atmo.wind = globalwind; // TODO replace with windmap
	}
	osg::observer_ptr<Atmosphere> Atmosphere::currentPtr = NULL;

}
