#pragma once

#include "../Framework/States/StateBase.h"

class Game;

class StateGameSelect : public StateBase
{
    public:
        StateGameSelect(Game& game);

        void handleEvent(sf::Event e) override;
        void render(sf::RenderTarget& target) override;

    private:

};