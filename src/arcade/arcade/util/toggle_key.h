#pragma once

#include <SFML/Graphics.hpp>

namespace arcade {
    class ToggleKey {
      public:
        ToggleKey(sf::Keyboard::Key);

        bool isKeyPressed();

      private:
        sf::Keyboard::Key m_key;
        sf::Clock m_delayTimer;
    };
} // namespace arcade