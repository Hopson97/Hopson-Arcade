#pragma once

#include "StateBase.h"
#include "../GUI/StackMenu.h"

class StateHighscores : public StateBase
{
    using Entry = std::pair<std::string, int>;

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

        void loadScores();
        void writeScores();
        void sortScores();

        gui::StackMenu m_submitScoreMenu;
        gui::StackMenu m_highscoreMenu;
        gui::StackMenu* m_pActiveMenu;

        std::vector<Entry> m_scores;

        State m_state;

        std::string m_submitString;
        int m_scoreToSubmit = 0;
};
