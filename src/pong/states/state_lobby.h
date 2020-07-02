#pragma once

#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

namespace arcade {
    namespace gui {
        class Widget;
    } // namespace gui

} // namespace arcade

namespace pong {

    class StateLobby : public arcade::StateBase {
      public:
        StateLobby(arcade::Game& game, const std::string& name);
        StateLobby(arcade::Game& game, const std::string& ip, const std::string& name);

        void handleEvent(sf::Event e) override;
        void handleInput() override{};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

      private:
        arcade::gui::StackMenu m_mainMenu;
        arcade::gui::StackMenu m_playerList;
        sf::RectangleShape m_banner;
        bool m_isHost;

        sf::TcpListener m_tcpListener;
        sf::TcpSocket m_socket;

        arcade::gui::Widget* m_startGameButton = nullptr;

        const std::string m_name;
        std::string m_opponentName;
    };
} // namespace pong