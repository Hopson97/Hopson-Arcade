#include "label.h"

#include <iostream>

namespace arcade {
    namespace gui {

        Label::Label()
        {
            m_label.setCharacterSize(30);
        }

        void Label::setLabel(const std::string& str)
        {
            m_label.setString(str);
        }

        void Label::handleEvent([[maybe_unused]] sf::Event e,
                                [[maybe_unused]] const sf::RenderWindow& window)
        {
        }

        void Label::render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_label);
        }

        void Label::setPosition(const sf::Vector2f& pos)
        {
            m_position = pos;
            m_label.setPosition(m_position.x,
                                m_position.y + m_label.getGlobalBounds().height - 32);
        }

        sf::Vector2f Label::getSize() const
        {
            return {m_label.getGlobalBounds().width,
                    m_label.getGlobalBounds().height + 5};
        }

        void Label::disable()
        {
        }

        void Label::enable()
        {
        }

    } // namespace gui
} // namespace arcade