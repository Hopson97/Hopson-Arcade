#pragma once

#include "Entity/Projectile.h"
#include "Entity/Invader.h"
#include "AnimationRenderer.h"
#include "DisplayInfo.h"

#include <vector>
#include <SFML/Audio.hpp>

#include "../Framework/Util/Random.h"

namespace SpaceInvaders 
{
    class World;

    using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

    /**
        Class to manage the drawing and updating of invaders
    */
    class InvaderManager
    {
    public:
        InvaderManager(World& world);

        //Moves all of the invaders to the left or right, if the clock has reached a certain time
        void tryStepInvaders();

        //Draws all of the alive invaders
        void drawInvaders(sf::RenderTarget& target);

        //Tries to collide the invaders with the projectiles
        //Returns the points of collision
        CollisionResult tryCollideWithProjectiles(std::vector<Projectile>& projectiles);

        //This is for firing projectiles from the enemy
        sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

        int getAliveInvadersCount() const;

        /*
            These two functions are for the initilization of the invaders.
            It will add one invader at a time unil all have been added.
        */
        void initAddInvader();
        bool areInvadersAlive() const;

    private:
        //Changes time between the alien's steps based on number alive
        void updateStepDelay();

        //Checks the invaders position to see if all the aliens should move down
        //Or if the game is over
        bool testInvaderPosition(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        World& m_world;


        AnimationRenderer m_invaderRenderer;
        unsigned m_aliveInvaders;

        bool m_hasAllInvadersBeenAdded = false;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;

        int m_initX = 0;
        int m_initY = 4;
        int m_ticks = 0;

        sf::Sound m_stepSounds[4];
        sf::Sound m_invaderKilledSound;
    };
}