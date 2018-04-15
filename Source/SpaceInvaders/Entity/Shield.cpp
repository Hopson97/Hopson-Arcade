#include "Shield.h"

#include "../DisplayInfo.h"
#include "Projectile.h"
#include "../../Framework/Util/Random.h"

#include <iostream>

namespace SpaceInvaders
{
    Shield::Shield(float x)
        : Collidable((float)SIZE, (float)SIZE)
        , m_position(x, Display::HEIGHT - 200)
    {
        using Sty = SectorStyle;
        for (float sy = 0; sy < 4; sy++) {
            for (float sx = 0; sx < 4; sx++) {
                Sty style = Sty::Square;
                int xP = (int)sx;
                int yP = (int)sy;
                if (xP == 0 && yP == 0) style = Sty::SlopeUp;
                if (xP == 3 && yP == 0) style = Sty::SlopeDown;
                if (xP == 1 && yP == 3) style = Sty::SlopeUnderUp;
                if (xP == 2 && yP == 3) style = Sty::SlopeUnderDown;

                m_sections.emplace_back(x + sx * SECT_SIZE,
                    m_position.y + sy * SECT_SIZE, style);
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

    Shield::ShieldSection& Shield::getSection(int x, int y)
    {
        return m_sections[y * 4 + x];
    }

    void Shield::destroyPoint(float relX, float relY)
    {
        //Test for out of bounds
        if (relX < 0 || relX >= SIZE ||
            relY < 0 || relY >= SIZE) return;

        //Get section this is inside of
        int xIndex = (int)relX / SECT_SIZE;
        int yIndex = (int)relY / SECT_SIZE;
        auto& section = getSection(xIndex, yIndex);
        auto& sectionPos = section.getPosition();

        //Transform to find the pixel coordinate
        float sectionTopLeftX = sectionPos.x - m_position.x;
        float sectionTopLeftY = sectionPos.y - m_position.y;
        float pixelX = relX - sectionTopLeftX;
        float pixelY = relY - sectionTopLeftY;

        //DESTROY
        section.destroyArea((int)pixelX, (int)pixelY);
    }


    bool Shield::isTouching(const Projectile& projectile)
    {
        static Random<> rand;
        if (projectile.getBox().intersects(getBox())) {
            for (auto& sector : m_sections) {
                auto result = sector.isTouching(projectile);
                if ((int)result.x == -1)
                    continue;
                else { //This means the projectile is touching the shield

                    //Get coordinate of collision point relative to top left of sheild
                    result.x -= m_position.x;
                    result.y -= m_position.y;

                    //Destory around point of collision
                    for (int y = -3; y < 3; y++) {
                        for (int x = -3; x < 3; x++) {
                            float newRelativeX = result.x + x * 2;
                            float newRelativeY = result.y + y * 2;
                            destroyPoint(newRelativeX, newRelativeY);
                        }
                    }

                    //blast damge
                    float radius = 12.0f;
                    for (int i = 0; i < 35; i++) {
                        float newRelativeX = result.x + rand.getFloatInRange(-radius, radius);
                        float newRelativeY = result.y + rand.getFloatInRange(-radius, radius);
                        destroyPoint(newRelativeX, newRelativeY);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    Shield::ShieldSection::ShieldSection(float tlX, float tlY, SectorStyle style)
        : Collidable((float)SECT_SIZE, (float)SECT_SIZE)
        , m_position({ tlX, tlY })
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

    const sf::Vector2f & Shield::ShieldSection::getPosition() const
    {
        return m_position;
    }

    sf::Vector2f Shield::ShieldSection::isTouching(const  Projectile & other)
    {
        for (auto& px : m_pixels) {
            if (other.getBox().contains(px.position) && px.color == sf::Color::Green) {
                return px.position;
            }
        }
        return { -1, -1 };
    }

    //Blacks out an area around the inputted point
    void Shield::ShieldSection::destroyArea(int x, int y)
    {
        for (int oY = -2; oY <= 2; oY++) {
            for (int oX = -2; oX <= 2; oX++) {
                int newX = x + oX;
                int newY = y + oY;
                if (newX < 0 || newX >= SECT_SIZE ||
                    newY < 0 || newY >= SECT_SIZE) continue;
                m_pixels[newY * SECT_SIZE + newX].color = sf::Color::Black;
            }
        }
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
}