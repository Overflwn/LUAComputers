#include "Lua_Computer.h"
#include <iostream>
using namespace LuaComputers::Lua;

std::queue<LuaComputers::ComputerEvent>* Computer::the_events;

int Computer::pullEvent(lua_State* L)
{
    LuaComputers::ComputerEvent event;
    bool shouldPop = false;
    if(the_events->size() > 0)
    {
        event = the_events->front();
        shouldPop = true;
    }
    lua_pushstring(L, event.type);
    lua_pushstring(L, event.data1);
    lua_pushstring(L, event.data2);
    lua_pushstring(L, event.data3);
    if(shouldPop)
    {
        the_events->pop();
    }
    return 4;
}

int Computer::pushEvent(lua_State* L)
{
    const char* type = nullptr;
    const char* data1 = nullptr;
    const char* data2 = nullptr;
    const char* data3 = nullptr;
    bool push = false;
    if(lua_gettop(L) == 4)
    {
        type = lua_tostring(L, -4);
        data1 = lua_tostring(L, -3);
        data2 = lua_tostring(L, -2);
        data3 = lua_tostring(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        push = true;
    }else if(lua_gettop(L) == 3)
    {
        type = lua_tostring(L, -3);
        data1 = lua_tostring(L, -2);
        data2 = lua_tostring(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        push = true;
    }else if(lua_gettop(L) == 2)
    {
        type = lua_tostring(L, -2);
        data1 = lua_tostring(L, -1);
        lua_pop(L, -1);
        lua_pop(L, -1);
        push = true;
    }else if(lua_gettop(L) == 1)
    {
        type = lua_tostring(L, -1);
        lua_pop(L, -1);
        push = true;
    }else
    {
        luaL_error(L, "expected string, string, string, string");
    }
    if(push)
    {
        the_events->push(LuaComputers::ComputerEvent(type, data1, data2, data3));
    }
    return 0;
}