#ifndef LUA_UDP_SENDER_H
#define LUA_UDP_SENDER_H
#include "NetworkMessage.h"
#include <queue>
#include <lua.hpp>
#include <lauxlib.h>

namespace LuaComputers::Lua
{
    struct UdpSender
    {
        static std::queue<LuaComputers::NetworkMessage>* msgQueue;
        static int send(lua_State* L);
    };
}

#endif