#include "Invader.h"

Invader::Invader(const sf::Vector2f & initialLocation)
    : m_location    (initialLocation)
{
}

void Invader::move(float x, float y)
{
    m_location += {x, y};
}


//temp for now//temp for now//temp for now//temp for now
void Invader::draw(sf::RenderTarget & target)
{
    sf::RectangleShape shape; 

    //temp for now
    shape.setSize({ WIDTH, HEIGHT });
    shape.setPosition(m_location);
    target.draw(shape);
}
