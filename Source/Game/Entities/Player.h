#pragma once

#include <SFML/Graphics.hpp>

#include "Collidable.h"
#include "../Util/Animation.h"

/**
    Represents the player
*/
class Player : public Collidable
{
    public:
        constexpr static int WIDTH = 44;
        constexpr static int HEIGHT = 32;

        Player();

        //Restart player after death
        //Returns false if out of lives
        bool restart();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

        //Gets the coordinates of the gun
        sf::Vector2f getGunPosition() const;

        const sf::Vector2f& getPosition() const;
        void onCollide() override;

        int getLives() const;
        bool isAlive() const;

        bool canBeRevived() const;

    private:
        sf::RectangleShape m_sprite;
        Animation m_deathAnimation;
        sf::Vector2f m_velocity;
        sf::Clock m_deathTimer;

        bool m_isAlive = true;
        int m_livesLeft = 3;

};