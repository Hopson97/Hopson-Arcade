#pragma once

#include <SFML/Graphics.hpp>

#include "../Collidable.h"
#include "../../Util/Random.h"

class UFO : public Collidable
{
    public:
        enum class State
        {
            Waiting,
            Flying,
            Destroyed
        };

        UFO(Random<>& rand);

        State getState() const;

        void update(float dt);

        void draw(sf::RenderTarget& window);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other);

    private:
       Random<>& m_rng;

       sf::RectangleShape m_sprite;
       float m_vx;
       State m_state;
       bool m_hasStateBeenGotSinceDeath;
};