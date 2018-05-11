/*
 * 		Lua_Terminal.h
 * 
 * Summary:
 * 		This class is just an interface for the actual
 * 		terminal class. It is basically just the lua
 * 		variant of the corresponding methods.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef LUA_TERMINAL_H
#define LUA_TERMINAL_H
#include "Color.h"
#include "Terminal.h"
#include <SFML/Graphics.hpp>
#include <lua5.2/lua.hpp>
#include <lua5.2/lauxlib.h>

namespace LuaComputers::Lua
{
	class Terminal
	{
	public:
		Terminal(LuaComputers::Terminal* the_terminal);
		~Terminal();
		int setPixel(lua_State* L);
		int getPixel(lua_State* L);
		void initColors();
		
		sf::Color asSFColor(int lc_color);
	private:
		LuaComputers::Terminal* the_terminal;
		LuaComputers::Color* colors;
	};
}

#endif