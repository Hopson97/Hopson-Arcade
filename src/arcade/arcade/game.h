#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "state/state_base.h"
#include "util/fps_counter.h"
#include "util/non_moveable.h"

namespace arcade {
    /**

        Main controlling class of the game.
        Handles state switches and the main loop, as well
        as counting the FPS
    */
    class Game : public NonCopyable, public NonMovable {
        struct Action {
            enum class Type {
                None,
                Push,
                Change,
                Pop,
                Quit,
            };
            Type type = Type::None;
            std::unique_ptr<StateBase> state;
        };

      public:
        Game();

        void run();

        template <typename T>
        void initGame();

        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        void exitGame();

        template <typename T, typename... Args>
        void pushState(Args&&... args);

        template <typename T, typename... Args>
        void changeState(Args&&... args);

        const sf::RenderWindow& getWindow() const;

        void resizeWindow(unsigned width, unsigned height);

      private:
        void handleEvent();
        void updateStates();

        StateBase& getCurrentState();

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<StateBase>> m_states;

        FPSCounter counter;

        Action m_action;
    };

    template <typename T>
    inline void Game::initGame()
    {
        m_states.push_back(std::make_unique<T>(*this));
    }

    template <typename T, typename... Args>
    inline void Game::pushState(Args&&... args)
    {
        m_action.type = Action::Type::Push;
        m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    inline void Game::changeState(Args&&... args)
    {
        m_action.type = Action::Type::Change;
        m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
    }
} // namespace arcade