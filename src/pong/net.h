#pragma once

#include <SFML/Network/Packet.hpp>

const uint16_t PORT = 52315;

enum class ToServerCommand : sf::Uint8 {
    Disconnect,
    Name,
};

enum class ToClientCommand : sf::Uint8 {
    Disconnect,
    Name,
};

template <typename T>
sf::Packet makePacket(T commandToSend)
{
    sf::Uint8 command = static_cast<sf::Uint8>(commandToSend);
    sf::Packet packet;
    packet << command;
    return packet;
}