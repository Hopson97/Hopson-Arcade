#include "state_lobby.h"

#include "../display_info.h"

#include <arcade/game.h>
#include <arcade/gui/button.h>

namespace pong {
    StateLobby::StateLobby(arcade::Game &game)
        : arcade::StateBase(game, "Main Menu", Display::WIDTH, Display::HEIGHT)
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
    {
        m_banner.setSize({(float)Display::WIDTH, 200});
        m_banner.setTexture(
            &arcade::ResourceHolder::get().textures.get("pg/logo"));

        auto exitBtn = arcade::gui::makeButton();
        exitBtn->setText("Exit game");
        exitBtn->setFunction([&]() { m_pGame->popState(); });

        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action", game.getWindow());
    }

    void StateLobby::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateLobby::update(sf::Time deltaTime) {}

    void StateLobby::render(sf::RenderTarget &renderer)
    {
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
} // namespace pong