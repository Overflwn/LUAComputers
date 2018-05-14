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
	
	std::cout << "C functions bound!" << std::endl;
}

void Computer::runBiosThread()
{
	std::cout << "Started" << std::endl;
	luaL_dofile(L, bios);
	std::cout << "Finished" << std::endl;
}

Computer::Computer(const char* bios, LuaComputers::Terminal& term) : bios(bios)
{
	L = luaL_newstate();
	Lua::Terminal::the_terminal = &term;
	Lua::Terminal::initColors();
	//Load standard libraries
	luaL_openlibs(L);
	//Bind C functions
	bindCFunctions(L);
	
	// Run the bios file in a seperate thread
	//luaL_dofile(L, bios);
	//std::thread bios_thread(runBiosThread, L, bios);
}

Computer::~Computer()
{
	delete L;
	
	L = nullptr;
	
}