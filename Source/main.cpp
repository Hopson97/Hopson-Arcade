#include <SFML/Graphics.hpp>
#include "input/keyboard.h"

int main() {
    sf::RenderWindow window({1280, 720}, "SFML", sf::Style::Default);
    window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	Keyboard keyboard;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
			keyboard.update(e);
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear();

        window.display();
    }
}
