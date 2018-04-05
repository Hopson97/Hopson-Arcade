#include "StatePlaying.h"

#include "../Game.h"

#include "../ResourceManager/ResourceHolder.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
, m_projectileRenderer  (4, 8, Projectile::WIDTH, Projectile::HEIGHT,
    ResourceHolder::get().textures.get("projectile"))
{
}

void StatePlaying::handleInput()
{
    m_player.input();

    //Fire projectiles
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

    //Get points of collisions and increase score if one is hit
    auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
    auto& collisions = result.second;
    m_score += result.first;
    //update the projectiles
    for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
        auto& projectile = *itr;
        if (!projectile.isActive()) {
            itr = m_projectiles.erase(itr);
        }
        else {
            if (projectile.tryCollideWith(m_player)) {
                collisions.emplace_back(m_player.getGunPosition());
            }
            projectile.update(deltaTime.asSeconds());
            itr++;
        }
    }
    
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{
    m_invaders.tryStepInvaders();

    //Try and shoot a projectile from an enemy positions
    if (m_invaderShotDelayTimer.getElapsedTime().asSeconds() >= 0.5 && 
        m_rng.getIntInRange(0, 25) == 2) {
        auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
        auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
        m_projectiles.emplace_back(point, type, Projectile::Direction::Down);
        m_invaderShotDelayTimer.restart();
    }
}
void StatePlaying::render(sf::RenderTarget& renderer)
{
    m_invaders.drawInvaders(renderer);
    m_player.draw(renderer);

    if (m_projectileAnimTimer.getElapsedTime().asSeconds() >= 0.1) {
        m_projectileRenderer.nextFrame();
        m_projectileAnimTimer.restart();
    }

    for (auto& proj : m_projectiles) {
        m_projectileRenderer.renderEntity(renderer, (int)proj.getType(), proj.getPosition());
    }
}
