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
    m_banner.setSize({ (float)Display::WIDTH, 200 });
    m_banner.setTexture(&ResourceHolder::get().textures.get("highscores"));
    createHighscoreView();
}

void StateHighscores::handleEvent(sf::Event e)
{
    m_pActiveMenu->handleEvent(e, m_pGame->getWindow());
}

void StateHighscores::update(sf::Time deltaTime) {}

void StateHighscores::render(sf::RenderTarget & renderer)
{
    m_pActiveMenu->render(renderer);
    if (m_state == State::Viewing) {
        for (auto& entry : m_entryBoxes) {
            entry.draw(renderer);
        }
        renderer.draw(m_banner);
    }
}

int StateHighscores::getHighestScore()
{
    std::ifstream inFile("res/scores.txt");
    std::string buffer;

    std::getline(inFile, buffer, ',');
    std::getline(inFile, buffer, ',');
    if (buffer.empty()) return 0;
    else return std::stoi(buffer);
}

void StateHighscores::initViewMenu()
{
    loadScores();

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
    nameBox->setLabel("Click text box to enter name");

    auto submit = std::make_unique<gui::Button>();
    submit->setText("Submit Score");
    submit->setFunction([&]() {
        if (!m_submitString.empty()) {
            submitScore();
            switchToViewMenu();
        }
    });
    

    auto back = std::make_unique<gui::Button>();
    back->setText("View HighScores");
    back->setFunction([&]() {
        loadScores();
        switchToViewMenu();
    });

    m_submitScoreMenu.addWidget(std::move(nameBox));
    m_submitScoreMenu.addWidget(std::move(submit));
    m_submitScoreMenu.addWidget(std::move(back));
}

void StateHighscores::switchToViewMenu()
{
    m_state = State::Viewing;
    m_pActiveMenu = &m_highscoreMenu;
    createHighscoreView();
}

void StateHighscores::createHighscoreView()
{
    loadScores();
    sortScores();
    m_entryBoxes.clear();
    for (unsigned i = 0; i < m_scores.size(); i++) {
        auto& name = m_scores[i].first;
        auto score = m_scores[i].second;

        m_entryBoxes.emplace_back(i + 1, name, score);
        if (i >= 9) return; //Only show top 10 scores
    }
}

void StateHighscores::loadScores()
{
    m_scores.clear();
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
    sortScores();
    std::ofstream outFile("res/scores.txt");
    for (auto& entry : m_scores) {
        outFile << entry.first << "," << entry.second << ",";
    }
}

void StateHighscores::sortScores()
{
    std::sort(m_scores.begin(), m_scores.end(), [](Entry& a, Entry& b) {
        return a.second > b.second;
    });
}

void StateHighscores::submitScore()
{
    loadScores();
    m_scores.emplace_back(std::make_pair(m_submitString, m_scoreToSubmit));
    writeScores();
}

StateHighscores::EntryBox::EntryBox(int position, const std::string & name, int score)
{
    float size = 35;
    float y = 200 + position * (size - 2);
    m_background.setSize({ Display::WIDTH / 1.5f, size });
    m_background.setPosition({ Display::WIDTH / 2 - m_background.getGlobalBounds().width / 2, y });

    m_nameText.setCharacterSize((unsigned)size - 5);
    m_scoreText.setCharacterSize((unsigned)size - 5);

    m_nameText.setString (std::to_string(position) + "     " + name);
    m_scoreText.setString(std::to_string(score));

    m_nameText.setPosition(m_background.getPosition());
    m_scoreText.setPosition(m_background.getPosition().x + 
                            m_background.getGlobalBounds().width - 
                            m_scoreText.getGlobalBounds().width - 10, 
                            y);

    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color::Green);
    m_background.setFillColor(
        position % 2 == 0 ?
            sf::Color::Black :
            sf::Color{50, 40, 50}
    );
}

void StateHighscores::EntryBox::draw(sf::RenderTarget & renderer)
{
    renderer.draw(m_background);
    renderer.draw(m_nameText);
    renderer.draw(m_scoreText);
}
