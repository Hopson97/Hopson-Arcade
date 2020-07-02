#pragma once

#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

namespace arcade {
    namespace gui {
        class Widget;
        class Label;
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
        void initPlayerList();
        void clientHandlePacket(sf::Packet& packet);
        void hostHandlePacket(sf::Packet& packet);

        arcade::gui::StackMenu m_mainMenu;
        arcade::gui::StackMenu m_playerList;
        bool m_isHost;
        bool m_hasConnection = false;

        sf::TcpListener m_tcpListener;
        sf::TcpSocket m_socket;

        arcade::gui::Widget* m_startGameButton = nullptr;

        arcade::gui::Label* m_otherPlayerLabel = nullptr;

        const std::string m_name;
        std::string m_hostIp;
        std::string m_opponentName;
    };
} // namespace pong