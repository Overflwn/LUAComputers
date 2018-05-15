#ifndef TERMINAL_H
#define TERMINAL_H
#include <SFML/Graphics.hpp>
#include "Pixel.h"
#include <vector>

namespace LuaComputers
{
	class Terminal
	{
	private:
		int width, height;
		LuaComputers::Pixel* pixels;
		const sf::Vector2f pixel_size;
		std::vector<sf::Vertex> pixels_vertices;
	public:
		Terminal();
		Terminal(int width, int height, int window_width, int window_height);
		~Terminal();
		int getWidth();
		int getHeight();
		void setPixel(int x, int y, sf::Color color);
		void clear(sf::Color color);
		void clearLine(int y, sf::Color color);
		void clearArea(int x, int y, int width, int height, sf::Color color);
		sf::Color getPixelColor(int x, int y);
		void draw(sf::RenderWindow& window);
		
	};
}

#endif