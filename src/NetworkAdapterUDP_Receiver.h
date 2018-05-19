#ifndef NETWORK_ADAPTER_UDP_RECEIVER_H
#define NETWORK_ADAPTER_UDP_RECEIVER_H

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <iostream>
#include <queue>
#include "ComputerEvent.h"
#include <atomic>

namespace LuaComputers
{
    class NetworkAdapterUDP_Receiver
    {
        private:
            sf::UdpSocket socket;
            char* buffer;
            std::size_t received;
            sf::IpAddress ip;
            std::queue<LuaComputers::ComputerEvent>* events;
            std::atomic<bool> running;
            unsigned short port;
        public:
            NetworkAdapterUDP_Receiver(unsigned short port, unsigned short bufferSize, std::queue<LuaComputers::ComputerEvent>& events);
            ~NetworkAdapterUDP_Receiver();
            void runUdpReceiverThread();
            void setRunning(bool running);
            void freeMemory();
    };
}

#endif