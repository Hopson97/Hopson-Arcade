#include "Invader.h"

Invader::Invader(const sf::Vector2f & initialLocation, Type type)
    :   m_location  (initialLocation)
    ,   m_type      (type)
{
}

void Invader::move(float x, float y)
{
    m_location += {x, y};
}

sf::FloatRect Invader::getBox() const
{
    return
    {
        m_location.x,
        m_location.y,
        Invader::WIDTH,
        Invader::HEIGHT
    };
}
