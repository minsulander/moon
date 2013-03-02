/*
** Lua binding: maudio
** Generated automatically by tolua++-1.0.92 on 08/12/09 16:13:16.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_maudio_open (lua_State* tolua_S);

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#include <maudio/AudioManager.h>
#include <maudio/Sound.h>

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_osg__Quat (lua_State* tolua_S)
{
 osg::Quat* self = (osg::Quat*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}

static int tolua_collect_osg__Vec3 (lua_State* tolua_S)
{
 osg::Vec3* self = (osg::Vec3*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"moon::Component");
 tolua_usertype(tolua_S,"maudio::Sound");
 tolua_usertype(tolua_S,"osg::Vec3");
 tolua_usertype(tolua_S,"osg::Quat");
 tolua_usertype(tolua_S,"maudio::AudioManager");
}

/* method: play of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_play00
static int tolua_maudio_maudio_AudioManager_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const float gain = ((const float)  tolua_tonumber(tolua_S,3,1.0));
  const float pitch = ((const float)  tolua_tonumber(tolua_S,4,1.0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'",NULL);
#endif
 {
  maudio::Sound* tolua_ret = (maudio::Sound*)  self->play(filename,gain,pitch);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"maudio::Sound");
 tolua_pushcppstring(tolua_S,(const char*)filename);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_play01
static int tolua_maudio_maudio_AudioManager_play01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const float gain = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float pitch = ((const float)  tolua_tonumber(tolua_S,4,0));
  const osg::Vec3* pos = ((const osg::Vec3*)  tolua_tousertype(tolua_S,5,0));
  const bool relative = ((const bool)  tolua_toboolean(tolua_S,6,true));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'",NULL);
#endif
 {
  maudio::Sound* tolua_ret = (maudio::Sound*)  self->play(filename,gain,pitch,*pos,relative);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"maudio::Sound");
 tolua_pushcppstring(tolua_S,(const char*)filename);
 }
 }
 return 2;
tolua_lerror:
 return tolua_maudio_maudio_AudioManager_play00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSound of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_getSound00
static int tolua_maudio_maudio_AudioManager_getSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSound'",NULL);
#endif
 {
  maudio::Sound* tolua_ret = (maudio::Sound*)  self->getSound(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"maudio::Sound");
 tolua_pushcppstring(tolua_S,(const char*)name);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getListenerPosition of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_getListenerPosition00
static int tolua_maudio_maudio_AudioManager_getListenerPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getListenerPosition'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getListenerPosition();
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
 tolua_error(tolua_S,"#ferror in function 'getListenerPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getListenerOrientation of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_getListenerOrientation00
static int tolua_maudio_maudio_AudioManager_getListenerOrientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"osg::Vec3",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
  osg::Vec3* forward = ((osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
  osg::Vec3* up = ((osg::Vec3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getListenerOrientation'",NULL);
#endif
 {
  self->getListenerOrientation(*forward,*up);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getListenerOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getListenerVelocity of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_getListenerVelocity00
static int tolua_maudio_maudio_AudioManager_getListenerVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getListenerVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getListenerVelocity();
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
 tolua_error(tolua_S,"#ferror in function 'getListenerVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxPitch of class  maudio::AudioManager */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_AudioManager_getMaxPitch00
static int tolua_maudio_maudio_AudioManager_getMaxPitch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::AudioManager",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::AudioManager* self = (maudio::AudioManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxPitch'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getMaxPitch();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxPitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_play00
static int tolua_maudio_maudio_Sound_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'",NULL);
#endif
 {
  self->play();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_pause00
static int tolua_maudio_maudio_Sound_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'",NULL);
#endif
 {
  self->pause();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rewind of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_rewind00
static int tolua_maudio_maudio_Sound_rewind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rewind'",NULL);
#endif
 {
  self->rewind();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rewind'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_stop00
static int tolua_maudio_maudio_Sound_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isPlaying of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_isPlaying00
static int tolua_maudio_maudio_Sound_isPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPlaying'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isPlaying();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPaused of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_isPaused00
static int tolua_maudio_maudio_Sound_isPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getGain of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getGain00
static int tolua_maudio_maudio_Sound_getGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGain'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getGain();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGain of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setGain00
static int tolua_maudio_maudio_Sound_setGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGain'",NULL);
#endif
 {
  self->setGain(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPitch of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getPitch00
static int tolua_maudio_maudio_Sound_getPitch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPitch'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getPitch();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPitch of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setPitch00
static int tolua_maudio_maudio_Sound_setPitch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPitch'",NULL);
#endif
 {
  self->setPitch(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLooping of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_isLooping00
static int tolua_maudio_maudio_Sound_isLooping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLooping'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isLooping();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLooping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLooping of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setLooping00
static int tolua_maudio_maudio_Sound_setLooping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLooping'",NULL);
#endif
 {
  self->setLooping(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLooping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setPosition00
static int tolua_maudio_maudio_Sound_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* pos = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
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

/* method: setDirection of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setDirection00
static int tolua_maudio_maudio_Sound_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* forward = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'",NULL);
#endif
 {
  self->setDirection(*forward);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setRotation00
static int tolua_maudio_maudio_Sound_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Quat",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const osg::Quat* rot = ((const osg::Quat*)  tolua_tousertype(tolua_S,2,0));
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

/* method: getRotation of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getRotation00
static int tolua_maudio_maudio_Sound_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDirection of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getDirection00
static int tolua_maudio_maudio_Sound_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getDirection();
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
 tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getPosition00
static int tolua_maudio_maudio_Sound_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setVelocity of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setVelocity00
static int tolua_maudio_maudio_Sound_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const osg::Vec3",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const osg::Vec3* vel = ((const osg::Vec3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'",NULL);
#endif
 {
  self->setVelocity(*vel);
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

/* method: getVelocity of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getVelocity00
static int tolua_maudio_maudio_Sound_getVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocity'",NULL);
#endif
 {
  osg::Vec3 tolua_ret = (osg::Vec3)  self->getVelocity();
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

/* method: getLength of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getLength00
static int tolua_maudio_maudio_Sound_getLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLength'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getLength();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: shouldAutoPlay of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_shouldAutoPlay00
static int tolua_maudio_maudio_Sound_shouldAutoPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'shouldAutoPlay'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->shouldAutoPlay();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shouldAutoPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoPlay of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setAutoPlay00
static int tolua_maudio_maudio_Sound_setAutoPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const bool value = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoPlay'",NULL);
#endif
 {
  self->setAutoPlay(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAutoPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTriggerMode of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setTriggerMode00
static int tolua_maudio_maudio_Sound_setTriggerMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  maudio::Sound::TriggerMode mode = ((maudio::Sound::TriggerMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTriggerMode'",NULL);
#endif
 {
  self->setTriggerMode(mode);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTriggerMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerMode of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getTriggerMode00
static int tolua_maudio_maudio_Sound_getTriggerMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerMode'",NULL);
#endif
 {
  maudio::Sound::TriggerMode tolua_ret = (maudio::Sound::TriggerMode)  self->getTriggerMode();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTriggerThreshold of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_setTriggerThreshold00
static int tolua_maudio_maudio_Sound_setTriggerThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"maudio::Sound",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  maudio::Sound* self = (maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
  const float value = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTriggerThreshold'",NULL);
#endif
 {
  self->setTriggerThreshold(value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTriggerThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTriggerThreshold of class  maudio::Sound */
#ifndef TOLUA_DISABLE_tolua_maudio_maudio_Sound_getTriggerThreshold00
static int tolua_maudio_maudio_Sound_getTriggerThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const maudio::Sound",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const maudio::Sound* self = (const maudio::Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTriggerThreshold'",NULL);
#endif
 {
  float tolua_ret = (float)  self->getTriggerThreshold();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTriggerThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_maudio_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"maudio",0);
 tolua_beginmodule(tolua_S,"maudio");
  tolua_cclass(tolua_S,"AudioManager","maudio::AudioManager","",NULL);
  tolua_beginmodule(tolua_S,"AudioManager");
   tolua_function(tolua_S,"play",tolua_maudio_maudio_AudioManager_play00);
   tolua_function(tolua_S,"play",tolua_maudio_maudio_AudioManager_play01);
   tolua_function(tolua_S,"getSound",tolua_maudio_maudio_AudioManager_getSound00);
   tolua_function(tolua_S,"getListenerPosition",tolua_maudio_maudio_AudioManager_getListenerPosition00);
   tolua_function(tolua_S,"getListenerOrientation",tolua_maudio_maudio_AudioManager_getListenerOrientation00);
   tolua_function(tolua_S,"getListenerVelocity",tolua_maudio_maudio_AudioManager_getListenerVelocity00);
   tolua_function(tolua_S,"getMaxPitch",tolua_maudio_maudio_AudioManager_getMaxPitch00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"maudio",0);
 tolua_beginmodule(tolua_S,"maudio");
  tolua_cclass(tolua_S,"Sound","maudio::Sound","moon::Component",NULL);
  tolua_beginmodule(tolua_S,"Sound");
   tolua_function(tolua_S,"play",tolua_maudio_maudio_Sound_play00);
   tolua_function(tolua_S,"pause",tolua_maudio_maudio_Sound_pause00);
   tolua_function(tolua_S,"rewind",tolua_maudio_maudio_Sound_rewind00);
   tolua_function(tolua_S,"stop",tolua_maudio_maudio_Sound_stop00);
   tolua_function(tolua_S,"isPlaying",tolua_maudio_maudio_Sound_isPlaying00);
   tolua_function(tolua_S,"isPaused",tolua_maudio_maudio_Sound_isPaused00);
   tolua_function(tolua_S,"getGain",tolua_maudio_maudio_Sound_getGain00);
   tolua_function(tolua_S,"setGain",tolua_maudio_maudio_Sound_setGain00);
   tolua_function(tolua_S,"getPitch",tolua_maudio_maudio_Sound_getPitch00);
   tolua_function(tolua_S,"setPitch",tolua_maudio_maudio_Sound_setPitch00);
   tolua_function(tolua_S,"isLooping",tolua_maudio_maudio_Sound_isLooping00);
   tolua_function(tolua_S,"setLooping",tolua_maudio_maudio_Sound_setLooping00);
   tolua_function(tolua_S,"setPosition",tolua_maudio_maudio_Sound_setPosition00);
   tolua_function(tolua_S,"setDirection",tolua_maudio_maudio_Sound_setDirection00);
   tolua_function(tolua_S,"setRotation",tolua_maudio_maudio_Sound_setRotation00);
   tolua_function(tolua_S,"getRotation",tolua_maudio_maudio_Sound_getRotation00);
   tolua_function(tolua_S,"getDirection",tolua_maudio_maudio_Sound_getDirection00);
   tolua_function(tolua_S,"getPosition",tolua_maudio_maudio_Sound_getPosition00);
   tolua_function(tolua_S,"setVelocity",tolua_maudio_maudio_Sound_setVelocity00);
   tolua_function(tolua_S,"getVelocity",tolua_maudio_maudio_Sound_getVelocity00);
   tolua_function(tolua_S,"getLength",tolua_maudio_maudio_Sound_getLength00);
   tolua_function(tolua_S,"shouldAutoPlay",tolua_maudio_maudio_Sound_shouldAutoPlay00);
   tolua_function(tolua_S,"setAutoPlay",tolua_maudio_maudio_Sound_setAutoPlay00);
   tolua_constant(tolua_S,"TARGET_NONE",maudio::Sound::TARGET_NONE);
   tolua_constant(tolua_S,"TARGET_GAIN",maudio::Sound::TARGET_GAIN);
   tolua_constant(tolua_S,"TARGET_PITCH",maudio::Sound::TARGET_PITCH);
   tolua_constant(tolua_S,"NO_TRIGGER",maudio::Sound::NO_TRIGGER);
   tolua_constant(tolua_S,"PLAY",maudio::Sound::PLAY);
   tolua_constant(tolua_S,"PAUSE",maudio::Sound::PAUSE);
   tolua_constant(tolua_S,"STOP",maudio::Sound::STOP);
   tolua_constant(tolua_S,"PLAY_STOP",maudio::Sound::PLAY_STOP);
   tolua_constant(tolua_S,"PLAY_PAUSE",maudio::Sound::PLAY_PAUSE);
   tolua_function(tolua_S,"setTriggerMode",tolua_maudio_maudio_Sound_setTriggerMode00);
   tolua_function(tolua_S,"getTriggerMode",tolua_maudio_maudio_Sound_getTriggerMode00);
   tolua_function(tolua_S,"setTriggerThreshold",tolua_maudio_maudio_Sound_setTriggerThreshold00);
   tolua_function(tolua_S,"getTriggerThreshold",tolua_maudio_maudio_Sound_getTriggerThreshold00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_maudio (lua_State* tolua_S) {
 return tolua_maudio_open(tolua_S);
};
#endif

