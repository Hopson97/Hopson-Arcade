#include "Projectile.h"

#include "../../DisplayInfo.h"

Projectile::Projectile(const sf::Vector2f & position, Type type, Direction direction)
    : Collidable    (WIDTH, HEIGHT)
    , m_position    (position)
    , m_type        (type)
    , m_direction   (direction)
{
    static int ID = 0;
    m_id = ID++;
}

void Projectile::update(float dt)
{
    float speed = 550 * (float)m_direction * dt;
    m_position.y += speed;
    if (m_position.y <= 0 || m_position.y >= Display::HEIGHT) {
        destroy();
    }
}

void Projectile::onCollide(Collidable& other)
{
    destroy();
}

void Projectile::destroy()
{
    m_isActive = false;
}

const sf::Vector2f & Projectile::getPosition() const
{
    return m_position;
}

Projectile::Type Projectile::getType() const
{
    return m_type;
}

bool Projectile::isActive() const
{
    return m_isActive;
}

Projectile::Direction Projectile::getDirection() const
{
    return m_direction;
}

int Projectile::getID() const
{
    return m_id;
}