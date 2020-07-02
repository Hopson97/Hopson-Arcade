#include "pong_server.h"
#include <iostream>

namespace pong {

    bool PongServer::start(uint16_t port)
    {
        sf::Uint8 id = 0;
        m_tcpListener.setBlocking(false);
        for (auto& client : m_connections) {
            client.id = id++;
            client.socket.setBlocking(false);
        }
        return m_tcpListener.listen(port) == sf::Socket::Done;
    }

    void PongServer::stop()
    {
        auto packet = makePacket(ToClientCommand::Disconnect);
        broadcast(packet);
    }

    void PongServer::update()
    {
        for (auto& client : m_connections) {
            sf::TcpSocket& socket = client.socket;
            if (!client.isConnected) {
                if (m_tcpListener.accept(socket) == sf::Socket::Done) {

                    auto playerListPacket = makePacket(ToClientCommand::PlayerList);
                    playerListPacket << (sf::Uint8)m_currentConnections;
                    for (auto& player : m_connections) {
                        if (player.isConnected) {
                            playerListPacket << player.id << player.name;
                        }
                    }
                    socket.send(playerListPacket);

                    m_currentConnections++;

                    client.isConnected = true;
                    auto packet = makePacket(ToClientCommand::PlayerId);
                    packet << client.id;
                    socket.send(packet);
                }
            }
            else {
                sf::Packet packet;
                if (socket.receive(packet) == sf::Socket::Done) {
                    sf::Uint8 cmd = 0;
                    packet >> cmd;
                    auto command = static_cast<ToServerCommand>(cmd);
                    handlePacket(command, packet);
                }
            }
        }
    }

    void PongServer::broadcast(sf::Packet& packet)
    {
        for (auto& client : m_connections) {
            if (client.isConnected) {
                client.socket.send(packet);
            }
        }
    }

    void PongServer::handlePacket(ToServerCommand command, sf::Packet& packet)
    {
        switch (command) {
            case ToServerCommand::Disconnect: {
                sf::Uint8 id;
                packet >> id;
                m_connections[id].isConnected = false;
                m_connections[id].socket.disconnect();

                auto broadcastPacket = makePacket(ToClientCommand::PlayerDisconnected);
                broadcastPacket << id;
                broadcast(broadcastPacket);
                m_currentConnections--;

            } break;

            case ToServerCommand::Name: {
                sf::Uint8 id;
                std::string name;
                packet >> id >> name;
                m_connections[id].name = name;
                std::cout << "Server got name " << name << ' ' << (int)id << std::endl;

                auto broadcastPacket = makePacket(ToClientCommand::PlayerConnected);
                broadcastPacket << id << name;
                broadcast(broadcastPacket);
            } break;

            default:
                break;
        }
    }
} // namespace pong
