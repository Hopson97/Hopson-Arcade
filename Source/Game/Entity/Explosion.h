#pragma once

#include <SFML/Graphics.hpp>

class Explosion
{
    public:
        Explosion(const sf::Vector2f& position);

        bool isLifeOver() const;
        const sf::Vector2f& getPosition() const;

    private:
        sf::Vector2f m_position;
        sf::Clock m_lifetimeCounter;
};