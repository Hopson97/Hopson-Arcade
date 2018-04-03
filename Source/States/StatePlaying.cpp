#include "StatePlaying.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../Game.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
{
    m_projectileSprite.setSize({ Projectile::WIDTH, Projectile::HEIGHT });
}

void StatePlaying::handleInput()
{
    m_player.input();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        m_shootDelayTimer.getElapsedTime().asSeconds() > 0.5f) {
        auto point = m_player.getGunPosition();
        point.y -= Projectile::HEIGHT;
        point.x -= Projectile::WIDTH / 2.0f;
        m_projectiles.emplace_back(point, Projectile::Type::Rectangle, Projectile::Direction::Up);
        m_shootDelayTimer.restart();
    }
}

void StatePlaying::update(sf::Time deltaTime)
{
    m_player.update(deltaTime.asSeconds());
    for (auto& proj : m_projectiles) {
        proj.update(deltaTime.asSeconds());
    }

    auto collisions = m_invaders.tryCollideWithProjectiles(m_projectiles);
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{
    m_invaders.tryStepInvaders();
}

void StatePlaying::render(sf::RenderTarget& renderer)
{
    m_invaders.drawInvaders(renderer);
    m_player.draw(renderer);
    for (auto& proj : m_projectiles) {
        m_projectileSprite.setPosition(proj.getPosition());
        renderer.draw(m_projectileSprite);
    }
}
