#pragma once

#include "../../arcade/util/animation.h"
#include "../../arcade/util/random.h"
#include "../collidable.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace space_invaders {
    class UFO : public Collidable {
      public:
        enum class State { Waiting, Flying, Destroyed };

        UFO(Random<> &rand);

        State getState() const;

        void update(float dt);

        void draw(sf::RenderTarget &window);

        const sf::Vector2f &getPosition() const;
        void onCollide(Collidable &other);

      private:
        Random<> &m_rng;

        sf::RectangleShape m_sprite;
        float m_vx;
        State m_state;
        Animation m_animation;

        sf::Sound m_flyingSound;
    };
} // namespace space_invaders