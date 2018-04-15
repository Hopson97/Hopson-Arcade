#pragma once

#include "../../Framework/States/StateBase.h"
#include "../../Framework/GUI/StackMenu.h"
#include "../../Framework/Util/Random.h"
#include "../StarryBackground.h"

namespace SpaceInvaders
{
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

        StarryBackground m_background;
    };
}