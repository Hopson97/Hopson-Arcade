#pragma once

#include <SFML/Graphics.hpp>

class Invader
{
    public:
        constexpr static float SIZE = 40;

    public:
        Invader(const sf::Vector2f& initialLocation);

        void move(float x, float y);
        void draw(sf::RenderTarget& target);

    private:
        sf::Vector2f m_location;
};
