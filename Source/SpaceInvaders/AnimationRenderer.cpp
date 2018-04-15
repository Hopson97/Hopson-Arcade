#include "AnimationRenderer.h"

namespace SpaceInvaders
{
    AnimationRenderer::AnimationRenderer(int frameWidth, int frameHeight, float entityWidth, float entityHeight, const sf::Texture & spriteSheet)
        : m_frameWidth(frameWidth)
        , m_frameHeight(frameHeight)
    {
        m_entity.setSize({ entityWidth, entityHeight });
        m_entity.setTexture(&spriteSheet);
    }

    void AnimationRenderer::nextFrame()
    {
        m_currentFrame++;
    }

    void AnimationRenderer::renderEntity(sf::RenderTarget & renderer, int type, const sf::Vector2f & position)
    {
        //Calculate texture coords
        int texLeft = (m_currentFrame % 2) * m_frameWidth;
        int texTop = (type * m_frameHeight);

        //Reposition and draw sprite
        m_entity.setPosition(position);
        m_entity.setTextureRect({ texLeft, texTop, m_frameWidth, m_frameHeight });
        renderer.draw(m_entity);
    }
}