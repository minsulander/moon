/*
** Lua binding: moonet
** Generated automatically by tolua++-1.0.92 on 06/07/09 15:23:16.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_moonet_open (lua_State* tolua_S);

#include <moonet/Client.h>
#include <moonet/NetworkManager.h>
#include <moonet/Player.h>

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"moonet::Player");
 tolua_usertype(tolua_S,"moonet::NetworkManager");
 tolua_usertype(tolua_S,"moonet::Client");
}

/* method: getPlayer of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_getPlayer00
static int tolua_moonet_moonet_Client_getPlayer00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_toString00
static int tolua_moonet_moonet_Client_toString00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_isConnected00
static int tolua_moonet_moonet_Client_isConnected00(lua_State* tolua_S)
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

/* method: me of class  moonet::Client */
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_me00
static int tolua_moonet_moonet_Client_me00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_getNumClients00
static int tolua_moonet_moonet_Client_getNumClients00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_getClient00
static int tolua_moonet_moonet_Client_getClient00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Client_isStillAround00
static int tolua_moonet_moonet_Client_isStillAround00(lua_State* tolua_S)
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

/* method: isActive of class  moonet::NetworkManager */
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_isActive00
static int tolua_moonet_moonet_NetworkManager_isActive00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_isServer00
static int tolua_moonet_moonet_NetworkManager_isServer00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_isClient00
static int tolua_moonet_moonet_NetworkManager_isClient00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_isConnected00
static int tolua_moonet_moonet_NetworkManager_isConnected00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_chat00
static int tolua_moonet_moonet_NetworkManager_chat00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_doStatistics00
static int tolua_moonet_moonet_NetworkManager_doStatistics00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_isDoingStatistics00
static int tolua_moonet_moonet_NetworkManager_isDoingStatistics00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_printStatistics00
static int tolua_moonet_moonet_NetworkManager_printStatistics00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_printClientList00
static int tolua_moonet_moonet_NetworkManager_printClientList00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_getDefaultSerializationInterval00
static int tolua_moonet_moonet_NetworkManager_getDefaultSerializationInterval00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_getDefaultFullSerializationInterval00
static int tolua_moonet_moonet_NetworkManager_getDefaultFullSerializationInterval00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_NetworkManager_setDefaultSerializationInterval00
static int tolua_moonet_moonet_NetworkManager_setDefaultSerializationInterval00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Player_setName00
static int tolua_moonet_moonet_Player_setName00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Player_getName00
static int tolua_moonet_moonet_Player_getName00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Player_me00
static int tolua_moonet_moonet_Player_me00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_moonet_moonet_Player_myName00
static int tolua_moonet_moonet_Player_myName00(lua_State* tolua_S)
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

/* Open function */
TOLUA_API int tolua_moonet_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_cclass(tolua_S,"Client","moonet::Client","",NULL);
  tolua_beginmodule(tolua_S,"Client");
   tolua_function(tolua_S,"getPlayer",tolua_moonet_moonet_Client_getPlayer00);
   tolua_function(tolua_S,"toString",tolua_moonet_moonet_Client_toString00);
   tolua_function(tolua_S,"isConnected",tolua_moonet_moonet_Client_isConnected00);
   tolua_function(tolua_S,"me",tolua_moonet_moonet_Client_me00);
   tolua_function(tolua_S,"getNumClients",tolua_moonet_moonet_Client_getNumClients00);
   tolua_function(tolua_S,"getClient",tolua_moonet_moonet_Client_getClient00);
   tolua_function(tolua_S,"isStillAround",tolua_moonet_moonet_Client_isStillAround00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_cclass(tolua_S,"NetworkManager","moonet::NetworkManager","",NULL);
  tolua_beginmodule(tolua_S,"NetworkManager");
   tolua_function(tolua_S,"isActive",tolua_moonet_moonet_NetworkManager_isActive00);
   tolua_function(tolua_S,"isServer",tolua_moonet_moonet_NetworkManager_isServer00);
   tolua_function(tolua_S,"isClient",tolua_moonet_moonet_NetworkManager_isClient00);
   tolua_function(tolua_S,"isConnected",tolua_moonet_moonet_NetworkManager_isConnected00);
   tolua_function(tolua_S,"chat",tolua_moonet_moonet_NetworkManager_chat00);
   tolua_function(tolua_S,"doStatistics",tolua_moonet_moonet_NetworkManager_doStatistics00);
   tolua_function(tolua_S,"isDoingStatistics",tolua_moonet_moonet_NetworkManager_isDoingStatistics00);
   tolua_function(tolua_S,"printStatistics",tolua_moonet_moonet_NetworkManager_printStatistics00);
   tolua_function(tolua_S,"printClientList",tolua_moonet_moonet_NetworkManager_printClientList00);
   tolua_function(tolua_S,"getDefaultSerializationInterval",tolua_moonet_moonet_NetworkManager_getDefaultSerializationInterval00);
   tolua_function(tolua_S,"getDefaultFullSerializationInterval",tolua_moonet_moonet_NetworkManager_getDefaultFullSerializationInterval00);
   tolua_function(tolua_S,"setDefaultSerializationInterval",tolua_moonet_moonet_NetworkManager_setDefaultSerializationInterval00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"moonet",0);
 tolua_beginmodule(tolua_S,"moonet");
  tolua_cclass(tolua_S,"Player","moonet::Player","",NULL);
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"setName",tolua_moonet_moonet_Player_setName00);
   tolua_function(tolua_S,"getName",tolua_moonet_moonet_Player_getName00);
   tolua_function(tolua_S,"me",tolua_moonet_moonet_Player_me00);
   tolua_function(tolua_S,"myName",tolua_moonet_moonet_Player_myName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_moonet (lua_State* tolua_S) {
 return tolua_moonet_open(tolua_S);
};
#endif

