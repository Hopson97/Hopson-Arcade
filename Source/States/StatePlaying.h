#pragma once

#include "StateBase.h"
#include "../Game/InvaderManager.h"
#include "../Game/Player.h"
#include "../Game/Projectile.h"
#include "../Game/AnimationRenderer.h"

class StatePlaying : public StateBase
{
    struct DisplayText
    {
        DisplayText();
        sf::Text text;
    };

    class LifeDisplay
    {
        public:
            LifeDisplay();

            void draw(sf::RenderTarget& window, int lives);

        private:
            DisplayText m_label;
            sf::RectangleShape m_lifeStamp;
    };

    class ScoreDisplay
    {
        public:
            ScoreDisplay();

            void update(int newScore);

            void draw(sf::RenderTarget& target);

        private:
            DisplayText m_label;

    };

    public:
        StatePlaying(Game& game);

        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        InvaderManager m_invaders;
        Player m_player;

        sf::Clock m_invaderShotDelayTimer;
        sf::Clock m_shootDelayTimer;
        std::vector<Projectile> m_projectiles;
        AnimationRenderer m_projectileRenderer;

        Random<> m_rng;
        sf::Clock m_projectileAnimTimer;
        
        int m_score = 0;

        LifeDisplay m_lifeDisplay;
        ScoreDisplay m_scoreDisplay;
};
