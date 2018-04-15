#pragma once

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    class Collidable
    {
    public:
        Collidable(float width, float height);

        bool tryCollideWith(Collidable& other);
        sf::FloatRect getBox() const;

        virtual const sf::Vector2f& getPosition() const = 0;
        virtual void onCollide(Collidable& other) = 0;

    private:
        sf::Vector2f m_size;
    };
}