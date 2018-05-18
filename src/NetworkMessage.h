#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

namespace LuaComputers
{
    struct NetworkMessage
    {
        const char* to;
        const char* message;
        NetworkMessage(const char* to, const char* message);
    };
}

#endif