#include "ComputerEvent.h"

using namespace LuaComputers;

ComputerEvent::ComputerEvent() : type(nullptr), data1(nullptr), data2(nullptr), data3(nullptr)
{}

ComputerEvent::ComputerEvent(const char* type) : type(type), data1(nullptr), data2(nullptr), data3(nullptr)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1) : type(type), data1(data1), data2(nullptr), data3(nullptr)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1, const char* data2) : type(type), data1(data1), data2(data2), data3(nullptr)
{}

ComputerEvent::ComputerEvent(const char* type, const char* data1, const char* data2, const char* data3) : type(type), data1(data1), data2(data2), data3(data3)
{}