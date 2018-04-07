#include "StatePlaying.h"


#include <iostream>
#include "../Game.h"
#include "../ResourceManager/ResourceHolder.h"

#include "../GUI/Button.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase       (game)
,   m_gameOverText  (30)
,   m_gameOverMenu  (game.getWindow(), Display::HEIGHT / 3)
{
    auto mmButton = std::make_unique<gui::Button>();
    mmButton->setText("Main Menu\n");
    mmButton->setFunction([&]() {
        m_pGame->popState();
    });

    auto exitButton = std::make_unique<gui::Button>();
    exitButton->setText("Exit game\n");
    exitButton->setFunction([&]() {
        
    });

    m_gameOverMenu.setTitle("GAME  OVER");
    m_gameOverMenu.addWidget(std::move(mmButton));
    m_gameOverMenu.addWidget(std::move(exitButton));
}

void StatePlaying::handleEvent(sf::Event e)
{
    m_gameOverMenu.handleEvent(e, m_pGame->getWindow());
}

void StatePlaying::handleInput()
{
    m_world.input();
}

void StatePlaying::update(sf::Time deltaTime)
{
    if (!m_isGameover) {
        m_score += m_world.update(deltaTime.asSeconds());
        m_scoreDisplay.update(m_score);
    }

    m_isGameover = m_world.isGameOver();
}


void StatePlaying::render(sf::RenderTarget& renderer)
{
    m_world.draw(renderer);

    m_lifeDisplay.draw(renderer, m_world.getPlayer().getLives());
    m_scoreDisplay.draw(renderer);

    //if (m_isGameover) {
        m_gameOverMenu.render(renderer);
        renderer.draw(m_gameOverText.text);
    //}
}

///////////////////////////////////////////////
//     display member functions       ///
StatePlaying::DisplayText::DisplayText(int size)
{
    text.setFillColor(sf::Color::White);
    text.setOutlineColor({100, 150, 100});
    //text.setOutlineThickness(1);
    text.setFont(ResourceHolder::get().fonts.get("arcade"));
    text.setCharacterSize(size);
}



StatePlaying::LifeDisplay::LifeDisplay()
{
    m_lifeStamp.setSize({Player::WIDTH / 2, Player::WIDTH / 2});
    m_lifeStamp.setTexture(&ResourceHolder::get().textures.get("player"));
    m_lifeStamp.setTextureRect({ 0, 0, 11, 8 });
    m_label.text.setPosition(Display::WIDTH - (Player::WIDTH * 4.5), 10);
    m_label.text.setString("LIVES");
    m_label.text.setOutlineThickness(0);
}

void StatePlaying::LifeDisplay::draw(sf::RenderTarget& window, int lives)
{
    float xOrigin = m_label.text.getPosition().x + 
        m_label.text.getGlobalBounds().width + 10;
    float yOrigin = m_label.text.getPosition().y +
        m_label.text.getGlobalBounds().height / 2;

    window.draw(m_label.text);
    for (int i = 0; i < lives; i++) {
        m_lifeStamp.setPosition(xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin);
        window.draw(m_lifeStamp);
    }
}

StatePlaying::ScoreDisplay::ScoreDisplay()
{
    m_label.text.setPosition(10, 10);
    m_label.text.setString("SCORE   0");
    m_label.text.setOutlineThickness(0);
}

void StatePlaying::ScoreDisplay::update(int newScore)
{
    m_label.text.setString("SCORE   " + std::to_string(newScore));
}

void StatePlaying::ScoreDisplay::draw(sf::RenderTarget & target)
{
    target.draw(m_label.text);
}
