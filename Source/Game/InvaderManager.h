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
        void recalculateInvaderEdges();

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        bool m_isMovingLeft = false;

        float m_invadersMinX = 10;
        float m_invadersMaxX = Display::WIDTH - m_invadersMinX;
        
        float m_invadersCurrMinX = 0;
        float m_invadersCurrMaxX = Display::WIDTH;
};