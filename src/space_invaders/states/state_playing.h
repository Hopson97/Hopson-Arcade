#pragma once

#include "../world.h"
#include <arcade/gui/stack_menu.h>
#include <arcade/state/state_base.h>

namespace space_invaders {
    /*
        The main state; where all the gameplay happens
    */
    class StatePlaying : public StateBase {
      public:
        StatePlaying(Game &game);

        void handleEvent(sf::Event e) override;
        void handleInput() override;
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget &renderer) override;

      private:
        World m_world;

        int m_score = 0;
        bool m_isGameover;
        sf::Clock m_gameOverClock;

        gui::StackMenu m_gameOverMenu;

        // Displays how many lives the player has left
        class LifeDisplay {
          public:
            LifeDisplay();

            void draw(sf::RenderTarget &window, int lives);

          private:
            gui::Widget::Text m_label;
            sf::RectangleShape m_lifeStamp;
        } m_lifeDisplay;

        // Displays the Player's current score
        class ScoreDisplay {
          public:
            ScoreDisplay(float centreX, const std::string &text);

            void update(int newScore);

            void draw(sf::RenderTarget &target);

            int getCurrentScoreDisplayed() const;

          private:
            void updateDisplay();

            gui::Widget::Text m_label;
            std::string m_text;
            int m_currentScore;
            float m_centerPosition;
        } m_scoreDisplay, m_highestScoreDisplay;
    };
} // namespace space_invaders