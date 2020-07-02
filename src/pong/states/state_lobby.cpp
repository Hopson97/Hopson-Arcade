#include "state_lobby.h"

#include "../display_info.h"

#include <SFML/Network/Packet.hpp>

#include "../net.h"
#include "state_error.h"
#include <arcade/game.h>
#include <arcade/gui/button.h>

namespace pong {
    StateLobby::StateLobby(arcade::Game& game, const std::string& name)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100, 400)
        , m_playerList({128, 64}, 250)
        , m_isHost(true)
        , m_name(name)
    {

        auto startButton = arcade::gui::makeButton();
        startButton->disable();
        startButton->setText("Start");
        startButton->setFunction([&]() {});

        if (m_tcpListener.listen(PORT) != sf::Socket::Done) {
            m_pGame->popState();
        }
        m_tcpListener.setBlocking(false);

        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() {
            if (m_hasConnection) {
                auto packet = makePacket(ToClientCommand::Disconnect);
                m_socket.send(packet);
                m_socket.disconnect();
            }
            m_pGame->popState();
        });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_startGameButton = m_mainMenu.addWidget(std::move(startButton));
        m_mainMenu.setTitle("Choose Action");

        m_playerList.setTitle("Player List");
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
            m_socket.send(packet);
            m_pGame->popState();
            m_socket.disconnect();
        });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Waiting for host to start game...");

        m_playerList.setTitle("Player List");
    }

    void StateLobby::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateLobby::update([[maybe_unused]] sf::Time deltaTime)
    {
        if (m_isHost) {
            if (m_tcpListener.accept(m_socket) == sf::Socket::Done) {
                m_hasConnection = true;
                m_startGameButton->enable();
                auto packet = makePacket(ToClientCommand::Name);
                packet << m_name;
                m_socket.send(packet);
                m_socket.setBlocking(false);
            }
        }
        else if (!m_hasConnection) {
            if (m_socket.connect(m_hostIp, PORT) != sf::Socket::Done) {
                m_pGame->changeState<StateError>(*m_pGame, "Failed to connect to host.");
                return;
            }
            m_socket.setBlocking(false);
            m_hasConnection = true;

            auto packet = makePacket(ToServerCommand::Name);
            packet << m_name;
            m_socket.send(packet);
        }
        if (m_hasConnection) {
            sf::Packet packet;
            if (m_socket.receive(packet) == sf::Socket::Done) {
                if (m_isHost) {
                    hostHandlePacket(packet);
                }
                else {
                    clientHandlePacket(packet);
                }
            }
        }
    }

    void StateLobby::clientHandlePacket(sf::Packet& packet)
    {
        sf::Int8 cmd;
        packet >> cmd;
        auto command = static_cast<ToClientCommand>(cmd);
        switch (command) {
            case ToClientCommand::Name:
                packet << m_opponentName;
                break;

            case ToClientCommand::Disconnect:
                m_pGame->changeState<StateError>(*m_pGame, "Host has disconnected.");
                m_socket.disconnect();
                break;

            default:
                break;
        }
    }

    void StateLobby::hostHandlePacket(sf::Packet& packet)
    {
        sf::Int8 cmd;
        packet >> cmd;
        auto command = static_cast<ToServerCommand>(cmd);
        switch (command) {
            case ToServerCommand::Name:
                packet << m_opponentName;
                break;

            case ToServerCommand::Disconnect:
                m_hasConnection = false;
                m_socket.disconnect();
                m_startGameButton->disable();
                break;

            default:
                break;
        }
    }

    void StateLobby::render(sf::RenderTarget& renderer)
    {
        m_playerList.render(renderer);
        m_mainMenu.render(renderer);
    }
} // namespace pong