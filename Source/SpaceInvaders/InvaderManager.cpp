#include "InvaderManager.h"

#include <iostream>

#include "../Framework/ResourceManager/ResourceHolder.h"
#include "World.h"

namespace SpaceInvaders
{
    namespace
    {
        const int MAX_INVADERS = 55;
    }

    InvaderManager::InvaderManager(World& world)
        : m_stepGap(sf::seconds(0.5f))
        , m_world(world)
        , m_invaderRenderer(12, 8, Invader::WIDTH, Invader::HEIGHT,
            ResourceHolder::get().textures.get("si/invaders"))
    {
        //Layout of the invaders 
        Invader::Type types[] = {
            Invader::Type::Squid, Invader::Type::Crab, Invader::Type::Crab,
            Invader::Type::Octopus, Invader::Type::Octopus
        };
        //Add invaders into the std::vector
        const int GAP = 10;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 11; x++) {
                //calcuate position for invader
                float invaderX = x * Invader::WIDTH + (GAP  * x * 3) + Invader::WIDTH;
                float invaderY = y * Invader::HEIGHT + (GAP * y) + Invader::HEIGHT * 4;
                m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
            }
        }

        //load sounds
        for (int i = 0; i < 4; i++) {
            m_stepSounds[i].setBuffer(
                ResourceHolder::get().soundBuffers.get("si/fastinvader" + std::to_string(i + 1)));
        }
        m_invaderKilledSound.setBuffer(
            ResourceHolder::get().soundBuffers.get("si/invaderkilled"));


    }

    void InvaderManager::tryStepInvaders()
    {
        //Only step if clock is over timer
        if (m_stepTimer.getElapsedTime() > m_stepGap) {
            m_invaderRenderer.nextFrame();
            //Calculate amount to step
            bool moveDown = false;
            float step = m_isMovingLeft ? -10.0f : 10.0f;
            if (m_moveDown) {
                step *= -1;
            }
            m_stepSounds[m_ticks++ % 4].play();

            //Move the invaders
            for (auto& invader : m_invaders) {
                if (!invader.isAlive()) continue;
                invader.move(step, 0.0f);
                if (m_moveDown) {
                    invader.move(0, Invader::HEIGHT / 2.0f);
                }
                else if (!moveDown) {
                    //Check invader position to see if all should move down
                    moveDown = testInvaderPosition(invader);
                }
            }

            if (m_moveDown) m_isMovingLeft = !m_isMovingLeft;
            m_moveDown = moveDown;
            m_stepTimer.restart();
        }
    }

    void InvaderManager::drawInvaders(sf::RenderTarget& target)
    {
        for (auto& invader : m_invaders) {
            if (!invader.isAlive()) continue;
            m_invaderRenderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
        }
    }

    CollisionResult InvaderManager::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
    {
        CollisionResult result;
        std::vector<sf::Vector2f> collisionPoints;
        for (auto& projectile : projectiles) {
            for (auto& invader : m_invaders) {
                if (!invader.isAlive() || !projectile.isActive())
                    continue;
                if (projectile.tryCollideWith(invader)) {
                    m_aliveInvaders--;
                    m_invaderKilledSound.play();
                    if (m_aliveInvaders == 0) {
                        m_hasAllInvadersBeenAdded = false;
                    }
                    result.second.emplace_back(invader.getPosition());
                    result.first += ((int)invader.getType() + 1) * 100;
                    updateStepDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
    {
        if (m_aliveInvaders == 0) return { -1, -1 };
        //Keep looping until an invader is found
        while (true) {
            auto invaderColumn = random.getIntInRange(0, 10);
            for (int y = 4; y >= 0; y--) {
                int index = y * 11 + invaderColumn;
                auto& invader = m_invaders.at(index);
                if (invader.isAlive()) {
                    return {
                        //transform to below the invader's center
                        invader.getPosition().x + Invader::WIDTH / 2,
                        invader.getPosition().y + Invader::HEIGHT + 5
                    };
                }
            }
        }
    }

    int InvaderManager::getAliveInvadersCount() const
    {
        return m_aliveInvaders;
    }

    //Adds invaders to scene 1 at a time
    void InvaderManager::initAddInvader()
    {
        static sf::Clock delay;
        if (delay.getElapsedTime().asSeconds() > 0.02) {
            m_invaders.at(m_initY * 11 + m_initX).makeAlive();
            m_aliveInvaders++;
            m_initX++;
            if (m_initX == 11) {
                m_initX = 0;
                m_initY--;
            }
            delay.restart();
        }

        if (m_aliveInvaders == MAX_INVADERS) {
            m_hasAllInvadersBeenAdded = true;
            m_initX = 0;
            m_initY = 4;
            updateStepDelay();
        }
    }

    bool InvaderManager::areInvadersAlive() const
    {
        return m_hasAllInvadersBeenAdded;
    }

    void InvaderManager::updateStepDelay()
    {
        m_stepGap = sf::seconds((float)m_aliveInvaders / 90.0f);
    }

    bool InvaderManager::testInvaderPosition(const Invader& invader) const
    {
        if (invader.getPosition().y > Display::HEIGHT - 150) {
            m_world.setGameIsOver();
        }
        return
            (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
            (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
    }
}