/*
 * 		Color.h
 * 
 * Summary:
 * 		This class is just a "container" for the available
 * 		colors.
 * 		It makes converting parameters from Lua to C++ easier.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef LC_COLOR_H
#define LC_COLOR_H
#include <SFML/Graphics.hpp>

namespace LuaComputers
{
	class Color
	{
	public:
		Color();
		Color(sf::Color color, int lc_color);
		int getLCColor();
		sf::Color getSFColor();
		void setLCColor(int lc_color);
		void setSFColor(sf::Color color);
	private:
		sf::Color color;
		int lc_color;
	};
}

#endif