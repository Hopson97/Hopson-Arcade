#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Util/Random.h"
#include "InvaderManager.h"

class ExplosionParticleSystem
{
    public:
        ExplosionParticleSystem();

        void update(float dt);

        void addParticles(const CollisionInfo& info);

        void draw(sf::RenderTarget& target);

    private:
        Random<> m_rng;

        std::vector<sf::Vector2f> m_particleVelocities;
        std::vector<sf::Vertex> m_particles;
};