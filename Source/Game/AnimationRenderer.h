#pragma once

#include <SFML/Graphics.hpp>

class AnimationRenderer
{
    public:
        AnimationRenderer(int frameWidth, int frameHeight, 
            float entityWidth, float entityHeight, 
            const sf::Texture& spriteSheet);

        void nextFrame();

        void renderEntity(sf::RenderTarget& renderer, int type, const sf::Vector2f& position);

    private:
        sf::RectangleShape m_entity;
        int m_currentFrame;
        const int m_frameWidth;
        const int m_frameHeight;
};