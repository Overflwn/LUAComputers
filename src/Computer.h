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
#include <lua.hpp>
#include <lauxlib.h>
#include "Lua_Terminal.h"
#include "Lua_Computer.h"
#include <queue>
#include "ComputerEvent.h"
#include "NetworkMessage.h"
#include "Lua_Udp_Sender.h"
#include <atomic>

namespace LuaComputers
{
	class Computer
	{
	public:
		Computer(const char* bios, LuaComputers::Terminal& term, std::queue<LuaComputers::ComputerEvent>& events, std::queue<LuaComputers::NetworkMessage>& msgQueue);
		~Computer();
		void runBiosThread();
		void freeMemory();
	private:
		lua_State* L;
		const char* bios;
		void bindCFunctions(lua_State* L);
	};
}

#endif
