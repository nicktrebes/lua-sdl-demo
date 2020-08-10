#ifndef LUASDL_H
#define LUASDL_H

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

int luasdl_createWindow(lua_State *L);
int luasdl_init(lua_State *L);
int luasdl_pollEvent(lua_State *L);
int luasdl_quit(lua_State *L);

extern int luaopen_libluasdl(lua_State *L);

#endif /* ! LUASDL_WINDOW_H */

