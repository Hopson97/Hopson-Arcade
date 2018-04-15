#pragma once

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Utility class for rendering a large number of entites which share
        the same animation
    */
    class AnimationRenderer
    {
    public:
        AnimationRenderer(int frameWidth, int frameHeight,
            float entityWidth, float entityHeight,
            const sf::Texture& spriteSheet);

        //Changes to the next frame
        void nextFrame();

        //Renders a single entity, using the current animation frame
        void renderEntity(sf::RenderTarget& renderer, int type, const sf::Vector2f& position);

    private:
        sf::RectangleShape m_entity;
        int m_currentFrame;
        const int m_frameWidth;
        const int m_frameHeight;
    };
}