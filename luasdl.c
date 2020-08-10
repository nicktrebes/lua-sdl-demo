#include <SDL2/SDL.h>
#include "luasdl.h"

static const struct luaL_Reg sdl_lib[] = {
	{"createWindow", luasdl_createWindow},
	{"init", luasdl_init},
	{"pollEvent", luasdl_pollEvent},
	{"quit", luasdl_quit},
	{NULL, NULL}
};

extern int luaopen_libluasdl(lua_State *L) {
	lua_newtable(L);
	luaL_setfuncs(L, sdl_lib, 0);

	return 1;
}

// return ok, err
int luasdl_init(lua_State *L) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		lua_pushboolean(L, 0);
		
		lua_pushliteral(L, "SDL_Error: ");
		lua_pushstring(L, SDL_GetError());
		lua_concat(L, 2);
		
		return 2;
	}

	lua_pushboolean(L, 1);

	return 1;
}

int luasdl_quit(lua_State *L) {
	SDL_Quit();

	return 0;
}

