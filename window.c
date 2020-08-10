#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "luasdl.h"

static int window_createRenderer(lua_State *L);
static int window_destroy(lua_State *L);

static const struct luaL_Reg window_lib[] = {
	{"createRenderer", window_createRenderer},
	{"destroy", window_destroy},
	{NULL, NULL},
};

// return win, err
int luasdl_createWindow(lua_State *L) {
	const char *title = luaL_checkstring(L, 1);
	int width = luaL_checkinteger(L, 2);
	int height = luaL_checkinteger(L, 3);

	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		lua_pushboolean(L, 0);

		lua_pushliteral(L, "SDL_Error: ");
		lua_pushstring(L, SDL_GetError());
		lua_concat(L, 2);

		return 2;
	}

	lua_pushlightuserdata(L, window);

	if (luaL_newmetatable(L, "SDL_Window")) {
		lua_pushliteral(L, "__index");
		lua_newtable(L);

		luaL_setfuncs(L, window_lib, 0);

		lua_settable(L, -3);
	}

	lua_setmetatable(L, -2);

	return 1;
}

static int renderer_clear(lua_State *L);
static int renderer_destroy(lua_State *L);
static int renderer_fillRect(lua_State *L);
static int renderer_present(lua_State *L);
static int renderer_setColor(lua_State *L);

static const struct luaL_Reg renderer_lib[] = {
	{"clear", renderer_clear},
	{"destroy", renderer_destroy},
	{"fillRect", renderer_fillRect},
	{"present", renderer_present},
	{"setColor", renderer_setColor},
	{NULL, NULL}
};

static int window_createRenderer(lua_State *L) {
	SDL_Window *window = (SDL_Window *)luaL_checkudata(L, 1, "SDL_Window");

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		lua_pushboolean(L, 0);

		lua_pushliteral(L, "SDL_Error: ");
		lua_pushstring(L, SDL_GetError());
		lua_concat(L, 2);

		return 2;
	}

	lua_pushlightuserdata(L, renderer);

	if (luaL_newmetatable(L, "SDL_Renderer")) {
		lua_pushliteral(L, "__index");
		lua_newtable(L);

		luaL_setfuncs(L, renderer_lib, 0);

		lua_settable(L, -3);
	}

	lua_setmetatable(L, -2);

	return 1;
}

static int window_destroy(lua_State *L) {
	SDL_DestroyWindow((SDL_Window *)luaL_checkudata(L, 1, "SDL_Window"));

	return 0;
}

static int renderer_clear(lua_State *L) {
	SDL_RenderClear((SDL_Renderer *)luaL_checkudata(L, 1, "SDL_Renderer"));

	return 0;
}

static int renderer_destroy(lua_State *L) {
	SDL_DestroyRenderer((SDL_Renderer *)luaL_checkudata(L, 1, "SDL_Renderer"));

	return 0;
}

static int renderer_fillRect(lua_State *L) {
	SDL_Rect rect;

	SDL_Renderer *renderer = (SDL_Renderer *)luaL_checkudata(L, 1, "SDL_Renderer");
	rect.x = luaL_checkinteger(L, 2);
	rect.y = luaL_checkinteger(L, 3);
	rect.w = luaL_checkinteger(L, 4);
	rect.h = luaL_checkinteger(L, 5);

	SDL_RenderFillRect(renderer, &rect);

	return 0;
}

static int renderer_present(lua_State *L) {
	SDL_RenderPresent((SDL_Renderer *)luaL_checkudata(L, 1, "SDL_Renderer"));

	return 0;
}

static int renderer_setColor(lua_State *L) {
	SDL_Renderer *renderer = (SDL_Renderer *)luaL_checkudata(L, 1, "SDL_Renderer");
	int r = luaL_checkinteger(L, 2);
	int g = luaL_checkinteger(L, 3);
	int b = luaL_checkinteger(L, 4);
	int a = luaL_optinteger(L, 5, 0xFF);
	
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	return 0;
}

