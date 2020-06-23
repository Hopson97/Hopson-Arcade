#pragma once

#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

namespace pong {

    class StateMainMenu : public arcade::StateBase {
      public:
        StateMainMenu(arcade::Game& game);

        void handleEvent(sf::Event e) override;
        void handleInput() override{};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

      private:
        arcade::gui::StackMenu m_mainMenu;
        arcade::gui::StackMenu m_joinMenu;
        arcade::gui::StackMenu* mp_activeMenu = nullptr;
        sf::RectangleShape m_banner;

        std::string m_joinIp;
    };
} // namespace pong