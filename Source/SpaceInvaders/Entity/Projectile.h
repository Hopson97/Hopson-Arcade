#pragma once

#include <SFML/Graphics.hpp>

#include "../Collidable.h"

namespace SpaceInvaders
{
    class Projectile : public Collidable
    {
    public:
        constexpr static float HEIGHT = 24;
        constexpr static float WIDTH = 12;

        enum class Type
        {
            Rectangle,
            Lightning,
            Knife
        };

        enum class Direction
        {
            Up = -1,
            Down = 1
        };

        Projectile(const sf::Vector2f& position, Type type, Direction direction);
        void update(float dt);
        void onCollide(Collidable& other) override;
        void destroy();

        const sf::Vector2f& getPosition() const;
        Type getType() const;
        bool isActive() const;
        Direction getDirection() const;

        int getID() const;

    private:
        sf::Vector2f m_position;
        Type m_type;
        Direction m_direction;
        bool m_isActive = true;
        int m_id;
    };
}