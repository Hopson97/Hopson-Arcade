#pragma once

#include <SFML/Graphics.hpp>
#include "../Util/Random.h"

class StarryBackground
{
    public:
        StarryBackground();

        void update(float dt);

        void draw(sf::RenderTarget& renderer);

    private:
        void giveStarRandomStartLocation(sf::Vertex& v);

        std::vector<sf::Vertex> m_stars;

        Random<> m_rng;
};