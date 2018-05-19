#include "Settings.h"

LuaComputers::Settings::Settings(int width, int height, int t_width, int t_height, const char* title, unsigned short networking_port) : 
    window_width(width), 
    window_height(height), 
    window_title(title), 
    terminal_width(t_width), 
    terminal_height(t_height),
    networking_port(networking_port)
{}

LuaComputers::Settings::Settings()
{}