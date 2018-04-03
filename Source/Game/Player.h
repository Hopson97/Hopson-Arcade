#pragma once

#include <SFML/Graphics.hpp>

/**
    Represents the player
*/
class Player
{
    public:
        Player();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

        //Gets the coordinates of the gun
        sf::Vector2f getGunPosition() const;

    private:
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
};