#pragma once

#include "../Framework/States/StateBase.h"

#include <vector>

class Game;

class StateGameSelect : public StateBase
{
    class GameSelect
    {
        public:
            GameSelect(const std::string& name, const sf::Texture& thumbnail)
            { }

            virtual std::unique_ptr<StateBase> getInitState() = 0;

        private:
            sf::RectangleShape m_container;
            sf::RectangleShape m_thumbnail;
    };

    public:
        StateGameSelect(Game& game);

        void onOpen() override;

        void handleEvent(sf::Event e) override;
        void render(sf::RenderTarget& target) override;

    private:
        void registerGame();

};