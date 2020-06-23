#pragma once

#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

namespace pong {

    class StateLobby : public arcade::StateBase {
      public:
        StateLobby(arcade::Game &game, bool isHost);

        void handleEvent(sf::Event e) override;
        void handleInput() override{};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget &renderer) override;

      private:
        arcade::gui::StackMenu m_mainMenu;
        sf::RectangleShape m_banner;
        bool m_isHost;
    };
} // namespace pong