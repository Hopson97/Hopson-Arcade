#pragma once

#include <SFML/Graphics.hpp>

/*

*/
class Invader
{
    public:
        constexpr static float WIDTH = 50;
        constexpr static float HEIGHT = 35;

    public:
        Invader(const sf::Vector2f& initialLocation);

        void move(float x, float y);
        void draw(sf::RenderTarget& target);

        const sf::Vector2f& getPosition() const { return m_location; }
        bool isAlive() const { return m_isAlive; }

    private:
        sf::Vector2f m_location;
        bool m_isAlive = true;
};
