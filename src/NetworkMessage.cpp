#include "NetworkMessage.h"

using namespace LuaComputers;

NetworkMessage::NetworkMessage(const char* to, const char* message) :
    to(to),
    message(message)
{
    
}