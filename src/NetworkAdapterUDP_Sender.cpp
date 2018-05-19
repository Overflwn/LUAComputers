#include "NetworkAdapterUDP_Sender.h"

using namespace LuaComputers;

NetworkAdapterUDP_Sender::NetworkAdapterUDP_Sender(unsigned short port, std::queue<LuaComputers::NetworkMessage>& msgQueue):
    port(port),
    msgQueue(&msgQueue),
    running(false)
{
}

NetworkAdapterUDP_Sender::~NetworkAdapterUDP_Sender()
{}

void NetworkAdapterUDP_Sender::runUdpSenderThread()
{
    std::cout << "Running UDP Sender thread.\n" << std::endl;
    running = true;
    while(running)
    {
        if(!msgQueue->empty())
        {
            LuaComputers::NetworkMessage msg = msgQueue->front();
            std::string message = msg.message;
            socket.send(message.c_str(), message.size()+1, msg.to, port);
            std::cout << "Sent message to " << msg.to << ": " << message << std::endl;
            msgQueue->pop();
        }
    }
    std::cout << "UDP Sender thread stopped.\n" << std::endl;
}

void NetworkAdapterUDP_Sender::freeMemory()
{
    msgQueue = nullptr;
}

void NetworkAdapterUDP_Sender::setRunning(bool running)
{
    this->running = running;
}