#pragma once

#include <SFML/Graphics.hpp>

class Projectile
{
    public:
        constexpr static float HEIGHT = 32;
        constexpr static float WIDTH = 8;

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
        const sf::Vector2f& getPosition() const { return m_position; }

        sf::FloatRect getBox();

    private:
        sf::Vector2f m_position;
        Type m_type;
        Direction m_direction;
};