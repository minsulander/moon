/*
** Lua binding: moon
** Generated automatically by tolua++-1.0.92-moon-customized on Tue Dec 22 16:21:28 2009.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_moon_open (lua_State* tolua_S);

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/MatrixTransform>
#include <mlog/Log.h>
#include <moonet/Client.h>
#include <moonet/NetworkManager.h>
#include <moonet/Player.h>
#include "mdraw/ConsoleWindow.h"
#include <mdraw/FadeText.h>
#include <mdraw/utils.h>
#include <moon/components/Component.h>
#include <moon/components/VisualModel.h>
#include <moon/components/Instrument.h>
#include <moon/objects/BaseObject.h>
#include <moon/objects/VisualObject.h>
#include <moon/objects/KinematicObject.h>
#include <moon/objects/Camera.h>
#include <moon/Parameter.h>
#include <moon/Scenario.h>
#include "moon/Application.h"
#include <moon/Viewer.h>
#include <moon/EditMode.h>
#include <moon/Scheduler.h>
#include <moon/SimulationManager.h>
#include <moon/NetworkGame.h>
#include <moon/Control.h>
#include <moon/Plugin.h>
#include <moon/PluginManager.h>

/* function to release collected object via destructor */
#ifdef __cplusplus

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

static int tolua_collect_osg__Vec4 (lua_State* tolua_S)
{
 osg::Vec4* self = (osg::Vec4*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_osg__BoundingBox (lua_State* tolua_S)
{
 osg::BoundingBox* self = (osg::BoundingBox*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"moon::Camera");
 tolua_usertype(tolua_S,"moon::Scheduler");
 tolua_usertype(tolua_S,"moon::BaseObject");
 tolua_usertype(tolua_S,"moon::Instrument");
 tolua_usertype(tolua_S,"osg::Node::NodeMask");
 tolua_usertype(tolua_S,"osg::Vec4");
 tolua_usertype(tolua_S,"osg::BoundingBox");
 tolua_usertype(tolua_S,"mdraw::ConsoleWindow");
 tolua_usertype(tolua_S,"moonet::Player");
 tolua_usertype(tolua_S,"osg::Node");
 tolua_usertype(tolua_S,"moon::Parameter");
 tolua_usertype(tolua_S,"moon::Viewer");
 tolua_usertype(tolua_S,"osgText::Text");
 tolua_usertype(tolua_S,"moon::Application");
 tolua_usertype(tolua_S,"moon::VisualModel");
 tolua_usertype(tolua_S,"moon::Control");
 tolua_usertype(tolua_S,"moon::EditHandler");
 tolua_usertype(tolua_S,"moonet::NetworkManager");
 tolua_usertype(tolua_S,"osg::Geode");
 tolua_usertype(tolua_S,"osg::Vec3");
 tolua_usertype(tolua_S,"moon::ComponentContainer");
 tolua_usertype(tolua_S,"moon::Plugin");
 tolua_usertype(tolua_S,"FactoryProduct");
 tolua_usertype(tolua_S,"moon::Component");
 tolua_usertype(tolua_S,"moon::NetworkGame");
 tolua_usertype(tolua_S,"moon::SimulationManager");
 tolua_usertype(tolua_S,"osgText::TextBase");
 tolua_usertype(tolua_S,"osg::Quat");
 tolua_usertype(tolua_S,"moonet::Client");
 tolua_usertype(tolua_S,"moon::PluginManager");
 tolua_usertype(tolua_S,"moon::KinematicObject");
 tolua_usertype(tolua_S,"osg::Transform");
 tolua_usertype(tolua_S,"osg::Object");
 tolua_usertype(tolua_S,"osg::MatrixTransform");
 tolua_usertype(tolua_S,"osg::Group");
 tolua_usertype(tolua_S,"moon::Scenario");
 tolua_usertype(tolua_S,"osg::Matrix");
 tolua_usertype(tolua_S,"moon::VisualObject");
}

/* method: new of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_new00
static int tolua_moon_osg_Vec3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Vec3* tolua_ret = (osg::Vec3*)  new osg::Vec3();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Vec3");
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

/* method: new_local of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_new00_local
static int tolua_moon_osg_Vec3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Vec3* tolua_ret = (osg::Vec3*)  new osg::Vec3();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Vec3");
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

/* method: new of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_new01
static int tolua_moon_osg_Vec3_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
 {
  osg::Vec3* tolua_ret = (osg::Vec3*)  new osg::Vec3(x,y,z);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Vec3");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Vec3_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_new01_local
static int tolua_moon_osg_Vec3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
 {
  osg::Vec3* tolua_ret = (osg::Vec3*)  new osg::Vec3(x,y,z);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Vec3");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Vec3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_set00
static int tolua_moon_osg_Vec3_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
 {
  self->set(x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_x00
static int tolua_moon_osg_Vec3_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'",NULL);
#endif
 {
  float tolua_ret = (float)  self->x();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_y00
static int tolua_moon_osg_Vec3_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'",NULL);
#endif
 {
  float tolua_ret = (float)  self->y();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: z of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_z00
static int tolua_moon_osg_Vec3_z00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'z'",NULL);
#endif
 {
  float tolua_ret = (float)  self->z();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'z'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: valid of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_valid00
static int tolua_moon_osg_Vec3_valid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'valid'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->valid();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'valid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isNaN of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_isNaN00
static int tolua_moon_osg_Vec3_isNaN00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isNaN'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isNaN();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isNaN'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__geti00
static int tolua_moon_osg_Vec3__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
 {
  float tolua_ret = (float)  self->operator[](i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__eq00
static int tolua_moon_osg_Vec3__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* v = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->operator==(*v);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__lt00
static int tolua_moon_osg_Vec3__lt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* v = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->operator<(*v);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.lt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__mul00
static int tolua_moon_osg_Vec3__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* v = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
 {
  float tolua_ret = (float)  self->operator*(*v);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__mul01
static int tolua_moon_osg_Vec3__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  float f = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->operator*(f);
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
tolua_lerror:
 return tolua_moon_osg_Vec3__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__div00
static int tolua_moon_osg_Vec3__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  float f = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->operator/(f);
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
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__add00
static int tolua_moon_osg_Vec3__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3 tolua_var_1 = *((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->operator+(tolua_var_1);
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
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3__sub00
static int tolua_moon_osg_Vec3__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* self = (const osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3 tolua_var_2 = *((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->operator-(tolua_var_2);
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
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_length00
static int tolua_moon_osg_Vec3_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'",NULL);
#endif
 {
  float tolua_ret = (float)  self->length();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length2 of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_length200
static int tolua_moon_osg_Vec3_length200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length2'",NULL);
#endif
 {
  float tolua_ret = (float)  self->length2();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalize of class  osg::Vec3 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec3_normalize00
static int tolua_moon_osg_Vec3_normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec3* self = (osg::Vec3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'",NULL);
#endif
 {
  float tolua_ret = (float)  self->normalize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_new00
static int tolua_moon_osg_Vec4_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Vec4* tolua_ret = (osg::Vec4*)  new osg::Vec4();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Vec4");
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

/* method: new_local of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_new00_local
static int tolua_moon_osg_Vec4_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Vec4* tolua_ret = (osg::Vec4*)  new osg::Vec4();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Vec4");
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

/* method: new of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_new01
static int tolua_moon_osg_Vec4_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  osg::Vec4* tolua_ret = (osg::Vec4*)  new osg::Vec4(x,y,z,w);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Vec4");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Vec4_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_new01_local
static int tolua_moon_osg_Vec4_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  osg::Vec4* tolua_ret = (osg::Vec4*)  new osg::Vec4(x,y,z,w);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Vec4");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Vec4_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_x00
static int tolua_moon_osg_Vec4_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec4* self = (osg::Vec4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'",NULL);
#endif
 {
  float tolua_ret = (float)  self->x();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_y00
static int tolua_moon_osg_Vec4_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec4* self = (osg::Vec4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'",NULL);
#endif
 {
  float tolua_ret = (float)  self->y();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: z of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_z00
static int tolua_moon_osg_Vec4_z00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec4* self = (osg::Vec4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'z'",NULL);
#endif
 {
  float tolua_ret = (float)  self->z();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'z'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: w of class  osg::Vec4 */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Vec4_w00
static int tolua_moon_osg_Vec4_w00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Vec4* self = (osg::Vec4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'w'",NULL);
#endif
 {
  float tolua_ret = (float)  self->w();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'w'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_new00
static int tolua_moon_osg_Quat_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Quat* tolua_ret = (osg::Quat*)  new osg::Quat();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Quat");
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

/* method: new_local of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_new00_local
static int tolua_moon_osg_Quat_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  osg::Quat* tolua_ret = (osg::Quat*)  new osg::Quat();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Quat");
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

/* method: new of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_new01
static int tolua_moon_osg_Quat_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  osg::Quat* tolua_ret = (osg::Quat*)  new osg::Quat(x,y,z,w);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Quat");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Quat_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_new01_local
static int tolua_moon_osg_Quat_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  osg::Quat* tolua_ret = (osg::Quat*)  new osg::Quat(x,y,z,w);
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"osg::Quat");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_osg_Quat_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_x00
static int tolua_moon_osg_Quat_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Quat* self = (osg::Quat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'",NULL);
#endif
 {
  float tolua_ret = (float)  self->x();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_y00
static int tolua_moon_osg_Quat_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Quat* self = (osg::Quat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'",NULL);
#endif
 {
  float tolua_ret = (float)  self->y();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: z of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_z00
static int tolua_moon_osg_Quat_z00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Quat* self = (osg::Quat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'z'",NULL);
#endif
 {
  float tolua_ret = (float)  self->z();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'z'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: w of class  osg::Quat */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Quat_w00
static int tolua_moon_osg_Quat_w00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Quat* self = (osg::Quat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'w'",NULL);
#endif
 {
  float tolua_ret = (float)  self->w();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'w'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  osg::Object */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Object_setName00
static int tolua_moon_osg_Object_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::Object",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::Object* self = (osg::Object*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(name);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  osg::Object */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Object_getName00
static int tolua_moon_osg_Object_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Object",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Object* self = (const osg::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: libraryName of class  osg::Object */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Object_libraryName00
static int tolua_moon_osg_Object_libraryName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Object",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Object* self = (const osg::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'libraryName'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->libraryName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'libraryName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: className of class  osg::Object */
#ifndef TOLUA_DISABLE_tolua_moon_osg_Object_className00
static int tolua_moon_osg_Object_className00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Object",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Object* self = (const osg::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'className'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->className();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'className'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: xMin of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_xMin00
static int tolua_moon_osg_BoundingBox_xMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'xMin'",NULL);
#endif
 {
  float tolua_ret = (float)  self->xMin();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'xMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: xMax of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_xMax00
static int tolua_moon_osg_BoundingBox_xMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'xMax'",NULL);
#endif
 {
  float tolua_ret = (float)  self->xMax();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'xMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: yMin of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_yMin00
static int tolua_moon_osg_BoundingBox_yMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'yMin'",NULL);
#endif
 {
  float tolua_ret = (float)  self->yMin();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'yMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: yMax of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_yMax00
static int tolua_moon_osg_BoundingBox_yMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'yMax'",NULL);
#endif
 {
  float tolua_ret = (float)  self->yMax();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'yMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: zMin of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_zMin00
static int tolua_moon_osg_BoundingBox_zMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'zMin'",NULL);
#endif
 {
  float tolua_ret = (float)  self->zMin();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'zMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: zMax of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_zMax00
static int tolua_moon_osg_BoundingBox_zMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'zMax'",NULL);
#endif
 {
  float tolua_ret = (float)  self->zMax();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'zMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: center of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_center00
static int tolua_moon_osg_BoundingBox_center00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'center'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->center();
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
 tolua_error(tolua_S,"#ferror in function 'center'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: radius of class  osg::BoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_osg_BoundingBox_radius00
static int tolua_moon_osg_BoundingBox_radius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osg::BoundingBox",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osg::BoundingBox* self = (osg::BoundingBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'radius'",NULL);
#endif
 {
  float tolua_ret = (float)  self->radius();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'radius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  osgText::TextBase */
#ifndef TOLUA_DISABLE_tolua_moon_osgText_TextBase_setText00
static int tolua_moon_osgText_TextBase_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osgText::TextBase",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osgText::TextBase* self = (osgText::TextBase*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'",NULL);
#endif
 {
  self->setText(text);
 tolua_pushcppstring(tolua_S,(const char*)text);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  osgText::Text */
#ifndef TOLUA_DISABLE_tolua_moon_osgText_Text_setColor00
static int tolua_moon_osgText_Text_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osgText::Text",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osgText::Text* self = (osgText::Text*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec4 color = *((osg::Vec4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'",NULL);
#endif
 {
  self->setColor(color);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  osgText::Text */
#ifndef TOLUA_DISABLE_tolua_moon_osgText_Text_getColor00
static int tolua_moon_osgText_Text_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"osgText::Text",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  osgText::Text* self = (osgText::Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'",NULL);
#endif
 {
  osg::Vec4 tolua_ret = (osg::Vec4)  self->getColor();
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::Vec4(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec4");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::Vec4));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::Vec4");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: mlog::getDebugLevel */
#ifndef TOLUA_DISABLE_tolua_moon_mlog_getDebugLevel00
static int tolua_moon_mlog_getDebugLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  int tolua_ret = (int)  mlog::getDebugLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDebugLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: mlog::dout */
#ifndef TOLUA_DISABLE_tolua_moon_mlog_dout00
static int tolua_moon_mlog_dout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const int level = ((const int)  tolua_tonumber(tolua_S,1,0));
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  mlog::LogCategory category = ((mlog::LogCategory) (int)  tolua_tonumber(tolua_S,3,mlog::SCRIPT));
 {
  mlog::dout(level,message,category);
 tolua_pushcppstring(tolua_S,(const char*)message);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayer of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_getPlayer00
static int tolua_moon_moonet_Client_getPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Client* self = (moonet::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayer'",NULL);
#endif
 {
  moonet::Player* tolua_ret = (moonet::Player*)  self->getPlayer();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moonet::Player");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_toString00
static int tolua_moon_moonet_Client_toString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Client* self = (moonet::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'",NULL);
#endif
 {
  std::string tolua_ret = (std::string)  self->toString();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnected of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_isConnected00
static int tolua_moon_moonet_Client_isConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Client* self = (moonet::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnected'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConnected();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_getState00
static int tolua_moon_moonet_Client_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Client* self = (moonet::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'",NULL);
#endif
 {
  moonet::ClientState tolua_ret = (moonet::ClientState)  self->getState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: me of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_me00
static int tolua_moon_moonet_Client_me00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moonet::Client* tolua_ret = (moonet::Client*)  moonet::Client::me();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moonet::Client");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'me'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumClients of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_getNumClients00
static int tolua_moon_moonet_Client_getNumClients00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  unsigned int tolua_ret = (unsigned int)  moonet::Client::getNumClients();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumClients'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClient of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_getClient00
static int tolua_moon_moonet_Client_getClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  moonet::Client* tolua_ret = (moonet::Client*)  moonet::Client::getClient(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moonet::Client");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isStillAround of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_isStillAround00
static int tolua_moon_moonet_Client_isStillAround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Client* client = ((moonet::Client*)  tolua_tousertype(tolua_S,2,0));
 {
  bool tolua_ret = (bool)  moonet::Client::isStillAround(client);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isStillAround'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMinimumClientState of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Client_getMinimumClientState00
static int tolua_moon_moonet_Client_getMinimumClientState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moonet::ClientState tolua_ret = (moonet::ClientState)  moonet::Client::getMinimumClientState();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMinimumClientState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isActive of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_isActive00
static int tolua_moon_moonet_NetworkManager_isActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isActive'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isActive();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isServer of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_isServer00
static int tolua_moon_moonet_NetworkManager_isServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isServer'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isServer();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClient of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_isClient00
static int tolua_moon_moonet_NetworkManager_isClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClient'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isClient();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnected of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_isConnected00
static int tolua_moon_moonet_NetworkManager_isConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnected'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConnected();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: chatSend of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_chat00
static int tolua_moon_moonet_NetworkManager_chat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'chatSend'",NULL);
#endif
 {
  self->chatSend(message);
 tolua_pushcppstring(tolua_S,(const char*)message);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'chat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doStatistics of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_doStatistics00
static int tolua_moon_moonet_NetworkManager_doStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,1));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doStatistics'",NULL);
#endif
 {
  self->doStatistics(level);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDoingStatistics of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_isDoingStatistics00
static int tolua_moon_moonet_NetworkManager_isDoingStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDoingStatistics'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isDoingStatistics();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDoingStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: printStatistics of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_printStatistics00
static int tolua_moon_moonet_NetworkManager_printStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'printStatistics'",NULL);
#endif
 {
  self->printStatistics();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'printStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: printClientList of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_printClientList00
static int tolua_moon_moonet_NetworkManager_printClientList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'printClientList'",NULL);
#endif
 {
  self->printClientList();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'printClientList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefaultSerializationInterval of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_getDefaultSerializationInterval00
static int tolua_moon_moonet_NetworkManager_getDefaultSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefaultSerializationInterval'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getDefaultSerializationInterval();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefaultFullSerializationInterval of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_getDefaultFullSerializationInterval00
static int tolua_moon_moonet_NetworkManager_getDefaultFullSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDefaultFullSerializationInterval'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getDefaultFullSerializationInterval();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultFullSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultSerializationInterval of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_NetworkManager_setDefaultSerializationInterval00
static int tolua_moon_moonet_NetworkManager_setDefaultSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::NetworkManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::NetworkManager* self = (moonet::NetworkManager*)  tolua_tousertype(tolua_S,1,0);
  const float seconds = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float fullseconds = ((const float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultSerializationInterval'",NULL);
#endif
 {
  self->setDefaultSerializationInterval(seconds,fullseconds);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  moonet::Player */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Player_setName00
static int tolua_moon_moonet_Player_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Player",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Player* self = (moonet::Player*)  tolua_tousertype(tolua_S,1,0);
  const std::string newname = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(newname);
 tolua_pushcppstring(tolua_S,(const char*)newname);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moonet::Player */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Player_getName00
static int tolua_moon_moonet_Player_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moonet::Player",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moonet::Player* self = (moonet::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: me of class  moonet::Player */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Player_me00
static int tolua_moon_moonet_Player_me00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Player",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moonet::Player* tolua_ret = (moonet::Player*)  moonet::Player::me();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moonet::Player");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'me'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: myName of class  moonet::Player */
#ifndef TOLUA_DISABLE_tolua_moon_moonet_Player_myName00
static int tolua_moon_moonet_Player_myName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moonet::Player",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  const std::string tolua_ret = (const std::string)  moonet::Player::myName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'myName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFont of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_setFont00
static int tolua_moon_mdraw_ConsoleWindow_setFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const std::string file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  double aspect = ((double)  tolua_tonumber(tolua_S,3,0));
  double widthmult = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFont'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->setFont(file,aspect,widthmult);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushcppstring(tolua_S,(const char*)file);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: charHeight of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_charHeight00
static int tolua_moon_mdraw_ConsoleWindow_charHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'charHeight'",NULL);
#endif
 {
  float tolua_ret = (float)  self->charHeight();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'charHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: charWidth of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_charWidth00
static int tolua_moon_mdraw_ConsoleWindow_charWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'charWidth'",NULL);
#endif
 {
  float tolua_ret = (float)  self->charWidth();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'charWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundColor of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_setBackgroundColor00
static int tolua_moon_mdraw_ConsoleWindow_setBackgroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec4* color = ((const osg::Vec4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundColor'",NULL);
#endif
 {
  self->setBackgroundColor(*color);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundColor of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_getBackgroundColor00
static int tolua_moon_mdraw_ConsoleWindow_getBackgroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const mdraw::ConsoleWindow* self = (const mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundColor'",NULL);
#endif
 {
  const osg::Vec4& tolua_ret = (const osg::Vec4&)  self->getBackgroundColor();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const osg::Vec4");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollUp of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollUp00
static int tolua_moon_mdraw_ConsoleWindow_scrollUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int lines = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollUp'",NULL);
#endif
 {
  self->scrollUp(lines);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollDown of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollDown00
static int tolua_moon_mdraw_ConsoleWindow_scrollDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int lines = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollDown'",NULL);
#endif
 {
  self->scrollDown(lines);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pageUp of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_pageUp00
static int tolua_moon_mdraw_ConsoleWindow_pageUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pageUp'",NULL);
#endif
 {
  self->pageUp();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pageUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pageDown of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_pageDown00
static int tolua_moon_mdraw_ConsoleWindow_pageDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pageDown'",NULL);
#endif
 {
  self->pageDown();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pageDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollRight of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollRight00
static int tolua_moon_mdraw_ConsoleWindow_scrollRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int cols = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollRight'",NULL);
#endif
 {
  self->scrollRight(cols);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollLeft of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollLeft00
static int tolua_moon_mdraw_ConsoleWindow_scrollLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int cols = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollLeft'",NULL);
#endif
 {
  self->scrollLeft(cols);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollHome of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollHome00
static int tolua_moon_mdraw_ConsoleWindow_scrollHome00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollHome'",NULL);
#endif
 {
  self->scrollHome();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollHome'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollEnd of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_scrollEnd00
static int tolua_moon_mdraw_ConsoleWindow_scrollEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollEnd'",NULL);
#endif
 {
  self->scrollEnd();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: del of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_del00
static int tolua_moon_mdraw_ConsoleWindow_del00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'del'",NULL);
#endif
 {
  self->del();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'del'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: backSpace of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_backSpace00
static int tolua_moon_mdraw_ConsoleWindow_backSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'backSpace'",NULL);
#endif
 {
  self->backSpace();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'backSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearLine of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_clearLine00
static int tolua_moon_mdraw_ConsoleWindow_clearLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearLine'",NULL);
#endif
 {
  self->clearLine();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cutLine of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_cutLine00
static int tolua_moon_mdraw_ConsoleWindow_cutLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cutLine'",NULL);
#endif
 {
  self->cutLine();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cutLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: upHistory of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_upHistory00
static int tolua_moon_mdraw_ConsoleWindow_upHistory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'upHistory'",NULL);
#endif
 {
  self->upHistory();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'upHistory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: downHistory of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_downHistory00
static int tolua_moon_mdraw_ConsoleWindow_downHistory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'downHistory'",NULL);
#endif
 {
  self->downHistory();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'downHistory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leftCursor of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_leftCursor00
static int tolua_moon_mdraw_ConsoleWindow_leftCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'leftCursor'",NULL);
#endif
 {
  self->leftCursor();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leftCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rightCursor of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_rightCursor00
static int tolua_moon_mdraw_ConsoleWindow_rightCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rightCursor'",NULL);
#endif
 {
  self->rightCursor();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rightCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: putch of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_putch00
static int tolua_moon_mdraw_ConsoleWindow_putch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const char ch = ((const char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'putch'",NULL);
#endif
 {
  self->putch(ch);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'putch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: print of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_print00
static int tolua_moon_mdraw_ConsoleWindow_print00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const std::string s = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'print'",NULL);
#endif
 {
  self->print(s);
 tolua_pushcppstring(tolua_S,(const char*)s);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'print'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resize of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_resize00
static int tolua_moon_mdraw_ConsoleWindow_resize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const int lines = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resize'",NULL);
#endif
 {
  self->resize(lines);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizeUp of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_sizeUp00
static int tolua_moon_mdraw_ConsoleWindow_sizeUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const int lines = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sizeUp'",NULL);
#endif
 {
  self->sizeUp(lines);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizeUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizeDown of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_sizeDown00
static int tolua_moon_mdraw_ConsoleWindow_sizeDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const int lines = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sizeDown'",NULL);
#endif
 {
  self->sizeDown(lines);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizeDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPrompt of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_setPrompt00
static int tolua_moon_mdraw_ConsoleWindow_setPrompt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const std::string prompt = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPrompt'",NULL);
#endif
 {
  self->setPrompt(prompt);
 tolua_pushcppstring(tolua_S,(const char*)prompt);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPrompt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCursorPosition of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_setCursorPosition00
static int tolua_moon_mdraw_ConsoleWindow_setCursorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const int cpos = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCursorPosition'",NULL);
#endif
 {
  self->setCursorPosition(cpos);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCursorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumLines of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_getNumLines00
static int tolua_moon_mdraw_ConsoleWindow_getNumLines00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumLines'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumLines();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumLines'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTop of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_setTop00
static int tolua_moon_mdraw_ConsoleWindow_setTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
  const bool top = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTop'",NULL);
#endif
 {
  self->setTop(top);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTop of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_getTop00
static int tolua_moon_mdraw_ConsoleWindow_getTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTop'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getTop();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_getHeight00
static int tolua_moon_mdraw_ConsoleWindow_getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getHeight();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastLine of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_ConsoleWindow_getLastLine00
static int tolua_moon_mdraw_ConsoleWindow_getLastLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"mdraw::ConsoleWindow",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  mdraw::ConsoleWindow* self = (mdraw::ConsoleWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastLine'",NULL);
#endif
 {
  std::string tolua_ret = (std::string)  self->getLastLine();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: mdraw::notify */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_notify00
static int tolua_moon_mdraw_notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,1,0));
 {
  mdraw::notify(message);
 tolua_pushcppstring(tolua_S,(const char*)message);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: mdraw::notify */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_notify01
static int tolua_moon_mdraw_notify01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec4",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,1,0));
  const osg::Vec4* color = ((const osg::Vec4*)  tolua_tousertype(tolua_S,2,0));
  const double start = ((const double)  tolua_tonumber(tolua_S,3,5));
  const double length = ((const double)  tolua_tonumber(tolua_S,4,1));
 {
  mdraw::notify(message,*color,start,length);
 tolua_pushcppstring(tolua_S,(const char*)message);
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_mdraw_notify00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: mdraw::getNodeString */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_getNodeString00
static int tolua_moon_mdraw_getNodeString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Node",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Node* node = ((const osg::Node*)  tolua_tousertype(tolua_S,1,0));
  const int indentlevel = ((const int)  tolua_tonumber(tolua_S,2,0));
 {
  std::string tolua_ret = (std::string)  mdraw::getNodeString(node,indentlevel);
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: mdraw::getBoundingBox */
#ifndef TOLUA_DISABLE_tolua_moon_mdraw_getBoundingBox00
static int tolua_moon_mdraw_getBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const osg::Node",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Node* node = ((const osg::Node*)  tolua_tousertype(tolua_S,1,0));
 {
  osg::BoundingBox tolua_ret = (osg::BoundingBox)  mdraw::getBoundingBox(node);
 {
#ifdef __cplusplus
 void* tolua_obj = new osg::BoundingBox(tolua_ret);
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::BoundingBox");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(osg::BoundingBox));
 tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"osg::BoundingBox");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTemplate of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_getTemplate00
static int tolua_moon_moon_Component_getTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTemplate'",NULL);
#endif
 {
  moon::Component* tolua_ret = (moon::Component*)  self->getTemplate();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Component");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: libraryName of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_libraryName00
static int tolua_moon_moon_Component_libraryName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'libraryName'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->libraryName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'libraryName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: className of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_className00
static int tolua_moon_moon_Component_className00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'className'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->className();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'className'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_setName00
static int tolua_moon_moon_Component_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(name);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_getName00
static int tolua_moon_moon_Component_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Component* self = (const moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  std::string tolua_ret = (std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: realize of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_realize00
static int tolua_moon_moon_Component_realize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
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

/* method: unrealize of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_unrealize00
static int tolua_moon_moon_Component_unrealize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isRealized of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_isRealized00
static int tolua_moon_moon_Component_isRealized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
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

/* method: update of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_update00
static int tolua_moon_moon_Component_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
  const double dt = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
 {
  self->update(dt);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_reset00
static int tolua_moon_moon_Component_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
 {
  self->reset();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResetState of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_setResetState00
static int tolua_moon_moon_Component_setResetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResetState'",NULL);
#endif
 {
  self->setResetState();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTag of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_setTag00
static int tolua_moon_moon_Component_setTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTag'",NULL);
#endif
 {
  self->setTag(tag,value);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasTag of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_hasTag00
static int tolua_moon_moon_Component_hasTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Component",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Component* self = (const moon::Component*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasTag'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->hasTag(tag);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRealizeMode of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_setRealizeMode00
static int tolua_moon_moon_Component_setRealizeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
  moon::Component::TraversalMode mode = ((moon::Component::TraversalMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRealizeMode'",NULL);
#endif
 {
  self->setRealizeMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRealizeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRealizeMode of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_getRealizeMode00
static int tolua_moon_moon_Component_getRealizeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Component* self = (const moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRealizeMode'",NULL);
#endif
 {
  moon::Component::TraversalMode tolua_ret = (moon::Component::TraversalMode)  self->getRealizeMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRealizeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateMode of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_setUpdateMode00
static int tolua_moon_moon_Component_setUpdateMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Component",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Component* self = (moon::Component*)  tolua_tousertype(tolua_S,1,0);
  moon::Component::TraversalMode mode = ((moon::Component::TraversalMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateMode'",NULL);
#endif
 {
  self->setUpdateMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateMode of class  moon::Component */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Component_getUpdateMode00
static int tolua_moon_moon_Component_getUpdateMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Component* self = (const moon::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateMode'",NULL);
#endif
 {
  moon::Component::TraversalMode tolua_ret = (moon::Component::TraversalMode)  self->getUpdateMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addComponent of class  moon::ComponentContainer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_ComponentContainer_addComponent00
static int tolua_moon_moon_ComponentContainer_addComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::ComponentContainer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::ComponentContainer* self = (moon::ComponentContainer*)  tolua_tousertype(tolua_S,1,0);
  moon::Component* component = ((moon::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addComponent'",NULL);
#endif
 {
  self->addComponent(component);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeComponent of class  moon::ComponentContainer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_ComponentContainer_removeComponent00
static int tolua_moon_moon_ComponentContainer_removeComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::ComponentContainer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::ComponentContainer* self = (moon::ComponentContainer*)  tolua_tousertype(tolua_S,1,0);
  moon::Component* component = ((moon::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeComponent'",NULL);
#endif
 {
  self->removeComponent(component);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumComponents of class  moon::ComponentContainer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_ComponentContainer_getNumComponents00
static int tolua_moon_moon_ComponentContainer_getNumComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::ComponentContainer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::ComponentContainer* self = (const moon::ComponentContainer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumComponents'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumComponents();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  moon::ComponentContainer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_ComponentContainer_getComponent00
static int tolua_moon_moon_ComponentContainer_getComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::ComponentContainer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::ComponentContainer* self = (moon::ComponentContainer*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponent'",NULL);
#endif
 {
  moon::Component* tolua_ret = (moon::Component*)  self->getComponent(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Component");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponentByTag of class  moon::ComponentContainer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_ComponentContainer_getComponentByTag00
static int tolua_moon_moon_ComponentContainer_getComponentByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::ComponentContainer",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::ComponentContainer* self = (moon::ComponentContainer*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponentByTag'",NULL);
#endif
 {
  moon::Component* tolua_ret = (moon::Component*)  self->getComponentByTag(tag);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Component");
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponentByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  moon::VisualModel */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualModel_getNode00
static int tolua_moon_moon_VisualModel_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualModel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualModel* self = (moon::VisualModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'",NULL);
#endif
 {
  osg::Node* tolua_ret = (osg::Node*)  self->getNode();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Node");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInitiallyHidden of class  moon::VisualModel */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualModel_isInitiallyHidden00
static int tolua_moon_moon_VisualModel_isInitiallyHidden00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::VisualModel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::VisualModel* self = (const moon::VisualModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInitiallyHidden'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isInitiallyHidden();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInitiallyHidden'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLabel of class  moon::Instrument */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Instrument_getLabel00
static int tolua_moon_moon_Instrument_getLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Instrument",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Instrument* self = (moon::Instrument*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLabel'",NULL);
#endif
 {
  osgText::Text* tolua_ret = (osgText::Text*)  self->getLabel(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osgText::Text");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRoot of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getRoot00
static int tolua_moon_moon_BaseObject_getRoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRoot'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getRoot();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRoot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTemplate of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getTemplate00
static int tolua_moon_moon_BaseObject_getTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTemplate'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getTemplate();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumChildren of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getNumChildren00
static int tolua_moon_moon_BaseObject_getNumChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumChildren'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumChildren();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_addChild00
static int tolua_moon_moon_BaseObject_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* child = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'",NULL);
#endif
 {
  self->addChild(child);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_removeChild00
static int tolua_moon_moon_BaseObject_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* child = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'",NULL);
#endif
 {
  self->removeChild(child);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChildren of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_removeChildren00
static int tolua_moon_moon_BaseObject_removeChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
  unsigned const int num = ((unsigned const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChildren'",NULL);
#endif
 {
  self->removeChildren(index,num);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_removeChild01
static int tolua_moon_moon_BaseObject_removeChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'",NULL);
#endif
 {
  self->removeChild(index);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_removeChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: separateChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_separateChild00
static int tolua_moon_moon_BaseObject_separateChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* child = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'separateChild'",NULL);
#endif
 {
  self->separateChild(child);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'separateChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: separateChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_separateChild01
static int tolua_moon_moon_BaseObject_separateChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'separateChild'",NULL);
#endif
 {
  self->separateChild(index);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_separateChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChild of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getChild00
static int tolua_moon_moon_BaseObject_getChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChild'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getChild(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildIndex of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getChildIndex00
static int tolua_moon_moon_BaseObject_getChildIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const moon::BaseObject* child = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildIndex'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getChildIndex(child);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParent of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getParent00
static int tolua_moon_moon_BaseObject_getParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParent'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getParent();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findRelated of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_findRelated00
static int tolua_moon_moon_BaseObject_findRelated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool childrenOnly = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findRelated'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->findRelated(name,childrenOnly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findRelated'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findRelatedByTemplate of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_findRelatedByTemplate00
static int tolua_moon_moon_BaseObject_findRelatedByTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const moon::BaseObject* templateObject = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
  const bool childrenOnly = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findRelatedByTemplate'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->findRelatedByTemplate(templateObject,childrenOnly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findRelatedByTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findRelatedByTag of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_findRelatedByTag00
static int tolua_moon_moon_BaseObject_findRelatedByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool childrenOnly = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findRelatedByTag'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->findRelatedByTag(tag,childrenOnly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findRelatedByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_show00
static int tolua_moon_moon_BaseObject_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hide of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_hide00
static int tolua_moon_moon_BaseObject_hide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hide'",NULL);
#endif
 {
  self->hide();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_addNode00
static int tolua_moon_moon_BaseObject_addNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'",NULL);
#endif
 {
  self->addNode(node);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDebugNode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_addDebugNode00
static int tolua_moon_moon_BaseObject_addDebugNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Node",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  osg::Node* node = ((osg::Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDebugNode'",NULL);
#endif
 {
  self->addDebugNode(node);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDebugNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getNode00
static int tolua_moon_moon_BaseObject_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'",NULL);
#endif
 {
  osg::Node* tolua_ret = (osg::Node*)  self->getNode();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Node");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: highlight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_highlight00
static int tolua_moon_moon_BaseObject_highlight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool on = ((const bool)  tolua_toboolean(tolua_S,2,0));
  moon::BaseObject::HighLightMode mode = ((moon::BaseObject::HighLightMode) (int)  tolua_tonumber(tolua_S,3,moon::BaseObject::THICK_SCRIBE));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'highlight'",NULL);
#endif
 {
  self->highlight(on,mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'highlight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: highlight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_highlight01
static int tolua_moon_moon_BaseObject_highlight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"const osg::Vec4",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool on = ((const bool)  tolua_toboolean(tolua_S,2,0));
  moon::BaseObject::HighLightMode mode = ((moon::BaseObject::HighLightMode) (int)  tolua_tonumber(tolua_S,3,0));
  const osg::Vec4* color = ((const osg::Vec4*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'highlight'",NULL);
#endif
 {
  self->highlight(on,mode,*color);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_highlight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplayMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setDisplayMode00
static int tolua_moon_moon_BaseObject_setDisplayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int mode = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplayMode'",NULL);
#endif
 {
  self->setDisplayMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getDisplayMode00
static int tolua_moon_moon_BaseObject_getDisplayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayMode'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getDisplayMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setName00
static int tolua_moon_moon_BaseObject_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(name);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getName00
static int tolua_moon_moon_BaseObject_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  std::string tolua_ret = (std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: id of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_id00
static int tolua_moon_moon_BaseObject_id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'id'",NULL);
#endif
 {
  long tolua_ret = (long)  self->id();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: pointAt of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_pointAt00
static int tolua_moon_moon_BaseObject_pointAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* pos = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAt'",NULL);
#endif
 {
  self->pointAt(*pos);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_pointAt01
static int tolua_moon_moon_BaseObject_pointAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double x = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double y = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double z = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAt'",NULL);
#endif
 {
  self->pointAt(x,y,z);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_pointAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_pointAt02
static int tolua_moon_moon_BaseObject_pointAt02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* other = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAt'",NULL);
#endif
 {
  self->pointAt(other);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_pointAt01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRange of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getRange00
static int tolua_moon_moon_BaseObject_getRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const moon::BaseObject* object = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRange'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getRange(object);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAzimuth of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getAzimuth00
static int tolua_moon_moon_BaseObject_getAzimuth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const moon::BaseObject* object = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAzimuth'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getAzimuth(object,rel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAzimuth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getElevation of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getElevation00
static int tolua_moon_moon_BaseObject_getElevation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const moon::BaseObject* object = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElevation'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getElevation(object,rel);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElevation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSpherical of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getSpherical00
static int tolua_moon_moon_BaseObject_getSpherical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  float range = ((float)  tolua_tonumber(tolua_S,2,0));
  float azimuth = ((float)  tolua_tonumber(tolua_S,3,0));
  float elevation = ((float)  tolua_tonumber(tolua_S,4,0));
  const moon::BaseObject* object = ((const moon::BaseObject*)  tolua_tousertype(tolua_S,5,0));
  const bool rel = ((const bool)  tolua_toboolean(tolua_S,6,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSpherical'",NULL);
#endif
 {
  self->getSpherical(range,azimuth,elevation,object,rel);
 tolua_pushnumber(tolua_S,(lua_Number)range);
 tolua_pushnumber(tolua_S,(lua_Number)azimuth);
 tolua_pushnumber(tolua_S,(lua_Number)elevation);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSpherical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeightAboveTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getHeightAboveTerrain00
static int tolua_moon_moon_BaseObject_getHeightAboveTerrain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,3,true));
  const double below = ((const double)  tolua_tonumber(tolua_S,4,10000.0));
  const double above = ((const double)  tolua_tonumber(tolua_S,5,1000.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeightAboveTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getHeightAboveTerrain(height,boundscenter,below,above);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)height);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeightAboveTerrain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeightAboveTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getHeightAboveTerrain01
static int tolua_moon_moon_BaseObject_getHeightAboveTerrain01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,6,"const osg::Node::NodeMask",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,3,0));
  const double below = ((const double)  tolua_tonumber(tolua_S,4,0));
  const double above = ((const double)  tolua_tonumber(tolua_S,5,0));
  const osg::Node::NodeMask* mask = ((const osg::Node::NodeMask*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeightAboveTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getHeightAboveTerrain(height,boundscenter,below,above,*mask);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)height);
 }
 }
 return 2;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getHeightAboveTerrain00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: clampToTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_clampToTerrain00
static int tolua_moon_moon_BaseObject_clampToTerrain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,2,true));
  const double below = ((const double)  tolua_tonumber(tolua_S,3,10000.0));
  const double above = ((const double)  tolua_tonumber(tolua_S,4,1000.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clampToTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->clampToTerrain(boundscenter,below,above);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clampToTerrain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clampToTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_clampToTerrain01
static int tolua_moon_moon_BaseObject_clampToTerrain01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"const osg::Node::NodeMask",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const double below = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double above = ((const double)  tolua_tonumber(tolua_S,4,0));
  const osg::Node::NodeMask* mask = ((const osg::Node::NodeMask*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clampToTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->clampToTerrain(boundscenter,below,above,*mask);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_moon_BaseObject_clampToTerrain00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignToTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_alignToTerrain00
static int tolua_moon_moon_BaseObject_alignToTerrain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,2,true));
  const double below = ((const double)  tolua_tonumber(tolua_S,3,10000.0));
  const double above = ((const double)  tolua_tonumber(tolua_S,4,1000.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignToTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->alignToTerrain(boundscenter,below,above);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'alignToTerrain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignToTerrain of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_alignToTerrain01
static int tolua_moon_moon_BaseObject_alignToTerrain01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"const osg::Node::NodeMask",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool boundscenter = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const double below = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double above = ((const double)  tolua_tonumber(tolua_S,4,0));
  const osg::Node::NodeMask* mask = ((const osg::Node::NodeMask*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignToTerrain'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->alignToTerrain(boundscenter,below,above,*mask);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_moon_BaseObject_alignToTerrain00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBottomCenter of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getBottomCenter00
static int tolua_moon_moon_BaseObject_getBottomCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBottomCenter'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getBottomCenter();
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
 tolua_error(tolua_S,"#ferror in function 'getBottomCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: asKinematic of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_asKinematic00
static int tolua_moon_moon_BaseObject_asKinematic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'asKinematic'",NULL);
#endif
 {
  moon::KinematicObject* tolua_ret = (moon::KinematicObject*)  self->asKinematic();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::KinematicObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'asKinematic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScriptUpdateInterval of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setScriptUpdateInterval00
static int tolua_moon_moon_BaseObject_setScriptUpdateInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double interval = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScriptUpdateInterval'",NULL);
#endif
 {
  self->setScriptUpdateInterval(interval);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScriptUpdateInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScriptUpdateInterval of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getScriptUpdateInterval00
static int tolua_moon_moon_BaseObject_getScriptUpdateInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScriptUpdateInterval'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getScriptUpdateInterval();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScriptUpdateInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_remove00
static int tolua_moon_moon_BaseObject_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double timeFromNow = ((const double)  tolua_tonumber(tolua_S,2,0.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'",NULL);
#endif
 {
  self->remove(timeFromNow);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRemoveTime of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setRemoveTime00
static int tolua_moon_moon_BaseObject_setRemoveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double time = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRemoveTime'",NULL);
#endif
 {
  self->setRemoveTime(time);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRemoveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRemoveTime of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getRemoveTime00
static int tolua_moon_moon_BaseObject_getRemoveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRemoveTime'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getRemoveTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRemoveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findParameter of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_findParameter00
static int tolua_moon_moon_BaseObject_findParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findParameter'",NULL);
#endif
 {
  moon::Parameter* tolua_ret = (moon::Parameter*)  self->findParameter(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Parameter");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setPosition00
static int tolua_moon_moon_BaseObject_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* position = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'",NULL);
#endif
 {
  self->setPosition(*position);
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

/* method: setPosition of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setPosition01
static int tolua_moon_moon_BaseObject_setPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double x = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double y = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double z = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'",NULL);
#endif
 {
  self->setPosition(x,y,z);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_setPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getPosition00
static int tolua_moon_moon_BaseObject_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPosition of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getPosition01
static int tolua_moon_moon_BaseObject_getPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'",NULL);
#endif
 {
  self->getPosition(x,y,z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setRotation00
static int tolua_moon_moon_BaseObject_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Quat* rotation = ((const osg::Quat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'",NULL);
#endif
 {
  self->setRotation(*rotation);
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

/* method: getRotation of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getRotation00
static int tolua_moon_moon_BaseObject_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAttitude of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setAttitude00
static int tolua_moon_moon_BaseObject_setAttitude00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* attitude = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttitude'",NULL);
#endif
 {
  self->setAttitude(*attitude);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttitude'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttitude of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getAttitude00
static int tolua_moon_moon_BaseObject_getAttitude00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttitude'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getAttitude();
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
 tolua_error(tolua_S,"#ferror in function 'getAttitude'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttitude of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setAttitude01
static int tolua_moon_moon_BaseObject_setAttitude01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double heading = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double pitch = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double roll = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttitude'",NULL);
#endif
 {
  self->setAttitude(heading,pitch,roll);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_setAttitude00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttitude of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getAttitude01
static int tolua_moon_moon_BaseObject_getAttitude01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  double heading = ((double)  tolua_tonumber(tolua_S,2,0));
  double pitch = ((double)  tolua_tonumber(tolua_S,3,0));
  double roll = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttitude'",NULL);
#endif
 {
  self->getAttitude(heading,pitch,roll);
 tolua_pushnumber(tolua_S,(lua_Number)heading);
 tolua_pushnumber(tolua_S,(lua_Number)pitch);
 tolua_pushnumber(tolua_S,(lua_Number)roll);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getAttitude00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: forward of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_forward00
static int tolua_moon_moon_BaseObject_forward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'forward'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->forward();
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
 tolua_error(tolua_S,"#ferror in function 'forward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: right of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_right00
static int tolua_moon_moon_BaseObject_right00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'right'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->right();
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
 tolua_error(tolua_S,"#ferror in function 'right'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: up of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_up00
static int tolua_moon_moon_BaseObject_up00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'up'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->up();
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
 tolua_error(tolua_S,"#ferror in function 'up'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: move of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_move00
static int tolua_moon_moon_BaseObject_move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double distance = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'move'",NULL);
#endif
 {
  self->move(distance);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'move'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: move of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_move01
static int tolua_moon_moon_BaseObject_move01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* relposition = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'move'",NULL);
#endif
 {
  self->move(*relposition);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_move00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: move of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_move02
static int tolua_moon_moon_BaseObject_move02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double x = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double y = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double z = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'move'",NULL);
#endif
 {
  self->move(x,y,z);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_move01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_rotate00
static int tolua_moon_moon_BaseObject_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double angle = ((const double)  tolua_tonumber(tolua_S,2,0));
  const osg::Vec3* axis = ((const osg::Vec3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'",NULL);
#endif
 {
  self->rotate(angle,*axis);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotateEuler of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_rotateEuler00
static int tolua_moon_moon_BaseObject_rotateEuler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* angles = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateEuler'",NULL);
#endif
 {
  self->rotateEuler(*angles);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotateEuler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotateEuler of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_rotateEuler01
static int tolua_moon_moon_BaseObject_rotateEuler01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double heading = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double pitch = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double roll = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateEuler'",NULL);
#endif
 {
  self->rotateEuler(heading,pitch,roll);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_rotateEuler00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: yaw of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_yaw00
static int tolua_moon_moon_BaseObject_yaw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double angle = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'yaw'",NULL);
#endif
 {
  self->yaw(angle);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'yaw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pitch of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_pitch00
static int tolua_moon_moon_BaseObject_pitch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double angle = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pitch'",NULL);
#endif
 {
  self->pitch(angle);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: roll of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_roll00
static int tolua_moon_moon_BaseObject_roll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double angle = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'roll'",NULL);
#endif
 {
  self->roll(angle);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'roll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_scale00
static int tolua_moon_moon_BaseObject_scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* scale = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'",NULL);
#endif
 {
  self->scale(*scale);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_scale01
static int tolua_moon_moon_BaseObject_scale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double amount = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'",NULL);
#endif
 {
  self->scale(amount);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_scale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTransform of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getTransform00
static int tolua_moon_moon_BaseObject_getTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTransform'",NULL);
#endif
 {
  osg::MatrixTransform* tolua_ret = (osg::MatrixTransform*)  self->getTransform();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::MatrixTransform");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransformMatrix of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setTransformMatrix00
static int tolua_moon_moon_BaseObject_setTransformMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Matrix* matrix = ((const osg::Matrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransformMatrix'",NULL);
#endif
 {
  self->setTransformMatrix(*matrix);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransformMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTransformMatrix of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getTransformMatrix00
static int tolua_moon_moon_BaseObject_getTransformMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTransformMatrix'",NULL);
#endif
 {
  const osg::Matrix& tolua_ret = (const osg::Matrix&)  self->getTransformMatrix();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const osg::Matrix");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTransformMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEulerAnglesFromMatrix of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getEulerAnglesFromMatrix00
static int tolua_moon_moon_BaseObject_getEulerAnglesFromMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Matrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Matrix* M = ((const osg::Matrix*)  tolua_tousertype(tolua_S,2,0));
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  moon::BaseObject::getEulerAnglesFromMatrix(*M);
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
 tolua_error(tolua_S,"#ferror in function 'getEulerAnglesFromMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMatrixFromEulerAngles of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getMatrixFromEulerAngles00
static int tolua_moon_moon_BaseObject_getMatrixFromEulerAngles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const osg::Vec3* angles = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
 {
  osg::Matrix tolua_ret = (osg::Matrix)  moon::BaseObject::getMatrixFromEulerAngles(*angles);
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
 tolua_error(tolua_S,"#ferror in function 'getMatrixFromEulerAngles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalUpVector of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getLocalUpVector00
static int tolua_moon_moon_BaseObject_getLocalUpVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalUpVector'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getLocalUpVector();
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
 tolua_error(tolua_S,"#ferror in function 'getLocalUpVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionLatLongHeight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setPositionLatLongHeight00
static int tolua_moon_moon_BaseObject_setPositionLatLongHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double latitude = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double longitude = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double height = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionLatLongHeight'",NULL);
#endif
 {
  self->setPositionLatLongHeight(latitude,longitude,height);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionLatLongHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionLatLongHeight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setPositionLatLongHeight01
static int tolua_moon_moon_BaseObject_setPositionLatLongHeight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* llh = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionLatLongHeight'",NULL);
#endif
 {
  self->setPositionLatLongHeight(*llh);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_BaseObject_setPositionLatLongHeight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionLatLongHeight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getPositionLatLongHeight00
static int tolua_moon_moon_BaseObject_getPositionLatLongHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionLatLongHeight'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getPositionLatLongHeight();
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
 tolua_error(tolua_S,"#ferror in function 'getPositionLatLongHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionLatLongHeight of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getPositionLatLongHeight01
static int tolua_moon_moon_BaseObject_getPositionLatLongHeight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  double latitude = ((double)  tolua_tonumber(tolua_S,2,0));
  double longitude = ((double)  tolua_tonumber(tolua_S,3,0));
  double height = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionLatLongHeight'",NULL);
#endif
 {
  self->getPositionLatLongHeight(latitude,longitude,height);
 tolua_pushnumber(tolua_S,(lua_Number)latitude);
 tolua_pushnumber(tolua_S,(lua_Number)longitude);
 tolua_pushnumber(tolua_S,(lua_Number)height);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getPositionLatLongHeight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isGeocentric of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isGeocentric00
static int tolua_moon_moon_BaseObject_isGeocentric00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isGeocentric'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isGeocentric();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isGeocentric'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwner of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getOwner00
static int tolua_moon_moon_BaseObject_getOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwner'",NULL);
#endif
 {
  moonet::Client* tolua_ret = (moonet::Client*)  self->getOwner();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moonet::Client");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOwner of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setOwner00
static int tolua_moon_moon_BaseObject_setOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moonet::Client* client = ((moonet::Client*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOwner'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->setOwner(client);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConstructed of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isConstructed00
static int tolua_moon_moon_BaseObject_isConstructed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConstructed'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConstructed();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConstructed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRemote of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isRemote00
static int tolua_moon_moon_BaseObject_isRemote00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRemote'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isRemote();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRemote'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCloaked of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setCloaked00
static int tolua_moon_moon_BaseObject_setCloaked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCloaked'",NULL);
#endif
 {
  self->setCloaked(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCloaked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCloaked of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isCloaked00
static int tolua_moon_moon_BaseObject_isCloaked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCloaked'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isCloaked();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCloaked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSerializationInterval of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setSerializationInterval00
static int tolua_moon_moon_BaseObject_setSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const float seconds = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float fullseconds = ((const float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSerializationInterval'",NULL);
#endif
 {
  self->setSerializationInterval(seconds,fullseconds);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSerializationInterval of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getSerializationInterval00
static int tolua_moon_moon_BaseObject_getSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSerializationInterval'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getSerializationInterval();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFullSerializationInterval of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getFullSerializationInterval00
static int tolua_moon_moon_BaseObject_getFullSerializationInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFullSerializationInterval'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getFullSerializationInterval();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFullSerializationInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVisibleToClient of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isVisibleToClient00
static int tolua_moon_moon_BaseObject_isVisibleToClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moonet::Client",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moonet::Client* client = ((moonet::Client*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVisibleToClient'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isVisibleToClient(client);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVisibleToClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: libraryName of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_libraryName00
static int tolua_moon_moon_BaseObject_libraryName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'libraryName'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->libraryName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'libraryName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: className of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_className00
static int tolua_moon_moon_BaseObject_className00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'className'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->className();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'className'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: realize of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_realize00
static int tolua_moon_moon_BaseObject_realize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: unrealize of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_unrealize00
static int tolua_moon_moon_BaseObject_unrealize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isRealized of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_isRealized00
static int tolua_moon_moon_BaseObject_isRealized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: update of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_update00
static int tolua_moon_moon_BaseObject_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const double dt = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
 {
  self->update(dt);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_reset00
static int tolua_moon_moon_BaseObject_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
 {
  self->reset();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResetState of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setResetState00
static int tolua_moon_moon_BaseObject_setResetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResetState'",NULL);
#endif
 {
  self->setResetState();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTag of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setTag00
static int tolua_moon_moon_BaseObject_setTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTag'",NULL);
#endif
 {
  self->setTag(tag,value);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasTag of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_hasTag00
static int tolua_moon_moon_BaseObject_hasTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasTag'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->hasTag(tag);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRealizeMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setRealizeMode00
static int tolua_moon_moon_BaseObject_setRealizeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject::TraversalMode mode = ((moon::BaseObject::TraversalMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRealizeMode'",NULL);
#endif
 {
  self->setRealizeMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRealizeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRealizeMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getRealizeMode00
static int tolua_moon_moon_BaseObject_getRealizeMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRealizeMode'",NULL);
#endif
 {
  moon::BaseObject::TraversalMode tolua_ret = (moon::BaseObject::TraversalMode)  self->getRealizeMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRealizeMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_setUpdateMode00
static int tolua_moon_moon_BaseObject_setUpdateMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject::TraversalMode mode = ((moon::BaseObject::TraversalMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateMode'",NULL);
#endif
 {
  self->setUpdateMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateMode of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getUpdateMode00
static int tolua_moon_moon_BaseObject_getUpdateMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateMode'",NULL);
#endif
 {
  moon::BaseObject::TraversalMode tolua_ret = (moon::BaseObject::TraversalMode)  self->getUpdateMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addComponent of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_addComponent00
static int tolua_moon_moon_BaseObject_addComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::Component* component = ((moon::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addComponent'",NULL);
#endif
 {
  self->addComponent(component);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeComponent of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_removeComponent00
static int tolua_moon_moon_BaseObject_removeComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::Component",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  moon::Component* component = ((moon::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeComponent'",NULL);
#endif
 {
  self->removeComponent(component);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumComponents of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getNumComponents00
static int tolua_moon_moon_BaseObject_getNumComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumComponents'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumComponents();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponent of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getComponent00
static int tolua_moon_moon_BaseObject_getComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponent'",NULL);
#endif
 {
  moon::Component* tolua_ret = (moon::Component*)  self->getComponent(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Component");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getComponentByTag of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getComponentByTag00
static int tolua_moon_moon_BaseObject_getComponentByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getComponentByTag'",NULL);
#endif
 {
  moon::Component* tolua_ret = (moon::Component*)  self->getComponentByTag(tag);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Component");
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getComponentByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumParameters of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getNumParameters00
static int tolua_moon_moon_BaseObject_getNumParameters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumParameters'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumParameters();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumParameters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParameter of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getParameter00
static int tolua_moon_moon_BaseObject_getParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParameter'",NULL);
#endif
 {
  moon::Parameter* tolua_ret = (moon::Parameter*)  self->getParameter(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Parameter");
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

/* method: getParameter of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getParameter01
static int tolua_moon_moon_BaseObject_getParameter01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const moon::BaseObject* self = (const moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParameter'",NULL);
#endif
 {
  const moon::Parameter* tolua_ret = (const moon::Parameter*)  self->getParameter(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"const moon::Parameter");
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getParameter00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParameter of class  moon::BaseObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_BaseObject_getParameter02
static int tolua_moon_moon_BaseObject_getParameter02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::BaseObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::BaseObject* self = (moon::BaseObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParameter'",NULL);
#endif
 {
  moon::Parameter* tolua_ret = (moon::Parameter*)  self->getParameter(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Parameter");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
tolua_lerror:
 return tolua_moon_moon_BaseObject_getParameter01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumModels of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_getNumModels00
static int tolua_moon_moon_VisualObject_getNumModels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::VisualObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::VisualObject* self = (const moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumModels'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumModels();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumModels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showModel of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showModel00
static int tolua_moon_moon_VisualObject_showModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showModel'",NULL);
#endif
 {
  self->showModel(index);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setModelVisibility of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_setModelVisibility00
static int tolua_moon_moon_VisualObject_setModelVisibility00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setModelVisibility'",NULL);
#endif
 {
  self->setModelVisibility(index,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setModelVisibility'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showModel of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showModel01
static int tolua_moon_moon_VisualObject_showModel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showModel'",NULL);
#endif
 {
  self->showModel(name);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_moon_VisualObject_showModel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setModelVisibility of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_setModelVisibility01
static int tolua_moon_moon_VisualObject_setModelVisibility01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setModelVisibility'",NULL);
#endif
 {
  self->setModelVisibility(name,value);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
tolua_lerror:
 return tolua_moon_moon_VisualObject_setModelVisibility00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: showModelsWithTag of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showModelsWithTag00
static int tolua_moon_moon_VisualObject_showModelsWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showModelsWithTag'",NULL);
#endif
 {
  self->showModelsWithTag(tag);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showModelsWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setModelVisibilityWithTag of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_setModelVisibilityWithTag00
static int tolua_moon_moon_VisualObject_setModelVisibilityWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setModelVisibilityWithTag'",NULL);
#endif
 {
  self->setModelVisibilityWithTag(tag,value);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setModelVisibilityWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showModelsWithoutTag of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showModelsWithoutTag00
static int tolua_moon_moon_VisualObject_showModelsWithoutTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showModelsWithoutTag'",NULL);
#endif
 {
  self->showModelsWithoutTag(tag);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showModelsWithoutTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setModelVisibilityWithoutTag of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_setModelVisibilityWithoutTag00
static int tolua_moon_moon_VisualObject_setModelVisibilityWithoutTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string tag = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const bool value = ((const bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setModelVisibilityWithoutTag'",NULL);
#endif
 {
  self->setModelVisibilityWithoutTag(tag,value);
 tolua_pushcppstring(tolua_S,(const char*)tag);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setModelVisibilityWithoutTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showAllModels of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showAllModels00
static int tolua_moon_moon_VisualObject_showAllModels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showAllModels'",NULL);
#endif
 {
  self->showAllModels();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showAllModels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideAllModels of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_hideAllModels00
static int tolua_moon_moon_VisualObject_hideAllModels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hideAllModels'",NULL);
#endif
 {
  self->hideAllModels();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hideAllModels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showLabel of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_showLabel00
static int tolua_moon_moon_VisualObject_showLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showLabel'",NULL);
#endif
 {
  self->showLabel();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideLabel of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_hideLabel00
static int tolua_moon_moon_VisualObject_hideLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hideLabel'",NULL);
#endif
 {
  self->hideLabel();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hideLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLabel of class  moon::VisualObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_VisualObject_setLabel00
static int tolua_moon_moon_VisualObject_setLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::VisualObject",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::VisualObject* self = (moon::VisualObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLabel'",NULL);
#endif
 {
  self->setLabel(text);
 tolua_pushcppstring(tolua_S,(const char*)text);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationPaused of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setAnimationPaused00
static int tolua_moon_moon_KinematicObject_setAnimationPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const bool paused = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const int controlPointIndex = ((const int)  tolua_tonumber(tolua_S,3,-1));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationPaused'",NULL);
#endif
 {
  self->setAnimationPaused(paused,controlPointIndex);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationPaused of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getAnimationPaused00
static int tolua_moon_moon_KinematicObject_getAnimationPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::KinematicObject* self = (const moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationPaused'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getAnimationPaused();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransformationUpdatesControlPoint of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setTransformationUpdatesControlPoint00
static int tolua_moon_moon_KinematicObject_setTransformationUpdatesControlPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const int controlPointIndex = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransformationUpdatesControlPoint'",NULL);
#endif
 {
  self->setTransformationUpdatesControlPoint(controlPointIndex);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransformationUpdatesControlPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setVelocity00
static int tolua_moon_moon_KinematicObject_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* vel = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
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

/* method: setVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setVelocity01
static int tolua_moon_moon_KinematicObject_setVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_moon_moon_KinematicObject_setVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setAngularVelocity00
static int tolua_moon_moon_KinematicObject_setAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* vel = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularVelocity'",NULL);
#endif
 {
  self->setAngularVelocity(*vel,relative);
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

/* method: setAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_setAngularVelocity01
static int tolua_moon_moon_KinematicObject_setAngularVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_moon_moon_KinematicObject_setAngularVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getVelocity00
static int tolua_moon_moon_KinematicObject_getVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getVelocity01
static int tolua_moon_moon_KinematicObject_getVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocity'",NULL);
#endif
 {
  self->getVelocity(x,y,z,relative);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_KinematicObject_getVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getWorldVelocity00
static int tolua_moon_moon_KinematicObject_getWorldVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::KinematicObject* self = (const moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getWorldVelocity();
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
 tolua_error(tolua_S,"#ferror in function 'getWorldVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getWorldVelocity01
static int tolua_moon_moon_KinematicObject_getWorldVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const moon::KinematicObject* self = (const moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldVelocity'",NULL);
#endif
 {
  self->getWorldVelocity(x,y,z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_KinematicObject_getWorldVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getAngularVelocity00
static int tolua_moon_moon_KinematicObject_getAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getAngularVelocity01
static int tolua_moon_moon_KinematicObject_getAngularVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngularVelocity'",NULL);
#endif
 {
  self->getAngularVelocity(x,y,z,relative);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_KinematicObject_getAngularVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getWorldAngularVelocity00
static int tolua_moon_moon_KinematicObject_getWorldAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::KinematicObject* self = (const moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldAngularVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getWorldAngularVelocity();
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
 tolua_error(tolua_S,"#ferror in function 'getWorldAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getWorldAngularVelocity01
static int tolua_moon_moon_KinematicObject_getWorldAngularVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const moon::KinematicObject* self = (const moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldAngularVelocity'",NULL);
#endif
 {
  self->getWorldAngularVelocity(x,y,z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_KinematicObject_getWorldAngularVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestPosition of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_requestPosition00
static int tolua_moon_moon_KinematicObject_requestPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* pos = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestPosition'",NULL);
#endif
 {
  self->requestPosition(*pos);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestRotation of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_requestRotation00
static int tolua_moon_moon_KinematicObject_requestRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Quat* rot = ((const osg::Quat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestRotation'",NULL);
#endif
 {
  self->requestRotation(*rot);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestAttitude of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_requestAttitude00
static int tolua_moon_moon_KinematicObject_requestAttitude00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* att = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestAttitude'",NULL);
#endif
 {
  self->requestAttitude(*att);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestAttitude'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_requestVelocity00
static int tolua_moon_moon_KinematicObject_requestVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* vel = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestVelocity'",NULL);
#endif
 {
  self->requestVelocity(*vel,relative);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestAngularVelocity of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_requestAngularVelocity00
static int tolua_moon_moon_KinematicObject_requestAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* vel = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestAngularVelocity'",NULL);
#endif
 {
  self->requestAngularVelocity(*vel,relative);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_stop00
static int tolua_moon_moon_KinematicObject_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'",NULL);
#endif
 {
  self->stop();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_getHeight00
static int tolua_moon_moon_KinematicObject_getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getHeight();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_moon_moon_KinematicObject_reset00
static int tolua_moon_moon_KinematicObject_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::KinematicObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::KinematicObject* self = (moon::KinematicObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
 {
  self->reset();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: linear_threshold of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_get_moon__KinematicObject_linear_threshold
static int tolua_get_moon__KinematicObject_linear_threshold(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)moon::KinematicObject::linear_threshold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: linear_threshold of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_set_moon__KinematicObject_linear_threshold
static int tolua_set_moon__KinematicObject_linear_threshold(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  moon::KinematicObject::linear_threshold = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: angular_threshold of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_get_moon__KinematicObject_angular_threshold
static int tolua_get_moon__KinematicObject_angular_threshold(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)moon::KinematicObject::angular_threshold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: angular_threshold of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_set_moon__KinematicObject_angular_threshold
static int tolua_set_moon__KinematicObject_angular_threshold(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  moon::KinematicObject::angular_threshold = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anim_velocity_timestep of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_get_moon__KinematicObject_anim_velocity_timestep
static int tolua_get_moon__KinematicObject_anim_velocity_timestep(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)moon::KinematicObject::anim_velocity_timestep);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anim_velocity_timestep of class  moon::KinematicObject */
#ifndef TOLUA_DISABLE_tolua_set_moon__KinematicObject_anim_velocity_timestep
static int tolua_set_moon__KinematicObject_anim_velocity_timestep(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  moon::KinematicObject::anim_velocity_timestep = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: isActive of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_isActive00
static int tolua_moon_moon_Camera_isActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isActive'",NULL);
#endif
 {
  const bool tolua_ret = (const bool)  self->isActive();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: activate of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_activate00
static int tolua_moon_moon_Camera_activate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'activate'",NULL);
#endif
 {
  self->activate();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'activate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPerspective of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setPerspective00
static int tolua_moon_moon_Camera_setPerspective00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const double fovy = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double aspect = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double nearclip = ((const double)  tolua_tonumber(tolua_S,4,-1));
  const double farclip = ((const double)  tolua_tonumber(tolua_S,5,-1));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPerspective'",NULL);
#endif
 {
  self->setPerspective(fovy,aspect,nearclip,farclip);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPerspective'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPerspective of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getPerspective00
static int tolua_moon_moon_Camera_getPerspective00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  double fovy = ((double)  tolua_tonumber(tolua_S,2,0));
  double aspect = ((double)  tolua_tonumber(tolua_S,3,0));
  double nearclip = ((double)  tolua_tonumber(tolua_S,4,0));
  double farclip = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPerspective'",NULL);
#endif
 {
  self->getPerspective(fovy,aspect,nearclip,farclip);
 tolua_pushnumber(tolua_S,(lua_Number)fovy);
 tolua_pushnumber(tolua_S,(lua_Number)aspect);
 tolua_pushnumber(tolua_S,(lua_Number)nearclip);
 tolua_pushnumber(tolua_S,(lua_Number)farclip);
 }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPerspective'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFOV of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getFOV00
static int tolua_moon_moon_Camera_getFOV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFOV'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getFOV();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFOV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAspect of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getAspect00
static int tolua_moon_moon_Camera_getAspect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAspect'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getAspect();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAspect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNearClip of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getNearClip00
static int tolua_moon_moon_Camera_getNearClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNearClip'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getNearClip();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNearClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFarClip of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getFarClip00
static int tolua_moon_moon_Camera_getFarClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFarClip'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getFarClip();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFarClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFree of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setFree00
static int tolua_moon_moon_Camera_setFree00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const bool flag = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFree'",NULL);
#endif
 {
  self->setFree(flag);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFree'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFree of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_isFree00
static int tolua_moon_moon_Camera_isFree00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFree'",NULL);
#endif
 {
  const bool tolua_ret = (const bool)  self->isFree();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFree'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLimit of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setLimit00
static int tolua_moon_moon_Camera_setLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  moon::Camera::CameraLimit limit = ((moon::Camera::CameraLimit) (int)  tolua_tonumber(tolua_S,2,0));
  const double value = ((const double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLimit'",NULL);
#endif
 {
  self->setLimit(limit,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLimit of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getLimit00
static int tolua_moon_moon_Camera_getLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  moon::Camera::CameraLimit limit = ((moon::Camera::CameraLimit) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLimit'",NULL);
#endif
 {
  const double tolua_ret = (const double)  self->getLimit(limit);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: track of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_track00
static int tolua_moon_moon_Camera_track00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* target = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'track'",NULL);
#endif
 {
  self->track(target);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'track'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: track of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_track01
static int tolua_moon_moon_Camera_track01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* target = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
  moon::Camera::TrackMode mode = ((moon::Camera::TrackMode) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'track'",NULL);
#endif
 {
  self->track(target,mode);
 }
 }
 return 0;
tolua_lerror:
 return tolua_moon_moon_Camera_track00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrackTarget of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getTrackTarget00
static int tolua_moon_moon_Camera_getTrackTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrackTarget'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getTrackTarget();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrackTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrackMode of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getTrackMode00
static int tolua_moon_moon_Camera_getTrackMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrackMode'",NULL);
#endif
 {
  moon::Camera::TrackMode tolua_ret = (moon::Camera::TrackMode)  self->getTrackMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrackMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTrackParameters of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setTrackParameters00
static int tolua_moon_moon_Camera_setTrackParameters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const double distance = ((const double)  tolua_tonumber(tolua_S,2,0));
  const double azimuth = ((const double)  tolua_tonumber(tolua_S,3,0));
  const double elevation = ((const double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTrackParameters'",NULL);
#endif
 {
  self->setTrackParameters(distance,azimuth,elevation);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTrackParameters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrackDistance of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getTrackDistance00
static int tolua_moon_moon_Camera_getTrackDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrackDistance'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTrackDistance();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrackDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrackAzimuth of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getTrackAzimuth00
static int tolua_moon_moon_Camera_getTrackAzimuth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrackAzimuth'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTrackAzimuth();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrackAzimuth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrackElevation of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getTrackElevation00
static int tolua_moon_moon_Camera_getTrackElevation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrackElevation'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTrackElevation();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrackElevation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHideWhenActive of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setHideWhenActive00
static int tolua_moon_moon_Camera_setHideWhenActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const bool flag = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHideWhenActive'",NULL);
#endif
 {
  self->setHideWhenActive(flag);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHideWhenActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hidesWhenActive of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_hidesWhenActive00
static int tolua_moon_moon_Camera_hidesWhenActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hidesWhenActive'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->hidesWhenActive();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hidesWhenActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMove2D of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setMove2D00
static int tolua_moon_moon_Camera_setMove2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const bool flag = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMove2D'",NULL);
#endif
 {
  self->setMove2D(flag);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMove2D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMove2D of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getMove2D00
static int tolua_moon_moon_Camera_getMove2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMove2D'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getMove2D();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMove2D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPivot of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setPivot00
static int tolua_moon_moon_Camera_setPivot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* pivot = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPivot'",NULL);
#endif
 {
  self->setPivot(*pivot);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPivot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPivot of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getPivot00
static int tolua_moon_moon_Camera_getPivot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPivot'",NULL);
#endif
 {
  const osg::Vec3& tolua_ret = (const osg::Vec3&)  self->getPivot();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const osg::Vec3");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPivot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInfoLevel of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_setInfoLevel00
static int tolua_moon_moon_Camera_setInfoLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
  const int level = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInfoLevel'",NULL);
#endif
 {
  self->setInfoLevel(level);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInfoLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInfoLevel of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getInfoLevel00
static int tolua_moon_moon_Camera_getInfoLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Camera* self = (const moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInfoLevel'",NULL);
#endif
 {
  int tolua_ret = (int)  self->getInfoLevel();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInfoLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHUD of class  moon::Camera */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Camera_getHUD00
static int tolua_moon_moon_Camera_getHUD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Camera",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Camera* self = (moon::Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHUD'",NULL);
#endif
 {
  osg::Node* tolua_ret = (osg::Node*)  self->getHUD();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"osg::Node");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHUD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  moon::Parameter */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Parameter_set00
static int tolua_moon_moon_Parameter_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Parameter",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Parameter* self = (moon::Parameter*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
 {
  self->set(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  moon::Parameter */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Parameter_get00
static int tolua_moon_moon_Parameter_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Parameter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Parameter* self = (moon::Parameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
 {
  float tolua_ret = (float)  self->get();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnected of class  moon::Parameter */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Parameter_isConnected00
static int tolua_moon_moon_Parameter_isConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Parameter",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Parameter* self = (const moon::Parameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnected'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConnected();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  moon::Scenario */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scenario_setName00
static int tolua_moon_moon_Scenario_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scenario",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scenario* self = (moon::Scenario*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(name);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::Scenario */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scenario_getName00
static int tolua_moon_moon_Scenario_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Scenario",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Scenario* self = (const moon::Scenario*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  std::string tolua_ret = (std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplayMode of class  moon::Scenario */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scenario_setDisplayMode00
static int tolua_moon_moon_Scenario_setDisplayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scenario",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scenario* self = (moon::Scenario*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int mode = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplayMode'",NULL);
#endif
 {
  self->setDisplayMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayMode of class  moon::Scenario */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scenario_getDisplayMode00
static int tolua_moon_moon_Scenario_getDisplayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Scenario",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Scenario* self = (const moon::Scenario*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayMode'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getDisplayMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: host of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_host00
static int tolua_moon_moon_Application_host00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string gameName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'host'",NULL);
#endif
 {
  self->host(gameName);
 tolua_pushcppstring(tolua_S,(const char*)gameName);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'host'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: host of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_host01
static int tolua_moon_moon_Application_host01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string gameName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string playerName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'host'",NULL);
#endif
 {
  self->host(gameName,playerName);
 tolua_pushcppstring(tolua_S,(const char*)gameName);
 tolua_pushcppstring(tolua_S,(const char*)playerName);
 }
 }
 return 2;
tolua_lerror:
 return tolua_moon_moon_Application_host00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: join of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_join00
static int tolua_moon_moon_Application_join00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string peer = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string playerName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'join'",NULL);
#endif
 {
  self->join(peer,playerName);
 tolua_pushcppstring(tolua_S,(const char*)peer);
 tolua_pushcppstring(tolua_S,(const char*)playerName);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'join'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disconnect of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_disconnect00
static int tolua_moon_moon_Application_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disconnect'",NULL);
#endif
 {
  self->disconnect();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getName00
static int tolua_moon_moon_Application_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDone of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setDone00
static int tolua_moon_moon_Application_setDone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const bool flag = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDone'",NULL);
#endif
 {
  self->setDone(flag);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDone of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_isDone00
static int tolua_moon_moon_Application_isDone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDone'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isDone();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEndTime of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setEndTime00
static int tolua_moon_moon_Application_setEndTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const double time = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEndTime'",NULL);
#endif
 {
  self->setEndTime(time);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEndTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEndTime of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getEndTime00
static int tolua_moon_moon_Application_getEndTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEndTime'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getEndTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEndTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNonRealtimeSimulation of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setNonRealtimeSimulation00
static int tolua_moon_moon_Application_setNonRealtimeSimulation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const int num = ((const int)  tolua_tonumber(tolua_S,2,1));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNonRealtimeSimulation'",NULL);
#endif
 {
  self->setNonRealtimeSimulation(num);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNonRealtimeSimulation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNonRealtimeSimulation of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getNonRealtimeSimulation00
static int tolua_moon_moon_Application_getNonRealtimeSimulation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNonRealtimeSimulation'",NULL);
#endif
 {
  int tolua_ret = (int)  self->getNonRealtimeSimulation();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNonRealtimeSimulation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTargetFrameRate of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setTargetFrameRate00
static int tolua_moon_moon_Application_setTargetFrameRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const float fps = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTargetFrameRate'",NULL);
#endif
 {
  self->setTargetFrameRate(fps);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTargetFrameRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTargetFrameRate of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getTargetFrameRate00
static int tolua_moon_moon_Application_getTargetFrameRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTargetFrameRate'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getTargetFrameRate();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTargetFrameRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAverageFrameRate of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getAverageFrameRate00
static int tolua_moon_moon_Application_getAverageFrameRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAverageFrameRate'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getAverageFrameRate();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAverageFrameRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSleepTime of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getSleepTime00
static int tolua_moon_moon_Application_getSleepTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSleepTime'",NULL);
#endif
 {
  int tolua_ret = (int)  self->getSleepTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSleepTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxSleepTime of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setMaxSleepTime00
static int tolua_moon_moon_Application_setMaxSleepTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const int time = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxSleepTime'",NULL);
#endif
 {
  self->setMaxSleepTime(time);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxSleepTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxSleepTime of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getMaxSleepTime00
static int tolua_moon_moon_Application_getMaxSleepTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxSleepTime'",NULL);
#endif
 {
  int tolua_ret = (int)  self->getMaxSleepTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxSleepTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setExitCode of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_setExitCode00
static int tolua_moon_moon_Application_setExitCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const int value = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setExitCode'",NULL);
#endif
 {
  self->setExitCode(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setExitCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getExitCode of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getExitCode00
static int tolua_moon_moon_Application_getExitCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Application* self = (const moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getExitCode'",NULL);
#endif
 {
  int tolua_ret = (int)  self->getExitCode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getExitCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_load00
static int tolua_moon_moon_Application_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'",NULL);
#endif
 {
  self->load(filename);
 tolua_pushcppstring(tolua_S,(const char*)filename);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_load01
static int tolua_moon_moon_Application_load01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string specname = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'",NULL);
#endif
 {
  self->load(filename,specname);
 tolua_pushcppstring(tolua_S,(const char*)filename);
 tolua_pushcppstring(tolua_S,(const char*)specname);
 }
 }
 return 2;
tolua_lerror:
 return tolua_moon_moon_Application_load00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_load02
static int tolua_moon_moon_Application_load02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string specname = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string spectype = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'",NULL);
#endif
 {
  self->load(filename,specname,spectype);
 tolua_pushcppstring(tolua_S,(const char*)filename);
 tolua_pushcppstring(tolua_S,(const char*)specname);
 tolua_pushcppstring(tolua_S,(const char*)spectype);
 }
 }
 return 3;
tolua_lerror:
 return tolua_moon_moon_Application_load01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScenario of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getScenario00
static int tolua_moon_moon_Application_getScenario00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScenario'",NULL);
#endif
 {
  moon::Scenario* tolua_ret = (moon::Scenario*)  self->getScenario();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Scenario");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScenario'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadScenario of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_loadScenario00
static int tolua_moon_moon_Application_loadScenario00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadScenario'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->loadScenario(name);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadScenario'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveScenario of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_saveScenario00
static int tolua_moon_moon_Application_saveScenario00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveScenario'",NULL);
#endif
 {
  self->saveScenario(filename);
 tolua_pushcppstring(tolua_S,(const char*)filename);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveScenario'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootPath of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getRootPath00
static int tolua_moon_moon_Application_getRootPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootPath'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getRootPath();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNetworkGame of class  moon::Application */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Application_getNetworkGame00
static int tolua_moon_moon_Application_getNetworkGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Application",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Application* self = (moon::Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNetworkGame'",NULL);
#endif
 {
  moon::NetworkGame* tolua_ret = (moon::NetworkGame*)  self->getNetworkGame();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::NetworkGame");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNetworkGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStatusText of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_setStatusText00
static int tolua_moon_moon_Viewer_setStatusText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStatusText'",NULL);
#endif
 {
  self->setStatusText(text);
 tolua_pushcppstring(tolua_S,(const char*)text);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStatusText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBannerText of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_setBannerText00
static int tolua_moon_moon_Viewer_setBannerText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBannerText'",NULL);
#endif
 {
  self->setBannerText(text);
 tolua_pushcppstring(tolua_S,(const char*)text);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBannerText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEditMode of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_setEditMode00
static int tolua_moon_moon_Viewer_setEditMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEditMode'",NULL);
#endif
 {
  self->setEditMode(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEditMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEditing of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_isEditing00
static int tolua_moon_moon_Viewer_isEditing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Viewer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Viewer* self = (const moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEditing'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isEditing();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEditing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getConsoleWindow of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_getConsoleWindow00
static int tolua_moon_moon_Viewer_getConsoleWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getConsoleWindow'",NULL);
#endif
 {
  mdraw::ConsoleWindow* tolua_ret = (mdraw::ConsoleWindow*)  self->getConsoleWindow();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"mdraw::ConsoleWindow");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConsoleWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showConsoleWindow of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_showConsoleWindow00
static int tolua_moon_moon_Viewer_showConsoleWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showConsoleWindow'",NULL);
#endif
 {
  self->showConsoleWindow(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showConsoleWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConsoleWindowShown of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_isConsoleWindowShown00
static int tolua_moon_moon_Viewer_isConsoleWindowShown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConsoleWindowShown'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isConsoleWindowShown();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConsoleWindowShown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: frame of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_frame00
static int tolua_moon_moon_Viewer_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'frame'",NULL);
#endif
 {
  self->frame();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setManipulator of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_setManipulator00
static int tolua_moon_moon_Viewer_setManipulator00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Viewer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Viewer* self = (moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int value = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setManipulator'",NULL);
#endif
 {
  self->setManipulator(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setManipulator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getManipulator of class  moon::Viewer */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Viewer_getManipulator00
static int tolua_moon_moon_Viewer_getManipulator00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const moon::Viewer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const moon::Viewer* self = (const moon::Viewer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getManipulator'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getManipulator();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getManipulator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEditMode of class  moon::EditHandler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_EditHandler_setEditMode00
static int tolua_moon_moon_EditHandler_setEditMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::EditHandler",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::EditHandler* self = (moon::EditHandler*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEditMode'",NULL);
#endif
 {
  self->setEditMode(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEditMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEditing of class  moon::EditHandler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_EditHandler_isEditing00
static int tolua_moon_moon_EditHandler_isEditing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::EditHandler",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::EditHandler* self = (moon::EditHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEditing'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isEditing();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEditing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSelectedObject of class  moon::EditHandler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_EditHandler_getSelectedObject00
static int tolua_moon_moon_EditHandler_getSelectedObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::EditHandler",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::EditHandler* self = (moon::EditHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSelectedObject'",NULL);
#endif
 {
  moon::BaseObject* tolua_ret = (moon::BaseObject*)  self->getSelectedObject();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::BaseObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSelectedObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: select of class  moon::EditHandler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_EditHandler_select00
static int tolua_moon_moon_EditHandler_select00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::EditHandler",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"moon::BaseObject",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::EditHandler* self = (moon::EditHandler*)  tolua_tousertype(tolua_S,1,0);
  moon::BaseObject* object = ((moon::BaseObject*)  tolua_tousertype(tolua_S,2,0));
  const bool childSelect = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'select'",NULL);
#endif
 {
  self->select(object,childSelect);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'select'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGrid of class  moon::EditHandler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_EditHandler_setGrid00
static int tolua_moon_moon_EditHandler_setGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::EditHandler",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::EditHandler* self = (moon::EditHandler*)  tolua_tousertype(tolua_S,1,0);
  const float size = ((const float)  tolua_tonumber(tolua_S,2,1.f));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGrid'",NULL);
#endif
 {
  self->setGrid(size);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: schedule of class  moon::Scheduler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scheduler_schedule00
static int tolua_moon_moon_Scheduler_schedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scheduler",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scheduler* self = (moon::Scheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string scriptFunctionName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const double deltaTime = ((const double)  tolua_tonumber(tolua_S,3,0));
  const bool repeat = ((const bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'schedule'",NULL);
#endif
 {
  self->schedule(scriptFunctionName,deltaTime,repeat);
 tolua_pushcppstring(tolua_S,(const char*)scriptFunctionName);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'schedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scheduleAt of class  moon::Scheduler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scheduler_scheduleAt00
static int tolua_moon_moon_Scheduler_scheduleAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scheduler",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scheduler* self = (moon::Scheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string scriptFunctionName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const double time = ((const double)  tolua_tonumber(tolua_S,3,0));
  const bool repeat = ((const bool)  tolua_toboolean(tolua_S,4,false));
  const double interval = ((const double)  tolua_tonumber(tolua_S,5,0.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scheduleAt'",NULL);
#endif
 {
  self->scheduleAt(scriptFunctionName,time,repeat,interval);
 tolua_pushcppstring(tolua_S,(const char*)scriptFunctionName);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scheduleAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scheduleAtGameTime of class  moon::Scheduler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scheduler_scheduleAtGameTime00
static int tolua_moon_moon_Scheduler_scheduleAtGameTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scheduler",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scheduler* self = (moon::Scheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string scriptFunctionName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const double time = ((const double)  tolua_tonumber(tolua_S,3,0));
  const bool repeat = ((const bool)  tolua_toboolean(tolua_S,4,false));
  const double interval = ((const double)  tolua_tonumber(tolua_S,5,0.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scheduleAtGameTime'",NULL);
#endif
 {
  self->scheduleAtGameTime(scriptFunctionName,time,repeat,interval);
 tolua_pushcppstring(tolua_S,(const char*)scriptFunctionName);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scheduleAtGameTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unschedule of class  moon::Scheduler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scheduler_unschedule00
static int tolua_moon_moon_Scheduler_unschedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scheduler",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scheduler* self = (moon::Scheduler*)  tolua_tousertype(tolua_S,1,0);
  const std::string scriptFunctionName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unschedule'",NULL);
#endif
 {
  self->unschedule(scriptFunctionName);
 tolua_pushcppstring(tolua_S,(const char*)scriptFunctionName);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unschedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  moon::Scheduler */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Scheduler_clear00
static int tolua_moon_moon_Scheduler_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Scheduler",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Scheduler* self = (moon::Scheduler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'",NULL);
#endif
 {
  self->clear();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeStep of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_getTimeStep00
static int tolua_moon_moon_SimulationManager_getTimeStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeStep'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTimeStep();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTimeStep of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_setTimeStep00
static int tolua_moon_moon_SimulationManager_setTimeStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
  const double value = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeStep'",NULL);
#endif
 {
  self->setTimeStep(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPaused of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_setPaused00
static int tolua_moon_moon_SimulationManager_setPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPaused'",NULL);
#endif
 {
  self->setPaused(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPaused of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_isPaused00
static int tolua_moon_moon_SimulationManager_isPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPaused'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isPaused();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTime of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_setTime00
static int tolua_moon_moon_SimulationManager_setTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
  const double time = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTime'",NULL);
#endif
 {
  self->setTime(time);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTime of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_getTime00
static int tolua_moon_moon_SimulationManager_getTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTime'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameTimeOffset of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_getGameTimeOffset00
static int tolua_moon_moon_SimulationManager_getGameTimeOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameTimeOffset'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getGameTimeOffset();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameTimeOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewerTimeOffset of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_getViewerTimeOffset00
static int tolua_moon_moon_SimulationManager_getViewerTimeOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewerTimeOffset'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getViewerTimeOffset();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getViewerTimeOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeScale of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_getTimeScale00
static int tolua_moon_moon_SimulationManager_getTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeScale'",NULL);
#endif
 {
  double tolua_ret = (double)  self->getTimeScale();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTimeScale of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_setTimeScale00
static int tolua_moon_moon_SimulationManager_setTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::SimulationManager* self = (moon::SimulationManager*)  tolua_tousertype(tolua_S,1,0);
  const double ratio = ((const double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeScale'",NULL);
#endif
 {
  self->setTimeScale(ratio);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  moon::SimulationManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_SimulationManager_instance00
static int tolua_moon_moon_SimulationManager_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"moon::SimulationManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  moon::SimulationManager& tolua_ret = (moon::SimulationManager&)  moon::SimulationManager::instance();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"moon::SimulationManager");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::NetworkGame */
#ifndef TOLUA_DISABLE_tolua_moon_moon_NetworkGame_getName00
static int tolua_moon_moon_NetworkGame_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::NetworkGame",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::NetworkGame* self = (moon::NetworkGame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScenarioName of class  moon::NetworkGame */
#ifndef TOLUA_DISABLE_tolua_moon_moon_NetworkGame_getScenarioName00
static int tolua_moon_moon_NetworkGame_getScenarioName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::NetworkGame",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::NetworkGame* self = (moon::NetworkGame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScenarioName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getScenarioName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScenarioName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGameTime of class  moon::NetworkGame */
#ifndef TOLUA_DISABLE_tolua_moon_moon_NetworkGame_getGameTime00
static int tolua_moon_moon_NetworkGame_getGameTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::NetworkGame",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::NetworkGame* self = (moon::NetworkGame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGameTime'",NULL);
#endif
 {
  const double tolua_ret = (const double)  self->getGameTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGameTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_setValue00
static int tolua_moon_moon_Control_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
  const float newvalue = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'",NULL);
#endif
 {
  self->setValue(newvalue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_getValue00
static int tolua_moon_moon_Control_getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'",NULL);
#endif
 {
  const float tolua_ret = (const float)  self->getValue();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setType of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_setType00
static int tolua_moon_moon_Control_setType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
  moon::Control::ControlType newtype = ((moon::Control::ControlType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setType'",NULL);
#endif
 {
  self->setType(newtype);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getType of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_getType00
static int tolua_moon_moon_Control_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'",NULL);
#endif
 {
  moon::Control::ControlType& tolua_ret = (moon::Control::ControlType&)  self->getType();
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

/* method: setName of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_setName00
static int tolua_moon_moon_Control_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
  const std::string newname = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'",NULL);
#endif
 {
  self->setName(newname);
 tolua_pushcppstring(tolua_S,(const char*)newname);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::Control */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Control_getName00
static int tolua_moon_moon_Control_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Control",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Control* self = (moon::Control*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const std::string tolua_ret = (const std::string)  self->getName();
 tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  moon::Plugin */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Plugin_getName00
static int tolua_moon_moon_Plugin_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Plugin",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Plugin* self = (moon::Plugin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  moon::Plugin */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Plugin_getDescription00
static int tolua_moon_moon_Plugin_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Plugin",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Plugin* self = (moon::Plugin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getDescription();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAuthor of class  moon::Plugin */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Plugin_getAuthor00
static int tolua_moon_moon_Plugin_getAuthor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Plugin",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Plugin* self = (moon::Plugin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAuthor'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getAuthor();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAuthor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  moon::Plugin */
#ifndef TOLUA_DISABLE_tolua_moon_moon_Plugin_getVersion00
static int tolua_moon_moon_Plugin_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::Plugin",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::Plugin* self = (moon::Plugin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getVersion();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  moon::PluginManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_PluginManager_load00
static int tolua_moon_moon_PluginManager_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::PluginManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::PluginManager* self = (moon::PluginManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'",NULL);
#endif
 {
  moon::Plugin* tolua_ret = (moon::Plugin*)  self->load(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Plugin");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadAll of class  moon::PluginManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_PluginManager_loadAll00
static int tolua_moon_moon_PluginManager_loadAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::PluginManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::PluginManager* self = (moon::PluginManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAll'",NULL);
#endif
 {
  self->loadAll();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  moon::PluginManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_PluginManager_get00
static int tolua_moon_moon_PluginManager_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::PluginManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::PluginManager* self = (moon::PluginManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
 {
  moon::Plugin* tolua_ret = (moon::Plugin*)  self->get(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Plugin");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumPlugins of class  moon::PluginManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_PluginManager_getNumPlugins00
static int tolua_moon_moon_PluginManager_getNumPlugins00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::PluginManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::PluginManager* self = (moon::PluginManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumPlugins'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getNumPlugins();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumPlugins'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlugin of class  moon::PluginManager */
#ifndef TOLUA_DISABLE_tolua_moon_moon_PluginManager_getPlugin00
static int tolua_moon_moon_PluginManager_getPlugin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"moon::PluginManager",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  moon::PluginManager* self = (moon::PluginManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int index = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlugin'",NULL);
#endif
 {
  moon::Plugin* tolua_ret = (moon::Plugin*)  self->getPlugin(index);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"moon::Plugin");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlugin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_moon_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"osg",0);
 tolua_beginmodule(tolua_S,"osg");
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Vec3","osg::Vec3","",tolua_collect_osg__Vec3);
  #else
  tolua_cclass(tolua_S,"Vec3","osg::Vec3","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Vec3");
   tolua_function(tolua_S,"new",tolua_moon_osg_Vec3_new00);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Vec3_new00_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Vec3_new00_local);
   tolua_function(tolua_S,"new",tolua_moon_osg_Vec3_new01);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Vec3_new01_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Vec3_new01_local);
   tolua_function(tolua_S,"set",tolua_moon_osg_Vec3_set00);
   tolua_function(tolua_S,"x",tolua_moon_osg_Vec3_x00);
   tolua_function(tolua_S,"y",tolua_moon_osg_Vec3_y00);
   tolua_function(tolua_S,"z",tolua_moon_osg_Vec3_z00);
   tolua_function(tolua_S,"valid",tolua_moon_osg_Vec3_valid00);
   tolua_function(tolua_S,"isNaN",tolua_moon_osg_Vec3_isNaN00);
   tolua_function(tolua_S,".geti",tolua_moon_osg_Vec3__geti00);
   tolua_function(tolua_S,".eq",tolua_moon_osg_Vec3__eq00);
   tolua_function(tolua_S,".lt",tolua_moon_osg_Vec3__lt00);
   tolua_function(tolua_S,".mul",tolua_moon_osg_Vec3__mul00);
   tolua_function(tolua_S,".mul",tolua_moon_osg_Vec3__mul01);
   tolua_function(tolua_S,".div",tolua_moon_osg_Vec3__div00);
   tolua_function(tolua_S,".add",tolua_moon_osg_Vec3__add00);
   tolua_function(tolua_S,".sub",tolua_moon_osg_Vec3__sub00);
   tolua_function(tolua_S,"length",tolua_moon_osg_Vec3_length00);
   tolua_function(tolua_S,"length2",tolua_moon_osg_Vec3_length200);
   tolua_function(tolua_S,"normalize",tolua_moon_osg_Vec3_normalize00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Vec4","osg::Vec4","",tolua_collect_osg__Vec4);
  #else
  tolua_cclass(tolua_S,"Vec4","osg::Vec4","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Vec4");
   tolua_function(tolua_S,"new",tolua_moon_osg_Vec4_new00);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Vec4_new00_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Vec4_new00_local);
   tolua_function(tolua_S,"new",tolua_moon_osg_Vec4_new01);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Vec4_new01_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Vec4_new01_local);
   tolua_function(tolua_S,"x",tolua_moon_osg_Vec4_x00);
   tolua_function(tolua_S,"y",tolua_moon_osg_Vec4_y00);
   tolua_function(tolua_S,"z",tolua_moon_osg_Vec4_z00);
   tolua_function(tolua_S,"w",tolua_moon_osg_Vec4_w00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Quat","osg::Quat","",tolua_collect_osg__Quat);
  #else
  tolua_cclass(tolua_S,"Quat","osg::Quat","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Quat");
   tolua_function(tolua_S,"new",tolua_moon_osg_Quat_new00);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Quat_new00_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Quat_new00_local);
   tolua_function(tolua_S,"new",tolua_moon_osg_Quat_new01);
   tolua_function(tolua_S,"new_local",tolua_moon_osg_Quat_new01_local);
   tolua_function(tolua_S,".call",tolua_moon_osg_Quat_new01_local);
   tolua_function(tolua_S,"x",tolua_moon_osg_Quat_x00);
   tolua_function(tolua_S,"y",tolua_moon_osg_Quat_y00);
   tolua_function(tolua_S,"z",tolua_moon_osg_Quat_z00);
   tolua_function(tolua_S,"w",tolua_moon_osg_Quat_w00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Object","osg::Object","",NULL);
  tolua_beginmodule(tolua_S,"Object");
   tolua_function(tolua_S,"setName",tolua_moon_osg_Object_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_osg_Object_getName00);
   tolua_function(tolua_S,"libraryName",tolua_moon_osg_Object_libraryName00);
   tolua_function(tolua_S,"className",tolua_moon_osg_Object_className00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Node","osg::Node","osg::Object",NULL);
  tolua_beginmodule(tolua_S,"Node");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Group","osg::Group","osg::Node",NULL);
  tolua_beginmodule(tolua_S,"Group");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Transform","osg::Transform","osg::Group",NULL);
  tolua_beginmodule(tolua_S,"Transform");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MatrixTransform","osg::MatrixTransform","osg::Transform",NULL);
  tolua_beginmodule(tolua_S,"MatrixTransform");
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BoundingBox","osg::BoundingBox","",tolua_collect_osg__BoundingBox);
  #else
  tolua_cclass(tolua_S,"BoundingBox","osg::BoundingBox","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BoundingBox");
   tolua_function(tolua_S,"xMin",tolua_moon_osg_BoundingBox_xMin00);
   tolua_function(tolua_S,"xMax",tolua_moon_osg_BoundingBox_xMax00);
   tolua_function(tolua_S,"yMin",tolua_moon_osg_BoundingBox_yMin00);
   tolua_function(tolua_S,"yMax",tolua_moon_osg_BoundingBox_yMax00);
   tolua_function(tolua_S,"zMin",tolua_moon_osg_BoundingBox_zMin00);
   tolua_function(tolua_S,"zMax",tolua_moon_osg_BoundingBox_zMax00);
   tolua_function(tolua_S,"center",tolua_moon_osg_BoundingBox_center00);
   tolua_function(tolua_S,"radius",tolua_moon_osg_BoundingBox_radius00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"osgText",0);
 tolua_beginmodule(tolua_S,"osgText");
  tolua_cclass(tolua_S,"TextBase","osgText::TextBase","",NULL);
  tolua_beginmodule(tolua_S,"TextBase");
   tolua_function(tolua_S,"setText",tolua_moon_osgText_TextBase_setText00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Text","osgText::Text","osgText::TextBase",NULL);
  tolua_beginmodule(tolua_S,"Text");
   tolua_function(tolua_S,"setColor",tolua_moon_osgText_Text_setColor00);
   tolua_function(tolua_S,"getColor",tolua_moon_osgText_Text_getColor00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,111,115,103, 46, 86,
  101, 99, 51, 58,103,101,116, 40, 41, 10,114,101,116,117,114,
  110, 32,115,101,108,102, 58,120, 40, 41, 44, 32,115,101,108,
  102, 58,121, 40, 41, 44, 32,115,101,108,102, 58,122, 40, 41,
   59, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  111,115,103, 46, 86,101, 99, 52, 58,103,101,116, 40, 41, 10,
  114,101,116,117,114,110, 32,115,101,108,102, 58,120, 40, 41,
   44, 32,115,101,108,102, 58,121, 40, 41, 44, 32,115,101,108,
  102, 58,122, 40, 41, 44, 32,115,101,108,102, 58,119, 40, 41,
   59, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  111,115,103, 46, 81,117, 97,116, 58,103,101,116, 40, 41, 10,
  114,101,116,117,114,110, 32,115,101,108,102, 58,120, 40, 41,
   44, 32,115,101,108,102, 58,121, 40, 41, 44, 32,115,101,108,
  102, 58,122, 40, 41, 44, 32,115,101,108,102, 58,119, 40, 41,
   59, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 1");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"mlog",0);
 tolua_beginmodule(tolua_S,"mlog");
  tolua_constant(tolua_S,"ERROR",mlog::ERROR);
  tolua_constant(tolua_S,"WARN",mlog::WARN);
  tolua_constant(tolua_S,"INFO",mlog::INFO);
  tolua_constant(tolua_S,"GENERAL",mlog::GENERAL);
  tolua_constant(tolua_S,"NETWORK",mlog::NETWORK);
  tolua_constant(tolua_S,"AUDIO",mlog::AUDIO);
  tolua_constant(tolua_S,"SCRIPT",mlog::SCRIPT);
  tolua_function(tolua_S,"getDebugLevel",tolua_moon_mlog_getDebugLevel00);
  tolua_function(tolua_S,"dout",tolua_moon_mlog_dout00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_constant(tolua_S,"CLIENT_INITIAL",moonet::CLIENT_INITIAL);
  tolua_constant(tolua_S,"CLIENT_READY",moonet::CLIENT_READY);
  tolua_cclass(tolua_S,"Client","moonet::Client","",NULL);
  tolua_beginmodule(tolua_S,"Client");
   tolua_function(tolua_S,"getPlayer",tolua_moon_moonet_Client_getPlayer00);
   tolua_function(tolua_S,"toString",tolua_moon_moonet_Client_toString00);
   tolua_function(tolua_S,"isConnected",tolua_moon_moonet_Client_isConnected00);
   tolua_function(tolua_S,"getState",tolua_moon_moonet_Client_getState00);
   tolua_function(tolua_S,"me",tolua_moon_moonet_Client_me00);
   tolua_function(tolua_S,"getNumClients",tolua_moon_moonet_Client_getNumClients00);
   tolua_function(tolua_S,"getClient",tolua_moon_moonet_Client_getClient00);
   tolua_function(tolua_S,"isStillAround",tolua_moon_moonet_Client_isStillAround00);
   tolua_function(tolua_S,"getMinimumClientState",tolua_moon_moonet_Client_getMinimumClientState00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_cclass(tolua_S,"NetworkManager","moonet::NetworkManager","",NULL);
  tolua_beginmodule(tolua_S,"NetworkManager");
   tolua_function(tolua_S,"isActive",tolua_moon_moonet_NetworkManager_isActive00);
   tolua_function(tolua_S,"isServer",tolua_moon_moonet_NetworkManager_isServer00);
   tolua_function(tolua_S,"isClient",tolua_moon_moonet_NetworkManager_isClient00);
   tolua_function(tolua_S,"isConnected",tolua_moon_moonet_NetworkManager_isConnected00);
   tolua_function(tolua_S,"chat",tolua_moon_moonet_NetworkManager_chat00);
   tolua_function(tolua_S,"doStatistics",tolua_moon_moonet_NetworkManager_doStatistics00);
   tolua_function(tolua_S,"isDoingStatistics",tolua_moon_moonet_NetworkManager_isDoingStatistics00);
   tolua_function(tolua_S,"printStatistics",tolua_moon_moonet_NetworkManager_printStatistics00);
   tolua_function(tolua_S,"printClientList",tolua_moon_moonet_NetworkManager_printClientList00);
   tolua_function(tolua_S,"getDefaultSerializationInterval",tolua_moon_moonet_NetworkManager_getDefaultSerializationInterval00);
   tolua_function(tolua_S,"getDefaultFullSerializationInterval",tolua_moon_moonet_NetworkManager_getDefaultFullSerializationInterval00);
   tolua_function(tolua_S,"setDefaultSerializationInterval",tolua_moon_moonet_NetworkManager_setDefaultSerializationInterval00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_cclass(tolua_S,"Player","moonet::Player","",NULL);
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"setName",tolua_moon_moonet_Player_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_moonet_Player_getName00);
   tolua_function(tolua_S,"me",tolua_moon_moonet_Player_me00);
   tolua_function(tolua_S,"myName",tolua_moon_moonet_Player_myName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_cclass(tolua_S,"ConsoleWindow","mdraw::ConsoleWindow","osg::Geode",NULL);
  tolua_beginmodule(tolua_S,"ConsoleWindow");
   tolua_function(tolua_S,"setFont",tolua_moon_mdraw_ConsoleWindow_setFont00);
   tolua_function(tolua_S,"charHeight",tolua_moon_mdraw_ConsoleWindow_charHeight00);
   tolua_function(tolua_S,"charWidth",tolua_moon_mdraw_ConsoleWindow_charWidth00);
   tolua_function(tolua_S,"setBackgroundColor",tolua_moon_mdraw_ConsoleWindow_setBackgroundColor00);
   tolua_function(tolua_S,"getBackgroundColor",tolua_moon_mdraw_ConsoleWindow_getBackgroundColor00);
   tolua_function(tolua_S,"scrollUp",tolua_moon_mdraw_ConsoleWindow_scrollUp00);
   tolua_function(tolua_S,"scrollDown",tolua_moon_mdraw_ConsoleWindow_scrollDown00);
   tolua_function(tolua_S,"pageUp",tolua_moon_mdraw_ConsoleWindow_pageUp00);
   tolua_function(tolua_S,"pageDown",tolua_moon_mdraw_ConsoleWindow_pageDown00);
   tolua_function(tolua_S,"scrollRight",tolua_moon_mdraw_ConsoleWindow_scrollRight00);
   tolua_function(tolua_S,"scrollLeft",tolua_moon_mdraw_ConsoleWindow_scrollLeft00);
   tolua_function(tolua_S,"scrollHome",tolua_moon_mdraw_ConsoleWindow_scrollHome00);
   tolua_function(tolua_S,"scrollEnd",tolua_moon_mdraw_ConsoleWindow_scrollEnd00);
   tolua_function(tolua_S,"del",tolua_moon_mdraw_ConsoleWindow_del00);
   tolua_function(tolua_S,"backSpace",tolua_moon_mdraw_ConsoleWindow_backSpace00);
   tolua_function(tolua_S,"clearLine",tolua_moon_mdraw_ConsoleWindow_clearLine00);
   tolua_function(tolua_S,"cutLine",tolua_moon_mdraw_ConsoleWindow_cutLine00);
   tolua_function(tolua_S,"upHistory",tolua_moon_mdraw_ConsoleWindow_upHistory00);
   tolua_function(tolua_S,"downHistory",tolua_moon_mdraw_ConsoleWindow_downHistory00);
   tolua_function(tolua_S,"leftCursor",tolua_moon_mdraw_ConsoleWindow_leftCursor00);
   tolua_function(tolua_S,"rightCursor",tolua_moon_mdraw_ConsoleWindow_rightCursor00);
   tolua_function(tolua_S,"putch",tolua_moon_mdraw_ConsoleWindow_putch00);
   tolua_function(tolua_S,"print",tolua_moon_mdraw_ConsoleWindow_print00);
   tolua_function(tolua_S,"resize",tolua_moon_mdraw_ConsoleWindow_resize00);
   tolua_function(tolua_S,"sizeUp",tolua_moon_mdraw_ConsoleWindow_sizeUp00);
   tolua_function(tolua_S,"sizeDown",tolua_moon_mdraw_ConsoleWindow_sizeDown00);
   tolua_function(tolua_S,"setPrompt",tolua_moon_mdraw_ConsoleWindow_setPrompt00);
   tolua_function(tolua_S,"setCursorPosition",tolua_moon_mdraw_ConsoleWindow_setCursorPosition00);
   tolua_function(tolua_S,"getNumLines",tolua_moon_mdraw_ConsoleWindow_getNumLines00);
   tolua_function(tolua_S,"setTop",tolua_moon_mdraw_ConsoleWindow_setTop00);
   tolua_function(tolua_S,"getTop",tolua_moon_mdraw_ConsoleWindow_getTop00);
   tolua_function(tolua_S,"getHeight",tolua_moon_mdraw_ConsoleWindow_getHeight00);
   tolua_function(tolua_S,"getLastLine",tolua_moon_mdraw_ConsoleWindow_getLastLine00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_function(tolua_S,"notify",tolua_moon_mdraw_notify00);
  tolua_function(tolua_S,"notify",tolua_moon_mdraw_notify01);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_function(tolua_S,"getNodeString",tolua_moon_mdraw_getNodeString00);
  tolua_function(tolua_S,"getBoundingBox",tolua_moon_mdraw_getBoundingBox00);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Component","moon::Component","",NULL);
  tolua_beginmodule(tolua_S,"Component");
   tolua_function(tolua_S,"getTemplate",tolua_moon_moon_Component_getTemplate00);
   tolua_function(tolua_S,"libraryName",tolua_moon_moon_Component_libraryName00);
   tolua_function(tolua_S,"className",tolua_moon_moon_Component_className00);
   tolua_function(tolua_S,"setName",tolua_moon_moon_Component_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_moon_Component_getName00);
   tolua_function(tolua_S,"realize",tolua_moon_moon_Component_realize00);
   tolua_function(tolua_S,"unrealize",tolua_moon_moon_Component_unrealize00);
   tolua_function(tolua_S,"isRealized",tolua_moon_moon_Component_isRealized00);
   tolua_function(tolua_S,"update",tolua_moon_moon_Component_update00);
   tolua_function(tolua_S,"reset",tolua_moon_moon_Component_reset00);
   tolua_function(tolua_S,"setResetState",tolua_moon_moon_Component_setResetState00);
   tolua_function(tolua_S,"setTag",tolua_moon_moon_Component_setTag00);
   tolua_function(tolua_S,"hasTag",tolua_moon_moon_Component_hasTag00);
   tolua_constant(tolua_S,"WITH_CONTAINER",moon::Component::WITH_CONTAINER);
   tolua_constant(tolua_S,"SPECIFIC",moon::Component::SPECIFIC);
   tolua_function(tolua_S,"setRealizeMode",tolua_moon_moon_Component_setRealizeMode00);
   tolua_function(tolua_S,"getRealizeMode",tolua_moon_moon_Component_getRealizeMode00);
   tolua_function(tolua_S,"setUpdateMode",tolua_moon_moon_Component_setUpdateMode00);
   tolua_function(tolua_S,"getUpdateMode",tolua_moon_moon_Component_getUpdateMode00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ComponentContainer","moon::ComponentContainer","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"ComponentContainer");
   tolua_function(tolua_S,"addComponent",tolua_moon_moon_ComponentContainer_addComponent00);
   tolua_function(tolua_S,"removeComponent",tolua_moon_moon_ComponentContainer_removeComponent00);
   tolua_function(tolua_S,"getNumComponents",tolua_moon_moon_ComponentContainer_getNumComponents00);
   tolua_function(tolua_S,"getComponent",tolua_moon_moon_ComponentContainer_getComponent00);
   tolua_function(tolua_S,"getComponentByTag",tolua_moon_moon_ComponentContainer_getComponentByTag00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"VisualModel","moon::VisualModel","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"VisualModel");
   tolua_function(tolua_S,"getNode",tolua_moon_moon_VisualModel_getNode00);
   tolua_function(tolua_S,"isInitiallyHidden",tolua_moon_moon_VisualModel_isInitiallyHidden00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Instrument","moon::Instrument","moon::VisualModel",NULL);
  tolua_beginmodule(tolua_S,"Instrument");
   tolua_function(tolua_S,"getLabel",tolua_moon_moon_Instrument_getLabel00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"BaseObject","moon::BaseObject","moon::ComponentContainer",NULL);
  tolua_beginmodule(tolua_S,"BaseObject");
   tolua_function(tolua_S,"getRoot",tolua_moon_moon_BaseObject_getRoot00);
   tolua_function(tolua_S,"getTemplate",tolua_moon_moon_BaseObject_getTemplate00);
   tolua_function(tolua_S,"getNumChildren",tolua_moon_moon_BaseObject_getNumChildren00);
   tolua_function(tolua_S,"addChild",tolua_moon_moon_BaseObject_addChild00);
   tolua_function(tolua_S,"removeChild",tolua_moon_moon_BaseObject_removeChild00);
   tolua_function(tolua_S,"removeChildren",tolua_moon_moon_BaseObject_removeChildren00);
   tolua_function(tolua_S,"removeChild",tolua_moon_moon_BaseObject_removeChild01);
   tolua_function(tolua_S,"separateChild",tolua_moon_moon_BaseObject_separateChild00);
   tolua_function(tolua_S,"separateChild",tolua_moon_moon_BaseObject_separateChild01);
   tolua_function(tolua_S,"getChild",tolua_moon_moon_BaseObject_getChild00);
   tolua_function(tolua_S,"getChildIndex",tolua_moon_moon_BaseObject_getChildIndex00);
   tolua_function(tolua_S,"getParent",tolua_moon_moon_BaseObject_getParent00);
   tolua_function(tolua_S,"findRelated",tolua_moon_moon_BaseObject_findRelated00);
   tolua_function(tolua_S,"findRelatedByTemplate",tolua_moon_moon_BaseObject_findRelatedByTemplate00);
   tolua_function(tolua_S,"findRelatedByTag",tolua_moon_moon_BaseObject_findRelatedByTag00);
   tolua_function(tolua_S,"show",tolua_moon_moon_BaseObject_show00);
   tolua_function(tolua_S,"hide",tolua_moon_moon_BaseObject_hide00);
   tolua_function(tolua_S,"addNode",tolua_moon_moon_BaseObject_addNode00);
   tolua_function(tolua_S,"addDebugNode",tolua_moon_moon_BaseObject_addDebugNode00);
   tolua_function(tolua_S,"getNode",tolua_moon_moon_BaseObject_getNode00);
   tolua_constant(tolua_S,"BBOX",moon::BaseObject::BBOX);
   tolua_constant(tolua_S,"THICK_BBOX",moon::BaseObject::THICK_BBOX);
   tolua_constant(tolua_S,"TRANSPARENT_BBOX",moon::BaseObject::TRANSPARENT_BBOX);
   tolua_constant(tolua_S,"SCRIBE",moon::BaseObject::SCRIBE);
   tolua_constant(tolua_S,"THICK_SCRIBE",moon::BaseObject::THICK_SCRIBE);
   tolua_function(tolua_S,"highlight",tolua_moon_moon_BaseObject_highlight00);
   tolua_function(tolua_S,"highlight",tolua_moon_moon_BaseObject_highlight01);
   tolua_constant(tolua_S,"DISPLAY_NORMAL",moon::BaseObject::DISPLAY_NORMAL);
   tolua_constant(tolua_S,"DISPLAY_DEBUG",moon::BaseObject::DISPLAY_DEBUG);
   tolua_function(tolua_S,"setDisplayMode",tolua_moon_moon_BaseObject_setDisplayMode00);
   tolua_function(tolua_S,"getDisplayMode",tolua_moon_moon_BaseObject_getDisplayMode00);
   tolua_function(tolua_S,"setName",tolua_moon_moon_BaseObject_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_moon_BaseObject_getName00);
   tolua_function(tolua_S,"id",tolua_moon_moon_BaseObject_id00);
   tolua_function(tolua_S,"pointAt",tolua_moon_moon_BaseObject_pointAt00);
   tolua_function(tolua_S,"pointAt",tolua_moon_moon_BaseObject_pointAt01);
   tolua_function(tolua_S,"pointAt",tolua_moon_moon_BaseObject_pointAt02);
   tolua_function(tolua_S,"getRange",tolua_moon_moon_BaseObject_getRange00);
   tolua_function(tolua_S,"getAzimuth",tolua_moon_moon_BaseObject_getAzimuth00);
   tolua_function(tolua_S,"getElevation",tolua_moon_moon_BaseObject_getElevation00);
   tolua_function(tolua_S,"getSpherical",tolua_moon_moon_BaseObject_getSpherical00);
   tolua_function(tolua_S,"getHeightAboveTerrain",tolua_moon_moon_BaseObject_getHeightAboveTerrain00);
   tolua_function(tolua_S,"getHeightAboveTerrain",tolua_moon_moon_BaseObject_getHeightAboveTerrain01);
   tolua_function(tolua_S,"clampToTerrain",tolua_moon_moon_BaseObject_clampToTerrain00);
   tolua_function(tolua_S,"clampToTerrain",tolua_moon_moon_BaseObject_clampToTerrain01);
   tolua_function(tolua_S,"alignToTerrain",tolua_moon_moon_BaseObject_alignToTerrain00);
   tolua_function(tolua_S,"alignToTerrain",tolua_moon_moon_BaseObject_alignToTerrain01);
   tolua_function(tolua_S,"getBottomCenter",tolua_moon_moon_BaseObject_getBottomCenter00);
   tolua_function(tolua_S,"asKinematic",tolua_moon_moon_BaseObject_asKinematic00);
   tolua_function(tolua_S,"setScriptUpdateInterval",tolua_moon_moon_BaseObject_setScriptUpdateInterval00);
   tolua_function(tolua_S,"getScriptUpdateInterval",tolua_moon_moon_BaseObject_getScriptUpdateInterval00);
   tolua_function(tolua_S,"remove",tolua_moon_moon_BaseObject_remove00);
   tolua_function(tolua_S,"setRemoveTime",tolua_moon_moon_BaseObject_setRemoveTime00);
   tolua_function(tolua_S,"getRemoveTime",tolua_moon_moon_BaseObject_getRemoveTime00);
   tolua_function(tolua_S,"findParameter",tolua_moon_moon_BaseObject_findParameter00);
   tolua_function(tolua_S,"setPosition",tolua_moon_moon_BaseObject_setPosition00);
   tolua_function(tolua_S,"setPosition",tolua_moon_moon_BaseObject_setPosition01);
   tolua_function(tolua_S,"getPosition",tolua_moon_moon_BaseObject_getPosition00);
   tolua_function(tolua_S,"getPosition",tolua_moon_moon_BaseObject_getPosition01);
   tolua_function(tolua_S,"setRotation",tolua_moon_moon_BaseObject_setRotation00);
   tolua_function(tolua_S,"getRotation",tolua_moon_moon_BaseObject_getRotation00);
   tolua_function(tolua_S,"setAttitude",tolua_moon_moon_BaseObject_setAttitude00);
   tolua_function(tolua_S,"getAttitude",tolua_moon_moon_BaseObject_getAttitude00);
   tolua_function(tolua_S,"setAttitude",tolua_moon_moon_BaseObject_setAttitude01);
   tolua_function(tolua_S,"getAttitude",tolua_moon_moon_BaseObject_getAttitude01);
   tolua_function(tolua_S,"forward",tolua_moon_moon_BaseObject_forward00);
   tolua_function(tolua_S,"right",tolua_moon_moon_BaseObject_right00);
   tolua_function(tolua_S,"up",tolua_moon_moon_BaseObject_up00);
   tolua_function(tolua_S,"move",tolua_moon_moon_BaseObject_move00);
   tolua_function(tolua_S,"move",tolua_moon_moon_BaseObject_move01);
   tolua_function(tolua_S,"move",tolua_moon_moon_BaseObject_move02);
   tolua_function(tolua_S,"rotate",tolua_moon_moon_BaseObject_rotate00);
   tolua_function(tolua_S,"rotateEuler",tolua_moon_moon_BaseObject_rotateEuler00);
   tolua_function(tolua_S,"rotateEuler",tolua_moon_moon_BaseObject_rotateEuler01);
   tolua_function(tolua_S,"yaw",tolua_moon_moon_BaseObject_yaw00);
   tolua_function(tolua_S,"pitch",tolua_moon_moon_BaseObject_pitch00);
   tolua_function(tolua_S,"roll",tolua_moon_moon_BaseObject_roll00);
   tolua_function(tolua_S,"scale",tolua_moon_moon_BaseObject_scale00);
   tolua_function(tolua_S,"scale",tolua_moon_moon_BaseObject_scale01);
   tolua_function(tolua_S,"getTransform",tolua_moon_moon_BaseObject_getTransform00);
   tolua_function(tolua_S,"setTransformMatrix",tolua_moon_moon_BaseObject_setTransformMatrix00);
   tolua_function(tolua_S,"getTransformMatrix",tolua_moon_moon_BaseObject_getTransformMatrix00);
   tolua_function(tolua_S,"getEulerAnglesFromMatrix",tolua_moon_moon_BaseObject_getEulerAnglesFromMatrix00);
   tolua_function(tolua_S,"getMatrixFromEulerAngles",tolua_moon_moon_BaseObject_getMatrixFromEulerAngles00);
   tolua_function(tolua_S,"getLocalUpVector",tolua_moon_moon_BaseObject_getLocalUpVector00);
   tolua_function(tolua_S,"setPositionLatLongHeight",tolua_moon_moon_BaseObject_setPositionLatLongHeight00);
   tolua_function(tolua_S,"setPositionLatLongHeight",tolua_moon_moon_BaseObject_setPositionLatLongHeight01);
   tolua_function(tolua_S,"getPositionLatLongHeight",tolua_moon_moon_BaseObject_getPositionLatLongHeight00);
   tolua_function(tolua_S,"getPositionLatLongHeight",tolua_moon_moon_BaseObject_getPositionLatLongHeight01);
   tolua_function(tolua_S,"isGeocentric",tolua_moon_moon_BaseObject_isGeocentric00);
   tolua_function(tolua_S,"getOwner",tolua_moon_moon_BaseObject_getOwner00);
   tolua_function(tolua_S,"setOwner",tolua_moon_moon_BaseObject_setOwner00);
   tolua_function(tolua_S,"isConstructed",tolua_moon_moon_BaseObject_isConstructed00);
   tolua_function(tolua_S,"isRemote",tolua_moon_moon_BaseObject_isRemote00);
   tolua_function(tolua_S,"setCloaked",tolua_moon_moon_BaseObject_setCloaked00);
   tolua_function(tolua_S,"isCloaked",tolua_moon_moon_BaseObject_isCloaked00);
   tolua_function(tolua_S,"setSerializationInterval",tolua_moon_moon_BaseObject_setSerializationInterval00);
   tolua_function(tolua_S,"getSerializationInterval",tolua_moon_moon_BaseObject_getSerializationInterval00);
   tolua_function(tolua_S,"getFullSerializationInterval",tolua_moon_moon_BaseObject_getFullSerializationInterval00);
   tolua_function(tolua_S,"isVisibleToClient",tolua_moon_moon_BaseObject_isVisibleToClient00);
   tolua_function(tolua_S,"libraryName",tolua_moon_moon_BaseObject_libraryName00);
   tolua_function(tolua_S,"className",tolua_moon_moon_BaseObject_className00);
   tolua_function(tolua_S,"realize",tolua_moon_moon_BaseObject_realize00);
   tolua_function(tolua_S,"unrealize",tolua_moon_moon_BaseObject_unrealize00);
   tolua_function(tolua_S,"isRealized",tolua_moon_moon_BaseObject_isRealized00);
   tolua_function(tolua_S,"update",tolua_moon_moon_BaseObject_update00);
   tolua_function(tolua_S,"reset",tolua_moon_moon_BaseObject_reset00);
   tolua_function(tolua_S,"setResetState",tolua_moon_moon_BaseObject_setResetState00);
   tolua_function(tolua_S,"setTag",tolua_moon_moon_BaseObject_setTag00);
   tolua_function(tolua_S,"hasTag",tolua_moon_moon_BaseObject_hasTag00);
   tolua_constant(tolua_S,"WITH_CONTAINER",moon::BaseObject::WITH_CONTAINER);
   tolua_constant(tolua_S,"SPECIFIC",moon::BaseObject::SPECIFIC);
   tolua_function(tolua_S,"setRealizeMode",tolua_moon_moon_BaseObject_setRealizeMode00);
   tolua_function(tolua_S,"getRealizeMode",tolua_moon_moon_BaseObject_getRealizeMode00);
   tolua_function(tolua_S,"setUpdateMode",tolua_moon_moon_BaseObject_setUpdateMode00);
   tolua_function(tolua_S,"getUpdateMode",tolua_moon_moon_BaseObject_getUpdateMode00);
   tolua_function(tolua_S,"addComponent",tolua_moon_moon_BaseObject_addComponent00);
   tolua_function(tolua_S,"removeComponent",tolua_moon_moon_BaseObject_removeComponent00);
   tolua_function(tolua_S,"getNumComponents",tolua_moon_moon_BaseObject_getNumComponents00);
   tolua_function(tolua_S,"getComponent",tolua_moon_moon_BaseObject_getComponent00);
   tolua_function(tolua_S,"getComponentByTag",tolua_moon_moon_BaseObject_getComponentByTag00);
   tolua_function(tolua_S,"getNumParameters",tolua_moon_moon_BaseObject_getNumParameters00);
   tolua_function(tolua_S,"getParameter",tolua_moon_moon_BaseObject_getParameter00);
   tolua_function(tolua_S,"getParameter",tolua_moon_moon_BaseObject_getParameter01);
   tolua_function(tolua_S,"getParameter",tolua_moon_moon_BaseObject_getParameter02);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,109,111,111,110, 46,
   67,111,109,112,111,110,101,110,116, 58,112,111,115,105,116,
  105,111,110, 88, 89, 90, 40, 41, 10,118, 32, 61, 32,115,101,
  108,102, 58,103,101,116, 80,111,115,105,116,105,111,110, 40,
   41, 10,114,101,116,117,114,110, 32,118, 58,103,101,116, 40,
   41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
  109,111,111,110, 46, 67,111,109,112,111,110,101,110,116, 58,
  112,111,115,105,116,105,111,110, 76, 76, 72, 40, 41, 10,118,
   32, 61, 32,115,101,108,102, 58,103,101,116, 80,111,115,105,
  116,105,111,110, 76, 97,116, 76,111,110,103, 72,101,105,103,
  104,116, 40, 41, 10,114,101,116,117,114,110, 32,118, 58,120,
   40, 41, 42, 49, 56, 48, 47,109, 97,116,104, 46,112,105, 44,
   32,118, 58,121, 40, 41, 42, 49, 56, 48, 47,109, 97,116,104,
   46,112,105, 44, 32,118, 58,122, 40, 41, 10,101,110,100, 10,
  102,117,110, 99,116,105,111,110, 32,109,111,111,110, 46, 67,
  111,109,112,111,110,101,110,116, 58, 97,116,116,105,116,117,
  100,101, 40, 41, 10,118, 32, 61, 32,115,101,108,102, 58,103,
  101,116, 65,116,116,105,116,117,100,101, 40, 41, 10,114,101,
  116,117,114,110, 32, 40,118, 42, 49, 56, 48, 47,109, 97,116,
  104, 46,112,105, 41, 58,103,101,116, 40, 41, 10,101,110,100,
  32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 2");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */

 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"VisualObject","moon::VisualObject","moon::BaseObject",NULL);
  tolua_beginmodule(tolua_S,"VisualObject");
   tolua_function(tolua_S,"getNumModels",tolua_moon_moon_VisualObject_getNumModels00);
   tolua_function(tolua_S,"showModel",tolua_moon_moon_VisualObject_showModel00);
   tolua_function(tolua_S,"setModelVisibility",tolua_moon_moon_VisualObject_setModelVisibility00);
   tolua_function(tolua_S,"showModel",tolua_moon_moon_VisualObject_showModel01);
   tolua_function(tolua_S,"setModelVisibility",tolua_moon_moon_VisualObject_setModelVisibility01);
   tolua_function(tolua_S,"showModelsWithTag",tolua_moon_moon_VisualObject_showModelsWithTag00);
   tolua_function(tolua_S,"setModelVisibilityWithTag",tolua_moon_moon_VisualObject_setModelVisibilityWithTag00);
   tolua_function(tolua_S,"showModelsWithoutTag",tolua_moon_moon_VisualObject_showModelsWithoutTag00);
   tolua_function(tolua_S,"setModelVisibilityWithoutTag",tolua_moon_moon_VisualObject_setModelVisibilityWithoutTag00);
   tolua_function(tolua_S,"showAllModels",tolua_moon_moon_VisualObject_showAllModels00);
   tolua_function(tolua_S,"hideAllModels",tolua_moon_moon_VisualObject_hideAllModels00);
   tolua_function(tolua_S,"showLabel",tolua_moon_moon_VisualObject_showLabel00);
   tolua_function(tolua_S,"hideLabel",tolua_moon_moon_VisualObject_hideLabel00);
   tolua_function(tolua_S,"setLabel",tolua_moon_moon_VisualObject_setLabel00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"KinematicObject","moon::KinematicObject","moon::VisualObject",NULL);
  tolua_beginmodule(tolua_S,"KinematicObject");
   tolua_function(tolua_S,"setAnimationPaused",tolua_moon_moon_KinematicObject_setAnimationPaused00);
   tolua_function(tolua_S,"getAnimationPaused",tolua_moon_moon_KinematicObject_getAnimationPaused00);
   tolua_function(tolua_S,"setTransformationUpdatesControlPoint",tolua_moon_moon_KinematicObject_setTransformationUpdatesControlPoint00);
   tolua_function(tolua_S,"setVelocity",tolua_moon_moon_KinematicObject_setVelocity00);
   tolua_function(tolua_S,"setVelocity",tolua_moon_moon_KinematicObject_setVelocity01);
   tolua_function(tolua_S,"setAngularVelocity",tolua_moon_moon_KinematicObject_setAngularVelocity00);
   tolua_function(tolua_S,"setAngularVelocity",tolua_moon_moon_KinematicObject_setAngularVelocity01);
   tolua_function(tolua_S,"getVelocity",tolua_moon_moon_KinematicObject_getVelocity00);
   tolua_function(tolua_S,"getVelocity",tolua_moon_moon_KinematicObject_getVelocity01);
   tolua_function(tolua_S,"getWorldVelocity",tolua_moon_moon_KinematicObject_getWorldVelocity00);
   tolua_function(tolua_S,"getWorldVelocity",tolua_moon_moon_KinematicObject_getWorldVelocity01);
   tolua_function(tolua_S,"getAngularVelocity",tolua_moon_moon_KinematicObject_getAngularVelocity00);
   tolua_function(tolua_S,"getAngularVelocity",tolua_moon_moon_KinematicObject_getAngularVelocity01);
   tolua_function(tolua_S,"getWorldAngularVelocity",tolua_moon_moon_KinematicObject_getWorldAngularVelocity00);
   tolua_function(tolua_S,"getWorldAngularVelocity",tolua_moon_moon_KinematicObject_getWorldAngularVelocity01);
   tolua_function(tolua_S,"requestPosition",tolua_moon_moon_KinematicObject_requestPosition00);
   tolua_function(tolua_S,"requestRotation",tolua_moon_moon_KinematicObject_requestRotation00);
   tolua_function(tolua_S,"requestAttitude",tolua_moon_moon_KinematicObject_requestAttitude00);
   tolua_function(tolua_S,"requestVelocity",tolua_moon_moon_KinematicObject_requestVelocity00);
   tolua_function(tolua_S,"requestAngularVelocity",tolua_moon_moon_KinematicObject_requestAngularVelocity00);
   tolua_function(tolua_S,"stop",tolua_moon_moon_KinematicObject_stop00);
   tolua_function(tolua_S,"getHeight",tolua_moon_moon_KinematicObject_getHeight00);
   tolua_function(tolua_S,"reset",tolua_moon_moon_KinematicObject_reset00);
   tolua_variable(tolua_S,"linear_threshold",tolua_get_moon__KinematicObject_linear_threshold,tolua_set_moon__KinematicObject_linear_threshold);
   tolua_variable(tolua_S,"angular_threshold",tolua_get_moon__KinematicObject_angular_threshold,tolua_set_moon__KinematicObject_angular_threshold);
   tolua_variable(tolua_S,"anim_velocity_timestep",tolua_get_moon__KinematicObject_anim_velocity_timestep,tolua_set_moon__KinematicObject_anim_velocity_timestep);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Camera","moon::Camera","moon::KinematicObject",NULL);
  tolua_beginmodule(tolua_S,"Camera");
   tolua_constant(tolua_S,"MIN_ROLL",moon::Camera::MIN_ROLL);
   tolua_constant(tolua_S,"MAX_ROLL",moon::Camera::MAX_ROLL);
   tolua_constant(tolua_S,"MIN_PITCH",moon::Camera::MIN_PITCH);
   tolua_constant(tolua_S,"MAX_PITCH",moon::Camera::MAX_PITCH);
   tolua_constant(tolua_S,"MIN_YAW",moon::Camera::MIN_YAW);
   tolua_constant(tolua_S,"MAX_YAW",moon::Camera::MAX_YAW);
   tolua_constant(tolua_S,"MIN_FORWARD",moon::Camera::MIN_FORWARD);
   tolua_constant(tolua_S,"MAX_FORWARD",moon::Camera::MAX_FORWARD);
   tolua_constant(tolua_S,"MIN_RIGHT",moon::Camera::MIN_RIGHT);
   tolua_constant(tolua_S,"MAX_RIGHT",moon::Camera::MAX_RIGHT);
   tolua_constant(tolua_S,"MIN_UP",moon::Camera::MIN_UP);
   tolua_constant(tolua_S,"MAX_UP",moon::Camera::MAX_UP);
   tolua_constant(tolua_S,"NONE",moon::Camera::NONE);
   tolua_constant(tolua_S,"POINT",moon::Camera::POINT);
   tolua_constant(tolua_S,"FOLLOW",moon::Camera::FOLLOW);
   tolua_constant(tolua_S,"CHASE",moon::Camera::CHASE);
   tolua_constant(tolua_S,"CHASE_HEADING",moon::Camera::CHASE_HEADING);
   tolua_function(tolua_S,"isActive",tolua_moon_moon_Camera_isActive00);
   tolua_function(tolua_S,"activate",tolua_moon_moon_Camera_activate00);
   tolua_function(tolua_S,"setPerspective",tolua_moon_moon_Camera_setPerspective00);
   tolua_function(tolua_S,"getPerspective",tolua_moon_moon_Camera_getPerspective00);
   tolua_function(tolua_S,"getFOV",tolua_moon_moon_Camera_getFOV00);
   tolua_function(tolua_S,"getAspect",tolua_moon_moon_Camera_getAspect00);
   tolua_function(tolua_S,"getNearClip",tolua_moon_moon_Camera_getNearClip00);
   tolua_function(tolua_S,"getFarClip",tolua_moon_moon_Camera_getFarClip00);
   tolua_function(tolua_S,"setFree",tolua_moon_moon_Camera_setFree00);
   tolua_function(tolua_S,"isFree",tolua_moon_moon_Camera_isFree00);
   tolua_function(tolua_S,"setLimit",tolua_moon_moon_Camera_setLimit00);
   tolua_function(tolua_S,"getLimit",tolua_moon_moon_Camera_getLimit00);
   tolua_function(tolua_S,"track",tolua_moon_moon_Camera_track00);
   tolua_function(tolua_S,"track",tolua_moon_moon_Camera_track01);
   tolua_function(tolua_S,"getTrackTarget",tolua_moon_moon_Camera_getTrackTarget00);
   tolua_function(tolua_S,"getTrackMode",tolua_moon_moon_Camera_getTrackMode00);
   tolua_function(tolua_S,"setTrackParameters",tolua_moon_moon_Camera_setTrackParameters00);
   tolua_function(tolua_S,"getTrackDistance",tolua_moon_moon_Camera_getTrackDistance00);
   tolua_function(tolua_S,"getTrackAzimuth",tolua_moon_moon_Camera_getTrackAzimuth00);
   tolua_function(tolua_S,"getTrackElevation",tolua_moon_moon_Camera_getTrackElevation00);
   tolua_function(tolua_S,"setHideWhenActive",tolua_moon_moon_Camera_setHideWhenActive00);
   tolua_function(tolua_S,"hidesWhenActive",tolua_moon_moon_Camera_hidesWhenActive00);
   tolua_function(tolua_S,"setMove2D",tolua_moon_moon_Camera_setMove2D00);
   tolua_function(tolua_S,"getMove2D",tolua_moon_moon_Camera_getMove2D00);
   tolua_function(tolua_S,"setPivot",tolua_moon_moon_Camera_setPivot00);
   tolua_function(tolua_S,"getPivot",tolua_moon_moon_Camera_getPivot00);
   tolua_function(tolua_S,"setInfoLevel",tolua_moon_moon_Camera_setInfoLevel00);
   tolua_function(tolua_S,"getInfoLevel",tolua_moon_moon_Camera_getInfoLevel00);
   tolua_function(tolua_S,"getHUD",tolua_moon_moon_Camera_getHUD00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Parameter","moon::Parameter","osg::Object",NULL);
  tolua_beginmodule(tolua_S,"Parameter");
   tolua_function(tolua_S,"set",tolua_moon_moon_Parameter_set00);
   tolua_function(tolua_S,"get",tolua_moon_moon_Parameter_get00);
   tolua_function(tolua_S,"isConnected",tolua_moon_moon_Parameter_isConnected00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Scenario","moon::Scenario","moon::ComponentContainer",NULL);
  tolua_beginmodule(tolua_S,"Scenario");
   tolua_function(tolua_S,"setName",tolua_moon_moon_Scenario_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_moon_Scenario_getName00);
   tolua_function(tolua_S,"setDisplayMode",tolua_moon_moon_Scenario_setDisplayMode00);
   tolua_function(tolua_S,"getDisplayMode",tolua_moon_moon_Scenario_getDisplayMode00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Application","moon::Application","",NULL);
  tolua_beginmodule(tolua_S,"Application");
   tolua_function(tolua_S,"host",tolua_moon_moon_Application_host00);
   tolua_function(tolua_S,"host",tolua_moon_moon_Application_host01);
   tolua_function(tolua_S,"join",tolua_moon_moon_Application_join00);
   tolua_function(tolua_S,"disconnect",tolua_moon_moon_Application_disconnect00);
   tolua_function(tolua_S,"getName",tolua_moon_moon_Application_getName00);
   tolua_function(tolua_S,"setDone",tolua_moon_moon_Application_setDone00);
   tolua_function(tolua_S,"isDone",tolua_moon_moon_Application_isDone00);
   tolua_function(tolua_S,"setEndTime",tolua_moon_moon_Application_setEndTime00);
   tolua_function(tolua_S,"getEndTime",tolua_moon_moon_Application_getEndTime00);
   tolua_function(tolua_S,"setNonRealtimeSimulation",tolua_moon_moon_Application_setNonRealtimeSimulation00);
   tolua_function(tolua_S,"getNonRealtimeSimulation",tolua_moon_moon_Application_getNonRealtimeSimulation00);
   tolua_function(tolua_S,"setTargetFrameRate",tolua_moon_moon_Application_setTargetFrameRate00);
   tolua_function(tolua_S,"getTargetFrameRate",tolua_moon_moon_Application_getTargetFrameRate00);
   tolua_function(tolua_S,"getAverageFrameRate",tolua_moon_moon_Application_getAverageFrameRate00);
   tolua_function(tolua_S,"getSleepTime",tolua_moon_moon_Application_getSleepTime00);
   tolua_function(tolua_S,"setMaxSleepTime",tolua_moon_moon_Application_setMaxSleepTime00);
   tolua_function(tolua_S,"getMaxSleepTime",tolua_moon_moon_Application_getMaxSleepTime00);
   tolua_function(tolua_S,"setExitCode",tolua_moon_moon_Application_setExitCode00);
   tolua_function(tolua_S,"getExitCode",tolua_moon_moon_Application_getExitCode00);
   tolua_function(tolua_S,"load",tolua_moon_moon_Application_load00);
   tolua_function(tolua_S,"load",tolua_moon_moon_Application_load01);
   tolua_function(tolua_S,"load",tolua_moon_moon_Application_load02);
   tolua_function(tolua_S,"getScenario",tolua_moon_moon_Application_getScenario00);
   tolua_function(tolua_S,"loadScenario",tolua_moon_moon_Application_loadScenario00);
   tolua_function(tolua_S,"saveScenario",tolua_moon_moon_Application_saveScenario00);
   tolua_function(tolua_S,"getRootPath",tolua_moon_moon_Application_getRootPath00);
   tolua_function(tolua_S,"getNetworkGame",tolua_moon_moon_Application_getNetworkGame00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Viewer","moon::Viewer","",NULL);
  tolua_beginmodule(tolua_S,"Viewer");
   tolua_function(tolua_S,"setStatusText",tolua_moon_moon_Viewer_setStatusText00);
   tolua_function(tolua_S,"setBannerText",tolua_moon_moon_Viewer_setBannerText00);
   tolua_function(tolua_S,"setEditMode",tolua_moon_moon_Viewer_setEditMode00);
   tolua_function(tolua_S,"isEditing",tolua_moon_moon_Viewer_isEditing00);
   tolua_function(tolua_S,"getConsoleWindow",tolua_moon_moon_Viewer_getConsoleWindow00);
   tolua_function(tolua_S,"showConsoleWindow",tolua_moon_moon_Viewer_showConsoleWindow00);
   tolua_function(tolua_S,"isConsoleWindowShown",tolua_moon_moon_Viewer_isConsoleWindowShown00);
   tolua_function(tolua_S,"frame",tolua_moon_moon_Viewer_frame00);
   tolua_function(tolua_S,"setManipulator",tolua_moon_moon_Viewer_setManipulator00);
   tolua_function(tolua_S,"getManipulator",tolua_moon_moon_Viewer_getManipulator00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"EditHandler","moon::EditHandler","",NULL);
  tolua_beginmodule(tolua_S,"EditHandler");
   tolua_function(tolua_S,"setEditMode",tolua_moon_moon_EditHandler_setEditMode00);
   tolua_function(tolua_S,"isEditing",tolua_moon_moon_EditHandler_isEditing00);
   tolua_function(tolua_S,"getSelectedObject",tolua_moon_moon_EditHandler_getSelectedObject00);
   tolua_function(tolua_S,"select",tolua_moon_moon_EditHandler_select00);
   tolua_function(tolua_S,"setGrid",tolua_moon_moon_EditHandler_setGrid00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Scheduler","moon::Scheduler","",NULL);
  tolua_beginmodule(tolua_S,"Scheduler");
   tolua_function(tolua_S,"schedule",tolua_moon_moon_Scheduler_schedule00);
   tolua_function(tolua_S,"scheduleAt",tolua_moon_moon_Scheduler_scheduleAt00);
   tolua_function(tolua_S,"scheduleAtGameTime",tolua_moon_moon_Scheduler_scheduleAtGameTime00);
   tolua_function(tolua_S,"unschedule",tolua_moon_moon_Scheduler_unschedule00);
   tolua_function(tolua_S,"clear",tolua_moon_moon_Scheduler_clear00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"SimulationManager","moon::SimulationManager","",NULL);
  tolua_beginmodule(tolua_S,"SimulationManager");
   tolua_function(tolua_S,"getTimeStep",tolua_moon_moon_SimulationManager_getTimeStep00);
   tolua_function(tolua_S,"setTimeStep",tolua_moon_moon_SimulationManager_setTimeStep00);
   tolua_function(tolua_S,"setPaused",tolua_moon_moon_SimulationManager_setPaused00);
   tolua_function(tolua_S,"isPaused",tolua_moon_moon_SimulationManager_isPaused00);
   tolua_function(tolua_S,"setTime",tolua_moon_moon_SimulationManager_setTime00);
   tolua_function(tolua_S,"getTime",tolua_moon_moon_SimulationManager_getTime00);
   tolua_function(tolua_S,"getGameTimeOffset",tolua_moon_moon_SimulationManager_getGameTimeOffset00);
   tolua_function(tolua_S,"getViewerTimeOffset",tolua_moon_moon_SimulationManager_getViewerTimeOffset00);
   tolua_function(tolua_S,"getTimeScale",tolua_moon_moon_SimulationManager_getTimeScale00);
   tolua_function(tolua_S,"setTimeScale",tolua_moon_moon_SimulationManager_setTimeScale00);
   tolua_function(tolua_S,"instance",tolua_moon_moon_SimulationManager_instance00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"NetworkGame","moon::NetworkGame","FactoryProduct",NULL);
  tolua_beginmodule(tolua_S,"NetworkGame");
   tolua_function(tolua_S,"getName",tolua_moon_moon_NetworkGame_getName00);
   tolua_function(tolua_S,"getScenarioName",tolua_moon_moon_NetworkGame_getScenarioName00);
   tolua_function(tolua_S,"getGameTime",tolua_moon_moon_NetworkGame_getGameTime00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Control","moon::Control","",NULL);
  tolua_beginmodule(tolua_S,"Control");
   tolua_constant(tolua_S,"MOMENTARY",moon::Control::MOMENTARY);
   tolua_constant(tolua_S,"TOGGLE",moon::Control::TOGGLE);
   tolua_constant(tolua_S,"AXIS",moon::Control::AXIS);
   tolua_function(tolua_S,"setValue",tolua_moon_moon_Control_setValue00);
   tolua_function(tolua_S,"getValue",tolua_moon_moon_Control_getValue00);
   tolua_function(tolua_S,"setType",tolua_moon_moon_Control_setType00);
   tolua_function(tolua_S,"getType",tolua_moon_moon_Control_getType00);
   tolua_function(tolua_S,"setName",tolua_moon_moon_Control_setName00);
   tolua_function(tolua_S,"getName",tolua_moon_moon_Control_getName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"Plugin","moon::Plugin","",NULL);
  tolua_beginmodule(tolua_S,"Plugin");
   tolua_function(tolua_S,"getName",tolua_moon_moon_Plugin_getName00);
   tolua_function(tolua_S,"getDescription",tolua_moon_moon_Plugin_getDescription00);
   tolua_function(tolua_S,"getAuthor",tolua_moon_moon_Plugin_getAuthor00);
   tolua_function(tolua_S,"getVersion",tolua_moon_moon_Plugin_getVersion00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moon",0);
 tolua_beginmodule(tolua_S,"moon");
  tolua_cclass(tolua_S,"PluginManager","moon::PluginManager","",NULL);
  tolua_beginmodule(tolua_S,"PluginManager");
   tolua_function(tolua_S,"load",tolua_moon_moon_PluginManager_load00);
   tolua_function(tolua_S,"loadAll",tolua_moon_moon_PluginManager_loadAll00);
   tolua_function(tolua_S,"get",tolua_moon_moon_PluginManager_get00);
   tolua_function(tolua_S,"getNumPlugins",tolua_moon_moon_PluginManager_getNumPlugins00);
   tolua_function(tolua_S,"getPlugin",tolua_moon_moon_PluginManager_getPlugin00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);

 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,111,115,103, 46, 86,
  101, 99, 51, 58, 95, 95,116,111,115,116,114,105,110,103, 40,
   41, 10,114,101,116,117,114,110, 32, 34, 40, 34, 32, 46, 46,
   32,115,101,108,102, 58,120, 40, 41, 32, 46, 46, 32, 34, 44,
   34, 32, 46, 46, 32,115,101,108,102, 58,121, 40, 41, 32, 46,
   46, 32, 34, 44, 34, 32, 46, 46, 32,115,101,108,102, 58,122,
   40, 41, 32, 46, 46, 32, 34, 41, 34, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,111,115,103, 46, 86,101, 99,
   52, 58, 95, 95,116,111,115,116,114,105,110,103, 40, 41, 10,
  114,101,116,117,114,110, 32, 34, 40, 34, 32, 46, 46, 32,115,
  101,108,102, 58,120, 40, 41, 32, 46, 46, 32, 34, 44, 34, 32,
   46, 46, 32,115,101,108,102, 58,121, 40, 41, 32, 46, 46, 32,
   34, 44, 34, 32, 46, 46, 32,115,101,108,102, 58,122, 40, 41,
   32, 46, 46, 32, 34, 44, 34, 32, 46, 46, 32,115,101,108,102,
   58,119, 40, 41, 32, 46, 46, 32, 34, 41, 34, 10,101,110,100,
   10,102,117,110, 99,116,105,111,110, 32,109,111,111,110, 46,
   66, 97,115,101, 79, 98,106,101, 99,116, 58, 95, 95,116,111,
  115,116,114,105,110,103, 40, 41, 10,114,101,116,117,114,110,
   32, 34, 79, 98,106,101, 99,116, 32, 39, 34, 32, 46, 46, 32,
  115,101,108,102, 58,103,101,116, 78, 97,109,101, 40, 41, 32,
   46, 46, 32, 34, 39, 34, 10,101,110,100, 10,102,117,110, 99,
  116,105,111,110, 32,109,111,111,110, 46, 67, 97,109,101,114,
   97, 58, 95, 95,116,111,115,116,114,105,110,103, 40, 41, 10,
  114,101,116,117,114,110, 32, 34, 67, 97,109,101,114, 97, 32,
   39, 34, 32, 46, 46, 32,115,101,108,102, 58,103,101,116, 78,
   97,109,101, 40, 41, 32, 46, 46, 32, 34, 39, 34, 10,101,110,
  100, 10,102,117,110, 99,116,105,111,110, 32,109,111,111,110,
   46, 83, 99,101,110, 97,114,105,111, 58, 95, 95,116,111,115,
  116,114,105,110,103, 40, 41, 10,114,101,116,117,114,110, 32,
   34, 83, 99,101,110, 97,114,105,111, 32, 39, 34, 32, 46, 46,
   32,115,101,108,102, 58,103,101,116, 78, 97,109,101, 40, 41,
   32, 46, 46, 32, 34, 39, 34, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/tostring.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,101,118,101,110,116, 32, 61, 32,123,125, 10,102,117,110,
   99,116,105,111,110, 32,101,118,101,110,116, 46,110,101,119,
   83, 99,101,110, 97,114,105,111, 40, 41, 10,105,102, 32, 40,
  118,105,101,119,101,114, 32, 61, 61, 32,110,105,108, 41, 32,
  116,104,101,110, 10,114,101,116,117,114,110, 10,101,110,100,
   10,105,102, 32, 40,115, 99,101,110, 97,114,105,111, 32, 61,
   61, 32,110,105,108, 41, 32,116,104,101,110, 10,118,105,101,
  119,101,114, 58,115,101,116, 66, 97,110,110,101,114, 84,101,
  120,116, 40, 34, 78, 79, 32, 83, 67, 69, 78, 65, 82, 73, 79,
   34, 41, 10,101,108,115,101,105,102, 32, 40,111, 98,106,101,
   99,116,115, 46, 99, 97,109, 32, 61, 61, 32,110,105,108, 32,
   97,110,100, 32,118,105,101,119,101,114, 58,103,101,116, 77,
   97,110,105,112,117,108, 97,116,111,114, 40, 41, 32, 61, 61,
   32, 48, 41, 32,116,104,101,110, 10,118,105,101,119,101,114,
   58,115,101,116, 66, 97,110,110,101,114, 84,101,120,116, 40,
   34, 78, 79, 32, 67, 65, 77, 69, 82, 65, 34, 41, 10,101,108,
  115,101,105,102, 32, 40,109,111,111,110, 46, 83,105,109,117,
  108, 97,116,105,111,110, 77, 97,110, 97,103,101,114, 58,105,
  110,115,116, 97,110, 99,101, 40, 41, 58,105,115, 80, 97,117,
  115,101,100, 40, 41, 32, 97,110,100, 32,110,111,116, 32,118,
  105,101,119,101,114, 58,105,115, 69,100,105,116,105,110,103,
   40, 41, 41, 32,116,104,101,110, 10,118,105,101,119,101,114,
   58,115,101,116, 66, 97,110,110,101,114, 84,101,120,116, 40,
   34, 80, 65, 85, 83, 69, 68, 34, 41, 10,101,108,115,101, 10,
  118,105,101,119,101,114, 58,115,101,116, 66, 97,110,110,101,
  114, 84,101,120,116, 40, 34, 34, 41, 10,101,110,100, 10,118,
  105,101,119,101,114, 58,115,101,116, 83,116, 97,116,117,115,
   84,101,120,116, 40, 34, 34, 41, 10,101,110,100, 10,101,118,
  101,110,116, 46,112, 97,117,115,101, 32, 61, 32,101,118,101,
  110,116, 46,110,101,119, 83, 99,101,110, 97,114,105,111, 10,
  101,118,101,110,116, 46,114,117,110, 32, 61, 32,101,118,101,
  110,116, 46,110,101,119, 83, 99,101,110, 97,114,105,111, 10,
   95,115, 97,118,101, 95,116,114,121, 32, 61, 32, 48, 10,102,
  117,110, 99,116,105,111,110, 32,101,118,101,110,116, 46,101,
  100,105,116,111,114, 83, 97,118,101, 40,102,111,114, 99,101,
   41, 10,116, 32, 61, 32,109,111,111,110, 46, 83,105,109,117,
  108, 97,116,105,111,110, 77, 97,110, 97,103,101,114, 58,105,
  110,115,116, 97,110, 99,101, 40, 41, 58,103,101,116, 84,105,
  109,101, 40, 41, 10,105,102, 32, 40,116, 32, 61, 61, 32, 48,
   32,111,114, 32, 95,115, 97,118,101, 95,116,114,121, 32, 62,
   32, 48, 41, 32,116,104,101,110, 10, 97,112,112, 58,115, 97,
  118,101, 83, 99,101,110, 97,114,105,111, 40, 34,115, 99,101,
  110, 97,114,105,111, 46,120,109,108, 34, 41, 10,109,100,114,
   97,119, 46,110,111,116,105,102,121, 40, 34, 83, 97,118,101,
  100, 32, 34, 32, 46, 46, 32, 97,112,112, 58,103,101,116, 82,
  111,111,116, 80, 97,116,104, 40, 41, 32, 46, 46, 32, 34, 47,
   34, 32, 46, 46, 32, 34,115, 99,101,110, 97,114,105,111, 46,
  120,109,108, 34, 41, 10, 95,115, 97,118,101, 95,116,114,121,
   32, 61, 32, 48, 10,101,108,115,101, 10,109,100,114, 97,119,
   46,110,111,116,105,102,121, 40, 34, 83,105,109,117,108, 97,
  116,105,111,110, 32,105,115, 32,110,111,116, 32, 97,116, 32,
  116, 61, 48, 33, 32, 80,114,101,115,115, 32, 94, 82, 32,116,
  111, 32,114,101,115,101,116, 32,115, 99,101,110, 97,114,105,
  111, 44, 32,111,114, 32, 94, 83, 32, 97,103, 97,105,110, 32,
  116,111, 32,102,111,114, 99,101, 32,115, 97,118,101, 46, 34,
   44, 32,118,101, 99, 40, 49, 44, 48, 44, 48, 44, 49, 41, 41,
   10, 95,115, 97,118,101, 95,116,114,121, 32, 61, 32, 95,115,
   97,118,101, 95,116,114,121, 32, 43, 32, 49, 10,101,110,100,
   10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,101,
  118,101,110,116, 46, 99,111,110,110,101, 99,116, 40, 99,108,
  105,101,110,116, 41, 10,105,102, 32, 40,110,101,116, 58,105,
  115, 83,101,114,118,101,114, 40, 41, 32, 97,110,100, 32, 99,
  108,105,101,110,116, 32,126, 61, 32,110,105,108, 41, 32,116,
  104,101,110, 10,109,100,114, 97,119, 46,110,111,116,105,102,
  121, 40, 34, 67,108,105,101,110,116, 32, 34, 32, 46, 46, 32,
   99,108,105,101,110,116, 58,116,111, 83,116,114,105,110,103,
   40, 41, 32, 46, 46, 32, 34, 32, 99,111,110,110,101, 99,116,
  101,100, 34, 41, 10,101,108,115,101, 10,109,100,114, 97,119,
   46,110,111,116,105,102,121, 40, 34, 67,111,110,110,101, 99,
  116,101,100, 34, 41, 10,101,110,100, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,101,118,101,110,116, 46,100,
  105,115, 99,111,110,110,101, 99,116, 40, 99,108,105,101,110,
  116, 41, 10,105,102, 32, 40,110,101,116, 58,105,115, 83,101,
  114,118,101,114, 40, 41, 32, 97,110,100, 32, 99,108,105,101,
  110,116, 32,126, 61, 32,110,105,108, 41, 32,116,104,101,110,
   10,109,100,114, 97,119, 46,110,111,116,105,102,121, 40, 34,
   67,108,105,101,110,116, 32, 34, 32, 46, 46, 32, 99,108,105,
  101,110,116, 58,116,111, 83,116,114,105,110,103, 40, 41, 32,
   46, 46, 32, 34, 32,100,105,115, 99,111,110,110,101, 99,116,
  101,100, 34, 41, 10,101,108,115,101, 10,109,100,114, 97,119,
   46,110,111,116,105,102,121, 40, 34, 68,105,115, 99,111,110,
  110,101, 99,116,101,100, 34, 41, 10,101,110,100, 10,101,110,
  100, 10,102,117,110, 99,116,105,111,110, 32,101,118,101,110,
  116, 46, 99,111,110,110,101, 99,116,105,111,110, 70, 97,105,
  108,101,100, 40, 41, 10,109,100,114, 97,119, 46,110,111,116,
  105,102,121, 40, 34, 67,111,110,110,101, 99,116,105,111,110,
   32,102, 97,105,108,101,100, 34, 41, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,101,118,101,110,116, 46,110,
  111, 70,114,101,101, 73,110, 99,111,109,105,110,103, 67,111,
  110,110,101, 99,116,105,111,110,115, 40, 41, 10,109,100,114,
   97,119, 46,110,111,116,105,102,121, 40, 34, 78,111, 32,102,
  114,101,101, 32,105,110, 99,111,109,105,110,103, 32, 99,111,
  110,110,101, 99,116,105,111,110,115, 34, 41, 10,101,110,100,
   10,102,117,110, 99,116,105,111,110, 32,101,118,101,110,116,
   46, 99,111,110,110,101, 99,116,105,111,110, 76,111,115,116,
   40, 99,108,105,101,110,116, 41, 10,105,102, 32, 40,110,101,
  116, 58,105,115, 83,101,114,118,101,114, 40, 41, 32, 97,110,
  100, 32, 99,108,105,101,110,116, 32,126, 61, 32,110,105,108,
   41, 32,116,104,101,110, 10,109,100,114, 97,119, 46,110,111,
  116,105,102,121, 40, 34, 67,108,105,101,110,116, 32, 34, 32,
   46, 46, 32, 99,108,105,101,110,116, 58,116,111, 83,116,114,
  105,110,103, 40, 41, 32, 46, 46, 32, 34, 32,108,111,115,116,
   32, 99,111,110,110,101, 99,116,105,111,110, 34, 41, 10,101,
  108,115,101, 10,109,100,114, 97,119, 46,110,111,116,105,102,
  121, 40, 34, 76,111,115,116, 32, 99,111,110,110,101, 99,116,
  105,111,110, 34, 41, 10,101,110,100, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,101,118,101,110,116, 46,112,
  108, 97,121,101,114, 74,111,105,110, 40,112,108, 97,121,101,
  114, 41, 10,109,100,114, 97,119, 46,110,111,116,105,102,121,
   40, 34, 80,108, 97,121,101,114, 32, 34, 32, 46, 46, 32,112,
  108, 97,121,101,114, 58,103,101,116, 78, 97,109,101, 40, 41,
   32, 46, 46, 32, 34, 32,106,111,105,110,101,100, 34, 41, 10,
  101,110,100, 10,102,117,110, 99,116,105,111,110, 32,101,118,
  101,110,116, 46,112,108, 97,121,101,114, 71,111,110,101, 40,
  112,108, 97,121,101,114, 41, 10,109,100,114, 97,119, 46,110,
  111,116,105,102,121, 40, 34, 80,108, 97,121,101,114, 32, 34,
   32, 46, 46, 32,112,108, 97,121,101,114, 58,103,101,116, 78,
   97,109,101, 40, 41, 32, 46, 46, 32, 34, 32,103,111,110,101,
   34, 41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
   32,101,118,101,110,116, 46,106,111,105,110, 71, 97,109,101,
   40,103, 97,109,101, 41, 10,109,100,114, 97,119, 46,110,111,
  116,105,102,121, 40, 34, 74,111,105,110,105,110,103, 32,103,
   97,109,101, 32, 34, 32, 46, 46, 32,103, 97,109,101, 58,103,
  101,116, 78, 97,109,101, 40, 41, 41, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,101,118,101,110,116, 46, 99,
  104, 97,116, 40,109,101,115,115, 97,103,101, 44, 32,112,108,
   97,121,101,114, 41, 10,105,102, 32, 40,112,108, 97,121,101,
  114, 32,126, 61, 32,110,105,108, 41, 32,116,104,101,110, 10,
  115,116,114, 32, 61, 32,112,108, 97,121,101,114, 58,103,101,
  116, 78, 97,109,101, 40, 41, 10,101,108,115,101, 10,115,116,
  114, 32, 61, 32, 34,115,101,114,118,101,114, 34, 10,101,110,
  100, 10,115,116,114, 32, 61, 32,115,116,114, 32, 46, 46, 32,
   34, 58, 32, 34, 32, 46, 46, 32,109,101,115,115, 97,103,101,
   10,109,100,114, 97,119, 46,110,111,116,105,102,121, 40,115,
  116,114, 41, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/events.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,101,118,101,110,116,
   46,107,101,121, 80,114,101,115,115, 40,105,100, 41, 10,109,
  108,111,103, 46,100,111,117,116, 40, 54, 44, 32, 34,101,118,
  101,110,116, 46,107,101,121, 80,114,101,115,115, 40, 34, 32,
   46, 46, 32,105,100, 32, 46, 46, 32, 34, 41, 92,110, 34, 41,
   10,105,102, 32, 40,105,100, 32, 61, 61, 32, 51, 50, 55, 54,
   56, 52, 32,111,114, 32,105,100, 32, 61, 61, 32, 51, 50, 55,
   55, 52, 56, 32,111,114, 32,105,100, 32, 61, 61, 32, 49, 54,
   56, 52, 50, 56, 53, 50, 41, 32,116,104,101,110, 10,105,102,
   32, 40,115, 99,101,110, 97,114,105,111, 58,103,101,116, 68,
  105,115,112,108, 97,121, 77,111,100,101, 40, 41, 32, 61, 61,
   32,109,111,111,110, 46, 66, 97,115,101, 79, 98,106,101, 99,
  116, 46, 68, 73, 83, 80, 76, 65, 89, 95, 78, 79, 82, 77, 65,
   76, 41, 32,116,104,101,110, 10,115, 99,101,110, 97,114,105,
  111, 58,115,101,116, 68,105,115,112,108, 97,121, 77,111,100,
  101, 40,109,111,111,110, 46, 66, 97,115,101, 79, 98,106,101,
   99,116, 46, 68, 73, 83, 80, 76, 65, 89, 95, 68, 69, 66, 85,
   71, 41, 10,101,108,115,101, 10,115, 99,101,110, 97,114,105,
  111, 58,115,101,116, 68,105,115,112,108, 97,121, 77,111,100,
  101, 40,109,111,111,110, 46, 66, 97,115,101, 79, 98,106,101,
   99,116, 46, 68, 73, 83, 80, 76, 65, 89, 95, 78, 79, 82, 77,
   65, 76, 41, 10,101,110,100, 10,114,101,116,117,114,110, 32,
  116,114,117,101, 10,101,108,115,101,105,102, 32, 40,105,100,
   32, 61, 61, 32, 51, 50, 55, 54, 57, 54, 32,111,114, 32,105,
  100, 32, 61, 61, 32, 51, 50, 55, 55, 54, 48, 32,111,114, 32,
  105,100, 32, 61, 61, 32, 49, 54, 56, 52, 50, 56, 54, 52, 41,
   32,116,104,101,110, 10,112, 97,117,115,101,100, 32, 61, 32,
  109,111,111,110, 46, 83,105,109,117,108, 97,116,105,111,110,
   77, 97,110, 97,103,101,114, 58,105,110,115,116, 97,110, 99,
  101, 40, 41, 58,105,115, 80, 97,117,115,101,100, 40, 41, 10,
  109,111,111,110, 46, 83,105,109,117,108, 97,116,105,111,110,
   77, 97,110, 97,103,101,114, 58,105,110,115,116, 97,110, 99,
  101, 40, 41, 58,115,101,116, 80, 97,117,115,101,100, 40,110,
  111,116, 32,112, 97,117,115,101,100, 41, 10,114,101,116,117,
  114,110, 32,116,114,117,101, 10,101,108,115,101,105,102, 32,
   40,105,100, 32, 61, 61, 32, 51, 50, 55, 54, 57, 56, 32,111,
  114, 32,105,100, 32, 61, 61, 32, 51, 50, 55, 55, 54, 50, 32,
  111,114, 32,105,100, 32, 61, 61, 32, 49, 54, 56, 52, 50, 56,
   54, 54, 41, 32,116,104,101,110, 10,109,111,111,110, 46, 83,
  105,109,117,108, 97,116,105,111,110, 77, 97,110, 97,103,101,
  114, 58,105,110,115,116, 97,110, 99,101, 40, 41, 58,115,101,
  116, 84,105,109,101, 40, 48, 41, 10,115, 99,101,110, 97,114,
  105,111, 58,114,101,115,101,116, 40, 41, 10,114,101,116,117,
  114,110, 32,116,114,117,101, 10,101,108,115,101,105,102, 32,
   40,105,100, 32, 61, 61, 32, 51, 50, 55, 54, 56, 51, 32,111,
  114, 32,105,100, 32, 61, 61, 32, 51, 50, 55, 55, 52, 55, 32,
  111,114, 32,105,100, 32, 61, 61, 32, 49, 54, 56, 52, 50, 56,
   53, 49, 41, 32,116,104,101,110, 10,118,105,101,119,101,114,
   58,115,104,111,119, 67,111,110,115,111,108,101, 87,105,110,
  100,111,119, 40,110,111,116, 32,118,105,101,119,101,114, 58,
  105,115, 67,111,110,115,111,108,101, 87,105,110,100,111,119,
   83,104,111,119,110, 40, 41, 41, 10,114,101,116,117,114,110,
   32,116,114,117,101, 10,101,108,115,101,105,102, 32, 40,105,
  100, 32, 61, 61, 32, 51, 50, 55, 54, 56, 53, 32,111,114, 32,
  105,100, 32, 61, 61, 32, 51, 50, 55, 55, 52, 57, 32,111,114,
   32,105,100, 32, 61, 61, 32, 49, 54, 56, 52, 50, 56, 53, 51,
   41, 32,116,104,101,110, 10,118,105,101,119,101,114, 58,115,
  101,116, 69,100,105,116, 77,111,100,101, 40,110,111,116, 32,
  118,105,101,119,101,114, 58,105,115, 69,100,105,116,105,110,
  103, 40, 41, 41, 10,101,118,101,110,116, 46,112, 97,117,115,
  101, 40,109,111,111,110, 46, 83,105,109,117,108, 97,116,105,
  111,110, 77, 97,110, 97,103,101,114, 58,105,110,115,116, 97,
  110, 99,101, 40, 41, 58,105,115, 80, 97,117,115,101,100, 40,
   41, 41, 10,114,101,116,117,114,110, 32,116,114,117,101, 10,
  101,110,100, 10,114,101,116,117,114,110, 32,102, 97,108,115,
  101, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/keys.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,116,112,114,105,110,116, 32, 61, 32,112,114,105,110,116,
   10,102,117,110, 99,116,105,111,110, 32,112,114,105,110,116,
   40, 46, 46, 46, 41, 10,102,111,114, 32,105, 44,118, 32,105,
  110, 32,105,112, 97,105,114,115, 40, 97,114,103, 41, 32,100,
  111, 10,105,102, 32, 40, 99,111,110,115,111,108,101, 41, 32,
  116,104,101,110, 10, 99,111,110,115,111,108,101, 58,112,114,
  105,110,116, 40,116,111,115,116,114,105,110,103, 40,118, 41,
   41, 10,101,108,115,101, 10,116,112,114,105,110,116, 40,118,
   41, 10,101,110,100, 10,101,110,100, 10,101,110,100, 10,102,
  117,110, 99,116,105,111,110, 32,118,101, 99, 40,120, 44,121,
   44,122, 44,119, 41, 10,105,102, 32, 40,119, 32, 61, 61, 32,
  110,105,108, 41, 32,116,104,101,110, 10,114,101,116,117,114,
  110, 32,111,115,103, 46, 86,101, 99, 51, 58,110,101,119, 40,
  120, 44,121, 44,122, 41, 10,101,108,115,101, 10,114,101,116,
  117,114,110, 32,111,115,103, 46, 86,101, 99, 52, 58,110,101,
  119, 40,120, 44,121, 44,122, 44,119, 41, 10,101,110,100, 10,
  101,110,100, 10,102,117,110, 99,116,105,111,110, 32,105,110,
  102,111, 40,111, 98,106,101, 99,116, 41, 10,112,114,105,110,
  116, 40,116,111,108,117, 97, 46,116,121,112,101, 40,111, 98,
  106,101, 99,116, 41, 32, 46, 46, 32, 34, 58, 32, 34, 32, 46,
   46, 32,116,111,115,116,114,105,110,103, 40,111, 98,106,101,
   99,116, 41, 41, 10,105,102, 32, 40,116,121,112,101, 40,111,
   98,106,101, 99,116, 41, 32, 61, 61, 32, 34,116, 97, 98,108,
  101, 34, 41, 32,116,104,101,110, 10,108,111, 99, 97,108, 32,
  105, 32, 61, 32, 48, 10,108,111, 99, 97,108, 32,108,105,115,
  116, 32, 61, 32,123,125, 10,102,111,114, 32,107, 44,118, 32,
  105,110, 32,112, 97,105,114,115, 40,111, 98,106,101, 99,116,
   41, 32,100,111, 10,105,102, 32, 40,110,111,116, 32, 40,116,
  111,108,117, 97, 46,116,121,112,101, 40,118, 41, 32, 61, 61,
   32, 34,102,117,110, 99,116,105,111,110, 34, 32, 97,110,100,
   32,115,116,114,105,110,103, 46,109, 97,116, 99,104, 40,107,
   44, 34, 95, 95, 34, 41, 32,126, 61, 32,110,105,108, 41, 41,
   32,116,104,101,110, 10,105, 32, 61, 32,105, 32, 43, 32, 49,
   10,108,105,115,116, 91,105, 93, 32, 61, 32, 34, 32, 34, 32,
   46, 46, 32,116,111,108,117, 97, 46,116,121,112,101, 40,118,
   41, 32, 46, 46, 32, 34, 58, 32, 34, 32, 46, 46, 32,107, 10,
  101,110,100, 10,101,110,100, 10,116, 97, 98,108,101, 46,115,
  111,114,116, 40,108,105,115,116, 41, 10,102,111,114, 32,105,
   44,118, 32,105,110, 32,105,112, 97,105,114,115, 40,108,105,
  115,116, 41, 32,100,111, 10,112,114,105,110,116, 40,118, 41,
   10,101,110,100, 10,101,110,100, 10,101,110,100, 10,102,117,
  110, 99,116,105,111,110, 32,109,111,111,110, 46, 99, 97,115,
  116, 40,111, 98,106, 41, 10,114,101,116,117,114,110, 32,116,
  111,108,117, 97, 46, 99, 97,115,116, 40,111, 98,106, 44, 32,
  111, 98,106, 58,108,105, 98,114, 97,114,121, 78, 97,109,101,
   40, 41, 32, 46, 46, 32, 34, 58, 58, 34, 32, 46, 46, 32,111,
   98,106, 58, 99,108, 97,115,115, 78, 97,109,101, 40, 41, 41,
   10,101,110,100, 10, 95, 80, 82, 79, 77, 80, 84, 32, 61, 32,
   34, 62, 34, 10, 95, 80, 82, 79, 77, 80, 84, 50, 32, 61, 32,
   34, 62, 62, 34, 10,109,108,111,103, 46,100,111,117,116, 40,
   49, 44, 32, 34,105,110,105,116, 46,108,117, 97, 32,108,111,
   97,100,101,100, 32, 79, 75, 92,110, 34, 44, 32,109,111,111,
  110, 46, 83, 67, 82, 73, 80, 84, 41,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/init.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,102,117,110, 99,116,105,111,110, 32,109,111,111,110, 46,
   67,111,109,112,111,110,101,110,116, 58,111,110, 73,110,105,
  116,105, 97,108,105,122,101, 40, 41, 10,116,101,109,112, 32,
   61, 32,115,101,108,102, 58,103,101,116, 84,101,109,112,108,
   97,116,101, 40, 41, 10,105,102, 32, 40,116,101,109,112, 41,
   32,116,104,101,110, 10,105,102, 32, 40,116,101,109,112, 46,
  111,110, 73,110,105,116,105, 97,108,105,122,101, 32,126, 61,
   32,115,101,108,102, 46,111,110, 73,110,105,116,105, 97,108,
  105,122,101, 41, 32,116,104,101,110, 10,116,101,109,112, 46,
  111,110, 73,110,105,116,105, 97,108,105,122,101, 40,115,101,
  108,102, 41, 10,101,110,100, 10,105,102, 32, 40,110,111,116,
   32,115,101,108,102, 46,111,110, 82,101,115,101,116, 41, 32,
  116,104,101,110, 32,115,101,108,102, 46,111,110, 82,101,115,
  101,116, 32, 61, 32,116,101,109,112, 46,111,110, 82,101,115,
  101,116, 59, 32,101,110,100, 10,105,102, 32, 40,110,111,116,
   32,115,101,108,102, 46,111,110, 82,101, 97,108,105,122,101,
   41, 32,116,104,101,110, 32,115,101,108,102, 46,111,110, 82,
  101, 97,108,105,122,101, 32, 61, 32,116,101,109,112, 46,111,
  110, 82,101, 97,108,105,122,101, 59, 32,101,110,100, 10,105,
  102, 32, 40,110,111,116, 32,115,101,108,102, 46,111,110, 85,
  110,114,101, 97,108,105,122,101, 41, 32,116,104,101,110, 32,
  115,101,108,102, 46,111,110, 85,110,114,101, 97,108,105,122,
  101, 32, 61, 32,116,101,109,112, 46,111,110, 85,110,114,101,
   97,108,105,122,101, 59, 32,101,110,100, 10,105,102, 32, 40,
  110,111,116, 32,115,101,108,102, 46,111,110, 67,111,110,116,
   97, 99,116, 41, 32,116,104,101,110, 32,115,101,108,102, 46,
  111,110, 67,111,110,116, 97, 99,116, 32, 61, 32,116,101,109,
  112, 46,111,110, 67,111,110,116, 97, 99,116, 59, 32,101,110,
  100, 10,105,102, 32, 40,110,111,116, 32,115,101,108,102, 46,
  111,110, 67,111,110,116, 97, 99,116, 70,101,101,100, 98, 97,
   99,107, 41, 32,116,104,101,110, 32,115,101,108,102, 46,111,
  110, 67,111,110,116, 97, 99,116, 70,101,101,100, 98, 97, 99,
  107, 32, 61, 32,116,101,109,112, 46,111,110, 67,111,110,116,
   97, 99,116, 70,101,101,100, 98, 97, 99,107, 59, 32,101,110,
  100, 10,105,102, 32, 40,110,111,116, 32,115,101,108,102, 46,
  111,110, 85,112,100, 97,116,101, 41, 32,116,104,101,110, 32,
  115,101,108,102, 46,111,110, 85,112,100, 97,116,101, 32, 61,
   32,116,101,109,112, 46,111,110, 85,112,100, 97,116,101, 59,
   32,101,110,100, 10,101,110,100, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/callbacks.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */


 { /* begin embedded lua code */
  int top = lua_gettop(tolua_S);
  static unsigned char B[] = {
  10,116,101,115,116, 32, 61, 32,123,125, 10,102,117,110, 99,
  116,105,111,110, 32,116,101,115,116, 46, 99,104,101, 99,107,
   40, 99,111,110,100,105,116,105,111,110, 44, 32,109,101,115,
  115, 97,103,101, 41, 10,105,102, 32, 40,110,111,116, 32, 99,
  111,110,100,105,116,105,111,110, 41, 32,116,104,101,110, 10,
  116,112,114,105,110,116, 40, 34, 70, 97,105,108,117,114,101,
   58, 32, 34, 32, 46, 46, 32,109,101,115,115, 97,103,101, 41,
   10,105,102, 32, 40, 99,111,110,115,111,108,101, 41, 32,116,
  104,101,110, 10, 99,111,110,115,111,108,101, 58,112,114,105,
  110,116, 40, 34, 70, 97,105,108,117,114,101, 58, 32, 34, 32,
   46, 46, 32,109,101,115,115, 97,103,101, 41, 10,101,110,100,
   10, 97,112,112, 58,115,101,116, 69,120,105,116, 67,111,100,
  101, 40, 49, 48, 48, 41, 10,101,108,115,101, 10,105,102, 32,
   40, 99,111,110,115,111,108,101, 41, 32,116,104,101,110, 10,
   99,111,110,115,111,108,101, 58,112,114,105,110,116, 40, 34,
   79, 75, 58, 32, 34, 32, 46, 46, 32,109,101,115,115, 97,103,
  101, 41, 10,101,110,100, 10,101,110,100, 10,101,110,100,32
  };
  tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lua/test.lua");
  lua_settop(tolua_S, top);
 } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_moon (lua_State* tolua_S) {
 return tolua_moon_open(tolua_S);
};
#endif

