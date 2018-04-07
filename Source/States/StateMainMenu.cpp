#include "StateMainMenu.h"

#include "../Game.h"

#include "../GUI/Button.h"
#include "StatePlaying.h"

StateMainMenu::StateMainMenu(Game & game)
    :   StateBase   (game)
    ,   m_mainMenu  (game.getWindow(), 200)
{
    m_banner.setSize({ (float)Display::WIDTH, 200 });
    m_banner.setTexture(&ResourceHolder::get().textures.get("logo"));


    auto play = std::make_unique<gui::Button>();
    play->setText("Play game");
    play->setFunction([&]() {
        m_pGame->pushState<StatePlaying>(game);
    });

    auto ex = std::make_unique<gui::Button>();
    ex->setText("Exit game");
    ex->setFunction([&]() {
        m_pGame->exitGame();
    });

    m_mainMenu.addWidget(std::move(play));
    m_mainMenu.addWidget(std::move(ex));
    m_mainMenu.setTitle("Choose Action");
}

void StateMainMenu::handleEvent(sf::Event e)
{
    m_mainMenu.handleEvent(e, m_pGame->getWindow());
}

void StateMainMenu::update(sf::Time deltaTime)
{
}

void StateMainMenu::render(sf::RenderTarget & renderer)
{
    m_mainMenu.render(renderer);
    renderer.draw(m_banner);
}
