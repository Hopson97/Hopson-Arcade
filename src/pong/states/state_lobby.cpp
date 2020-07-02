#include "state_lobby.h"

#include "../display_info.h"
#include "../net.h"
#include "state_error.h"
#include <SFML/Network/Packet.hpp>
#include <arcade/game.h>
#include <arcade/gui/button.h>
#include <arcade/gui/label.h>
#include <iostream>

namespace pong {
    StateLobby::StateLobby(arcade::Game& game, const std::string& name)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100, 400)
        , m_playerList({128, 64}, 250)
        , m_isHost(true)
        , m_name(name)
        , m_hostIp(sf::IpAddress::LocalHost)

    {
        auto startButton = arcade::gui::makeButton();
        startButton->disable();
        startButton->setText("Start");
        startButton->setFunction([&]() {});

        if (!m_server.start(PORT)) {
            m_pGame->popState();
        };

        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() {
            m_server.stop();
            m_pGame->popState();
        });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_startGameButton = m_mainMenu.addWidget(std::move(startButton));
        m_mainMenu.setTitle("Choose Action");

        initPlayerList();
    }

    StateLobby::StateLobby(arcade::Game& game, const std::string& ip,
                           const std::string& name)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100, 400)
        , m_playerList({128, 64}, 250)
        , m_isHost(false)
        , m_name(name)
        , m_hostIp(ip)
    {
        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() {
            auto packet = makePacket(ToServerCommand::Disconnect);
            packet << m_playerId;
            m_socket.send(packet);
            m_pGame->popState();
            m_socket.disconnect();
        });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Waiting for host to start game...");

        initPlayerList();
    }

    void StateLobby::connectToServer()
    {
        if (m_socket.connect(sf::IpAddress::LocalHost, PORT) != sf::Socket::Done) {
            m_pGame->changeState<StateError>(*m_pGame, "Failed to connect to host.");
        }
        m_socket.setBlocking(false);
        m_isConnected = true;
    }

    void StateLobby::initPlayerList()
    {
        m_playerList.setTitle("Player List");
        for (auto& label : m_playerNameLabels) {
            auto ref = arcade::gui::makeLabel();
            label = (arcade::gui::Label*)m_playerList.addWidget(std::move(ref));
        }
    }

    void StateLobby::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateLobby::handlePacket(ToClientCommand command, sf::Packet& packet)
    {
        switch (command) {
            case ToClientCommand::Disconnect:
                m_pGame->changeState<StateError>(*m_pGame, "Host has disconnected.");
                m_socket.disconnect();
                break;

            case ToClientCommand::PlayerId: {
                packet >> m_playerId;
                auto namePacket = makePacket(ToServerCommand::Name);

                namePacket << m_playerId << m_name;
                m_socket.send(namePacket);
            } break;

            case ToClientCommand::PlayerConnected: {
                m_peerConnections++;
                checkHostStartButton();
                sf::Uint8 id;
                std::string name;
                packet >> id >> name;
                m_playerNameLabels[id]->setLabel(name);
            } break;

            case ToClientCommand::PlayerDisconnected: {
                m_peerConnections--;
                checkHostStartButton();
                sf::Uint8 id;
                packet >> id;
                m_playerNameLabels[id]->setLabel("");
            } break;

            case ToClientCommand::PlayerList: {
                sf::Uint8 count;
                packet >> count;
                m_peerConnections += count;
                for (int i = 0; i < (int)count; i++) {
                    sf::Uint8 id;
                    std::string name;
                    packet >> id >> name;
                    std::cout << "PLAYER LIST IDX AND NAME " << (int)id << " >" << name
                              << '\n';
                    m_playerNameLabels[id]->setLabel(name);
                }
                std::cout << "GOT PLAYER LIST " << (int)count << std::endl;
            } break;

            default:
                break;
        }
    } // namespace pong

    void StateLobby::update([[maybe_unused]] sf::Time deltaTime)
    {
        if (!m_isConnected) {
            connectToServer();
        }
        if (m_isHost) {
            m_server.update();
        }
        if (m_isConnected) {
            sf::Packet packet;
            if (m_socket.receive(packet) == sf::Socket::Done) {
                sf::Uint8 cmd = 0;
                packet >> cmd;
                auto command = static_cast<ToClientCommand>(cmd);
                handlePacket(command, packet);
            }
        }
    }

    void StateLobby::checkHostStartButton()
    {
        if (m_isHost) {
            if (m_peerConnections > 1) {
                m_startGameButton->enable();
            }
            else {
                m_startGameButton->disable();
            }
        }
    }

    void StateLobby::render(sf::RenderTarget& renderer)
    {
        m_playerList.render(renderer);
        m_mainMenu.render(renderer);
    }
} // namespace pong