#include "NetworkAdapterUDP_Receiver.h"
#include <iostream>

using namespace LuaComputers;

NetworkAdapterUDP_Receiver::NetworkAdapterUDP_Receiver(unsigned short port, unsigned short bufferSize, std::queue<LuaComputers::ComputerEvent>& events) : 
    buffer(new char[bufferSize]),
    events(&events),
    received(0),
    running(false),
    port(port)
{
    socket.bind(port);
    socket.setBlocking(false);
}

NetworkAdapterUDP_Receiver::~NetworkAdapterUDP_Receiver()
{
}

void NetworkAdapterUDP_Receiver::runUdpReceiverThread()
{
    std::cout << "Running UDP Receiver thread.\n" << std::endl;
    running = true;
    while(running)
    {
        sf::Socket::Status status_code = socket.receive(buffer, sizeof(buffer), received, ip, port);
        if(status_code == sf::Socket::Done)
        {
            events->push(LuaComputers::ComputerEvent("network_message", 
            ip.toString().c_str(), 
            std::to_string(port).c_str(), 
            buffer));
            std::cout << "Message from " << ip.toString() << ": " << buffer << std::endl;
        }
    }
    std::cout << "UDP Receiver thread stopped.\n" << std::endl;
}

void NetworkAdapterUDP_Receiver::setRunning(bool running)
{
    this->running = running;
}

void NetworkAdapterUDP_Receiver::freeMemory()
{
    delete[] buffer;
    buffer = nullptr;
    events = nullptr;
}