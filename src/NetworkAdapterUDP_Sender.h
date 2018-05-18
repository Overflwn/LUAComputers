#ifndef NETWORK_ADAPTER_UDP_SENDER_H
#define NETWORK_ADAPTER_UDP_SENDER_H

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "NetworkMessage.h"
#include <iostream>
#include <queue>
#include "ComputerEvent.h"
#include <atomic>

namespace LuaComputers
{
    class NetworkAdapterUDP_Sender
    {
        private:
            sf::UdpSocket socket;
            std::queue<LuaComputers::NetworkMessage>* msgQueue;
            std::atomic<bool> running;
            unsigned short port;
        public:
            NetworkAdapterUDP_Sender(unsigned short port, std::queue<LuaComputers::NetworkMessage>& msgQueue);
            ~NetworkAdapterUDP_Sender();
            void runUdpSenderThread();
            void setRunning(bool running);
            void freeMemory();
    };
}

#endif