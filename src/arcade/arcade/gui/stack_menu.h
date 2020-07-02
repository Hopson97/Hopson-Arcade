/**
 * @file stack_menu.h
 * @author Matthew Hopson
 * @brief Class definition for a stack menu
 * @version 0.1
 * @date 2019-06-03
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../util/non_copyable.h"
#include "widget.h"

namespace arcade {
    namespace gui {
        /**
         * @brief Class for a stack menu
         * A stack menu is a menu where its widgets appear in a vertical stack
         */
        class StackMenu : public NonCopyable {
          public:
            StackMenu(const sf::RenderWindow& window, float baseY, int width = 300);
            StackMenu(const sf::Vector2f& position, int width);

            StackMenu(StackMenu&& other);
            StackMenu& operator=(StackMenu&& other);

            ~StackMenu() = default;

            Widget* addWidget(std::unique_ptr<Widget> w);
            /*
            template<typename T, typename... Args>
            void addWidget(Args&&... args) {
                auto w = std::make_unique<T>(std::forward<Args>(args)...);
                initWidget(*w);
                m_widgets.push_back(std::move(w));
            }*/

            void setTitle(const std::string& title);

            void handleEvent(sf::Event e, const sf::RenderWindow& window);
            void render(sf::RenderTarget& renderer);

          private:
            void initWidget(Widget& w);

            std::vector<std::unique_ptr<Widget>> m_widgets;
            sf::RectangleShape m_background;

            sf::Vector2f m_basePosition;
            sf::Vector2f m_baseSize;

            Widget::Text m_titleText;
        };

    } // namespace gui
} // namespace arcade