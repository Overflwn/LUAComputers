#include "Pixel.h"
using namespace LuaComputers;

Pixel::Pixel() : color(sf::Color::White)
{
	shape.setFillColor(sf::Color::White);
	
}

Pixel::Pixel(sf::Color color) : color(color)
{
	shape.setFillColor(color);
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