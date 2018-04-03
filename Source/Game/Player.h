#pragma once

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

    private:
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
};