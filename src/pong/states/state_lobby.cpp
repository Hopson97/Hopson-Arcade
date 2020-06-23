#include "state_lobby.h"

#include "../display_info.h"

#include <arcade/game.h>
#include <arcade/gui/button.h>


const uint16_t PORT = 52345;

namespace pong {
    StateLobby::StateLobby(arcade::Game& game)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
        , m_isHost(true)
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
        m_mainMenu.setTitle("Choose Action", game.getWindow());
    }

    StateLobby::StateLobby(arcade::Game& game, const std::string& ip)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
        , m_isHost(false)
    {
        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() { m_pGame->popState(); });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Waiting for host to start game...", game.getWindow());

        if(m_socket.connect(ip, PORT) != sf::Socket::Done) {
            m_pGame->popState();
        }
        m_socket.setBlocking(false);
    }

    void StateLobby::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateLobby::update([[maybe_unused]]sf::Time deltaTime)
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
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
} // namespace pong