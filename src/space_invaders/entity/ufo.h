#pragma once

#include <arcade/util/animation.h>
#include <arcade/util/random.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../collidable.h"

namespace space_invaders {
    class UFO : public Collidable {
      public:
        enum class State { Waiting, Flying, Destroyed };

        UFO(arcade::Random<> &rand);

        State getState() const;

        void update(float dt);

        void draw(sf::RenderTarget &window);

        const sf::Vector2f &getPosition() const;
        void onCollide(Collidable &other);

      private:
        arcade::Random<> &m_rng;

        sf::RectangleShape m_sprite;
        float m_vx;
        State m_state;
        arcade::Animation m_animation;

        sf::Sound m_flyingSound;
    };
} // namespace space_invaders