#include "Lua_Udp_Sender.h"

using namespace LuaComputers::Lua;

std::queue<LuaComputers::NetworkMessage>* UdpSender::msgQueue;

int UdpSender::send(lua_State* L)
{
    // Queue a NetworkMessage object to be processed by the actual UDP socket
    if(lua_gettop(L) >= 2)
    {
        const char* to = lua_tostring(L, -2);
        const char* message = lua_tostring(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        msgQueue->push(LuaComputers::NetworkMessage(to, message));
        return 0;
    }else
    {
        luaL_error(L, "expected string, string");
        return 1;
    }

}