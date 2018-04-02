#include "InvaderManager.h"

#include <iostream>

InvaderManager::InvaderManager()
    : m_stepGap (sf::seconds(0.4f))
{
    //add invaders into the vector
    const int GAP = 10;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            //calcuate position for invader
            float invaderX = x * Invader::WIDTH + (GAP  * x * 2)  + m_invadersMinX * 2;
            float invaderY = y * Invader::HEIGHT + (GAP * y)      + Invader::HEIGHT * 2;
            m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY });
        }
    }
    recalculateInvaderEdges();
}

void InvaderManager::tryStepInvaders()
{
    if (m_stepTimer.getElapsedTime() > m_stepGap) {
        float step = m_isMovingLeft ? -10 : 10;

        for (auto& invader : m_invaders) {
            if (m_invadersCurrMinX <= m_invadersMinX) {
                invader.move(0, Invader::WIDTH);
                m_isMovingLeft = false;
                step *= -1;
                continue;
            }
            else if (m_invadersCurrMaxX >= m_invadersMaxX) {
                invader.move(0, Invader::WIDTH);
                m_isMovingLeft = true;
                step *= -1;
                continue;
            }
            invader.move(step, 0.0f);
        }
        m_stepTimer.restart();
    }
}

void InvaderManager::drawInvaders(sf::RenderTarget& target)
{
    sf::RectangleShape box;
    box.setSize({ m_invadersMaxX - m_invadersMinX , 1000 });
    box.setPosition(m_invadersMinX, 70);
    box.setFillColor({ 0, 0, 0, 0 });
    box.setOutlineThickness(2);
    target.draw(box);
    
    sf::RectangleShape box2;
    box2.setSize({ m_invadersCurrMaxX - m_invadersCurrMinX , 500 });
    box2.setPosition(m_invadersCurrMinX, 70);
    box2.setFillColor({ 0, 50, 0, 50 });
    
    box2.setOutlineThickness(2);
    box2.setOutlineColor({ 100, 0, 50, 255 });
    target.draw(box2);
    

    for (auto& invader : m_invaders) {
        invader.draw(target);
    }
}

//hacky tempory solution to find the bounds of the invaders
void InvaderManager::recalculateInvaderEdges()
{
    //Try find left-most invader
    bool found = false;
    for (int x = 0; x < 11 && !found; x++) {
        for (int y = 0; y < 5; y++) {
            auto& invader = m_invaders[y * 11 + x];
            if (invader.isAlive()) {
                m_invadersCurrMinX = invader.getPosition().x;
                found = true;
                break;
            }
        }
    }

    //Try find right-most invader
    for (int x = 11; x >= 0 && !found; x--) {
        for (int y = 0; y < 5; y++) {
            auto& invader = m_invaders[y * 11 + x];
            if (invader.isAlive()) {
                m_invadersCurrMaxX = invader.getPosition().x + Invader::WIDTH;
                found = true;
                break;
            }
        }
    }
    
}
