/*
** Lua binding: moodyn
** Generated automatically by tolua++-1.0.92-moon-customized on Sun Dec 16 21:46:25 2012.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_moodyn_open (lua_State* tolua_S);

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#include <moodyn/components/Body.h>
#include <moodyn/components/Geometry.h>
#include <moodyn/components/Joint.h>
#include <moodyn/objects/DynamicPhysicalObject.h>
#include <moodyn/objects/DynamicVehicle.h>
#include <moodyn/objects/PhysicalObject.h>
#include <moodyn/objects/Thruster.h>

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_dGeomID (lua_State* tolua_S)
{
 dGeomID* self = (dGeomID*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_osg__Quat (lua_State* tolua_S)
{
 osg::Quat* self = (osg::Quat*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_osg__Matrix (lua_State* tolua_S)
{
 osg::Matrix* self = (osg::Matrix*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_osg__Vec3 (lua_State* tolua_S)
{
 osg::Vec3* self = (osg::Vec3*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_moodyn__Geometry__Shape (lua_State* tolua_S)
{
 moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_dBodyID (lua_State* tolua_S)
{
 dBodyID* self = (dBodyID*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"dGeomID");
 tolua_usertype(tolua_S,"osg::Quat");
 tolua_usertype(tolua_S,"moon::BaseObject");
 tolua_usertype(tolua_S,"moon::Control");
 tolua_usertype(tolua_S,"moon::Vehicle");
 tolua_usertype(tolua_S,"moodyn::Body");
 tolua_usertype(tolua_S,"osg::Image");
 tolua_usertype(tolua_S,"osg::Vec3");
 tolua_usertype(tolua_S,"osg::BoundingBox");
 tolua_usertype(tolua_S,"dBodyID");
 tolua_usertype(tolua_S,"moodyn::Joint");
 tolua_usertype(tolua_S,"moon::Component");
 tolua_usertype(tolua_S,"osg::HeightField");
 tolua_usertype(tolua_S,"osg::Node");
 tolua_usertype(tolua_S,"osg::BoundingSphere");
 tolua_usertype(tolua_S,"osg::Referenced");
 tolua_usertype(tolua_S,"moon::KinematicObject");
 tolua_usertype(tolua_S,"moodyn::DynamicPhysicalObject");
 tolua_usertype(tolua_S,"moodyn::Geometry");
 tolua_usertype(tolua_S,"moodyn::Thruster");
 tolua_usertype(tolua_S,"osg::Matrix");
 tolua_usertype(tolua_S,"moodyn::PhysicalObject");
 tolua_usertype(tolua_S,"moodyn::Geometry::Shape");
 tolua_usertype(tolua_S,"moodyn::DynamicVehicle");
}

/* method: realize of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_realize00
static int tolua_moodyn_moodyn_Body_realize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'realize'",NULL);
#endif
 {
  self->realize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'realize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unrealize of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_unrealize00
static int tolua_moodyn_moodyn_Body_unrealize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unrealize'",NULL);
#endif
 {
  self->unrealize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unrealize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRealized of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_isRealized00
static int tolua_moodyn_moodyn_Body_isRealized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRealized'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isRealized();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRealized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransformation of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setTransformation00
static int tolua_moodyn_moodyn_Body_setTransformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransformation'",NULL);
#endif
 {
  self->setTransformation(*M);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTransformation of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getTransformation00
static int tolua_moodyn_moodyn_Body_getTransformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTransformation'",NULL);
#endif
 {
  osg::Matrix tolua_ret = (osg::Matrix)  self->getTransformation();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Matrix(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Matrix");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Matrix));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Matrix");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTransformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setPosition00
static int tolua_moodyn_moodyn_Body_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* pos = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'",NULL);
#endif
 {
  self->setPosition(*pos);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getPosition00
static int tolua_moodyn_moodyn_Body_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getPosition();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setRotation00
static int tolua_moodyn_moodyn_Body_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Quat* rot = ((osg::Quat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'",NULL);
#endif
 {
  self->setRotation(*rot);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getRotation00
static int tolua_moodyn_moodyn_Body_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'",NULL);
#endif
 {
  osg::Quat tolua_ret = (osg::Quat)  self->getRotation();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Quat(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Quat");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Quat));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Quat");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setVelocity00
static int tolua_moodyn_moodyn_Body_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* vel = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'",NULL);
#endif
 {
  self->setVelocity(*vel,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVelocity of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getVelocity00
static int tolua_moodyn_moodyn_Body_getVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getVelocity(rel);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularVelocity of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setAngularVelocity00
static int tolua_moodyn_moodyn_Body_setAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* avel = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularVelocity'",NULL);
#endif
 {
  self->setAngularVelocity(*avel,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngularVelocity of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getAngularVelocity00
static int tolua_moodyn_moodyn_Body_getAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngularVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAngularVelocity(rel);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addForce of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_addForce00
static int tolua_moodyn_moodyn_Body_addForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* F = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addForce'",NULL);
#endif
 {
  self->addForce(*F,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addForceAt of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_addForceAt00
static int tolua_moodyn_moodyn_Body_addForceAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* F = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addForceAt'",NULL);
#endif
 {
  self->addForceAt(*F,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addForceAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addForceAt of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_addForceAt01
static int tolua_moodyn_moodyn_Body_addForceAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* F = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,0));
  osg::Vec3* pos = ((osg::Vec3*)  tolua_tousertype(tolua_S,4,0));
  const bool relpos = ((const bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addForceAt'",NULL);
#endif
 {
  self->addForceAt(*F,rel,*pos,relpos);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Body_addForceAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTorque of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_addTorque00
static int tolua_moodyn_moodyn_Body_addTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* Q = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTorque'",NULL);
#endif
 {
  self->addTorque(*Q,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setForce of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setForce00
static int tolua_moodyn_moodyn_Body_setForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* F = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setForce'",NULL);
#endif
 {
  self->setForce(*F,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTorque of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setTorque00
static int tolua_moodyn_moodyn_Body_setTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* Q = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTorque'",NULL);
#endif
 {
  self->setTorque(*Q,rel);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getForce of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getForce00
static int tolua_moodyn_moodyn_Body_getForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getForce'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getForce(rel);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTorque of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getTorque00
static int tolua_moodyn_moodyn_Body_getTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTorque'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getTorque(rel);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMass of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_getMass00
static int tolua_moodyn_moodyn_Body_getMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMass'",NULL);
#endif
 {
  const double tolua_ret = (const double)  self->getMass();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMass of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_setMass00
static int tolua_moodyn_moodyn_Body_setMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  const double newmass = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMass'",NULL);
#endif
 {
  self->setMass(newmass);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_isEnabled00
static int tolua_moodyn_moodyn_Body_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Body* self = (const moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'",NULL);
#endif
 {
  const bool tolua_ret = (const bool)  self->isEnabled();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enable of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_enable00
static int tolua_moodyn_moodyn_Body_enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enable'",NULL);
#endif
 {
  self->enable();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disable of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_disable00
static int tolua_moodyn_moodyn_Body_disable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disable'",NULL);
#endif
 {
  self->disable();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnectedTo of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_isConnectedTo00
static int tolua_moodyn_moodyn_Body_isConnectedTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Body* other = ((moodyn::Body*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnectedTo'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConnectedTo(other);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnectedTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: id of class  moodyn::Body */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Body_id00
static int tolua_moodyn_moodyn_Body_id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Body* self = (moodyn::Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'id'",NULL);
#endif
 {
  dBodyID tolua_ret = (dBodyID)  self->id();
 {
#ifdef __cplusplus
 void* tolua_obj = new dBodyID(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"dBodyID");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(dBodyID));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"dBodyID");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'id'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new00
static int tolua_moodyn_moodyn_Geometry_Shape_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new00_local
static int tolua_moodyn_moodyn_Geometry_Shape_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new01
static int tolua_moodyn_moodyn_Geometry_Shape_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry::ShapeType ntype = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double np1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double np2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double np3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double np4 = ((double)  tolua_tonumber(tolua_S,6,0));
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape(ntype,np1,np2,np3,np4);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_Shape_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new01_local
static int tolua_moodyn_moodyn_Geometry_Shape_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry::ShapeType ntype = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double np1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double np2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double np3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double np4 = ((double)  tolua_tonumber(tolua_S,6,0));
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape(ntype,np1,np2,np3,np4);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_Shape_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new02
static int tolua_moodyn_moodyn_Geometry_Shape_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,7,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry::ShapeType ntype = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double np1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double np2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double np3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double np4 = ((double)  tolua_tonumber(tolua_S,6,0));
  osg::Matrix* nM = ((osg::Matrix*)  tolua_tousertype(tolua_S,7,0));
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape(ntype,np1,np2,np3,np4,*nM);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_Shape_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Shape */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_Shape_new02_local
static int tolua_moodyn_moodyn_Geometry_Shape_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,7,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry::ShapeType ntype = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double np1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double np2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double np3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double np4 = ((double)  tolua_tonumber(tolua_S,6,0));
  osg::Matrix* nM = ((osg::Matrix*)  tolua_tousertype(tolua_S,7,0));
 {
  moodyn::Geometry::Shape* tolua_ret = (moodyn::Geometry::Shape*)  new moodyn::Geometry::Shape(ntype,np1,np2,np3,np4,*nM);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_Shape_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_type
static int tolua_get_moodyn__Geometry__Shape_type(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_type
static int tolua_set_moodyn__Geometry__Shape_type(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p1 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_p1
static int tolua_get_moodyn__Geometry__Shape_p1(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p1'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->p1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p1 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_p1
static int tolua_set_moodyn__Geometry__Shape_p1(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p1'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p1 = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p2 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_p2
static int tolua_get_moodyn__Geometry__Shape_p2(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p2'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->p2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p2 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_p2
static int tolua_set_moodyn__Geometry__Shape_p2(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p2'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p2 = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p3 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_p3
static int tolua_get_moodyn__Geometry__Shape_p3(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p3'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->p3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p3 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_p3
static int tolua_set_moodyn__Geometry__Shape_p3(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p3'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p3 = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p4 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_p4
static int tolua_get_moodyn__Geometry__Shape_p4(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p4'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->p4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p4 of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_p4
static int tolua_set_moodyn__Geometry__Shape_p4(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p4'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p4 = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: M of class  Shape */
#ifndef TOLUA_DISABLE_tolua_get_moodyn__Geometry__Shape_M
static int tolua_get_moodyn__Geometry__Shape_M(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'M'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->M,"osg::Matrix");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: M of class  Shape */
#ifndef TOLUA_DISABLE_tolua_set_moodyn__Geometry__Shape_M
static int tolua_set_moodyn__Geometry__Shape_M(lua_State* tolua_S)
{
  moodyn::Geometry::Shape* self = (moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'M'",NULL);
 if (!tolua_isusertype(tolua_S,2,"osg::Matrix",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->M = *((osg::Matrix*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBody of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setBody00
static int tolua_moodyn_moodyn_Geometry_setBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Body",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Body* body = ((moodyn::Body*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBody'",NULL);
#endif
 {
  self->setBody(body);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBody of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setBody01
static int tolua_moodyn_moodyn_Geometry_setBody01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Body* body = ((moodyn::Body*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* offset = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBody'",NULL);
#endif
 {
  self->setBody(body,*offset);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_setBody00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getBody00
static int tolua_moodyn_moodyn_Geometry_getBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody'",NULL);
#endif
 {
  moodyn::Body* tolua_ret = (moodyn::Body*)  self->getBody();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Body");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addShape of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addShape00
static int tolua_moodyn_moodyn_Geometry_addShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Geometry::Shape",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry::Shape* shape = ((moodyn::Geometry::Shape*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addShape'",NULL);
#endif
 {
  self->addShape(*shape);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addShape of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addShape01
static int tolua_moodyn_moodyn_Geometry_addShape01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry::ShapeType type = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double p1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double p2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double p3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double p4 = ((double)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addShape'",NULL);
#endif
 {
  self->addShape(type,p1,p2,p3,p4);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addShape00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addShape of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addShape02
static int tolua_moodyn_moodyn_Geometry_addShape02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,7,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry::ShapeType type = ((moodyn::Geometry::ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
  double p1 = ((double)  tolua_tonumber(tolua_S,3,0));
  double p2 = ((double)  tolua_tonumber(tolua_S,4,0));
  double p3 = ((double)  tolua_tonumber(tolua_S,5,0));
  double p4 = ((double)  tolua_tonumber(tolua_S,6,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,7,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addShape'",NULL);
#endif
 {
  self->addShape(type,p1,p2,p3,p4,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addShape01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addMesh of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addMesh00
static int tolua_moodyn_moodyn_Geometry_addMesh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addMesh'",NULL);
#endif
 {
  self->addMesh(node);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMesh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addMesh of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addMesh01
static int tolua_moodyn_moodyn_Geometry_addMesh01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addMesh'",NULL);
#endif
 {
  self->addMesh(node,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addMesh00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHeightField of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addHeightField00
static int tolua_moodyn_moodyn_Geometry_addHeightField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::HeightField",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::HeightField* grid = ((osg::HeightField*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHeightField'",NULL);
#endif
 {
  self->addHeightField(grid);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHeightField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHeightField of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addHeightField01
static int tolua_moodyn_moodyn_Geometry_addHeightField01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::HeightField",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::HeightField* grid = ((osg::HeightField*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHeightField'",NULL);
#endif
 {
  self->addHeightField(grid,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addHeightField00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHeightField of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addHeightField02
static int tolua_moodyn_moodyn_Geometry_addHeightField02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Image",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Image* img = ((osg::Image*)  tolua_tousertype(tolua_S,2,0));
  float vscale = ((float)  tolua_tonumber(tolua_S,3,0));
  float hscale = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHeightField'",NULL);
#endif
 {
  self->addHeightField(img,vscale,hscale);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addHeightField01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHeightField of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addHeightField03
static int tolua_moodyn_moodyn_Geometry_addHeightField03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Image",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Image* img = ((osg::Image*)  tolua_tousertype(tolua_S,2,0));
  float vscale = ((float)  tolua_tonumber(tolua_S,3,0));
  float hscale = ((float)  tolua_tonumber(tolua_S,4,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHeightField'",NULL);
#endif
 {
  self->addHeightField(img,vscale,hscale,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addHeightField02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: merge of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_merge00
static int tolua_moodyn_moodyn_Geometry_merge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry* other = ((moodyn::Geometry*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'merge'",NULL);
#endif
 {
  self->merge(other);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'merge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: merge of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_merge01
static int tolua_moodyn_moodyn_Geometry_merge01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry* other = ((moodyn::Geometry*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'merge'",NULL);
#endif
 {
  self->merge(other,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_merge00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getShape of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getShape00
static int tolua_moodyn_moodyn_Geometry_getShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Geometry* self = (const moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getShape'",NULL);
#endif
 {
  moodyn::Geometry::Shape& tolua_ret = (moodyn::Geometry::Shape&)  self->getShape(index);
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"moodyn::Geometry::Shape");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeShape of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_removeShape00
static int tolua_moodyn_moodyn_Geometry_removeShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeShape'",NULL);
#endif
 {
  self->removeShape(index);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumShapes of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getNumShapes00
static int tolua_moodyn_moodyn_Geometry_getNumShapes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Geometry* self = (const moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumShapes'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumShapes();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumShapes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransformation of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setTransformation00
static int tolua_moodyn_moodyn_Geometry_setTransformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransformation'",NULL);
#endif
 {
  self->setTransformation(*M);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: id of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_id00
static int tolua_moodyn_moodyn_Geometry_id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  unsigned int shapeno = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'id'",NULL);
#endif
 {
  dGeomID tolua_ret = (dGeomID)  self->id(shapeno);
 {
#ifdef __cplusplus
 void* tolua_obj = new dGeomID(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"dGeomID");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(dGeomID));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"dGeomID");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'id'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getPosition00
static int tolua_moodyn_moodyn_Geometry_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  unsigned int shapeno = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getPosition(shapeno);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: transform of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_transform00
static int tolua_moodyn_moodyn_Geometry_transform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'transform'",NULL);
#endif
 {
  self->transform(*M);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_isEnabled00
static int tolua_moodyn_moodyn_Geometry_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Geometry* self = (const moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isEnabled();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enable of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_enable00
static int tolua_moodyn_moodyn_Geometry_enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enable'",NULL);
#endif
 {
  self->enable();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disable of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_disable00
static int tolua_moodyn_moodyn_Geometry_disable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disable'",NULL);
#endif
 {
  self->disable();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: realize of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_realize00
static int tolua_moodyn_moodyn_Geometry_realize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'realize'",NULL);
#endif
 {
  self->realize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'realize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unrealize of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_unrealize00
static int tolua_moodyn_moodyn_Geometry_unrealize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unrealize'",NULL);
#endif
 {
  self->unrealize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unrealize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRealized of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_isRealized00
static int tolua_moodyn_moodyn_Geometry_isRealized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Geometry* self = (const moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRealized'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isRealized();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRealized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkContact of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_checkContact00
static int tolua_moodyn_moodyn_Geometry_checkContact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Geometry* self = (const moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry* other = ((moodyn::Geometry*)  tolua_tousertype(tolua_S,2,0));
  unsigned int shapeno = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int othershapeno = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkContact'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->checkContact(other,shapeno,othershapeno);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkContact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaterialID of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setMaterialID00
static int tolua_moodyn_moodyn_Geometry_setMaterialID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  unsigned int id = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaterialID'",NULL);
#endif
 {
  self->setMaterialID(id);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaterialID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaterialID of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getMaterialID00
static int tolua_moodyn_moodyn_Geometry_getMaterialID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaterialID'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getMaterialID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaterialID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContactConnected of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setContactConnected00
static int tolua_moodyn_moodyn_Geometry_setContactConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContactConnected'",NULL);
#endif
 {
  self->setContactConnected(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContactConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: shouldContactConnected of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_shouldContactConnected00
static int tolua_moodyn_moodyn_Geometry_shouldContactConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'shouldContactConnected'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->shouldContactConnected();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shouldContactConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDebugNode of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_createDebugNode00
static int tolua_moodyn_moodyn_Geometry_createDebugNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createDebugNode'",NULL);
#endif
 {
  osg::Node* tolua_ret = (osg::Node*)  self->createDebugNode();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Node");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDebugNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBoundingSphere of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addBoundingSphere00
static int tolua_moodyn_moodyn_Geometry_addBoundingSphere00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::BoundingSphere",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::BoundingSphere* bsphere = ((osg::BoundingSphere*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoundingSphere'",NULL);
#endif
 {
  self->addBoundingSphere(*bsphere);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBoundingSphere'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBoundingSphere of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addBoundingSphere01
static int tolua_moodyn_moodyn_Geometry_addBoundingSphere01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::BoundingSphere",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::BoundingSphere* bsphere = ((osg::BoundingSphere*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoundingSphere'",NULL);
#endif
 {
  self->addBoundingSphere(*bsphere,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addBoundingSphere00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBoundingBox of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addBoundingBox00
static int tolua_moodyn_moodyn_Geometry_addBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::BoundingBox* bbox = ((osg::BoundingBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoundingBox'",NULL);
#endif
 {
  self->addBoundingBox(*bbox);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBoundingBox of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addBoundingBox01
static int tolua_moodyn_moodyn_Geometry_addBoundingBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::BoundingBox* bbox = ((osg::BoundingBox*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoundingBox'",NULL);
#endif
 {
  self->addBoundingBox(*bbox,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addBoundingBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addShapesFromBounds of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addShapesFromBounds00
static int tolua_moodyn_moodyn_Geometry_addShapesFromBounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addShapesFromBounds'",NULL);
#endif
 {
  self->addShapesFromBounds(node);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addShapesFromBounds'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addShapesFromBounds of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_addShapesFromBounds01
static int tolua_moodyn_moodyn_Geometry_addShapesFromBounds01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
  osg::Matrix* M = ((osg::Matrix*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addShapesFromBounds'",NULL);
#endif
 {
  self->addShapesFromBounds(node,*M);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_Geometry_addShapesFromBounds00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserData of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_setUserData00
static int tolua_moodyn_moodyn_Geometry_setUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Referenced",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
  osg::Referenced* data = ((osg::Referenced*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUserData'",NULL);
#endif
 {
  self->setUserData(data);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserData of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getUserData00
static int tolua_moodyn_moodyn_Geometry_getUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUserData'",NULL);
#endif
 {
  void* tolua_ret = (void*)  self->getUserData();
 tolua_pushuserdata(tolua_S,(void*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContactForce of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getContactForce00
static int tolua_moodyn_moodyn_Geometry_getContactForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContactForce'",NULL);
#endif
 {
  osg::Vec3& tolua_ret = (osg::Vec3&)  self->getContactForce();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"osg::Vec3");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContactForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContactTorque of class  moodyn::Geometry */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Geometry_getContactTorque00
static int tolua_moodyn_moodyn_Geometry_getContactTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Geometry* self = (moodyn::Geometry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContactTorque'",NULL);
#endif
 {
  osg::Vec3& tolua_ret = (osg::Vec3&)  self->getContactTorque();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"osg::Vec3");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContactTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getType of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getType00
static int tolua_moodyn_moodyn_Joint_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'",NULL);
#endif
 {
  const moodyn::Joint::JointType& tolua_ret = (const moodyn::Joint::JointType&)  self->getType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchor of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getAnchor00
static int tolua_moodyn_moodyn_Joint_getAnchor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,2,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchor'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAnchor(relative,relativebody1);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchor of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setAnchor00
static int tolua_moodyn_moodyn_Joint_setAnchor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* anchor = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchor'",NULL);
#endif
 {
  self->setAnchor(*anchor,relative,relativebody1);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAxis of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getAxis00
static int tolua_moodyn_moodyn_Joint_getAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,2,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAxis'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAxis(relative,relativebody1);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAxis of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setAxis00
static int tolua_moodyn_moodyn_Joint_setAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* axis = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAxis'",NULL);
#endif
 {
  self->setAxis(*axis,relative,relativebody1);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAxis2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getAxis200
static int tolua_moodyn_moodyn_Joint_getAxis200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,2,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAxis2'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAxis2(relative,relativebody1);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAxis2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAxis2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setAxis200
static int tolua_moodyn_moodyn_Joint_setAxis200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* axis2 = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,true));
  const bool relativebody1 = ((const bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAxis2'",NULL);
#endif
 {
  self->setAxis2(*axis2,relative,relativebody1);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAxis2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setParameter00
static int tolua_moodyn_moodyn_Joint_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Joint::JointParameter parameter = ((moodyn::Joint::JointParameter) (int)  tolua_tonumber(tolua_S,2,0));
  const double value = ((const double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'",NULL);
#endif
 {
  self->setParameter(parameter,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParameter of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getParameter00
static int tolua_moodyn_moodyn_Joint_getParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Joint::JointParameter parameter = ((moodyn::Joint::JointParameter) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParameter'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getParameter(parameter);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody1 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getBody100
static int tolua_moodyn_moodyn_Joint_getBody100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody1'",NULL);
#endif
 {
  moodyn::Body* tolua_ret = (moodyn::Body*)  self->getBody1();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Body");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getBody200
static int tolua_moodyn_moodyn_Joint_getBody200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody2'",NULL);
#endif
 {
  moodyn::Body* tolua_ret = (moodyn::Body*)  self->getBody2();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Body");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attach of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_attach00
static int tolua_moodyn_moodyn_Joint_attach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Body",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"moodyn::Body",1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Body* body1 = ((moodyn::Body*)  tolua_tousertype(tolua_S,2,0));
  moodyn::Body* body2 = ((moodyn::Body*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attach'",NULL);
#endif
 {
  self->attach(body1,body2);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detach of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_detach00
static int tolua_moodyn_moodyn_Joint_detach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detach'",NULL);
#endif
 {
  self->detach();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeflection of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getDeflection00
static int tolua_moodyn_moodyn_Joint_getDeflection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDeflection'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getDeflection();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeflection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeflection2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getDeflection200
static int tolua_moodyn_moodyn_Joint_getDeflection200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDeflection2'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getDeflection2();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeflection2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRate of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getRate00
static int tolua_moodyn_moodyn_Joint_getRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRate'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getRate();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRate2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getRate200
static int tolua_moodyn_moodyn_Joint_getRate200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRate2'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getRate2();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRate2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addForce of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_addForce00
static int tolua_moodyn_moodyn_Joint_addForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const float F1 = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float F2 = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float F3 = ((const float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addForce'",NULL);
#endif
 {
  self->addForce(F1,F2,F3);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRefDeflection of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setRefDeflection00
static int tolua_moodyn_moodyn_Joint_setRefDeflection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRefDeflection'",NULL);
#endif
 {
  self->setRefDeflection(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRefDeflection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRefDeflection of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getRefDeflection00
static int tolua_moodyn_moodyn_Joint_getRefDeflection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Joint* self = (const moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRefDeflection'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getRefDeflection();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRefDeflection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRefDeflection2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setRefDeflection200
static int tolua_moodyn_moodyn_Joint_setRefDeflection200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRefDeflection2'",NULL);
#endif
 {
  self->setRefDeflection2(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRefDeflection2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRefDeflection2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getRefDeflection200
static int tolua_moodyn_moodyn_Joint_getRefDeflection200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Joint* self = (const moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRefDeflection2'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getRefDeflection2();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRefDeflection2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: steer of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_steer00
static int tolua_moodyn_moodyn_Joint_steer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const float deflection = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float velocity = ((const float)  tolua_tonumber(tolua_S,3,0.f));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'steer'",NULL);
#endif
 {
  self->steer(deflection,velocity);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'steer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: steer2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_steer200
static int tolua_moodyn_moodyn_Joint_steer200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const float deflection = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float velocity = ((const float)  tolua_tonumber(tolua_S,3,0.f));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'steer2'",NULL);
#endif
 {
  self->steer2(deflection,velocity);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'steer2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getForce1 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getForce100
static int tolua_moodyn_moodyn_Joint_getForce100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getForce1'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getForce1();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getForce1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getForce2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getForce200
static int tolua_moodyn_moodyn_Joint_getForce200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getForce2'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getForce2();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getForce2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTorque1 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getTorque100
static int tolua_moodyn_moodyn_Joint_getTorque100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTorque1'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getTorque1();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTorque1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTorque2 of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getTorque200
static int tolua_moodyn_moodyn_Joint_getTorque200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTorque2'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getTorque2();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTorque2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBreakImpulse of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setBreakImpulse00
static int tolua_moodyn_moodyn_Joint_setBreakImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const double impulse = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBreakImpulse'",NULL);
#endif
 {
  self->setBreakImpulse(impulse);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBreakImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBreakImpulse of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getBreakImpulse00
static int tolua_moodyn_moodyn_Joint_getBreakImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Joint* self = (const moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBreakImpulse'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getBreakImpulse();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBreakImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBreakAngularImpulse of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_setBreakAngularImpulse00
static int tolua_moodyn_moodyn_Joint_setBreakAngularImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
  const double impulse = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBreakAngularImpulse'",NULL);
#endif
 {
  self->setBreakAngularImpulse(impulse);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBreakAngularImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBreakAngularImpulse of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_getBreakAngularImpulse00
static int tolua_moodyn_moodyn_Joint_getBreakAngularImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Joint* self = (const moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBreakAngularImpulse'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getBreakAngularImpulse();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBreakAngularImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: realize of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_realize00
static int tolua_moodyn_moodyn_Joint_realize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'realize'",NULL);
#endif
 {
  self->realize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'realize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unrealize of class  moodyn::Joint */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Joint_unrealize00
static int tolua_moodyn_moodyn_Joint_unrealize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::Joint* self = (moodyn::Joint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unrealize'",NULL);
#endif
 {
  self->unrealize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unrealize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* vel = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'",NULL);
#endif
 {
  self->setVelocity(*vel,relative);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity01
static int tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const double x = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double y = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double z = ((const double)  tolua_tonumber(tolua_S,4,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'",NULL);
#endif
 {
  self->setVelocity(x,y,z,relative);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* angvel = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularVelocity'",NULL);
#endif
 {
  self->setAngularVelocity(*angvel,relative);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity01
static int tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const double x = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double y = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double z = ((const double)  tolua_tonumber(tolua_S,4,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularVelocity'",NULL);
#endif
 {
  self->setAngularVelocity(x,y,z,relative);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_getVelocity00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_getVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getVelocity(relative);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngularVelocity of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_getAngularVelocity00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_getAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngularVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAngularVelocity(relative);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec3(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec3));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec3");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_getBody00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_getBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody'",NULL);
#endif
 {
  moodyn::Body* tolua_ret = (moodyn::Body*)  self->getBody();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Body");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addJoint of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"moodyn::DynamicPhysicalObject",1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Joint* joint = ((moodyn::Joint*)  tolua_tousertype(tolua_S,2,0));
  moodyn::DynamicPhysicalObject* connection = ((moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addJoint'",NULL);
#endif
 {
  self->addJoint(joint,connection);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addJoint of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint01
static int tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"moon::BaseObject",1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Joint::JointType type = ((moodyn::Joint::JointType) (int)  tolua_tonumber(tolua_S,2,0));
  moon::BaseObject* connection = ((moon::BaseObject*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addJoint'",NULL);
#endif
 {
  self->addJoint(type,connection);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumJoints of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_getNumJoints00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_getNumJoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumJoints'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumJoints();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumJoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getJoint of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_getJoint00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_getJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getJoint'",NULL);
#endif
 {
  moodyn::Joint* tolua_ret = (moodyn::Joint*)  self->getJoint(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Joint");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeJoint of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Joint",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Joint* joint = ((moodyn::Joint*)  tolua_tousertype(tolua_S,2,0));
  const bool otherSide = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeJoint'",NULL);
#endif
 {
  self->removeJoint(joint,otherSide);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeJoints of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoints00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
  unsigned const int num = ((unsigned const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeJoints'",NULL);
#endif
 {
  self->removeJoints(index,num);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeJoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeJoint of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint01
static int tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeJoint'",NULL);
#endif
 {
  self->removeJoint(index);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStatic of class  moodyn::DynamicPhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicPhysicalObject_setStatic00
static int tolua_moodyn_moodyn_DynamicPhysicalObject_setStatic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicPhysicalObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicPhysicalObject* self = (moodyn::DynamicPhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStatic'",NULL);
#endif
 {
  self->setStatic(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStatic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enter of class  moodyn::DynamicVehicle */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicVehicle_enter00
static int tolua_moodyn_moodyn_DynamicVehicle_enter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicVehicle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicVehicle* self = (moodyn::DynamicVehicle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enter'",NULL);
#endif
 {
  self->enter();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: exit of class  moodyn::DynamicVehicle */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicVehicle_exit00
static int tolua_moodyn_moodyn_DynamicVehicle_exit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicVehicle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicVehicle* self = (moodyn::DynamicVehicle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exit'",NULL);
#endif
 {
  self->exit();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: current of class  moodyn::DynamicVehicle */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicVehicle_current00
static int tolua_moodyn_moodyn_DynamicVehicle_current00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moodyn::DynamicVehicle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moon::Vehicle* tolua_ret = (moon::Vehicle*)  moodyn::DynamicVehicle::current();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Vehicle");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'current'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cycleCameraMode of class  moodyn::DynamicVehicle */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicVehicle_cycleCameraMode00
static int tolua_moodyn_moodyn_DynamicVehicle_cycleCameraMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicVehicle",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicVehicle* self = (moodyn::DynamicVehicle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cycleCameraMode'",NULL);
#endif
 {
  self->cycleCameraMode();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cycleCameraMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getControl of class  moodyn::DynamicVehicle */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_DynamicVehicle_getControl00
static int tolua_moodyn_moodyn_DynamicVehicle_getControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::DynamicVehicle",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::DynamicVehicle* self = (moodyn::DynamicVehicle*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getControl'",NULL);
#endif
 {
  moon::Control* tolua_ret = (moon::Control*)  self->getControl(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Control");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGeometry of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_setGeometry00
static int tolua_moodyn_moodyn_PhysicalObject_setGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moodyn::Geometry",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  moodyn::Geometry* geometry = ((moodyn::Geometry*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGeometry'",NULL);
#endif
 {
  self->setGeometry(geometry);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGeometry of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_getGeometry00
static int tolua_moodyn_moodyn_PhysicalObject_getGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGeometry'",NULL);
#endif
 {
  moodyn::Geometry* tolua_ret = (moodyn::Geometry*)  self->getGeometry();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moodyn::Geometry");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: damage of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_damage00
static int tolua_moodyn_moodyn_PhysicalObject_damage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const float magnitude = ((const float)  tolua_tonumber(tolua_S,2,0));
  unsigned const int category = ((unsigned const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'damage'",NULL);
#endif
 {
  self->damage(magnitude,category);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'damage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHealth of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_getHealth00
static int tolua_moodyn_moodyn_PhysicalObject_getHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::PhysicalObject* self = (const moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHealth'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getHealth();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHealth of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_setHealth00
static int tolua_moodyn_moodyn_PhysicalObject_setHealth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHealth'",NULL);
#endif
 {
  self->setHealth(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHealth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_destroy00
static int tolua_moodyn_moodyn_PhysicalObject_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'",NULL);
#endif
 {
  self->destroy();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDestroyed of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_isDestroyed00
static int tolua_moodyn_moodyn_PhysicalObject_isDestroyed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::PhysicalObject* self = (const moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDestroyed'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isDestroyed();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDestroyed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDamageResistance of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_setDamageResistance00
static int tolua_moodyn_moodyn_PhysicalObject_setDamageResistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moodyn::PhysicalObject* self = (moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  const float ratio = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float threshold = ((const float)  tolua_tonumber(tolua_S,3,0.f));
  unsigned const int category = ((unsigned const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDamageResistance'",NULL);
#endif
 {
  self->setDamageResistance(ratio,threshold,category);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDamageResistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHealthReduction of class  moodyn::PhysicalObject */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_PhysicalObject_getHealthReduction00
static int tolua_moodyn_moodyn_PhysicalObject_getHealthReduction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::PhysicalObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::PhysicalObject* self = (const moodyn::PhysicalObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int category = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHealthReduction'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getHealthReduction(category);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHealthReduction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOnGround of class  moodyn::Thruster */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Thruster_isOnGround00
static int tolua_moodyn_moodyn_Thruster_isOnGround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Thruster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Thruster* self = (const moodyn::Thruster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOnGround'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isOnGround();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOnGround'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isControlsFlipped of class  moodyn::Thruster */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Thruster_isControlsFlipped00
static int tolua_moodyn_moodyn_Thruster_isControlsFlipped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Thruster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Thruster* self = (const moodyn::Thruster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isControlsFlipped'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isControlsFlipped();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isControlsFlipped'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRecoveringFCS of class  moodyn::Thruster */
#ifndef TOLUA_DISABLE_tolua_moodyn_moodyn_Thruster_isRecoveringFCS00
static int tolua_moodyn_moodyn_Thruster_isRecoveringFCS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moodyn::Thruster",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moodyn::Thruster* self = (const moodyn::Thruster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRecoveringFCS'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isRecoveringFCS();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRecoveringFCS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_moodyn_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"Body","moodyn::Body","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"Body");
   tolua_function(tolua_S,"realize",tolua_moodyn_moodyn_Body_realize00);
   tolua_function(tolua_S,"unrealize",tolua_moodyn_moodyn_Body_unrealize00);
   tolua_function(tolua_S,"isRealized",tolua_moodyn_moodyn_Body_isRealized00);
   tolua_function(tolua_S,"setTransformation",tolua_moodyn_moodyn_Body_setTransformation00);
   tolua_function(tolua_S,"getTransformation",tolua_moodyn_moodyn_Body_getTransformation00);
   tolua_function(tolua_S,"setPosition",tolua_moodyn_moodyn_Body_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_moodyn_moodyn_Body_getPosition00);
   tolua_function(tolua_S,"setRotation",tolua_moodyn_moodyn_Body_setRotation00);
   tolua_function(tolua_S,"getRotation",tolua_moodyn_moodyn_Body_getRotation00);
   tolua_function(tolua_S,"setVelocity",tolua_moodyn_moodyn_Body_setVelocity00);
   tolua_function(tolua_S,"getVelocity",tolua_moodyn_moodyn_Body_getVelocity00);
   tolua_function(tolua_S,"setAngularVelocity",tolua_moodyn_moodyn_Body_setAngularVelocity00);
   tolua_function(tolua_S,"getAngularVelocity",tolua_moodyn_moodyn_Body_getAngularVelocity00);
   tolua_function(tolua_S,"addForce",tolua_moodyn_moodyn_Body_addForce00);
   tolua_function(tolua_S,"addForceAt",tolua_moodyn_moodyn_Body_addForceAt00);
   tolua_function(tolua_S,"addForceAt",tolua_moodyn_moodyn_Body_addForceAt01);
   tolua_function(tolua_S,"addTorque",tolua_moodyn_moodyn_Body_addTorque00);
   tolua_function(tolua_S,"setForce",tolua_moodyn_moodyn_Body_setForce00);
   tolua_function(tolua_S,"setTorque",tolua_moodyn_moodyn_Body_setTorque00);
   tolua_function(tolua_S,"getForce",tolua_moodyn_moodyn_Body_getForce00);
   tolua_function(tolua_S,"getTorque",tolua_moodyn_moodyn_Body_getTorque00);
   tolua_function(tolua_S,"getMass",tolua_moodyn_moodyn_Body_getMass00);
   tolua_function(tolua_S,"setMass",tolua_moodyn_moodyn_Body_setMass00);
   tolua_function(tolua_S,"isEnabled",tolua_moodyn_moodyn_Body_isEnabled00);
   tolua_function(tolua_S,"enable",tolua_moodyn_moodyn_Body_enable00);
   tolua_function(tolua_S,"disable",tolua_moodyn_moodyn_Body_disable00);
   tolua_function(tolua_S,"isConnectedTo",tolua_moodyn_moodyn_Body_isConnectedTo00);
   tolua_function(tolua_S,"id",tolua_moodyn_moodyn_Body_id00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"Geometry","moodyn::Geometry","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"Geometry");
   tolua_constant(tolua_S,"NONE",moodyn::Geometry::NONE);
   tolua_constant(tolua_S,"BOX",moodyn::Geometry::BOX);
   tolua_constant(tolua_S,"SPHERE",moodyn::Geometry::SPHERE);
   tolua_constant(tolua_S,"CAPSULE",moodyn::Geometry::CAPSULE);
   tolua_constant(tolua_S,"CYLINDER",moodyn::Geometry::CYLINDER);
   tolua_constant(tolua_S,"PLANE",moodyn::Geometry::PLANE);
   tolua_constant(tolua_S,"MESH",moodyn::Geometry::MESH);
   tolua_constant(tolua_S,"HEIGHTFIELD",moodyn::Geometry::HEIGHTFIELD);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Shape","moodyn::Geometry::Shape","",tolua_collect_moodyn__Geometry__Shape);
   #else
   tolua_cclass(tolua_S,"Shape","moodyn::Geometry::Shape","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Shape");
    tolua_function(tolua_S,"new",tolua_moodyn_moodyn_Geometry_Shape_new00);
    tolua_function(tolua_S,"new_local",tolua_moodyn_moodyn_Geometry_Shape_new00_local);
    tolua_function(tolua_S,".call",tolua_moodyn_moodyn_Geometry_Shape_new00_local);
    tolua_function(tolua_S,"new",tolua_moodyn_moodyn_Geometry_Shape_new01);
    tolua_function(tolua_S,"new_local",tolua_moodyn_moodyn_Geometry_Shape_new01_local);
    tolua_function(tolua_S,".call",tolua_moodyn_moodyn_Geometry_Shape_new01_local);
    tolua_function(tolua_S,"new",tolua_moodyn_moodyn_Geometry_Shape_new02);
    tolua_function(tolua_S,"new_local",tolua_moodyn_moodyn_Geometry_Shape_new02_local);
    tolua_function(tolua_S,".call",tolua_moodyn_moodyn_Geometry_Shape_new02_local);
    tolua_variable(tolua_S,"type",tolua_get_moodyn__Geometry__Shape_type,tolua_set_moodyn__Geometry__Shape_type);
    tolua_variable(tolua_S,"p1",tolua_get_moodyn__Geometry__Shape_p1,tolua_set_moodyn__Geometry__Shape_p1);
    tolua_variable(tolua_S,"p2",tolua_get_moodyn__Geometry__Shape_p2,tolua_set_moodyn__Geometry__Shape_p2);
    tolua_variable(tolua_S,"p3",tolua_get_moodyn__Geometry__Shape_p3,tolua_set_moodyn__Geometry__Shape_p3);
    tolua_variable(tolua_S,"p4",tolua_get_moodyn__Geometry__Shape_p4,tolua_set_moodyn__Geometry__Shape_p4);
    tolua_variable(tolua_S,"M",tolua_get_moodyn__Geometry__Shape_M,tolua_set_moodyn__Geometry__Shape_M);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"setBody",tolua_moodyn_moodyn_Geometry_setBody00);
   tolua_function(tolua_S,"setBody",tolua_moodyn_moodyn_Geometry_setBody01);
   tolua_function(tolua_S,"getBody",tolua_moodyn_moodyn_Geometry_getBody00);
   tolua_function(tolua_S,"addShape",tolua_moodyn_moodyn_Geometry_addShape00);
   tolua_function(tolua_S,"addShape",tolua_moodyn_moodyn_Geometry_addShape01);
   tolua_function(tolua_S,"addShape",tolua_moodyn_moodyn_Geometry_addShape02);
   tolua_function(tolua_S,"addMesh",tolua_moodyn_moodyn_Geometry_addMesh00);
   tolua_function(tolua_S,"addMesh",tolua_moodyn_moodyn_Geometry_addMesh01);
   tolua_function(tolua_S,"addHeightField",tolua_moodyn_moodyn_Geometry_addHeightField00);
   tolua_function(tolua_S,"addHeightField",tolua_moodyn_moodyn_Geometry_addHeightField01);
   tolua_function(tolua_S,"addHeightField",tolua_moodyn_moodyn_Geometry_addHeightField02);
   tolua_function(tolua_S,"addHeightField",tolua_moodyn_moodyn_Geometry_addHeightField03);
   tolua_function(tolua_S,"merge",tolua_moodyn_moodyn_Geometry_merge00);
   tolua_function(tolua_S,"merge",tolua_moodyn_moodyn_Geometry_merge01);
   tolua_function(tolua_S,"getShape",tolua_moodyn_moodyn_Geometry_getShape00);
   tolua_function(tolua_S,"removeShape",tolua_moodyn_moodyn_Geometry_removeShape00);
   tolua_function(tolua_S,"getNumShapes",tolua_moodyn_moodyn_Geometry_getNumShapes00);
   tolua_function(tolua_S,"setTransformation",tolua_moodyn_moodyn_Geometry_setTransformation00);
   tolua_function(tolua_S,"id",tolua_moodyn_moodyn_Geometry_id00);
   tolua_function(tolua_S,"getPosition",tolua_moodyn_moodyn_Geometry_getPosition00);
   tolua_function(tolua_S,"transform",tolua_moodyn_moodyn_Geometry_transform00);
   tolua_function(tolua_S,"isEnabled",tolua_moodyn_moodyn_Geometry_isEnabled00);
   tolua_function(tolua_S,"enable",tolua_moodyn_moodyn_Geometry_enable00);
   tolua_function(tolua_S,"disable",tolua_moodyn_moodyn_Geometry_disable00);
   tolua_function(tolua_S,"realize",tolua_moodyn_moodyn_Geometry_realize00);
   tolua_function(tolua_S,"unrealize",tolua_moodyn_moodyn_Geometry_unrealize00);
   tolua_function(tolua_S,"isRealized",tolua_moodyn_moodyn_Geometry_isRealized00);
   tolua_function(tolua_S,"checkContact",tolua_moodyn_moodyn_Geometry_checkContact00);
   tolua_function(tolua_S,"setMaterialID",tolua_moodyn_moodyn_Geometry_setMaterialID00);
   tolua_function(tolua_S,"getMaterialID",tolua_moodyn_moodyn_Geometry_getMaterialID00);
   tolua_function(tolua_S,"setContactConnected",tolua_moodyn_moodyn_Geometry_setContactConnected00);
   tolua_function(tolua_S,"shouldContactConnected",tolua_moodyn_moodyn_Geometry_shouldContactConnected00);
   tolua_function(tolua_S,"createDebugNode",tolua_moodyn_moodyn_Geometry_createDebugNode00);
   tolua_function(tolua_S,"addBoundingSphere",tolua_moodyn_moodyn_Geometry_addBoundingSphere00);
   tolua_function(tolua_S,"addBoundingSphere",tolua_moodyn_moodyn_Geometry_addBoundingSphere01);
   tolua_function(tolua_S,"addBoundingBox",tolua_moodyn_moodyn_Geometry_addBoundingBox00);
   tolua_function(tolua_S,"addBoundingBox",tolua_moodyn_moodyn_Geometry_addBoundingBox01);
   tolua_function(tolua_S,"addShapesFromBounds",tolua_moodyn_moodyn_Geometry_addShapesFromBounds00);
   tolua_function(tolua_S,"addShapesFromBounds",tolua_moodyn_moodyn_Geometry_addShapesFromBounds01);
   tolua_function(tolua_S,"setUserData",tolua_moodyn_moodyn_Geometry_setUserData00);
   tolua_function(tolua_S,"getUserData",tolua_moodyn_moodyn_Geometry_getUserData00);
   tolua_function(tolua_S,"getContactForce",tolua_moodyn_moodyn_Geometry_getContactForce00);
   tolua_function(tolua_S,"getContactTorque",tolua_moodyn_moodyn_Geometry_getContactTorque00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"Joint","moodyn::Joint","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"Joint");
   tolua_constant(tolua_S,"NONE",moodyn::Joint::NONE);
   tolua_constant(tolua_S,"BALL",moodyn::Joint::BALL);
   tolua_constant(tolua_S,"HINGE",moodyn::Joint::HINGE);
   tolua_constant(tolua_S,"SLIDER",moodyn::Joint::SLIDER);
   tolua_constant(tolua_S,"UNIVERSAL",moodyn::Joint::UNIVERSAL);
   tolua_constant(tolua_S,"HINGE2",moodyn::Joint::HINGE2);
   tolua_constant(tolua_S,"FIXED",moodyn::Joint::FIXED);
   tolua_constant(tolua_S,"AMOTOR",moodyn::Joint::AMOTOR);
   tolua_constant(tolua_S,"LOSTOP",moodyn::Joint::LOSTOP);
   tolua_constant(tolua_S,"HISTOP",moodyn::Joint::HISTOP);
   tolua_constant(tolua_S,"VELOCITY",moodyn::Joint::VELOCITY);
   tolua_constant(tolua_S,"MAXFORCE",moodyn::Joint::MAXFORCE);
   tolua_constant(tolua_S,"FUDGE",moodyn::Joint::FUDGE);
   tolua_constant(tolua_S,"BOUNCE",moodyn::Joint::BOUNCE);
   tolua_constant(tolua_S,"CFM",moodyn::Joint::CFM);
   tolua_constant(tolua_S,"STOP_ERP",moodyn::Joint::STOP_ERP);
   tolua_constant(tolua_S,"STOP_CFM",moodyn::Joint::STOP_CFM);
   tolua_constant(tolua_S,"SUSPENSION_ERP",moodyn::Joint::SUSPENSION_ERP);
   tolua_constant(tolua_S,"SUSPENSION_CFM",moodyn::Joint::SUSPENSION_CFM);
   tolua_constant(tolua_S,"LOSTOP2",moodyn::Joint::LOSTOP2);
   tolua_constant(tolua_S,"HISTOP2",moodyn::Joint::HISTOP2);
   tolua_constant(tolua_S,"VELOCITY2",moodyn::Joint::VELOCITY2);
   tolua_constant(tolua_S,"MAXFORCE2",moodyn::Joint::MAXFORCE2);
   tolua_constant(tolua_S,"FUDGE2",moodyn::Joint::FUDGE2);
   tolua_constant(tolua_S,"BOUNCE2",moodyn::Joint::BOUNCE2);
   tolua_constant(tolua_S,"CFM2",moodyn::Joint::CFM2);
   tolua_constant(tolua_S,"STOP_ERP2",moodyn::Joint::STOP_ERP2);
   tolua_constant(tolua_S,"STOP_CFM2",moodyn::Joint::STOP_CFM2);
   tolua_constant(tolua_S,"SUSPENSION_ERP2",moodyn::Joint::SUSPENSION_ERP2);
   tolua_constant(tolua_S,"SUSPENSION_CFM2",moodyn::Joint::SUSPENSION_CFM2);
   tolua_constant(tolua_S,"LOSTOP3",moodyn::Joint::LOSTOP3);
   tolua_constant(tolua_S,"HISTOP3",moodyn::Joint::HISTOP3);
   tolua_constant(tolua_S,"VELOCITY3",moodyn::Joint::VELOCITY3);
   tolua_constant(tolua_S,"MAXFORCE3",moodyn::Joint::MAXFORCE3);
   tolua_constant(tolua_S,"FUDGE3",moodyn::Joint::FUDGE3);
   tolua_constant(tolua_S,"BOUNCE3",moodyn::Joint::BOUNCE3);
   tolua_constant(tolua_S,"CFM3",moodyn::Joint::CFM3);
   tolua_constant(tolua_S,"STOP_ERP3",moodyn::Joint::STOP_ERP3);
   tolua_constant(tolua_S,"STOP_CFM3",moodyn::Joint::STOP_CFM3);
   tolua_constant(tolua_S,"SUSPENSION_ERP3",moodyn::Joint::SUSPENSION_ERP3);
   tolua_constant(tolua_S,"SUSPENSION_CFM3",moodyn::Joint::SUSPENSION_CFM3);
   tolua_constant(tolua_S,"_END_ODE_PARAMETERS",moodyn::Joint::_END_ODE_PARAMETERS);
   tolua_constant(tolua_S,"SPRING",moodyn::Joint::SPRING);
   tolua_constant(tolua_S,"DAMP",moodyn::Joint::DAMP);
   tolua_constant(tolua_S,"SPRING2",moodyn::Joint::SPRING2);
   tolua_constant(tolua_S,"DAMP2",moodyn::Joint::DAMP2);
   tolua_constant(tolua_S,"STEER_VELOCITY",moodyn::Joint::STEER_VELOCITY);
   tolua_constant(tolua_S,"STEER_VELOCITY2",moodyn::Joint::STEER_VELOCITY2);
   tolua_constant(tolua_S,"STEER_TOLERANCE",moodyn::Joint::STEER_TOLERANCE);
   tolua_constant(tolua_S,"STEER_TOLERANCE2",moodyn::Joint::STEER_TOLERANCE2);
   tolua_function(tolua_S,"getType",tolua_moodyn_moodyn_Joint_getType00);
   tolua_function(tolua_S,"getAnchor",tolua_moodyn_moodyn_Joint_getAnchor00);
   tolua_function(tolua_S,"setAnchor",tolua_moodyn_moodyn_Joint_setAnchor00);
   tolua_function(tolua_S,"getAxis",tolua_moodyn_moodyn_Joint_getAxis00);
   tolua_function(tolua_S,"setAxis",tolua_moodyn_moodyn_Joint_setAxis00);
   tolua_function(tolua_S,"getAxis2",tolua_moodyn_moodyn_Joint_getAxis200);
   tolua_function(tolua_S,"setAxis2",tolua_moodyn_moodyn_Joint_setAxis200);
   tolua_function(tolua_S,"setParameter",tolua_moodyn_moodyn_Joint_setParameter00);
   tolua_function(tolua_S,"getParameter",tolua_moodyn_moodyn_Joint_getParameter00);
   tolua_function(tolua_S,"getBody1",tolua_moodyn_moodyn_Joint_getBody100);
   tolua_function(tolua_S,"getBody2",tolua_moodyn_moodyn_Joint_getBody200);
   tolua_function(tolua_S,"attach",tolua_moodyn_moodyn_Joint_attach00);
   tolua_function(tolua_S,"detach",tolua_moodyn_moodyn_Joint_detach00);
   tolua_function(tolua_S,"getDeflection",tolua_moodyn_moodyn_Joint_getDeflection00);
   tolua_function(tolua_S,"getDeflection2",tolua_moodyn_moodyn_Joint_getDeflection200);
   tolua_function(tolua_S,"getRate",tolua_moodyn_moodyn_Joint_getRate00);
   tolua_function(tolua_S,"getRate2",tolua_moodyn_moodyn_Joint_getRate200);
   tolua_function(tolua_S,"addForce",tolua_moodyn_moodyn_Joint_addForce00);
   tolua_function(tolua_S,"setRefDeflection",tolua_moodyn_moodyn_Joint_setRefDeflection00);
   tolua_function(tolua_S,"getRefDeflection",tolua_moodyn_moodyn_Joint_getRefDeflection00);
   tolua_function(tolua_S,"setRefDeflection2",tolua_moodyn_moodyn_Joint_setRefDeflection200);
   tolua_function(tolua_S,"getRefDeflection2",tolua_moodyn_moodyn_Joint_getRefDeflection200);
   tolua_function(tolua_S,"steer",tolua_moodyn_moodyn_Joint_steer00);
   tolua_function(tolua_S,"steer2",tolua_moodyn_moodyn_Joint_steer200);
   tolua_function(tolua_S,"getForce1",tolua_moodyn_moodyn_Joint_getForce100);
   tolua_function(tolua_S,"getForce2",tolua_moodyn_moodyn_Joint_getForce200);
   tolua_function(tolua_S,"getTorque1",tolua_moodyn_moodyn_Joint_getTorque100);
   tolua_function(tolua_S,"getTorque2",tolua_moodyn_moodyn_Joint_getTorque200);
   tolua_function(tolua_S,"setBreakImpulse",tolua_moodyn_moodyn_Joint_setBreakImpulse00);
   tolua_function(tolua_S,"getBreakImpulse",tolua_moodyn_moodyn_Joint_getBreakImpulse00);
   tolua_function(tolua_S,"setBreakAngularImpulse",tolua_moodyn_moodyn_Joint_setBreakAngularImpulse00);
   tolua_function(tolua_S,"getBreakAngularImpulse",tolua_moodyn_moodyn_Joint_getBreakAngularImpulse00);
   tolua_function(tolua_S,"realize",tolua_moodyn_moodyn_Joint_realize00);
   tolua_function(tolua_S,"unrealize",tolua_moodyn_moodyn_Joint_unrealize00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"DynamicPhysicalObject","moodyn::DynamicPhysicalObject","moodyn::PhysicalObject",NULL);
  tolua_beginmodule(tolua_S,"DynamicPhysicalObject");
   tolua_function(tolua_S,"setVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity00);
   tolua_function(tolua_S,"setVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_setVelocity01);
   tolua_function(tolua_S,"setAngularVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity00);
   tolua_function(tolua_S,"setAngularVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_setAngularVelocity01);
   tolua_function(tolua_S,"getVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_getVelocity00);
   tolua_function(tolua_S,"getAngularVelocity",tolua_moodyn_moodyn_DynamicPhysicalObject_getAngularVelocity00);
   tolua_function(tolua_S,"getBody",tolua_moodyn_moodyn_DynamicPhysicalObject_getBody00);
   tolua_function(tolua_S,"addJoint",tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint00);
   tolua_function(tolua_S,"addJoint",tolua_moodyn_moodyn_DynamicPhysicalObject_addJoint01);
   tolua_function(tolua_S,"getNumJoints",tolua_moodyn_moodyn_DynamicPhysicalObject_getNumJoints00);
   tolua_function(tolua_S,"getJoint",tolua_moodyn_moodyn_DynamicPhysicalObject_getJoint00);
   tolua_function(tolua_S,"removeJoint",tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint00);
   tolua_function(tolua_S,"removeJoints",tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoints00);
   tolua_function(tolua_S,"removeJoint",tolua_moodyn_moodyn_DynamicPhysicalObject_removeJoint01);
   tolua_function(tolua_S,"setStatic",tolua_moodyn_moodyn_DynamicPhysicalObject_setStatic00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"DynamicVehicle","moodyn::DynamicVehicle","moodyn::DynamicPhysicalObject",NULL);
  tolua_beginmodule(tolua_S,"DynamicVehicle");
   tolua_function(tolua_S,"enter",tolua_moodyn_moodyn_DynamicVehicle_enter00);
   tolua_function(tolua_S,"exit",tolua_moodyn_moodyn_DynamicVehicle_exit00);
   tolua_function(tolua_S,"current",tolua_moodyn_moodyn_DynamicVehicle_current00);
   tolua_function(tolua_S,"cycleCameraMode",tolua_moodyn_moodyn_DynamicVehicle_cycleCameraMode00);
   tolua_function(tolua_S,"getControl",tolua_moodyn_moodyn_DynamicVehicle_getControl00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"PhysicalObject","moodyn::PhysicalObject","moon::KinematicObject",NULL);
  tolua_beginmodule(tolua_S,"PhysicalObject");
   tolua_function(tolua_S,"setGeometry",tolua_moodyn_moodyn_PhysicalObject_setGeometry00);
   tolua_function(tolua_S,"getGeometry",tolua_moodyn_moodyn_PhysicalObject_getGeometry00);
   tolua_function(tolua_S,"damage",tolua_moodyn_moodyn_PhysicalObject_damage00);
   tolua_function(tolua_S,"getHealth",tolua_moodyn_moodyn_PhysicalObject_getHealth00);
   tolua_function(tolua_S,"setHealth",tolua_moodyn_moodyn_PhysicalObject_setHealth00);
   tolua_function(tolua_S,"destroy",tolua_moodyn_moodyn_PhysicalObject_destroy00);
   tolua_function(tolua_S,"isDestroyed",tolua_moodyn_moodyn_PhysicalObject_isDestroyed00);
   tolua_function(tolua_S,"setDamageResistance",tolua_moodyn_moodyn_PhysicalObject_setDamageResistance00);
   tolua_function(tolua_S,"getHealthReduction",tolua_moodyn_moodyn_PhysicalObject_getHealthReduction00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moodyn",0);
 tolua_beginmodule(tolua_S,"moodyn");
  tolua_cclass(tolua_S,"Thruster","moodyn::Thruster","moodyn::DynamicVehicle",NULL);
  tolua_beginmodule(tolua_S,"Thruster");
   tolua_function(tolua_S,"isOnGround",tolua_moodyn_moodyn_Thruster_isOnGround00);
   tolua_function(tolua_S,"isControlsFlipped",tolua_moodyn_moodyn_Thruster_isControlsFlipped00);
   tolua_function(tolua_S,"isRecoveringFCS",tolua_moodyn_moodyn_Thruster_isRecoveringFCS00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_moodyn (lua_State* tolua_S) {
 return tolua_moodyn_open(tolua_S);
};
#endif

