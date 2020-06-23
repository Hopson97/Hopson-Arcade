#include "state_main_menu.h"

#include "../display_info.h"
#include "state_lobby.h"

#include <arcade/game.h>
#include <arcade/gui/button.h>
#include <arcade/gui/textbox.h>

namespace pong {
    StateMainMenu::StateMainMenu(arcade::Game &game)
        : arcade::StateBase(game, "Main Menu", Display::WIDTH, Display::HEIGHT)
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
        , m_joinMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
        , mp_activeMenu(&m_mainMenu)
    {
        m_banner.setSize({(float)Display::WIDTH, 200});
        m_banner.setTexture(
            &arcade::ResourceHolder::get().textures.get("pong/logo"));

        {
            auto vsComputer = arcade::gui::makeButton();
            vsComputer->setText("Play Vs Computer");
            // vsComputer->setFunction(
            //    [&]() { m_pGame->pushState<StateLobby>(*m_pGame); });

            auto playBtn = arcade::gui::makeButton();
            playBtn->setText("Create Lobby");
            playBtn->setFunction(
                [&]() { m_pGame->pushState<StateLobby>(*m_pGame, true); });

            auto joinBtn = arcade::gui::makeButton();
            joinBtn->setText("Join Lobby");
            joinBtn->setFunction([&]() { mp_activeMenu = &m_joinMenu; });

            auto exitBtn = arcade::gui::makeButton();
            exitBtn->setText("Exit game");
            exitBtn->setFunction([&]() { m_pGame->popState(); });

            m_mainMenu.addWidget(std::move(vsComputer));
            m_mainMenu.addWidget(std::move(playBtn));
            m_mainMenu.addWidget(std::move(joinBtn));
            m_mainMenu.addWidget(std::move(exitBtn));
            m_mainMenu.setTitle("Choose Action", game.getWindow());
        }
        {
            auto ipBox = arcade::gui::makeTextBox(m_joinIp);
            ipBox->setLabel("Enter host IP Address");

            auto joinBtn = arcade::gui::makeButton();
            joinBtn->setText("Join Lobby");
            joinBtn->setFunction(
                [&]() { m_pGame->pushState<StateLobby>(*m_pGame, false); });

            auto backBtn = arcade::gui::makeButton();
            backBtn->setText("Back");
            backBtn->setFunction([&]() { mp_activeMenu = &m_mainMenu; });

            m_joinMenu.setTitle("", game.getWindow());
            m_joinMenu.addWidget(std::move(ipBox));
            m_joinMenu.addWidget(std::move(joinBtn));
            m_joinMenu.addWidget(std::move(backBtn));
        }
    }

    void StateMainMenu::handleEvent(sf::Event e)
    {
        mp_activeMenu->handleEvent(e, m_pGame->getWindow());
    }

    void StateMainMenu::update(sf::Time deltaTime) { (void)deltaTime; }

    void StateMainMenu::render(sf::RenderTarget &renderer)
    {

        mp_activeMenu->render(renderer);
        renderer.draw(m_banner);
    }
} // namespace pong