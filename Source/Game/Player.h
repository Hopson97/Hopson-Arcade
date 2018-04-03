#pragma once

#include <SFML/Graphics.hpp>

#include "Collidable.h"

/**
    Represents the player
*/
class Player : public Collidable
{
    public:
        Player();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

        //Gets the coordinates of the gun
        sf::Vector2f getGunPosition() const;

        const sf::Vector2f& getPosition() const { return m_sprite.getPosition(); }
        void onCollide() override;

    private:
        sf::RectangleShape m_sprite;
        sf::Vector2f m_velocity;
};