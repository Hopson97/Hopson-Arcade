#include "StateMainMenu.h"

#include "../../Arcade/Game.h"

#include "../../Framework/GUI/Button.h"
#include "StatePlaying.h"
#include "StateHighscores.h"

namespace SpaceInvaders
{
    StateMainMenu::StateMainMenu(Game & game)
        : StateBase(game, "Main Menu", Display::WIDTH, Display::HEIGHT)
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
    {
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&ResourceHolder::get().textures.get("si/logo"));


        auto playBtn = gui::makeButton();
        playBtn->setText("Play game");
        playBtn->setFunction([&]() {
            m_pGame->pushState<StatePlaying>(*m_pGame);
        });

        auto highscoresBtn = gui::makeButton();
        highscoresBtn->setText("Highscores");
        highscoresBtn->setFunction([&]() {
            m_pGame->pushState<StateHighscores>(*m_pGame);
        });

        auto exitBtn = gui::makeButton();
        exitBtn->setText("Exit game");
        exitBtn->setFunction([&]() {
            m_pGame->popState();
        });

        m_mainMenu.addWidget(std::move(playBtn));
        m_mainMenu.addWidget(std::move(highscoresBtn));
        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action", game.getWindow());

        
    }

    void StateMainMenu::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateMainMenu::update(sf::Time deltaTime)
    {
        m_background.update(deltaTime.asSeconds());
    }

    void StateMainMenu::render(sf::RenderTarget & renderer)
    {
        m_background.draw(renderer);
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
}