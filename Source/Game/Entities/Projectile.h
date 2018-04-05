#pragma once

#include <SFML/Graphics.hpp>

#include "Collidable.h"

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
        void onCollide() override;
        Type getType() const { return m_type; }

        const sf::Vector2f& getPosition() const { return m_position; }

        bool isActive() const { return m_isActive; }

    private:
        sf::Vector2f m_position;
        Type m_type;
        Direction m_direction;
        bool m_isActive = true;
};