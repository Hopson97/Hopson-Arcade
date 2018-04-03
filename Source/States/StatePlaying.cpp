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
    auto collisions = m_invaders.tryCollideWithProjectiles(m_projectiles);

    //update the projectiles
    for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
        auto& projectile = *itr;
        if (!projectile.isActive()) {
            itr = m_projectiles.erase(itr);
            if (projectile.tryCollideWith(m_player)) {
                collisions.emplace_back(m_player.getGunPosition());
            }
        }
        else {
            projectile.update(deltaTime.asSeconds());
            itr++;
        }
    }
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
