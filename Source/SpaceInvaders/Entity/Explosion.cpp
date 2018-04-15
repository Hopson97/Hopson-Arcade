#include "Explosion.h"

namespace SpaceInvaders
{
    Explosion::Explosion(const sf::Vector2f & position)
        : m_position(position)
    {
    }

    bool Explosion::isLifeOver() const
    {
        return m_lifetimeCounter.getElapsedTime().asSeconds() >= 0.2f;
    }

    const sf::Vector2f & Explosion::getPosition() const
    {
        return m_position;
    }
}