#include "StarryBackground.h"

#include "DisplayInfo.h"

namespace SpaceInvaders
{
    StarryBackground::StarryBackground()
    {
        for (int i = 0; i < 500; i++) {
            sf::Vertex star;
            giveStarRandomStartLocation(star);
            star.position.y -= Display::HEIGHT;
            m_stars.push_back(star);
        }
    }

    void StarryBackground::update(float dt)
    {
        for (auto& star : m_stars) {
            star.position.y -= 250 * dt;
            if (star.position.y <= 0) {
                giveStarRandomStartLocation(star);
            }
        }
    }

    void StarryBackground::draw(sf::RenderTarget & renderer)
    {
        renderer.draw(m_stars.data(), m_stars.size(), sf::Points);
    }

    void StarryBackground::giveStarRandomStartLocation(sf::Vertex & star)
    {
        star.position = { m_rng.getFloatInRange(0, (float)Display::WIDTH),
            m_rng.getFloatInRange((float)Display::HEIGHT, (float)Display::HEIGHT  * 2.0f) };
    }
}