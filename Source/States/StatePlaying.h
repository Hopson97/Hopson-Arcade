#pragma once

#include "StateBase.h"
#include "../Game/InvaderManager.h"

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        InvaderManager m_invaders;
};
