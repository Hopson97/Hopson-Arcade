#pragma once

#include <SFML/Graphics.hpp>

#include "AnimationRenderer.h"
#include "InvaderManager.h"
#include "Entity/Player.h"
#include "Entity/Projectile.h"
#include "Entity/Explosion.h"
#include "Entity/Shield.h"
#include "Entity/UFO.h"

namespace SpaceInvaders
{
    /**
        The class which manages the world and th interactions between different entites
    */
    class World
    {
    public:
        World();

        void input();
        int update(float dt);
        void draw(sf::RenderTarget& target);

        const Player& getPlayer() const;

        bool isGameOver() const;

        void setGameIsOver() { m_isGameOver = true; }

    private:
        void playerProjectileInput();
        void enemyProjectileFire();
        CollisionResult getCollisionResult(float dtt);
        void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);

        AnimationRenderer m_projectileRenderer;
        InvaderManager m_invaders;
        Player m_player;
        UFO m_ufo;

        std::vector<Projectile> m_projectiles;
        std::vector<Explosion> m_explosions;
        std::vector<Shield> m_shields;

        sf::RectangleShape m_explodeShape;
        sf::Clock m_invaderShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animTimer;

        sf::Sound m_playerShoot;

        Random<> m_rng;

        bool m_isGameOver = false;
    };
}