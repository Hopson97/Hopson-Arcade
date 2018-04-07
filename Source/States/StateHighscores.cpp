#include "StateHighscores.h"

#include "../Game.h"
#include "../DisplayInfo.h"
#include "../GUI/Button.h"
#include "../GUI/Textbox.h"

StateHighscores::StateHighscores(Game & game, int score)
    : StateHighscores(game)
{
    initSubmitMenu();
    m_pActiveMenu = &m_submitScoreMenu;
    m_state = State::Submitting;
}

StateHighscores::StateHighscores(Game & game)
    :   StateBase(game)
    , m_submitScoreMenu(game.getWindow(), 100.0f)
    , m_highscoreMenu(game.getWindow(), Display::HEIGHT - 100.0f)
    , m_state (State::Viewing)
{
    initViewMenu();
    m_pActiveMenu = &m_highscoreMenu;
}

void StateHighscores::handleEvent(sf::Event e)
{
}

void StateHighscores::update(sf::Time deltaTime)
{
}

void StateHighscores::render(sf::RenderTarget & renderer)
{
}

void StateHighscores::initViewMenu()
{
    auto back = std::make_unique<gui::Button>();
    back->setText("Main Menu");
    back->setFunction([&]() {
        m_pGame->popState();
    });
    m_highscoreMenu.addWidget(std::move(back));
}

void StateHighscores::initSubmitMenu()
{
    auto field = std::make_unique<gui::TextBox>(m_submitString);

    auto back = std::make_unique<gui::Button>();
    back->setText("View HighScores");
    back->setFunction([&]() {
        m_pGame->popState();
    });
    m_submitScoreMenu.addWidget(std::move(back));
}
