/*
** Lua binding: userobj
** Generated automatically by tolua++-1.0.92 on 03/08/14 15:28:47.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_userobj_open (lua_State* tolua_S);

#include "userobj.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"KeyFrameObject");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"AnimateObject");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCArray");
}

/* method: create of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_create00
static int tolua_userobj_KeyFrameObject_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   KeyFrameObject* tolua_ret = (KeyFrameObject*)  KeyFrameObject::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"KeyFrameObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_rotate of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_get_rotate00
static int tolua_userobj_KeyFrameObject_get_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_rotate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get_rotate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_scalex of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_get_scalex00
static int tolua_userobj_KeyFrameObject_get_scalex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_scalex'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get_scalex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_scalex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_scaley of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_get_scaley00
static int tolua_userobj_KeyFrameObject_get_scaley00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_scaley'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get_scaley();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_scaley'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_posx of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_get_posx00
static int tolua_userobj_KeyFrameObject_get_posx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_posx'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get_posx();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_posx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_posy of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_get_posy00
static int tolua_userobj_KeyFrameObject_get_posy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_posy'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get_posy();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_posy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getkey_index of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_getkey_index00
static int tolua_userobj_KeyFrameObject_getkey_index00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getkey_index'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getkey_index();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getkey_index'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getkey_frame of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_getkey_frame00
static int tolua_userobj_KeyFrameObject_getkey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getkey_frame'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getkey_frame();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getkey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gettex_name of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_gettex_name00
static int tolua_userobj_KeyFrameObject_gettex_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gettex_name'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->gettex_name();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gettex_name'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_rotate of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_set_rotate00
static int tolua_userobj_KeyFrameObject_set_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_rotate'", NULL);
#endif
  {
   self->set_rotate(r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_scale of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_set_scale00
static int tolua_userobj_KeyFrameObject_set_scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  float sx = ((float)  tolua_tonumber(tolua_S,2,0));
  float sy = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_scale'", NULL);
#endif
  {
   self->set_scale(sx,sy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set_pos of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_set_pos00
static int tolua_userobj_KeyFrameObject_set_pos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  float px = ((float)  tolua_tonumber(tolua_S,2,0));
  float py = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set_pos'", NULL);
#endif
  {
   self->set_pos(px,py);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set_pos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setkey_frame of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_setkey_frame00
static int tolua_userobj_KeyFrameObject_setkey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  const char* frame = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setkey_frame'", NULL);
#endif
  {
   self->setkey_frame(frame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setkey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: settex_name of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_settex_name00
static int tolua_userobj_KeyFrameObject_settex_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'settex_name'", NULL);
#endif
  {
   self->settex_name(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'settex_name'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setkey_index of class  KeyFrameObject */
#ifndef TOLUA_DISABLE_tolua_userobj_KeyFrameObject_setkey_index00
static int tolua_userobj_KeyFrameObject_setkey_index00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"KeyFrameObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  KeyFrameObject* self = (KeyFrameObject*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setkey_index'", NULL);
#endif
  {
   self->setkey_index(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setkey_index'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_create00
static int tolua_userobj_AnimateObject_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool bone = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   AnimateObject* tolua_ret = (AnimateObject*)  AnimateObject::create(bone);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimateObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getseq of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_getseq00
static int tolua_userobj_AnimateObject_getseq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getseq'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getseq();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getseq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isbone of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_isbone00
static int tolua_userobj_AnimateObject_isbone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isbone'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isbone();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isbone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setcur_frame of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_setcur_frame00
static int tolua_userobj_AnimateObject_setcur_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
  const char* frame = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setcur_frame'", NULL);
#endif
  {
   self->setcur_frame(frame,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setcur_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setkey_frame of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_setkey_frame00
static int tolua_userobj_AnimateObject_setkey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* spr = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
  bool iskey = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setkey_frame'", NULL);
#endif
  {
   self->setkey_frame(spr,index,iskey);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setkey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getkey_frame of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_getkey_frame00
static int tolua_userobj_AnimateObject_getkey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getkey_frame'", NULL);
#endif
  {
   KeyFrameObject* tolua_ret = (KeyFrameObject*)  self->getkey_frame(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"KeyFrameObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getkey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: prikey_frame of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_prikey_frame00
static int tolua_userobj_AnimateObject_prikey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'prikey_frame'", NULL);
#endif
  {
   self->prikey_frame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'prikey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: plykey_frame of class  AnimateObject */
#ifndef TOLUA_DISABLE_tolua_userobj_AnimateObject_plykey_frame00
static int tolua_userobj_AnimateObject_plykey_frame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimateObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimateObject* self = (AnimateObject*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* spr = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'plykey_frame'", NULL);
#endif
  {
   self->plykey_frame(spr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'plykey_frame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_userobj_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"KeyFrameObject","KeyFrameObject","CCObject",NULL);
  tolua_beginmodule(tolua_S,"KeyFrameObject");
   tolua_function(tolua_S,"create",tolua_userobj_KeyFrameObject_create00);
   tolua_function(tolua_S,"get_rotate",tolua_userobj_KeyFrameObject_get_rotate00);
   tolua_function(tolua_S,"get_scalex",tolua_userobj_KeyFrameObject_get_scalex00);
   tolua_function(tolua_S,"get_scaley",tolua_userobj_KeyFrameObject_get_scaley00);
   tolua_function(tolua_S,"get_posx",tolua_userobj_KeyFrameObject_get_posx00);
   tolua_function(tolua_S,"get_posy",tolua_userobj_KeyFrameObject_get_posy00);
   tolua_function(tolua_S,"getkey_index",tolua_userobj_KeyFrameObject_getkey_index00);
   tolua_function(tolua_S,"getkey_frame",tolua_userobj_KeyFrameObject_getkey_frame00);
   tolua_function(tolua_S,"gettex_name",tolua_userobj_KeyFrameObject_gettex_name00);
   tolua_function(tolua_S,"set_rotate",tolua_userobj_KeyFrameObject_set_rotate00);
   tolua_function(tolua_S,"set_scale",tolua_userobj_KeyFrameObject_set_scale00);
   tolua_function(tolua_S,"set_pos",tolua_userobj_KeyFrameObject_set_pos00);
   tolua_function(tolua_S,"setkey_frame",tolua_userobj_KeyFrameObject_setkey_frame00);
   tolua_function(tolua_S,"settex_name",tolua_userobj_KeyFrameObject_settex_name00);
   tolua_function(tolua_S,"setkey_index",tolua_userobj_KeyFrameObject_setkey_index00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AnimateObject","AnimateObject","CCObject",NULL);
  tolua_beginmodule(tolua_S,"AnimateObject");
   tolua_function(tolua_S,"create",tolua_userobj_AnimateObject_create00);
   tolua_function(tolua_S,"getseq",tolua_userobj_AnimateObject_getseq00);
   tolua_function(tolua_S,"isbone",tolua_userobj_AnimateObject_isbone00);
   tolua_function(tolua_S,"setcur_frame",tolua_userobj_AnimateObject_setcur_frame00);
   tolua_function(tolua_S,"setkey_frame",tolua_userobj_AnimateObject_setkey_frame00);
   tolua_function(tolua_S,"getkey_frame",tolua_userobj_AnimateObject_getkey_frame00);
   tolua_function(tolua_S,"prikey_frame",tolua_userobj_AnimateObject_prikey_frame00);
   tolua_function(tolua_S,"plykey_frame",tolua_userobj_AnimateObject_plykey_frame00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_userobj (lua_State* tolua_S) {
 return tolua_userobj_open(tolua_S);
};
#endif

