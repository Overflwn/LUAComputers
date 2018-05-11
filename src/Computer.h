/*
 * 		Computer.h
 * 
 * Summary:
 * 		This class is responsible for the lua "vm",
 * 		links the C/C++ functions to that vm and
 * 		finally starts up the bios luafile.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef COMPUTER_H
#define COMPUTER_H
#include <lua5.2/lua.hpp>
#include <lua5.2/lauxlib.h>
#include "Lua_Terminal.h"

namespace LuaComputers
{
	class Computer
	{
	public:
		Computer(const char* bios);
		~Computer();
	private:
		lua_State* L;
		void bindCFunctions(lua_State* L);
		Lua::Terminal* lua_terminal;
	};
}

#endif