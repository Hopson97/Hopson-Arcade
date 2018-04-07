#include "StateHighscores.h"

#include "../Game.h"
#include "../DisplayInfo.h"
#include "../GUI/Button.h"
#include "../GUI/Textbox.h"

#include <fstream>
#include <sstream>
#include <iostream>

StateHighscores::StateHighscores(Game & game, int score)
    : StateHighscores(game)
{
    initSubmitMenu();
    m_scoreToSubmit = score;
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
    loadScores();
}

void StateHighscores::handleEvent(sf::Event e)
{
    m_pActiveMenu->handleEvent(e, m_pGame->getWindow());
}

void StateHighscores::update(sf::Time deltaTime)
{
}

void StateHighscores::render(sf::RenderTarget & renderer)
{
    m_pActiveMenu->render(renderer);
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
    auto nameBox = std::make_unique<gui::TextBox>(m_submitString);
    nameBox->setLabel("Enter name");

    auto submit = std::make_unique<gui::Button>();
    submit->setText("Submit Score");
    submit->setFunction([&]() {
        if (m_submitString.empty()) {

        }
        else {

        }
    });
    

    auto back = std::make_unique<gui::Button>();
    back->setText("View HighScores");
    back->setFunction([&]() {
        m_pGame->popState();
    });

    m_submitScoreMenu.addWidget(std::move(nameBox));
    m_submitScoreMenu.addWidget(std::move(submit));
    m_submitScoreMenu.addWidget(std::move(back));
}

void StateHighscores::loadScores()
{
    std::ifstream inFile("res/scores.txt");
    std::string line;
    int switcher = 0;
    std::string name;
    int score;
    while (std::getline(inFile, line, ',')) {
        if (switcher++ % 2 == 0) {
            name = line;
        }
        else {
            score = std::stoi(line);
            m_scores.emplace_back(std::make_pair(name, score));
        }
    }
    sortScores();
}

void StateHighscores::writeScores()
{
    std::ofstream outFile("res/scores.txt");

    for (auto& entry : m_scores) {
        outFile << entry.first << "," << entry.second;
    }
}

void StateHighscores::sortScores()
{
    std::sort(m_scores.begin(), m_scores.end(), [](Entry& a, Entry& b) {
        return a.second > b.second;
    });
}
