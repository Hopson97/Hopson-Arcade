#pragma once

#include "net.h"
#include <array>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>

namespace pong {
    // A client-side player. This is either the player, a peer, or a "AI" player

    enum class PongPlayerDirection {
        UpDown,
        LeftRight,
    };

    struct PongPlayer {
        std::string name;
        int score = 0;
        bool isConnected = false;

        sf::RectangleShape paddle;
        PongPlayerDirection direction;
    };

    using PongClientPlayerList = std::array<PongPlayer, MAX_CONNECTS>;
} // namespace pong
