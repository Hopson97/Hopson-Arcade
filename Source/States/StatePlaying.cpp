#include "StatePlaying.h"


#include <iostream>
#include "../Game.h"
#include "../ResourceManager/ResourceHolder.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
, m_projectileRenderer  (4, 8, Projectile::WIDTH, Projectile::HEIGHT,
    ResourceHolder::get().textures.get("projectile"))
{
}

void StatePlaying::handleInput()
{
    if (m_player.isAlive()) {
        m_player.input();

        //Fire projectiles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            m_shootDelayTimer.getElapsedTime().asSeconds() > 0.5f) {
            auto point = m_player.getGunPosition();
            point.y -= Projectile::HEIGHT;
            point.x -= Projectile::WIDTH / 2.0f;
            m_projectiles.emplace_back(point, Projectile::Type::Rectangle, Projectile::Direction::Up);
            m_shootDelayTimer.restart();
        }
    }
    else {
        if (m_player.canBeRevived()) {
            if (!m_player.restart()) {
                //go to gameover state
            }
        }
    }
}

void StatePlaying::update(sf::Time deltaTime)
{
    m_player.update(deltaTime.asSeconds());
    if (m_player.isAlive()) {
        //Get points of collisions and increase score if one is hit
        auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
        auto& collisions = result.second;
        m_score += result.first;

        if (result.first >= 0) {
            m_score += result.first;
            m_scoreDisplay.update(m_score);
        }

        //update the projectiles
        for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
            auto& projectile = *itr;
            if (!projectile.isActive()) {
                itr = m_projectiles.erase(itr);
            }
            else {
                //Test for player getting hit 
                if (projectile.tryCollideWith(m_player)) {
                    collisions.emplace_back(m_player.getGunPosition());
                    m_projectiles.clear();
                    return;
                }
                projectile.update(deltaTime.asSeconds());
                itr++;
            }
        }

        for (auto& location : collisions) {
           
        }
    }
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{
    if (m_player.isAlive()) {
        m_invaders.tryStepInvaders();

        //Try and shoot a projectile from an enemy positions
        if (m_invaderShotDelayTimer.getElapsedTime().asSeconds() >= 0.5 &&
            m_rng.getIntInRange(0, 25) == 2) {
            auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
            auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
            m_projectiles.emplace_back(point, type, Projectile::Direction::Down);
            m_invaderShotDelayTimer.restart();
        }
    }
}
void StatePlaying::render(sf::RenderTarget& renderer)
{
    m_invaders.drawInvaders(renderer);
    m_player.draw(renderer);

    if (m_projectileAnimTimer.getElapsedTime().asSeconds() >= 0.1) {
        m_projectileRenderer.nextFrame();
        m_projectileAnimTimer.restart();
    }
    
    for (auto& proj : m_projectiles) {
        m_projectileRenderer.renderEntity(renderer, (int)proj.getType(), proj.getPosition());
    }

    m_lifeDisplay.draw(renderer, m_player.getLives());
    m_scoreDisplay.draw(renderer);
}

///////////////////////////////////////////////
//     display member functions       ///
StatePlaying::DisplayText::DisplayText()
{
    text.setFillColor(sf::Color::White);
    text.setOutlineColor({100, 150, 100});
    text.setOutlineThickness(1);
    text.setFont(ResourceHolder::get().fonts.get("arcade"));
    text.setCharacterSize(20);
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
