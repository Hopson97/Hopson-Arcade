#include "InvaderManager.h"

#include <iostream>

#include "../ResourceManager/ResourceHolder.h"

InvaderManager::InvaderManager()
    : m_stepGap (sf::seconds(0.5f))
{
    m_invaderSprite.setSize({ Invader::WIDTH, Invader::HEIGHT });
    m_invaderSprite.setTexture(&ResourceHolder::get().textures.get("invaders"));

    Invader::Type types[] = {
        Invader::Type::Squid,
        Invader::Type::Flat,
        Invader::Type::Flat,
        Invader::Type::Bug,
        Invader::Type::Bug,
    };
    //add invaders into the vector
    const int GAP = 10;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            //calcuate position for invader
            float invaderX = x * Invader::WIDTH + (GAP  * x * 2) + Invader::WIDTH;
            float invaderY = y * Invader::HEIGHT + (GAP * y) + Invader::HEIGHT * 3;
            m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
        }
    }
    m_aliveInvaders = m_invaders.size();
}

void InvaderManager::tryStepInvaders()
{
    //Only step if clock is over timer
    if (m_stepTimer.getElapsedTime() > m_stepGap) {
        m_currFrame++;
        //Calculate amount to step
        bool moveDown = false;
        float step = m_isMovingLeft ? -10.0f : 10.0f;
        if (m_moveDown) {
            step *= -1;
        }
        
        //Move the invaders
        for (auto& invader : m_invaders) {
            if (!invader.isAlive()) continue;
            invader.move(step, 0.0f);
            if (m_moveDown) {
                invader.move(0, Invader::HEIGHT / 2.0f);
            }
            else if (!moveDown) {
                //Check invader position to see if all should move down
                moveDown = shouldMoveDown(invader); 
            }
        }

        if (m_moveDown) m_isMovingLeft = !m_isMovingLeft;
        m_moveDown = moveDown;
        m_stepTimer.restart();
    }
}

void InvaderManager::drawInvaders(sf::RenderTarget& target)
{
    const int frameWidth = 12;
    const int frameHeight = 8;

    for (auto& invader : m_invaders) {
        if (!invader.isAlive()) continue;
        //Calculate texture coords
        int invaderType = static_cast<int>(invader.getType());
        int texLeft = (m_currFrame % 2) * frameWidth;
        int texTop = (invaderType * frameHeight);

        //Reposition and draw sprite
        m_invaderSprite.setPosition(invader.getPosition());
        m_invaderSprite.setTextureRect({ texLeft, texTop, frameWidth, frameHeight });
        target.draw(m_invaderSprite);
    }
}

std::vector<sf::Vector2f> InvaderManager::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
{
    std::vector<sf::Vector2f> collisionPoints;
    for (auto itr = projectiles.begin(); itr != projectiles.end();) {
        auto& projectile = *itr;
        bool hit = false;
        for (auto& invader : m_invaders) {
            if (!invader.isAlive()) continue;
            if (invader.getBox().intersects(projectile.getBox())) {
                invader.hit();
                m_aliveInvaders--;
                collisionPoints.emplace_back(projectile.getPosition());
                hit = true;
            }
        }
        //Remove projectile if the projectile has hit an invader
        if (hit) {
            itr = projectiles.erase(itr);
        }
        else {
            itr++;
        }
    }
    return collisionPoints;
}

bool InvaderManager::shouldMoveDown(const Invader& invader) const
{
    
    return
        (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
        (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
}

