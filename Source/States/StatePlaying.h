#pragma once

#include "StateBase.h"
#include "../Game/World.h"
#include "../Game/GameDisplays.h"

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        World m_world;

        int m_score = 0;

        //Helpful class to create some generic text stuff
        struct DisplayText
        {
            DisplayText();
            sf::Text text;
        };

        //Displays how many lives the player has left
        class LifeDisplay
        {
            public:
                LifeDisplay();

                void draw(sf::RenderTarget& window, int lives);

            private:
                DisplayText m_label;
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
                DisplayText m_label;
        } m_scoreDisplay;
};
