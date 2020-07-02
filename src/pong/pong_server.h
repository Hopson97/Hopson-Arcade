#pragma once

#include "net.h"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <array>
#include <cstdint>

namespace pong {
    struct Connection {
        sf::Uint8 id = 0;
        sf::TcpSocket socket;
        bool isConnected = false;

        std::string name;
    };

    class PongServer {
      public:
        enum class State {
            Lobby,
            InGame,
        };
        State state = State::Lobby;

        bool start(uint16_t port);
        void stop();

        void update();

      private:
        void handlePacket(ToServerCommand command, sf::Packet& packet);
        void broadcast(sf::Packet& packet);

        std::array<Connection, MAX_CONNECTS> m_connections;
        sf::TcpListener m_tcpListener;

        int m_currentConnections = 0;
    };
} // namespace pong
