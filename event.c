#include <SDL2/SDL_events.h>
#include "luasdl.h"

int luasdl_pollEvent(lua_State *L) {
	SDL_Event event;
	if (!SDL_PollEvent(&event)) return 0;

	lua_newtable(L);
	lua_pushliteral(L, "type");

	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		lua_pushliteral(L, "mouseDown");
		lua_settable(L, -3);

		lua_pushliteral(L, "x");
		lua_pushinteger(L, event.button.x);
		lua_settable(L, -3);

		lua_pushliteral(L, "y");
		lua_pushinteger(L, event.button.y);
		lua_settable(L, -3);
		break;

	case SDL_MOUSEBUTTONUP:
		lua_pushliteral(L, "mouseUp");
		lua_settable(L, -3);
		break;

	case SDL_MOUSEMOTION:
		lua_pushliteral(L, "mouseMove");
		lua_settable(L, -3);

		lua_pushliteral(L, "x");
		lua_pushinteger(L, event.motion.x);
		lua_settable(L, -3);

		lua_pushliteral(L, "y");
		lua_pushinteger(L, event.motion.y);
		lua_settable(L, -3);
		break;

	case SDL_QUIT:
		lua_pushliteral(L, "quit");
		lua_settable(L, -3);
		break;

	default:
		lua_pushliteral(L, "unsupported");
		lua_settable(L, -3);
		break;
	}

	return 1;
}

