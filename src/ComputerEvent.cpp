#include "ComputerEvent.h"

using namespace LuaComputers;

ComputerEvent::ComputerEvent()
{}

ComputerEvent::ComputerEvent(const char* type) : type(type)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1) : type(type), data1(data1)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1, const char* data2) : type(type), data1(data1), data2(data2)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1, const char* data2, const char* data3) : type(type), data1(data1), data2(data2), data3(data3)
{}