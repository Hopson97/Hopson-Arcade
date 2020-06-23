
#include "pong/states/state_main_menu.h"
#include "space_invaders/states/state_main_menu.h"
#include <arcade/game.h>

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
    void setConsolePosition()
    {
#ifdef _WIN32
        HWND consoleWindow = GetConsoleWindow();
        SetWindowPos(consoleWindow, 0, 0, 0, 500, 500, SWP_NOSIZE | SWP_NOZORDER);
#endif
    }

    constexpr int GAMES = 2;

    template <typename T>
    void run()
    {
        std::cout << "\nTo choose another Game, simply close the window\n";
        std::cin.ignore();
        arcade::Game app{};
        app.initGame<T>();
        app.run();
        std::cout << '\n';
    }

    bool isValidChoice(int option)
    {
        return option > 0 && option <= GAMES + 1;
    }
} // namespace

int main()
{
    setConsolePosition();
    bool exit = false;
    while (!exit) {
        int option = 0;
        std::cout << "Which Game would you like to play?\n"
                  << "1. Space Invaders\n"
                  << "2. Pong\n"
                  << GAMES + 1 << ". Exit\n";

        while (!isValidChoice(option)) {
            std::cin >> option;

            if (!isValidChoice(option)) {
                std::cout << "Invalid option, please pick a number between 1 and "
                          << GAMES + 1 << "\n";
                std::cin.ignore();
            }
        }

        switch (option) {
            case 1:
                run<space_invaders::StateMainMenu>();
                break;

            case 2:
                run<pong::StateMainMenu>();
                break;

            case GAMES + 1:
                exit = true;
                break;

            default:
                break;
        }
    }
}