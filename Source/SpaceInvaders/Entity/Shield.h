#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "../Collidable.h"

namespace SpaceInvaders
{
    class Projectile;

    class Shield : private Collidable
    {
        constexpr static int SECT_SIZE = 20;

        enum class SectorStyle
        {
            Square, SlopeUp, SlopeDown, SlopeUnderUp, SlopeUnderDown
        };
        class ShieldSection : public Collidable
        {
        public:
            ShieldSection(float tlX, float tlY, SectorStyle style);

            void draw(sf::RenderTarget& target);

            const sf::Vector2f& getPosition() const;
            void onCollide(Collidable& other) {}

            sf::Vector2f isTouching(const Projectile& other);

            void destroyArea(int x, int y);

        private:
            void calculatePixelCoord(int x, int y, sf::Vertex& v, SectorStyle style);
            std::array<sf::Vertex, SECT_SIZE * SECT_SIZE> m_pixels;
            sf::Vector2f m_position;
        };

    public:
        constexpr static int SIZE = SECT_SIZE * 4;

        Shield(float x);

        void draw(sf::RenderTarget& target);
        bool isTouching(const Projectile& projectile);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other) {}

    private:
        ShieldSection & getSection(int x, int y);

        void destroyPoint(float relX, float relY);

        std::vector<ShieldSection> m_sections;
        sf::Vector2f m_position;
    };
}