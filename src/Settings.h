/*
 * 		ComputerEvent
 * 
 * Summary:
 * 		This class is a "container" for program-specific
 * 		settings, like the window resolution.
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef SETTINGS_H
#define SETTINGS_H

namespace LuaComputers
{
	struct Settings
	{
	public:
		int window_width;
		int window_height;
		int terminal_width;
		int terminal_height;
		const char* window_title;
		Settings();
		Settings(int width, int height, int t_width, int t_height, const char* title);
	};
}

#endif