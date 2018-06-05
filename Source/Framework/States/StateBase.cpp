#include "StateBase.h"

#include "../../Arcade/Game.h"

StateBase::StateBase(Game & game, const char * name)
    : m_pGame(&game)
    , m_name(name)
{}

StateBase::StateBase(Game & game, const char * name, unsigned resizeWindowWidth, unsigned resizeWindowHeight)
    : m_pGame(&game)
    , m_name(name)
{
    m_pGame->resizeWindow(resizeWindowWidth, resizeWindowHeight);
}
