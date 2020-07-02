#pragma once

#include <SFML/Network/Packet.hpp>
#include <array>

namespace pong {
    const uint16_t PORT = 52324;
    const int MAX_CONNECTS = 4;

    enum class ToServerCommand : sf::Uint8 {
        Disconnect,
        Name,
    };

    enum class ToClientCommand : sf::Uint8 {
        // Just the enum
        Disconnect,

        // u8: player id
        PlayerId,

        // u8: player id
        // string: name
        PlayerConnected,

        // u8: player id
        PlayerDisconnected,

        // u8: count
        // <u8, sting>[count]: id, name
        PlayerList
    };

    template <typename T>
    sf::Packet makePacket(T commandToSend)
    {
        sf::Uint8 command = static_cast<sf::Uint8>(commandToSend);
        sf::Packet packet;
        packet << command;
        return packet;
    }

} // namespace pong