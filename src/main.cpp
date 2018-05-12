/*
 * 		LuaComputers - C++ / SFML version
 * 
 * 	WARNING: This is a test-build as I don't know
 * 			 C++ that much so I basically am learning by doing.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 * 
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <lua.hpp>
#include <lauxlib.h>
#include "Settings.h"
#include "Terminal.h"
#include <SimpleIni.h>
#include "ComputerEvent.h"
#include "Computer.h"
#include <queue>
#include <string>
#include <stdlib.h>

static float _VERSION = 0.1f;


static LuaComputers::Settings* loadSettings(const char* file)
{
	/*
	 * Load up an .xml file and load the settings from it.
	 * Warning: No real error checking
	 */
	LuaComputers::Settings* settings = new LuaComputers::Settings();
	/*tinyxml2::XMLDocument doc;
	doc.LoadFile(file);
	const tinyxml2::XMLElement* window_settings = doc.FirstChildElement("settings")->FirstChildElement("window");
	const tinyxml2::XMLElement* terminal_settings = doc.FirstChildElement("settings")->FirstChildElement("terminal");
	const char* title = window_settings->FirstChildElement("title")->GetText();
	int w_width = window_settings->FirstChildElement("width")->IntText(800);
	int w_height = window_settings->FirstChildElement("height")->IntText(600);
	int t_width = terminal_settings->FirstChildElement("width")->IntText(51);
	int t_height = terminal_settings->FirstChildElement("height")->IntText(19);*/
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(file);
	const char* title = ini.GetValue("window", "title", "CLuaComputers");
	const char* w_width_s = ini.GetValue("window", "width", "816");
	const char* w_height_s = ini.GetValue("window", "height", "608");
	const char* t_width_s = ini.GetValue("terminal", "width", "51");
	const char* t_height_s = ini.GetValue("terminal", "height", "19");

	int w_width = 0;
	int w_height = 0;
	int t_width = 0;
	int t_height = 0;
	w_width = strtol(w_width_s, nullptr, 10);
	w_height = strtol(w_height_s, nullptr, 10);
	t_width = strtol(t_width_s, nullptr, 10);
	t_height = strtol(t_height_s, nullptr, 10);



	settings->window_width = w_width;
	settings->window_height = w_height;
	settings->window_title = title;
	settings->terminal_width = t_width;
	settings->terminal_height = t_height;
	return settings;
}

int main(int argc, char **argv)
{
	std::cout << "LuaComputers Ver. " << _VERSION << std::endl;
	//Load settings from settings.xml
	std::cout << "Loading settings" << std::endl;
	LuaComputers::Settings* settings = loadSettings("settings.ini");
	std::cout << "Window W,H: " << settings->window_width << "," << settings->window_height << std::endl
			<< "Terminal W,H: " << settings->terminal_width << "," << settings->terminal_height << std::endl;
	
	LuaComputers::Terminal term(settings->terminal_width, settings->terminal_height, settings->window_width, settings->window_height);
	term.setPixel(3, 5, sf::Color::Red, 'H');
	term.setPixel(4, 5, sf::Color::Red, 'e');
	term.setPixel(5, 5, sf::Color::Red, 'l');
	term.setPixel(6, 5, sf::Color::Red, 'l');
	term.setPixel(7, 5, sf::Color::Red, 'o');
	term.setPixel(8, 5, sf::Color::Black, ' ', sf::Color::White);
	term.setPixel(9, 5, sf::Color::Red, 'W');
	term.setPixel(10, 5, sf::Color::Red, 'o');
	term.setPixel(11, 5, sf::Color::Red, 'r');
	term.setPixel(12, 5, sf::Color::Red, 'l');
	term.setPixel(13, 5, sf::Color::Red, 'd');
	
	sf::Clock clock;
	sf::Time time;
	
	std::queue<LuaComputers::ComputerEvent> events;
	
	LuaComputers::Computer computer("bios.lua", term);
	
	sf::Thread b_thread(&LuaComputers::Computer::runBiosThread, &computer);
	b_thread.launch();
	
	//Main SFML loop
	sf::RenderWindow window(sf::VideoMode(settings->window_width, settings->window_height), settings->window_title);
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					b_thread.terminate();
					break;
				case sf::Event::TextEntered:
					events.push(LuaComputers::ComputerEvent("char", std::to_string(event.text.unicode).c_str()));
					break;
			}
		}
		
		window.clear();
		term.draw(window);
		window.display();
		
		time = clock.getElapsedTime();
		//std::cout << 1.0f/time.asSeconds() << std::endl;
		window.setTitle("FPS: " + std::to_string(1.0f/time.asSeconds()));
		clock.restart().asSeconds();
	}
	
	return 0;
}
