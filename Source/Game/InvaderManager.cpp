#include "InvaderManager.h"

InvaderManager::InvaderManager()
    : m_stepGap (sf::seconds(0.4f))
{
    const int GAP = 20;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 11; x++) {
            float invaderX = x * Invader::SIZE + (GAP * x * 2) + Invader::SIZE * 2;
            float invaderY = y * Invader::SIZE + (GAP * y)     + Invader::SIZE * 2;
            m_invadersCurrMaxX = std::max(m_invadersCurrMaxX, invaderX + Invader::SIZE);
            m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY });
        }
    }
}

void InvaderManager::tryStepInvaders()
{
    const auto step = m_isMovingLeft ? -15 : 15;
    if (m_stepTimer.getElapsedTime() > m_stepGap) {
        m_invadersCurrMinX += step;
        m_invadersCurrMaxX += step;
        for (auto& invader : m_invaders) {
            if (m_invadersCurrMinX <= m_invadersMinX) {
                invader.move(0, Invader::SIZE);
                m_isMovingLeft = false;
                continue;
            }
            else if (m_invadersCurrMaxX >= m_invadersMaxX) {
                invader.move(0, Invader::SIZE);
                m_isMovingLeft = true;
                continue;
            }
            invader.move(step, 0.0f);
        }
        m_stepTimer.restart();
    }
}

void InvaderManager::drawInvaders(sf::RenderTarget& target)
{
    for (auto& invader : m_invaders) {
        invader.draw(target);
    }
}
