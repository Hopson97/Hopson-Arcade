#include "stack_menu.h"

#include "../resources/resource_holder.h"

namespace arcade {
    constexpr float BASE_Y = 95.0f;

    namespace gui {
        StackMenu::StackMenu(const sf::RenderWindow& window, float baseY, int width)
            : m_basePosition((float)window.getSize().x / 2.0f, baseY)
            , m_baseSize(width, 20)
        {
            m_background.setOutlineThickness(2);
            m_background.setOutlineColor(sf::Color::Green);
            m_background.setFillColor({100, 100, 100, 230});
            m_background.setSize(m_baseSize);
            m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, baseY - 30);

            m_titleText.setPosition(0, baseY - 35);
            m_titleText.setOutlineColor(sf::Color::Black);
            m_titleText.setOutlineThickness(1);
            m_titleText.setCharacterSize(30);
        }

        StackMenu::StackMenu(const sf::Vector2f& position, int width)
            : m_basePosition(position)
            , m_baseSize(width, 20)
        {
            m_background.setOutlineThickness(2);
            m_background.setOutlineColor(sf::Color::Green);
            m_background.setFillColor({100, 100, 100, 230});
            m_background.setSize(m_baseSize);
            m_background.setPosition(m_basePosition.x - m_baseSize.x / 2,
                                     position.y - 30);

            m_titleText.setPosition(position.x, position.y - 35);
            m_titleText.setOutlineColor(sf::Color::Black);
            m_titleText.setOutlineThickness(1);
            m_titleText.setCharacterSize(30);
        }

        StackMenu::StackMenu(StackMenu&& other)
            : m_widgets(std::move(other.m_widgets))
            , m_background(std::move(other.m_background))
            , m_basePosition(other.m_basePosition)
            , m_baseSize(other.m_baseSize)
        {
        }

        StackMenu& StackMenu::operator=(StackMenu&& other)
        {
            m_widgets = std::move(other.m_widgets);
            m_background = std::move(other.m_background);
            m_basePosition = other.m_basePosition;
            m_baseSize = other.m_baseSize;

            return *this;
        }

        Widget* StackMenu::addWidget(std::unique_ptr<Widget> w)
        {
            initWidget(*w);
            m_widgets.push_back(std::move(w));
            return m_widgets.back().get();
        }

        void StackMenu::initWidget(Widget& widget)
        {
            widget.setPosition(
                {m_basePosition.x - widget.getSize().x / 2, m_basePosition.y});

            m_basePosition.y += widget.getSize().y + 25;
            m_baseSize.y += widget.getSize().y + 25;
            m_background.setSize(m_baseSize);
        }

        void StackMenu::setTitle(const std::string& title)
        {
            m_titleText.setString(title);
            m_titleText.setPosition(m_background.getPosition().x +
                                        m_background.getSize().x / 2 -
                                        m_titleText.getGlobalBounds().width / 2,
                                    m_titleText.getPosition().y);
            m_basePosition.y += m_titleText.getGlobalBounds().height;
            m_baseSize.y += m_titleText.getGlobalBounds().height;
            m_background.setSize(m_baseSize);
        }

        void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
        {
            for (auto& widget : m_widgets) {
                widget->handleEvent(e, window);
            }
        }

        void StackMenu::render(sf::RenderTarget& renderer)
        {
            renderer.draw(m_background);
            renderer.draw(m_titleText);
            for (auto& widget : m_widgets) {
                widget->render(renderer);
            }
        }

    } // namespace gui
} // namespace arcade