#include "Projectile.h"

#include "../DisplayInfo.h"

Projectile::Projectile(const sf::Vector2f & position, Type type, Direction direction)
    : Collidable    (WIDTH, HEIGHT)
    , m_position    (position)
    , m_type        (type)
    , m_direction   (direction)
{

}

void Projectile::update(float dt)
{
    float speed = 750 * (float)m_direction * dt;
    m_position.y += speed;
    if (m_position.y <= 0 || m_position.y >= Display::HEIGHT) {
        m_isActive = false;
    }
}

void Projectile::onCollide()
{
    m_isActive = false;
}
