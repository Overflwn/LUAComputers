#include "Terminal.h"
#include <stdio.h>

using namespace LuaComputers;

Terminal::Terminal(int width, int height, int window_width, int window_height) : width(width), height(height), pixel_size(window_width/width, window_height/height)
{
	printf("Created terminal with dimensions (%d x %d).\nPixels are (%f x %f).\n", width, height, pixel_size.x, pixel_size.y);
	pixels = new LuaComputers::Pixel[height*width];
	font.loadFromFile("Minecraft.otf");
	
	
	float scaling_x = window_width / 816;
	float scaling_y = window_height / 608;
	
	//Init: Set up the size for each pixel
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			
			float pos_x = static_cast<float>(x) * pixel_size.x;
			float pos_y = static_cast<float>(y) * pixel_size.y;
			printf("PIXEL: %d,    %f x %f\n", y*width+x, pos_x, pos_y);
			pixels[y*width+x].getShape().setSize(pixel_size);
			pixels[y*width+x].getShape().setPosition(pos_x, pos_y);
			pixels[y*width+x].character.setPosition(pos_x+3, pos_y);
			pixels[y*width+x].character.setFont(font);
			//pixels[y*width+x].character.setCharacterSize(static_cast<int>(pixel_size.x)*2-1);
			pixels[y*width+x].character.setCharacterSize(32*scaling_x);
			//This scaling was tested on a 51x19 terminal size and 816x608 window size.
			pixels[y*width+x].character.setScale(0.675f, 0.8f);
			sf::FloatRect bounds = pixels[y*width+x].character.getGlobalBounds();
			printf("BOUNDS: %f,%f\n", bounds.left, bounds.top);
			//pixels[y*width+x].character.setPosition(pos_x + (pixel_size.x / 2 - bounds.width / 2),pos_y);
		}
	}
}

Terminal::~Terminal()
{
	//Clear up memory shit
	delete[] pixels;
	printf("Destroyed terminal.\n");
}

void Terminal::setPixel(int x, int y, sf::Color color)
{
	pixels[y*width+x].setColor(color);
}

void Terminal::setPixel(int x, int y, sf::Color color, char character)
{
	pixels[y*width+x].setColor(color);
	pixels[y*width+x].character.setString(character);
}

void Terminal::setPixel(int x, int y, sf::Color color, char character, sf::Color textColor)
{
	pixels[y*width+x].setColor(color);
	pixels[y*width+x].character.setString(character);
	pixels[y*width+x].character.setFillColor(textColor);
}

sf::Color Terminal::getPixelColor(int x, int y)
{
	return pixels[y*width+x].getColor();
}

sf::Color Terminal::getPixelTextColor(int x, int y)
{
	return pixels[y*width+x].character.getFillColor();
}

const char* Terminal::getPixelCharacter(int x, int y)
{
	return pixels[y*width+x].character.getString().toAnsiString().c_str();
}

void Terminal::draw(sf::RenderWindow& window)
{
	for(int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			window.draw(pixels[y*width+x].getShape());
			window.draw(pixels[y*width+x].character);
		}
	}
}