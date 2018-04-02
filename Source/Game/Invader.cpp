#include "Invader.h"

Invader::Invader(const sf::Vector2f & initialLocation)
    : m_location    (initialLocation)
{
}

void Invader::move(float x, float y)
{
    m_location += {x, y};
}

void Invader::draw(sf::RenderTarget & target)
{
    sf::RectangleShape shape; 
    shape.setSize({ SIZE, SIZE });
    shape.setPosition(m_location);
    target.draw(shape);
}
