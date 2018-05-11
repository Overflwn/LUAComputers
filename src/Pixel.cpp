#include "Pixel.h"
using namespace LuaComputers;

Pixel::Pixel() : color(sf::Color::White)
{
	shape.setFillColor(sf::Color::White);
	character.setString(" ");
	character.setColor(sf::Color::Black);
	
}

Pixel::Pixel(sf::Color color, char character) : color(color)
{
	shape.setFillColor(color);
	this->character.setString(character);
}

sf::Color Pixel::getColor()
{
	return this->color;
}

void Pixel::setColor(sf::Color color)
{
	this->color = color;
	this->shape.setFillColor(color);
}

sf::RectangleShape& Pixel::getShape()
{
	return this->shape;
}