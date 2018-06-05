#pragma once

#include <vector>

#include "GameSelect.h"

class Game;

class StateGameSelect : public StateBase
{
    public:
        StateGameSelect(Game& game);

        void onOpen() override;

        void handleEvent(sf::Event e) override;
        void render(sf::RenderTarget& target) override;

    private:
        void registerGame(std::shared_ptr<GameSelect> gameSelect);

        std::vector<std::shared_ptr<GameSelect>> m_gameSelects;
};