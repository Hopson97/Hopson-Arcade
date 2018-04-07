#include "StateMainMenu.h"

#include "../Game.h"

#include "../GUI/Button.h"
#include "StatePlaying.h"
#include "StateHighscores.h"

StateMainMenu::StateMainMenu(Game & game)
    :   StateBase   (game)
    ,   m_mainMenu  (game.getWindow(), Display::HEIGHT / 2 - 100)
{
    m_banner.setSize({ (float)Display::WIDTH, 200 });
    m_banner.setTexture(&ResourceHolder::get().textures.get("logo"));


    auto play = std::make_unique<gui::Button>();
    play->setText("Play game");
    play->setFunction([&]() {
        m_pGame->pushState<StatePlaying>(*m_pGame);
    });

    auto highscores = std::make_unique<gui::Button>();
    highscores->setText("Highscores");
    highscores->setFunction([&]() {
        m_pGame->pushState<StateHighscores>(*m_pGame);
    });

    auto ex = std::make_unique<gui::Button>();
    ex->setText("Exit game");
    ex->setFunction([&]() {
        m_pGame->exitGame();
    });

    m_mainMenu.addWidget(std::move(play));
    m_mainMenu.addWidget(std::move(highscores));
    m_mainMenu.addWidget(std::move(ex));
    m_mainMenu.setTitle("Choose Action");

    for (int i = 0; i < 250; i++) {
        sf::Vertex star;
        giveStarRandomStartLocation(star);
        star.position.y -= Display::HEIGHT;
        m_stars.push_back(star);
    }
}

void StateMainMenu::handleEvent(sf::Event e)
{
    m_mainMenu.handleEvent(e, m_pGame->getWindow());
}

void StateMainMenu::update(sf::Time deltaTime)
{
    for (auto& star : m_stars) {
        star.position.y -= 250 * deltaTime.asSeconds();
        if (star.position.y <= 0) {
            giveStarRandomStartLocation(star);
        }
    }
}

void StateMainMenu::render(sf::RenderTarget & renderer)
{
    renderer.draw(m_stars.data(), m_stars.size(), sf::Points);
    m_mainMenu.render(renderer);
    renderer.draw(m_banner);
}

void StateMainMenu::giveStarRandomStartLocation(sf::Vertex & star)
{
    star.position = { m_rng.getFloatInRange(0, (float)Display::WIDTH),
        m_rng.getFloatInRange((float)Display::HEIGHT, (float)Display::HEIGHT  * 2.0f)};
}
