#pragma once

#include "StateBase.h"
#include "../Game/World.h"

#include "../GUI/StackMenu.h"

/*
    The main state; where all the gameplay happens
*/
class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleEvent    (sf::Event e)                   override;
        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        World m_world;

        int m_score = 0;
        bool m_isGameover;
        sf::Clock m_gameOverClock;

        gui::StackMenu m_gameOverMenu;

        //Displays how many lives the player has left
        class LifeDisplay
        {
            public:
                LifeDisplay();

                void draw(sf::RenderTarget& window, int lives);

            private:
                gui::Widget::Text m_label;
                sf::RectangleShape m_lifeStamp;
        } m_lifeDisplay;

        //Displays the Player's current score
        class ScoreDisplay
        {
            public:
                ScoreDisplay();

                void update(int newScore);

                void draw(sf::RenderTarget& target);

            private:
                gui::Widget::Text m_label;
        } m_scoreDisplay;
};
