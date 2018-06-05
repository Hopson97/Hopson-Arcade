#include "StateGameSelect.h"

#include "Game.h"

StateGameSelect::StateGameSelect(Game& game)
    :   StateBase(game, "Game Select", 1280, 720)
{
}


void StateGameSelect::handleEvent(sf::Event e)
{
}

void StateGameSelect::render(sf::RenderTarget & target)
{
}
