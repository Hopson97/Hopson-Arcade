#pragma once

#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

namespace arcade {
    namespace gui {
        class Widget;
    } // namespace gui

} // namespace arcade

namespace pong {

    class StateError : public arcade::StateBase {
      public:
        StateError(arcade::Game& game, const std::string& message);

        void handleEvent(sf::Event e) override;
        void handleInput() override{};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

      private:
        arcade::gui::StackMenu m_messageMenu;
    };
} // namespace pong