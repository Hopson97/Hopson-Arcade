#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f & position, Type type, Direction direction)
    : m_position    (position)
    , m_type        (type)
    , m_direction   (direction)
{

}

void Projectile::update(float dt)
{
    float speed = 500 * (float)m_direction * dt;
    m_position.y += speed;
}

sf::FloatRect Projectile::getBox()
{
    return 
    {
        m_position.x,
        m_position.y,
        WIDTH,
        HEIGHT
    };
}
