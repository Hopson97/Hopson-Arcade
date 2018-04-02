#pragma once

#include "Invader.h"
#include "../DisplayInfo.h"

#include <vector>

class InvaderManager
{
    public:
        InvaderManager();

        void tryStepInvaders();
        void drawInvaders(sf::RenderTarget& target);

    private:
        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        bool m_isMovingLeft = false;

        float m_invadersMinX = Invader::SIZE * 2;
        float m_invadersMaxX = WIDTH - m_invadersCurrMinX;

        float m_invadersCurrMinX = m_invadersMinX;
        float m_invadersCurrMaxX;
};