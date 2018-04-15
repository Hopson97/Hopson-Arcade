#include "Invader.h"

namespace SpaceInvaders
{
    Invader::Invader(const sf::Vector2f & initialLocation, Type type)
        : Collidable(WIDTH, HEIGHT)
        , m_location(initialLocation)
        , m_type(type)
        , m_initialPosition(initialLocation)
    {
    }

    void Invader::move(float x, float y)
    {
        m_location += {x, y};
    }

    const sf::Vector2f & Invader::getPosition() const
    {
        return m_location;
    }

    bool Invader::isAlive() const
    {
        return m_isAlive;
    }

    Invader::Type Invader::getType() const
    {
        return m_type;
    }

    void Invader::onCollide(Collidable& other)
    {
        m_isAlive = false;
    }
}