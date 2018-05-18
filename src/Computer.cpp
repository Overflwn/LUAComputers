#include "Computer.h"
#include <iostream>
#include <SFML/System.hpp>


using namespace LuaComputers;

void Computer::bindCFunctions(lua_State* L)
{
	/*
	 *	EXAMPLE:
			lua_pushcfunction(L, foo);
			lua_setglobal(L, "cpp_foo");
	 */
	lua_pushcfunction(L, Lua::Terminal::getPixel);
	lua_setglobal(L, "getPixel");
	lua_pushcfunction(L, Lua::Terminal::setPixel);
	lua_setglobal(L, "setPixel");
	lua_pushcfunction(L, Lua::Terminal::clear);
	lua_setglobal(L, "clear");
	lua_pushcfunction(L, Lua::Terminal::clearLine);
	lua_setglobal(L, "clearLine");
	lua_pushcfunction(L, Lua::Terminal::clearArea);
	lua_setglobal(L, "clearArea");
	lua_pushcfunction(L, Lua::Computer::pullEvent);
	lua_setglobal(L, "pullEvent");
	lua_pushcfunction(L, Lua::Computer::pushEvent);
	lua_setglobal(L, "pushEvent");
	lua_pushcfunction(L, Lua::UdpSender::send);
	lua_setglobal(L, "network_send");

	//Pop 7 times to get rid of the functions in the stack
	for(int i = 0; i < 8; i++)
	{
		lua_pop(L, -1);
	}
	
	std::cout << "C functions bound!" << std::endl;
}

void Computer::runBiosThread()
{
	std::cout << "Started" << std::endl;
	luaL_dofile(L, bios);
	std::cout << "Finished" << std::endl;
}

Computer::Computer(const char* bios, LuaComputers::Terminal& term, std::queue<LuaComputers::ComputerEvent>& events, std::queue<LuaComputers::NetworkMessage>& msgQueue) : bios(bios)
{
	L = luaL_newstate();
	Lua::Terminal::the_terminal = &term;
	Lua::Computer::the_events = &events;
	Lua::UdpSender::msgQueue = &msgQueue;
	Lua::Terminal::initColors();
	//Load standard libraries
	luaL_openlibs(L);
	//Bind C functions
	bindCFunctions(L);
	
	// Run the bios file in a seperate thread
	//luaL_dofile(L, bios);
	//std::thread bios_thread(runBiosThread, L, bios);
}

void Computer::freeMemory()
{
	//delete L;
	L = nullptr;
}
Computer::~Computer()
{}
