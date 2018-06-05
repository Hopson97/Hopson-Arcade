#include "StateGameSelect.h"

#include "../Game.h"

StateGameSelect::StateGameSelect(Game& game)
    :   StateBase(game, "Game Select", 1280, 720)
{
    registerGame(std::make_shared<SpaceInvadersSelect>("SpaceInvaders"));
}

void StateGameSelect::onOpen()
{
    m_pGame->resizeWindow(1280, 720);
}


void StateGameSelect::handleEvent(sf::Event e)
{
    std::shared_ptr<GameSelect> selectedGame = nullptr;
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            switch (e.mouseButton.button) {
                case sf::Mouse::Left: {
                    for (auto & game : m_gameSelects) {
                        selectedGame = game;
                        break;
                    }

                }
                default: 
                    break;
            }
        default: 
            break;
    }

    if (selectedGame) {
        m_pGame->pushState(selectedGame->getInitState(*m_pGame));
    }
}

void StateGameSelect::render(sf::RenderTarget& target)
{
    for (auto& g : m_gameSelects) {
        g->draw(target);
    }
}

void StateGameSelect::registerGame(std::shared_ptr<GameSelect> gameSelect)
{
    const float w = GameSelect::WIDTH;
    const int index = m_gameSelects.size() % 2 != 0;

    float x = ((w / 4) - 5) + (m_gameSelects.size() % 2 == 0 ? 0 : w) + index * 10;
    float y = int(m_gameSelects.size() / 2) * (GameSelect::HEIGHT);

    gameSelect->setPosition({ x, y });
    m_gameSelects.push_back(gameSelect);
}
