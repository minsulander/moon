/*
** Lua binding: mdraw
** Generated automatically by tolua++-1.0.92 on 06/07/09 15:23:17.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_mdraw_open (lua_State* tolua_S);

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#include "mdraw/ConsoleWindow.h"
#include <mdraw/FadeText.h>
#include <mdraw/utils.h>

/* function to release collected object via destructor */
#ifdef __cplusplus

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
 tolua_usertype(tolua_S,"mdraw::ConsoleWindow");
 tolua_usertype(tolua_S,"osg::Node");
 tolua_usertype(tolua_S,"osg::BoundingBox");
 tolua_usertype(tolua_S,"osg::Vec4");
 tolua_usertype(tolua_S,"osg::Geode");
}

/* method: setFont of class  mdraw::ConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_setFont00
static int tolua_mdraw_mdraw_ConsoleWindow_setFont00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_charHeight00
static int tolua_mdraw_mdraw_ConsoleWindow_charHeight00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_charWidth00
static int tolua_mdraw_mdraw_ConsoleWindow_charWidth00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_setBackgroundColor00
static int tolua_mdraw_mdraw_ConsoleWindow_setBackgroundColor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_getBackgroundColor00
static int tolua_mdraw_mdraw_ConsoleWindow_getBackgroundColor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollUp00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollUp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollDown00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollDown00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_pageUp00
static int tolua_mdraw_mdraw_ConsoleWindow_pageUp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_pageDown00
static int tolua_mdraw_mdraw_ConsoleWindow_pageDown00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollRight00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollRight00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollLeft00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollLeft00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollHome00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollHome00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_scrollEnd00
static int tolua_mdraw_mdraw_ConsoleWindow_scrollEnd00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_del00
static int tolua_mdraw_mdraw_ConsoleWindow_del00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_backSpace00
static int tolua_mdraw_mdraw_ConsoleWindow_backSpace00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_clearLine00
static int tolua_mdraw_mdraw_ConsoleWindow_clearLine00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_cutLine00
static int tolua_mdraw_mdraw_ConsoleWindow_cutLine00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_upHistory00
static int tolua_mdraw_mdraw_ConsoleWindow_upHistory00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_downHistory00
static int tolua_mdraw_mdraw_ConsoleWindow_downHistory00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_leftCursor00
static int tolua_mdraw_mdraw_ConsoleWindow_leftCursor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_rightCursor00
static int tolua_mdraw_mdraw_ConsoleWindow_rightCursor00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_putch00
static int tolua_mdraw_mdraw_ConsoleWindow_putch00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_print00
static int tolua_mdraw_mdraw_ConsoleWindow_print00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_resize00
static int tolua_mdraw_mdraw_ConsoleWindow_resize00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_sizeUp00
static int tolua_mdraw_mdraw_ConsoleWindow_sizeUp00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_sizeDown00
static int tolua_mdraw_mdraw_ConsoleWindow_sizeDown00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_setPrompt00
static int tolua_mdraw_mdraw_ConsoleWindow_setPrompt00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_setCursorPosition00
static int tolua_mdraw_mdraw_ConsoleWindow_setCursorPosition00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_getNumLines00
static int tolua_mdraw_mdraw_ConsoleWindow_getNumLines00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_setTop00
static int tolua_mdraw_mdraw_ConsoleWindow_setTop00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_getTop00
static int tolua_mdraw_mdraw_ConsoleWindow_getTop00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_getHeight00
static int tolua_mdraw_mdraw_ConsoleWindow_getHeight00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_ConsoleWindow_getLastLine00
static int tolua_mdraw_mdraw_ConsoleWindow_getLastLine00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_notify00
static int tolua_mdraw_mdraw_notify00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_notify01
static int tolua_mdraw_mdraw_notify01(lua_State* tolua_S)
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
 return tolua_mdraw_mdraw_notify00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: mdraw::getNodeString */
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_getNodeString00
static int tolua_mdraw_mdraw_getNodeString00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_mdraw_mdraw_getBoundingBox00
static int tolua_mdraw_mdraw_getBoundingBox00(lua_State* tolua_S)
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

/* Open function */
TOLUA_API int tolua_mdraw_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_cclass(tolua_S,"ConsoleWindow","mdraw::ConsoleWindow","osg::Geode",NULL);
  tolua_beginmodule(tolua_S,"ConsoleWindow");
   tolua_function(tolua_S,"setFont",tolua_mdraw_mdraw_ConsoleWindow_setFont00);
   tolua_function(tolua_S,"charHeight",tolua_mdraw_mdraw_ConsoleWindow_charHeight00);
   tolua_function(tolua_S,"charWidth",tolua_mdraw_mdraw_ConsoleWindow_charWidth00);
   tolua_function(tolua_S,"setBackgroundColor",tolua_mdraw_mdraw_ConsoleWindow_setBackgroundColor00);
   tolua_function(tolua_S,"getBackgroundColor",tolua_mdraw_mdraw_ConsoleWindow_getBackgroundColor00);
   tolua_function(tolua_S,"scrollUp",tolua_mdraw_mdraw_ConsoleWindow_scrollUp00);
   tolua_function(tolua_S,"scrollDown",tolua_mdraw_mdraw_ConsoleWindow_scrollDown00);
   tolua_function(tolua_S,"pageUp",tolua_mdraw_mdraw_ConsoleWindow_pageUp00);
   tolua_function(tolua_S,"pageDown",tolua_mdraw_mdraw_ConsoleWindow_pageDown00);
   tolua_function(tolua_S,"scrollRight",tolua_mdraw_mdraw_ConsoleWindow_scrollRight00);
   tolua_function(tolua_S,"scrollLeft",tolua_mdraw_mdraw_ConsoleWindow_scrollLeft00);
   tolua_function(tolua_S,"scrollHome",tolua_mdraw_mdraw_ConsoleWindow_scrollHome00);
   tolua_function(tolua_S,"scrollEnd",tolua_mdraw_mdraw_ConsoleWindow_scrollEnd00);
   tolua_function(tolua_S,"del",tolua_mdraw_mdraw_ConsoleWindow_del00);
   tolua_function(tolua_S,"backSpace",tolua_mdraw_mdraw_ConsoleWindow_backSpace00);
   tolua_function(tolua_S,"clearLine",tolua_mdraw_mdraw_ConsoleWindow_clearLine00);
   tolua_function(tolua_S,"cutLine",tolua_mdraw_mdraw_ConsoleWindow_cutLine00);
   tolua_function(tolua_S,"upHistory",tolua_mdraw_mdraw_ConsoleWindow_upHistory00);
   tolua_function(tolua_S,"downHistory",tolua_mdraw_mdraw_ConsoleWindow_downHistory00);
   tolua_function(tolua_S,"leftCursor",tolua_mdraw_mdraw_ConsoleWindow_leftCursor00);
   tolua_function(tolua_S,"rightCursor",tolua_mdraw_mdraw_ConsoleWindow_rightCursor00);
   tolua_function(tolua_S,"putch",tolua_mdraw_mdraw_ConsoleWindow_putch00);
   tolua_function(tolua_S,"print",tolua_mdraw_mdraw_ConsoleWindow_print00);
   tolua_function(tolua_S,"resize",tolua_mdraw_mdraw_ConsoleWindow_resize00);
   tolua_function(tolua_S,"sizeUp",tolua_mdraw_mdraw_ConsoleWindow_sizeUp00);
   tolua_function(tolua_S,"sizeDown",tolua_mdraw_mdraw_ConsoleWindow_sizeDown00);
   tolua_function(tolua_S,"setPrompt",tolua_mdraw_mdraw_ConsoleWindow_setPrompt00);
   tolua_function(tolua_S,"setCursorPosition",tolua_mdraw_mdraw_ConsoleWindow_setCursorPosition00);
   tolua_function(tolua_S,"getNumLines",tolua_mdraw_mdraw_ConsoleWindow_getNumLines00);
   tolua_function(tolua_S,"setTop",tolua_mdraw_mdraw_ConsoleWindow_setTop00);
   tolua_function(tolua_S,"getTop",tolua_mdraw_mdraw_ConsoleWindow_getTop00);
   tolua_function(tolua_S,"getHeight",tolua_mdraw_mdraw_ConsoleWindow_getHeight00);
   tolua_function(tolua_S,"getLastLine",tolua_mdraw_mdraw_ConsoleWindow_getLastLine00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_function(tolua_S,"notify",tolua_mdraw_mdraw_notify00);
  tolua_function(tolua_S,"notify",tolua_mdraw_mdraw_notify01);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"mdraw",0);
 tolua_beginmodule(tolua_S,"mdraw");
  tolua_function(tolua_S,"getNodeString",tolua_mdraw_mdraw_getNodeString00);
  tolua_function(tolua_S,"getBoundingBox",tolua_mdraw_mdraw_getBoundingBox00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_mdraw (lua_State* tolua_S) {
 return tolua_mdraw_open(tolua_S);
};
#endif

