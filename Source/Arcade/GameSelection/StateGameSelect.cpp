#include "StateGameSelect.h"

#include "../Game.h"

StateGameSelect::StateGameSelect(Game& game)
    :   StateBase(game, "Game Select", 1280, 720)
{
    registerGame(std::make_unique<SpaceInvadersSelect>("SpaceInvaders"));
    registerGame(std::make_unique<SpaceInvadersSelect>("SpaceInvaders"));
    registerGame(std::make_unique<SpaceInvadersSelect>("SpaceInvaders"));
    registerGame(std::make_unique<SpaceInvadersSelect>("SpaceInvaders"));
    registerGame(std::make_unique<SpaceInvadersSelect>("SpaceInvaders"));
}

void StateGameSelect::onOpen()
{
    m_pGame->resizeWindow(1280, 720);
}


void StateGameSelect::handleEvent(sf::Event e)
{
}

void StateGameSelect::render(sf::RenderTarget& target)
{
    for (auto& g : m_gameSelects) {
        g->draw(target);
    }
}

void StateGameSelect::registerGame(std::unique_ptr<GameSelect> gameSelect)
{
    float x = 123.0f + (m_gameSelects.size() % 2 == 0 ? 0 : GameSelect::WIDTH);
    float y = int(m_gameSelects.size() / 2) * (GameSelect::HEIGHT);

    gameSelect->setPosition({ x, y });
    m_gameSelects.push_back(std::move(gameSelect));
}
