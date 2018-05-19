#ifndef LUA_COMPUTER_H
#define LUA_COMPUTER_H
#include <lua.hpp>
#include <lauxlib.h>
#include <queue>
#include "ComputerEvent.h"

namespace LuaComputers::Lua
{
    struct Computer
    {
        static std::queue<LuaComputers::ComputerEvent>* the_events;
        static int pullEvent(lua_State* L);
        static int pushEvent(lua_State* L);
    };
}

#endif