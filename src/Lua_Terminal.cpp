#include "Lua_Terminal.h"

#include <cmath>

using namespace LuaComputers::Lua;

Terminal::Terminal(LuaComputers::Terminal* the_terminal) : the_terminal(the_terminal)
{
	colors = new LuaComputers::Color[16];
}

Terminal::~Terminal()
{
	delete[] colors;
	//Don't delete the_terminal as it is defined in Computer.cpp, so Computer.cpp has to delete it
	
	colors = nullptr;
	the_terminal = nullptr;
}

void Terminal::initColors()
{
	
	for(int i = 0; i < 16; i++)
	{
		colors[i].setLCColor(static_cast<int>(pow(2, i)));
		switch(i)
		{
			case 0:
				colors[i].setSFColor(sf::Color(25, 25, 25));
				break;
			case 1:
				colors[i].setSFColor(sf::Color(242, 178, 51));
				break;
			case 2:
				colors[i].setSFColor(sf::Color(229, 127, 216));
				break;
			case 3:
				colors[i].setSFColor(sf::Color(153, 178, 242));
				break;
			case 4:
				colors[i].setSFColor(sf::Color(222, 222, 108));
				break;
			case 5:
				colors[i].setSFColor(sf::Color(127, 204, 25));
				break;
			case 6:
				colors[i].setSFColor(sf::Color(242, 178, 204));
				break;
			case 7:
				colors[i].setSFColor(sf::Color(76,76,76));
				break;
			case 8:
				colors[i].setSFColor(sf::Color(153, 153, 153));
				break;
			case 9:
				colors[i].setSFColor(sf::Color(76, 153, 178));
				break;
			case 10:
				colors[i].setSFColor(sf::Color(178, 102, 229));
				break;
			case 11:
				colors[i].setSFColor(sf::Color(51, 102, 204));
				break;
			case 12:
				colors[i].setSFColor(sf::Color(127, 102, 76));
				break;
			case 13:
				colors[i].setSFColor(sf::Color(87, 166, 78));
				break;
			case 14:
				colors[i].setSFColor(sf::Color(204, 76, 76));
				break;
			case 15:
				colors[i].setSFColor(sf::Color(240, 240, 240));
				break;
			default:
				colors[i].setSFColor(sf::Color(25, 25, 25));
		}
	}
}

sf::Color Terminal::asSFColor(int lc_color)
{
	sf::Color col = sf::Color::Black;
	for(int i = 0; i < 16; i++)
	{
		if(colors[i].getLCColor() == lc_color)
		{
			col = colors[i].getSFColor();
		}
	}
	return col;
}

int Terminal::getPixel(lua_State* L)
{
	int y = lua_tonumber(L, -1);
	int x = lua_tonumber(L, -1);
	sf::Color bg_color = the_terminal->getPixelColor(x, y);
	sf::Color fg_color = the_terminal->getPixelTextColor(x, y);
	const char* the_char = the_terminal->getPixelCharacter(x, y);
	int lc_bg_color = 0;
	int lc_fg_color = 0;
	
	for(int i = 0; i < 16; i++)
	{
		if(colors[i].getSFColor() == bg_color)
		{
			lc_bg_color = colors[i].getLCColor();
		}
		if(colors[i].getSFColor() == fg_color)
		{
			lc_fg_color = colors[i].getLCColor();
		}
	}
	
	lua_pushstring(L, the_char);
	lua_pushnumber(L, lc_bg_color);
	lua_pushnumber(L, lc_fg_color);
	
	//We return 3 values (character, background_color, text_color) 
	return 3;
}

int Terminal::setPixel(lua_State* L)
{
	const char* newchar = lua_tostring(L, -1);
	int lc_fg_color = lua_tonumber(L, -1);
	int lc_bg_color = lua_tonumber(L, -1);
	int y = lua_tonumber(L, -1);
	int x = lua_tonumber(L, -1);
	sf::Color bg_color = asSFColor(lc_bg_color);
	sf::Color fg_color = asSFColor(lc_fg_color);
	the_terminal->setPixel(x, y, bg_color, newchar[0], fg_color);
	return 0;
}