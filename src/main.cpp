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
#include <simpleini/SimpleIni.h>
#include "ComputerEvent.h"
#include "NetworkAdapterUDP_Receiver.h"
#include "NetworkAdapterUDP_Sender.h"
#include "Computer.h"
#include "NetworkMessage.h"
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
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(file);
	const char* title = ini.GetValue("window", "title", "CLuaComputers");
	const char* w_width_s = ini.GetValue("window", "width", "816");
	const char* w_height_s = ini.GetValue("window", "height", "608");
	const char* t_width_s = ini.GetValue("terminal", "width", "51");
	const char* t_height_s = ini.GetValue("terminal", "height", "19");
	const char* c_networking_port_s = ini.GetValue("computer", "networking_port");

	int w_width = 0;
	int w_height = 0;
	int t_width = 0;
	int t_height = 0;
	unsigned short c_networking_port = 0;
	w_width = strtol(w_width_s, nullptr, 10);
	w_height = strtol(w_height_s, nullptr, 10);
	t_width = strtol(t_width_s, nullptr, 10);
	t_height = strtol(t_height_s, nullptr, 10);
	c_networking_port = static_cast<unsigned short>(strtol(c_networking_port_s, nullptr, 6969));



	settings->window_width = w_width;
	settings->window_height = w_height;
	settings->window_title = title;
	settings->terminal_width = t_width;
	settings->terminal_height = t_height;
	settings->networking_port = c_networking_port;
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
	std::cout << "Term created" << std::endl;
	sf::Clock clock;
	sf::Time time;
	
	std::queue<LuaComputers::ComputerEvent> events;
	std::queue<LuaComputers::NetworkMessage> msgQueue;
	LuaComputers::NetworkAdapterUDP_Receiver udp_receiver(settings->networking_port,1024, events);
	LuaComputers::NetworkAdapterUDP_Sender udp_sender(settings->networking_port,msgQueue);
	LuaComputers::Computer computer("bios.lua", term, events, msgQueue);
	
	
	sf::Thread b_thread(&LuaComputers::Computer::runBiosThread, &computer);
	b_thread.launch();

	sf::Thread c_thread(&LuaComputers::NetworkAdapterUDP_Receiver::runUdpReceiverThread, &udp_receiver);
	c_thread.launch();

	sf::Thread d_thread(&LuaComputers::NetworkAdapterUDP_Sender::runUdpSenderThread, &udp_sender);
	d_thread.launch();
	
	//Main SFML loop
	sf::RenderWindow window(sf::VideoMode(settings->window_width, settings->window_height+20), settings->window_title);
	sf::RectangleShape control_panel(sf::Vector2f(settings->window_width, 20));
	control_panel.setPosition(sf::Vector2f(0, window.getSize().y-20));
	control_panel.setFillColor(sf::Color(200, 200, 200));
	bool running = true;
	while(window.isOpen() && running)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					udp_receiver.setRunning(false);
					udp_sender.setRunning(false);
					c_thread.wait();
					d_thread.wait();
					b_thread.terminate();
					//c_thread.terminate();
					computer.freeMemory();
					udp_receiver.freeMemory();
					udp_sender.freeMemory();
					window.close();
					running = false;
					break;
				case sf::Event::TextEntered:
					events.push(LuaComputers::ComputerEvent("char", std::to_string(event.text.unicode).c_str(), "nil", "nil"));
					break;
			}
			if(!running)
				break;
		}
		if(!running)
		{
			break;
		}
			
		
		window.clear();
		term.draw(window);
		window.draw(control_panel);
		window.display();
		
		time = clock.getElapsedTime();
		//std::cout << 1.0f/time.asSeconds() << std::endl;
		window.setTitle("FPS: " + std::to_string(1.0f/time.asSeconds()));
		clock.restart().asSeconds();
	}
	
	return 0;
}
