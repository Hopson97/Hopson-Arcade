#pragma once

#include "../arcade/util/random.h"
#include <SFML/Graphics.hpp>

namespace space_invaders {

    class StarryBackground {
      public:
        StarryBackground();

        void update(float dt);

        void draw(sf::RenderTarget &renderer);

      private:
        void giveStarRandomStartLocation(sf::Vertex &v);

        std::vector<sf::Vertex> m_stars;

        Random<> m_rng;
    };
} // namespace space_invaders