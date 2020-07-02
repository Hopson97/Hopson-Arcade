#include "state_error.h"

#include "../display_info.h"

#include <SFML/Network/Packet.hpp>

#include "../net.h"
#include <arcade/game.h>
#include <arcade/gui/button.h>

namespace pong {
    StateError::StateError(arcade::Game& game, const std::string& message)
        : arcade::StateBase(game, "State Error")
        , m_messageMenu(game.getWindow(), Display::HEIGHT / 2 - 100, 400)
    {

        auto exit = arcade::gui::makeButton();
        exit->setText("Exit");
        exit->setFunction([&]() { game.popState(); });

        m_messageMenu.addWidget(std::move(exit));
        m_messageMenu.setTitle(message);
    }

    void StateError::handleEvent(sf::Event e)
    {
        m_messageMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateError::update([[maybe_unused]] sf::Time deltaTime)
    {
    }

    void StateError::render(sf::RenderTarget& renderer)
    {
        m_messageMenu.render(renderer);
    }
} // namespace pong