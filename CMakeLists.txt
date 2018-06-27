cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(include)

project(LuaComputers)

add_executable(
	LuaComputers
	src/main.cpp
	src/Color.cpp
	src/Computer.cpp
	src/ComputerEvent.cpp
	src/Lua_Computer.cpp
	src/Lua_Terminal.cpp
	src/Lua_Udp_Sender.cpp
	src/NetworkAdapterUDP_Receiver.cpp
	src/NetworkAdapterUDP_Sender.cpp
	src/NetworkMessage.cpp
	src/Pixel.cpp
	src/Settings.cpp
	src/Terminal.cpp
)

target_link_libraries(
	LuaComputers
	-lsfml-graphics
	-lsfml-window
	-lsfml-network
	-lsfml-system
	-llua
	-ldl
)
