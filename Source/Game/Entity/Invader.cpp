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

void Invader::onCollide()
{
    m_isAlive = false;
}
