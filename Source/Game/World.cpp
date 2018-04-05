#include "World.h"
#include "../ResourceManager/ResourceHolder.h"

World::World()
:    m_projectileRenderer(4, 8, Projectile::WIDTH, Projectile::HEIGHT,
    ResourceHolder::get().textures.get("projectile"))
{
    m_explodeShape.setSize({ 52, 28 });
    m_explodeShape.setTexture(&ResourceHolder::get().textures.get("explosion"));
}

void World::input()
{
    if (m_player.isAlive()) {
        m_player.input();
        playerProjectileInput();
    } 
    else {
        m_player.tryRevive();
    }
}

int World::update(float dt)
{
    int score = 0;
    m_player.update(dt);
    if (m_player.isAlive()) {
        m_invaders.tryStepInvaders();
        enemyProjectileFire();

        //pair of score gained and points of collision list
        auto collisionResult = getCollisionResult(dt);
        if (collisionResult.second.size() > 0) {
            score += collisionResult.first;
            for (auto& point : collisionResult.second) {
                m_explosions.emplace_back(point);
            }
        }
    }

    for (auto itr = m_explosions.begin(); itr != m_explosions.end();) {
        if (itr->isLifeOver()) {
            itr = m_explosions.erase(itr);
        }
        else {
            itr++;
        }
    }


    return score;
}

void World::draw(sf::RenderTarget & target)
{
    m_invaders.drawInvaders(target);
    m_player.draw(target);

    if (m_animTimer.getElapsedTime().asSeconds() > 0.2) {
        m_projectileRenderer.nextFrame();
        m_animTimer.restart();
    }

    for (auto& proj : m_projectiles) {
        m_projectileRenderer.renderEntity(target, (int)proj.getType(), proj.getPosition());
    }

    for (auto& exp : m_explosions) {
        m_explodeShape.setPosition(exp.getPosition());
        target.draw(m_explodeShape);
    }
}

const Player & World::getPlayer() const
{
    return m_player;
}

//TODO GENERALISE THESE TWO FUNCTIONS VV
void World::playerProjectileInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        m_playerShotClock.getElapsedTime().asSeconds() > 0.5f) {
        auto point = m_player.getGunPosition();
        point.y -= Projectile::HEIGHT;
        point.x -= Projectile::WIDTH / 2.0f;
        m_projectiles.emplace_back(point, Projectile::Type::Rectangle, Projectile::Direction::Up);
        m_playerShotClock.restart();
    }
}

void World::enemyProjectileFire()
{
    if (m_invaderShotClock.getElapsedTime().asSeconds() >= 0.5 &&
        m_rng.getIntInRange(0, 25) == 2) {
        auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
        auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
        m_projectiles.emplace_back(point, type, Projectile::Direction::Down);
        m_invaderShotClock.restart();
    }
}

CollisionResult World::getCollisionResult(float dt)
{
    auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
    updateProjectiles(dt, result.second);
    return result;
}

void World::updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints)
{
    for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
        auto& projectile = *itr;
        if (!projectile.isActive()) {
            itr = m_projectiles.erase(itr);
        }
        else {
            //Test for player getting hit 
            if (projectile.tryCollideWith(m_player)) {
                collisionPoints.emplace_back(m_player.getGunPosition());
                m_projectiles.clear();
                return;
            }
            projectile.update(dt);
            itr++;
        }
    }
}
