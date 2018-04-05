#include "Invader.h"

Invader::Invader(const sf::Vector2f & initialLocation, Type type)
    :   Collidable    (WIDTH, HEIGHT)
    ,   m_location  (initialLocation)
    ,   m_type      (type)
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

void Invader::onCollide(const Collidable& other)
{
    m_isAlive = false;
}
