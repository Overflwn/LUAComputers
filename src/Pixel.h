/*
 * 		ComputerEvent
 * 
 * Summary:
 * 		This class is a "container" for the pseudo-pixels
 * 		of the terminal.
 * 		These pixels contain information about their background color,
 * 		text color, the character that they display and also
 * 		the actual SFML drawable shape.
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef PIXEL_H
#define PIXEL_H
#include <SFML/Graphics.hpp>

namespace LuaComputers
{
	class Pixel
	{
	public:
		Pixel();
		Pixel(sf::Color color);
		sf::Color getColor();
		void setColor(sf::Color color);
		sf::RectangleShape& getShape();
	private:
		sf::Color color;
		sf::RectangleShape shape;
	};
}

#endif