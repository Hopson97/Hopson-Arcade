#pragma once

#include <SFML/Graphics.hpp>

class Collidable
{
    public:
        Collidable(float width, float height);

        virtual const sf::Vector2f& getPosition() const = 0;
        sf::FloatRect getBox();

    private:
        sf::Vector2f m_size;
};