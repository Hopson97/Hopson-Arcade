#pragma once

#include "Invader.h"
#include "../DisplayInfo.h"

#include <vector>

class InvaderManager
{
    public:
        InvaderManager();

        //Moves all of the invaders to the left or right
        void tryStepInvaders();

        //Draws all of the alive invaders
        void drawInvaders(sf::RenderTarget& target);

    private:
        //Checks the invaders position to see if all the aliens should move down
        bool shouldMoveDown(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;
};