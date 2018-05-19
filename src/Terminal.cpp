#include "Terminal.h"
#include <stdio.h>

using namespace LuaComputers;

Terminal::Terminal(int width, int height, int window_width, int window_height) : width(width), height(height), pixel_size(window_width/width, window_height/height)
{
	printf("Created terminal with dimensions (%d x %d).\nPixels are (%f x %f).\n", width, height, pixel_size.x, pixel_size.y);
	//pixels = new LuaComputers::Pixel[height*width];
	
	float scaling_x = window_width / 816;
	float scaling_y = window_height / 608;
	
	//Init: Set up the size for each pixel
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			
			float pos_x = static_cast<float>(x) * pixel_size.x;
			float pos_y = static_cast<float>(y) * pixel_size.y;
			/*pixels[y*width+x].getShape().setSize(pixel_size);
			pixels[y*width+x].getShape().setPosition(pos_x, pos_y);*/
			//Top-left
			pixels_vertices.push_back(sf::Vertex(sf::Vector2f(pos_x, pos_y), sf::Color::Black));
			//Top-Right
			pixels_vertices.push_back(sf::Vertex(sf::Vector2f(pos_x+pixel_size.x, pos_y), sf::Color::Black));
			//Bottom-Right
			pixels_vertices.push_back(sf::Vertex(sf::Vector2f(pos_x+pixel_size.x, pos_y+pixel_size.y), sf::Color::Black));
			//Bottom-Left
			pixels_vertices.push_back(sf::Vertex(sf::Vector2f(pos_x, pos_y+pixel_size.y), sf::Color::Black));
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
	//pixels[y*width+x].setColor(color);
	//4 because we have 4 vertices per pixel
	int position = y*(width*4)+x*4;
	pixels_vertices[position].color = color;
	pixels_vertices[position+1].color = color;
	pixels_vertices[position+2].color = color;
	pixels_vertices[position+3].color = color;
}

sf::Color Terminal::getPixelColor(int x, int y)
{
	//return pixels[y*width+x].getColor();
	int position = y*(width*4)+x*4;
	return pixels_vertices[position].color;
}

void Terminal::clear(sf::Color color)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			//pixels[y*width+x].setColor(color);
			setPixel(x, y, color);
		}
	}
}

void Terminal::clearLine(int y, sf::Color color)
{
	for(int x = 0; x < width; x++)
	{
		//pixels[y*width+x].setColor(color);
		setPixel(x, y, color);
	}
}

void Terminal::clearArea(int x, int y, int _width, int _height, sf::Color color)
{
	for(int y2 = y; y2 < y+_height-1; y2++)
	{
		for(int x2 = x; x2 < x+_width-1; x2++)
		{
			//pixels[y2*width+x2].setColor(color);
			setPixel(x2, y2, color);
		}
	}
}

void Terminal::draw(sf::RenderWindow& window)
{
	/*printf("DRAWING");
	//texture.clear();
	for(int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//window.draw(pixels[y*width+x].getShape());
			texture.draw(pixels[y*width+x].getShape());
		}
	}
	texture.display();*/
	window.draw(&pixels_vertices[0], pixels_vertices.size(), sf::Quads);
}
