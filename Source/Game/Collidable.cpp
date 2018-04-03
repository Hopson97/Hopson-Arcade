#include "Collidable.h"

Collidable::Collidable(float width, float height)
    : m_size    (width, height)
{}

sf::FloatRect Collidable::getBox()
{
    return
    {
        getPosition().x,
        getPosition().y,
        m_size.x,
        m_size.y
    };
}
