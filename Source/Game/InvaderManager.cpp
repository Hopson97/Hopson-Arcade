#include "InvaderManager.h"

#include <iostream>

#include "../ResourceManager/ResourceHolder.h"

InvaderManager::InvaderManager()
    : m_stepGap(sf::seconds(0.5f))
    , m_invaderRenderer(12, 8, Invader::WIDTH, Invader::HEIGHT, 
        ResourceHolder::get().textures.get("invaders"))
{
    //Layout of the invaders 
    Invader::Type types[] = {
        Invader::Type::Squid, Invader::Type::Bug, Invader::Type::Bug,
        Invader::Type::Flat, Invader::Type::Flat
    };
    //Add invaders into the std::vector
    const int GAP = 10;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            //calcuate position for invader
            float invaderX = x * Invader::WIDTH + (GAP  * x * 3) + Invader::WIDTH;
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
        m_invaderRenderer.nextFrame();
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
        m_invaderRenderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
    }
}

CollisionResult InvaderManager::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
{
    CollisionResult result;
    std::vector<sf::Vector2f> collisionPoints;
    for (auto& projectile : projectiles) {
        for (auto& invader : m_invaders) {
            if (!invader.isAlive() || !projectile.isActive()) 
                continue;
            if (projectile.tryCollideWith(invader)) {
                m_aliveInvaders--;
                result.second.emplace_back(invader.getPosition());
                result.first += ((int)invader.getType() + 1) * 100;
            }
        }
    }
    return result;
}

sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
{
    //Keep looping until an invader is found
    while (true) {
        auto invaderColumn = random.getIntInRange(0, 10);
        for (int y = 4; y >= 0; y--) {
            int index = y * 11 + invaderColumn;
            auto& invader = m_invaders.at(index);
            if (invader.isAlive()) {
                return {
                    //transform to below the invader's center
                    invader.getPosition().x + Invader::WIDTH / 2,
                    invader.getPosition().y + Invader::HEIGHT + 5
                };
            }
        }
    }
}

bool InvaderManager::shouldMoveDown(const Invader& invader) const
{
    return
        (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
        (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
}

