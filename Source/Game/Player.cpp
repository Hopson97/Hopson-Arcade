#include "Player.h"
#include "../DisplayInfo.h"
#include "../ResourceManager/ResourceHolder.h"

namespace {
    constexpr float BASE_Y = (float)Display::HEIGHT - 40.0f;
}

Player::Player()
{
    m_sprite.setSize({ 44, 32 });
    m_sprite.setPosition({ Display::WIDTH / 2, BASE_Y });
    m_sprite.setTexture(&ResourceHolder::get().textures.get("player"));
}

void Player::input()
{
    using Key = sf::Keyboard::Key;
    auto keyDown = [](sf::Keyboard::Key k) {
        return sf::Keyboard::isKeyPressed(k);
    };

    float speed = 20;
    if (keyDown(Key::A)) {
        m_velocity.x -= speed;
    }
    else if (keyDown(Key::D)) {
        m_velocity.x += speed;
    }
}

void Player::update(float dt)
{
    auto w = m_sprite.getGlobalBounds().width;
    m_sprite.move(m_velocity * dt);
    m_velocity *= 0.95f;
    if (m_sprite.getPosition().x <= 0) {
        m_velocity.x = 1.0f;
        m_sprite.setPosition(1.0f, BASE_Y);
    }
    else if (m_sprite.getPosition().x + w >= Display::WIDTH) {
        m_velocity.x = -1.0f;
        m_sprite.setPosition(Display::WIDTH - 1.0f - w, BASE_Y);
    }
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(m_sprite);
}

sf::Vector2f Player::getGunPosition() const
{
    return 
    {
        m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
        m_sprite.getPosition().y
    };
}
