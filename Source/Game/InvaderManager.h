#pragma once

#include "Entity/Projectile.h"
#include "Entity/Invader.h"
#include "AnimationRenderer.h"
#include "../DisplayInfo.h"

#include <vector>

#include "../Util/Random.h"

using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

/**
    Class to manage the drawing and updating of invaders
*/
class InvaderManager
{
    public:
        InvaderManager();

        //Moves all of the invaders to the left or right, if the clock has reached a certain time
        void tryStepInvaders();

        //Draws all of the alive invaders
        void drawInvaders(sf::RenderTarget& target);

        //Tries to collide the invaders with the projectiles
        //Returns the points of collision
        CollisionResult tryCollideWithProjectiles(std::vector<Projectile>& projectiles);

        //This is for firing projectiles from the enemy
        sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

    private:
        //Checks the invaders position to see if all the aliens should move down
        bool shouldMoveDown(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;


        AnimationRenderer m_invaderRenderer;
        unsigned m_aliveInvaders;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;
};