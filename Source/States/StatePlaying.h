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
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        World m_world;

        int m_score = 0;

        LifeDisplay m_lifeDisplay;
        ScoreDisplay m_scoreDisplay;
};
