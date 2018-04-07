#pragma once

#include "StateBase.h"
#include "../GUI/StackMenu.h"

class StateMainMenu : public StateBase
{
    public:
        StateMainMenu(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        gui::StackMenu m_mainMenu;

        sf::RectangleShape m_banner;
};
