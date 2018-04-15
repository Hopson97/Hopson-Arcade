#pragma once

#include "../../Framework/States/StateBase.h"
#include "../../Framework/GUI/StackMenu.h"
#include "../../Framework/GUI/Widget.h"
#include "../StarryBackground.h"
namespace SpaceInvaders
{
    class StateHighscores : public StateBase
    {
        using Entry = std::pair<std::string, int>;

        struct EntryBox
        {
        public:
            EntryBox(int position, const std::string& name, int score);

            void draw(sf::RenderTarget& renderer);

        private:
            sf::RectangleShape m_background;
            gui::Widget::Text m_nameText;
            gui::Widget::Text m_scoreText;

        };

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

        static int getHighestScore();

    private:
        void initViewMenu();
        void initSubmitMenu();

        void switchToViewMenu();
        void createHighscoreView();
        void loadScores();
        void writeScores();
        void sortScores();
        void submitScore();

        gui::StackMenu m_submitScoreMenu;
        gui::StackMenu m_highscoreMenu;
        gui::StackMenu* m_pActiveMenu;

        std::vector<Entry> m_scores;
        std::vector<EntryBox> m_entryBoxes;

        StarryBackground m_background;

        State m_state;

        std::string m_submitString;
        int m_scoreToSubmit = 0;

        sf::RectangleShape m_banner;
    };
}