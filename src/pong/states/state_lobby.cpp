#include "state_lobby.h"

#include "../display_info.h"

#include <SFML/Network/Packet.hpp>

#include <arcade/game.h>
#include <arcade/gui/button.h>

const uint16_t PORT = 52345;

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
        exitBtn->setFunction([&]() { m_pGame->popState(); });

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
    {
        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() { m_pGame->popState(); });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Waiting for host to start game...");

        if (m_socket.connect(ip, PORT) != sf::Socket::Done) {
            m_pGame->popState();
        }
        m_socket.setBlocking(false);

        sf::Packet packet;
        packet << m_name;
        m_socket.send(packet);

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
                m_startGameButton->enable();
            }
        }
        else {
        }
    }
    void StateLobby::render(sf::RenderTarget& renderer)
    {
        m_playerList.render(renderer);
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
} // namespace pong