#include <stdio.h>
#include <string.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

//待Lua调用的C注册函数。
static int pb_get_flag_value(lua_State* L)
{
    const char* flag_name = static_cast<const char*>(luaL_checkstring(L,1));
    const char* flag_value = "true";
    lua_pushstring(L, flag_value);
    return 1;
}

static const luaL_Reg libs[] =
{
	{"get_flag_value", pb_get_flag_value},
	{NULL, NULL}
};

extern "C" {
int luaopen_expflag(lua_State* L)
{
    //luaL_register(L, "expflag", libs);
    //luaL_setfuncs(L, libs, 0);
    luaL_newlib(L, libs);
    return 1;
}
}
