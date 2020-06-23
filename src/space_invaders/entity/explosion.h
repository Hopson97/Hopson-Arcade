#pragma once

#include <SFML/Graphics.hpp>

namespace space_invaders {
    /*
        Represents a single explosion entity
    */
    class Explosion {
      public:
        Explosion(const sf::Vector2f& position);

        bool isLifeOver() const;
        const sf::Vector2f& getPosition() const;

      private:
        sf::Vector2f m_position;     // The position of the explosion
        sf::Clock m_lifetimeCounter; // Clock for checking if the explosion is
                                     // outlived
    };
} // namespace space_invaders