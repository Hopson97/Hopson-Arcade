#pragma once

#include "../net.h"
#include "../pong_server.h"
#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

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
        void connectToServer();
        void initPlayerList();

        void checkHostStartButton();

        void handlePacket(ToClientCommand command, sf::Packet& packet);

        PongServer m_server;
        sf::TcpSocket m_socket;

        arcade::gui::StackMenu m_mainMenu;
        arcade::gui::StackMenu m_playerList;

        arcade::gui::Widget* m_startGameButton = nullptr;

        std::array<arcade::gui::Label*, MAX_CONNECTS> m_playerNameLabels;

        bool m_isHost;
        bool m_isConnected = false;

        std::string m_name;
        sf::IpAddress m_hostIp;

        sf::Uint8 m_playerId;

        int m_peerConnections = 0;
    };
} // namespace pong