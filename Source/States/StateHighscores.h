#pragma once

#include "StateBase.h"
#include "../GUI/StackMenu.h"

class StateHighscores : public StateBase
{
    enum class State {
        Submitting,
        Viewing
    };

    public:
        StateHighscores(Game& game, int score);
        StateHighscores(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        void initViewMenu();
        void initSubmitMenu();

        gui::StackMenu m_submitScoreMenu;
        gui::StackMenu m_highscoreMenu;
        gui::StackMenu* m_pActiveMenu;

        State m_state;

        std::string m_submitString;
};
