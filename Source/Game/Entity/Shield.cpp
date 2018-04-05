#include "Shield.h"

#include "../../DisplayInfo.h"

Shield::ShieldSection::ShieldSection(float tlX, float tlY, SectorStyle style)
{
    for (float y = 0; y < SECT_SIZE; y++) {
        for (float x = 0; x < SECT_SIZE; x++) {
            sf::Vertex pixel;
            pixel.color = sf::Color::Green;
            pixel.position = { x + tlX, y + tlY };
            calculatePixelCoord((int)x, (int)y, pixel, style);
        }
    }
}

void Shield::ShieldSection::draw(sf::RenderTarget & target)
{
    target.draw(m_pixels.data(), m_pixels.size(), sf::Points);
}

Shield::Shield(float x)
    : Collidable(SIZE, SIZE)
{
    using Sty = SectorStyle;
    float y = Display::HEIGHT - 200;
    for (float sy = 0; sy < 4; sy++) {
        for (float sx = 0; sx < 4; sx++) {
            Sty style = Sty::Square;
            int xP = (int)sx;
            int yP = (int)sy;
            if (xP == 0 && yP == 0) style = Sty::SlopeUp;
            if (xP == 3 && yP == 0) style = Sty::SlopeDown;
            if (xP == 1 && yP == 3) style = Sty::SlopeUnderUp;
            if (xP == 2 && yP == 3) style = Sty::SlopeUnderDown;
            m_sections.emplace_back(x + sx * SECT_SIZE, y + sy * SECT_SIZE, style);
        }
    }
}

void Shield::draw(sf::RenderTarget & target)
{
    for (auto& sect : m_sections) {
        sect.draw(target);
    }
}

const sf::Vector2f & Shield::getPosition() const
{
    return m_position;
}

void Shield::onCollide(const Collidable& other)
{
}




void Shield::ShieldSection::calculatePixelCoord(int x, int y, sf::Vertex & pixel, SectorStyle style)
{
    switch (style) {
    case SectorStyle::Square:
        m_pixels[y * SECT_SIZE + x] = pixel;
        break;

    case SectorStyle::SlopeUp:
        if (SECT_SIZE - y < x) {
            m_pixels[y * SECT_SIZE + x] = pixel;
        }
        break;

    case SectorStyle::SlopeDown:
        if (x < y) {
            m_pixels[y * SECT_SIZE + x] = pixel;
        }
        break;

    case SectorStyle::SlopeUnderUp:
        if (SECT_SIZE - x > y) {
            m_pixels[y * SECT_SIZE + x] = pixel;
        }
        break;

    case SectorStyle::SlopeUnderDown:
        if (x > y) {
            m_pixels[y * SECT_SIZE + x] = pixel;
        }
        break;
    }
}