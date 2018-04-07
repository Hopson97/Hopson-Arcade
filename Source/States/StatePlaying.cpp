#include "StatePlaying.h"


#include <iostream>
#include "../Game.h"
#include "../ResourceManager/ResourceHolder.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase       (game)
,   m_gameOverText  (30)
{
    m_gameOverText.text.setString("GAME OVER");
    m_gameOverText.text.setPosition(
        Display::WIDTH / 2 - m_gameOverText.text.getGlobalBounds().width / 2,
        Display::HEIGHT / 2
    );
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
    else if (m_gameOverClock.getElapsedTime().asSeconds() >= 3)
    {
        
    }

    if (m_world.getPlayer().getLives() == -1) {
        m_isGameover = true;

    }
}


void StatePlaying::render(sf::RenderTarget& renderer)
{
    m_world.draw(renderer);

    m_lifeDisplay.draw(renderer, m_world.getPlayer().getLives());
    m_scoreDisplay.draw(renderer);

    if (m_isGameover) {
        renderer.draw(m_gameOverText.text);
    }
}

///////////////////////////////////////////////
//     display member functions       ///
StatePlaying::DisplayText::DisplayText(int size)
{
    text.setFillColor(sf::Color::White);
    text.setOutlineColor({100, 150, 100});
    text.setOutlineThickness(1);
    text.setFont(ResourceHolder::get().fonts.get("arcade"));
    text.setCharacterSize(size);
}



StatePlaying::LifeDisplay::LifeDisplay()
{
    m_lifeStamp.setSize({Player::WIDTH / 2, Player::WIDTH / 2});
    m_lifeStamp.setTexture(&ResourceHolder::get().textures.get("player"));
    m_lifeStamp.setTextureRect({ 0, 0, 11, 8 });
    m_label.text.setPosition(Display::WIDTH - (Player::WIDTH * 4), 10);
    m_label.text.setString("LIVES");
}

void StatePlaying::LifeDisplay::draw(sf::RenderTarget& window, int lives)
{
    float xOrigin = m_label.text.getPosition().x + 
        m_label.text.getGlobalBounds().width + 10;
    float yOrigin = 10;

    window.draw(m_label.text);
    for (int i = 0; i < lives; i++) {
        m_lifeStamp.setPosition(xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin);
        window.draw(m_lifeStamp);
    }
}

StatePlaying::ScoreDisplay::ScoreDisplay()
{
    m_label.text.setPosition(10, 10);
    m_label.text.setString("SCORE\n0");
}

void StatePlaying::ScoreDisplay::update(int newScore)
{
    m_label.text.setString("SCORE\n" + std::to_string(newScore));
}

void StatePlaying::ScoreDisplay::draw(sf::RenderTarget & target)
{
    target.draw(m_label.text);
}
