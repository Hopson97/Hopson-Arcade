#include "state_lobby.h"

#include "../display_info.h"

#include <arcade/game.h>
#include <arcade/gui/button.h>

namespace pong {
    StateLobby::StateLobby(arcade::Game& game, bool isHost)
        : arcade::StateBase(game, "State Lobby")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
        , m_isHost(isHost)
    {
        if (isHost) {
            auto startButton = arcade::gui::makeButton();
            startButton->disable();
            startButton->setText("Start");
            startButton->setFunction([&]() {});
            m_mainMenu.addWidget(std::move(startButton));

            if (m_tcpListener.listen(52345) != sf::Socket::Done) {
                m_pGame->popState();
            }
            m_tcpListener.setBlocking(false);
        }

        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Back");
        exitBtn->setFunction([&]() { m_pGame->popState(); });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action", game.getWindow());
    }

    void StateLobby::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateLobby::update(sf::Time deltaTime)
    {
        if (m_isHost) {
            if (m_tcpListener.accept(m_otherPlayer) == sf::Socket::Done) {
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