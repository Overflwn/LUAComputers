/*
 * 		ComputerEvent
 * 
 * Summary:
 * 		This class is just a "container" for the available
 * 		events.
 * 		It makes converting parameters from Lua to C++ easier.
 * 
 * 	Note:
 * 		Every parameter of these events are strings.
 * 
 * 	Author:
 * 		Piorjade
 * 
 * 	Last Edited:
 * 		05/11/18 (MM/DD/YY)
 */

#ifndef COMPUTEREVENT_H
#define COMPUTEREVENT_H

namespace LuaComputers
{
	class ComputerEvent
	{
	public:
		const char* type;
		const char* data1;
		const char* data2;
		const char* data3;
		ComputerEvent();
		ComputerEvent(const char* type);
		ComputerEvent(const char* type, const char* data1);
		ComputerEvent(const char* type, const char* data1, const char* data2);
		ComputerEvent(const char* type, const char* data1, const char* data2, const char* data3);
	};
}

#endif