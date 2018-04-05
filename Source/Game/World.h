#pragma once

#include <SFML/Graphics.hpp>

#include "AnimationRenderer.h"
#include "InvaderManager.h"
#include "Entity/Player.h"
#include "Entity/Projectile.h"
#include "Entity/Explosion.h"


class World
{
    public:
        World();

        void input();
        int update(float dt);
        void draw(sf::RenderTarget& target);

        const Player& getPlayer() const;

    private:
        void playerProjectileInput();
        void enemyProjectileFire();
        CollisionResult getCollisionResult(float dtt);
        void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);

        AnimationRenderer m_projectileRenderer;
        InvaderManager m_invaders;
        Player m_player;

        std::vector<Projectile> m_projectiles;
        std::vector<Explosion> m_explosions;

        sf::RectangleShape m_explodeShape;
        sf::Clock m_invaderShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animTimer;

        Random<> m_rng;
};