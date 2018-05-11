#include "Computer.h"

using namespace LuaComputers;

void Computer::bindCFunctions(lua_State* L)
{
	/*
	 *	EXAMPLE:
			lua_pushcfunction(L, foo);
			lua_setglobal(L, "cpp_foo");
	 */
	lua_pushcfunction(lua_terminal->getPixel);
	lua_setglobal(L, "getPixel");
	lua_pushcfunction(lua_terminal->setPixel);
	lua_setglobal(L, "setPixel");
}

Computer::Computer(const char* bios, LuaComputers::Terminal terminal)
{
	L = luaL_newstate();
	lua_terminal = new Lua::Terminal(terminal);
	
	//Load standard libraries
	luaL_openlibs(L);
	//Bind C functions
	bindCFunctions(L);
}

Computer::~Computer()
{
	delete lua_terminal;
	delete L;
	
	L = nullptr;
	lua_terminal = nullptr;
	
}