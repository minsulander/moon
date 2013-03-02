#ifndef ODE_OSG_H_
#define ODE_OSG_H_

namespace moodyn {
	
	/// \addtogroup dynamics
	/// @{
	
	/// Converts an osg::Matrix to an ODE dMatrix3
    inline void odeMatrixFromOsg(const osg::Matrix &R, dMatrix3 &r) {
		r[ 0] = R(0,0);
		r[ 1] = R(1,0);
		r[ 2] = R(2,0);
		r[ 3] = 0.0;
		r[ 4] = R(0,1);
		r[ 5] = R(1,1);
		r[ 6] = R(2,1);
		r[ 7] = 0.0;
		r[ 8] = R(0,2);
		r[ 9] = R(1,2);
		r[10] = R(2,2);
		r[11] = 0.0;
    }
    
	/// Converts an ODE matrix to an osg::Matrix
    inline const osg::Matrix osgMatrixFromOde(const dReal* r, const dReal *p) {
		osg::Matrix M;
		M.set(r[0], r[4], r[8], 0,
			  r[1], r[5], r[9], 0,
			  r[2], r[6], r[10], 0,
			  p[0], p[1], p[2], 1.0);
		return M;
    }
	
	/// Converts an ODE dVector3 to an osg::Vec3
	inline const osg::Vec3 osgVec3FromOde(const dVector3 v) {
		return osg::Vec3(v[0],v[1],v[2]);
	}

	/// @}
	
}

#endif /*ODE_OSG_H_*/
