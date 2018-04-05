#include "ExplosionParticleSystem.h"

#include "../DisplayInfo.h"

ExplosionParticleSystem::ExplosionParticleSystem()
{
    m_particleVelocities.reserve(1024);
    m_particles.reserve(1024);
}

void ExplosionParticleSystem::update(float dt)
{
    std::vector<unsigned> particlesToRemove;
    for (int i = 0; i < m_particles.size(); i++) {
        auto& vel       = m_particleVelocities[i];
        auto& particle  = m_particles[i];

        vel.y += 1000 * dt;
        particle.position += vel * dt;

        if (particle.position.y > Display::HEIGHT) {
            particlesToRemove.push_back(i);
        }
    }

    //remove off-screen particles
    for (auto remove : particlesToRemove) {
        m_particleVelocities.erase(m_particleVelocities.begin() + remove);
        m_particles         .erase(m_particles.begin() + remove);

        //DISGUSTING HACK REEEEEE
        for (auto& remove : particlesToRemove) {
            remove--;
        }
    }
}

void ExplosionParticleSystem::addParticles(const CollisionInfo)
{
    for (int i = 0; i < amount; i++) {
        sf::Vertex particle;
        sf::Vector2f velocity{
            m_rng.getFloatInRange(-100, 100),
            m_rng.getFloatInRange(-500, 0)
        };
        particle.position = location;
        m_particleVelocities.push_back(velocity);
        m_particles.push_back(particle);
    }
}

void ExplosionParticleSystem::draw(sf::RenderTarget & target)
{
    target.draw(m_particles.data(), m_particles.size(), sf::Points);
}
