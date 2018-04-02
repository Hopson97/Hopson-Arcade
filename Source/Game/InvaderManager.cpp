#include "InvaderManager.h"

#include <iostream>

InvaderManager::InvaderManager()
    : m_stepGap (sf::seconds(0.5f))
{
    //add invaders into the vector
    const int GAP = 10;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            //calcuate position for invader
            float invaderX = x * Invader::WIDTH + (GAP  * x * 2);
            float invaderY = y * Invader::HEIGHT + (GAP * y) + 100;
            m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY });
        }
    }
}

void InvaderManager::tryStepInvaders()
{
    //Only step if clock is over timer
    if (m_stepTimer.getElapsedTime() > m_stepGap) {
        //Calculate amount to step
        bool moveDown = false;
        float step = m_isMovingLeft ? -10 : 10;
        if (m_moveDown) {
            step *= -1;
        }
        
        //Move the invaders
        for (auto& invader : m_invaders) {
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
    for (auto& invader : m_invaders) {
        invader.draw(target);
    }
}

bool InvaderManager::shouldMoveDown(const Invader& invader) const
{
    
    return
        (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
        (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
}

