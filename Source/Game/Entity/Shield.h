#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "../Collidable.h"

class Projectile;

class Shield : public Collidable
{
    constexpr static int SECT_SIZE = 20;

    enum class SectorStyle
    {
        Square, SlopeUp, SlopeDown, SlopeUnderUp, SlopeUnderDown
    };
    class ShieldSection
    {
        public:
            ShieldSection(float tlX, float tlY, SectorStyle style);

            void draw(sf::RenderTarget& target);

        private:
            void calculatePixelCoord(int x, int y, sf::Vertex& v, SectorStyle style);
            std::array<sf::Vertex, SECT_SIZE * SECT_SIZE> m_pixels;
    };

    public:
        constexpr static int SIZE = SECT_SIZE * 4;

        Shield(float x);

        void draw(sf::RenderTarget& target);

        const sf::Vector2f& getPosition() const;
        void onCollide(const Collidable& other);

    private:
        std::vector<ShieldSection> m_sections;
        sf::Vector2f m_position;
};