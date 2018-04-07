#pragma once

#include "StateBase.h"
#include "../GUI/StackMenu.h"
#include "../Util/Random.h"

class StateMainMenu : public StateBase
{
    public:
        StateMainMenu(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        void giveStarRandomStartLocation(sf::Vertex& v);

        gui::StackMenu m_mainMenu;

        sf::RectangleShape m_banner;

        std::vector<sf::Vertex> m_stars;

        Random<> m_rng;
};
