#include "Color.h"

using namespace LuaComputers;

Color::Color() : color(sf::Color::White), lc_color(0)
{}

Color::Color(sf::Color color, int lc_color) : color(color), lc_color(lc_color)
{}

int Color::getLCColor()
{
	return lc_color;
}

sf::Color Color::getSFColor()
{
	return color;
}

void Color::setLCColor(int lc_color)
{
	this->lc_color = lc_color;
}

void Color::setSFColor(sf::Color color)
{
	this->color = color;
}