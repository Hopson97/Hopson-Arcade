#pragma once

#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.h"

class Game;

class StateBase : public NonCopyable {
  public:
    StateBase(Game &game, const char *name);

    StateBase(Game &game, const char *name, unsigned resizeWindowWidth,
              unsigned resizeWindowHeight);

    virtual ~StateBase() = default;

    virtual void onOpen() {}
    virtual void handleEvent([[maybe_unused]] sf::Event e) {}
    virtual void handleInput() {}
    virtual void update([[maybe_unused]] sf::Time deltaTime) {}
    virtual void fixedUpdate([[maybe_unused]] sf::Time deltaTime) {}
    virtual void render(sf::RenderTarget &renderer) = 0;

    const std::string &getName() { return m_name; }

  protected:
    Game *m_pGame;
    std::string m_name;
};
