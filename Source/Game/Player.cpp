#include "Player.h"
#include "../DisplayInfo.h"
#include "../ResourceManager/ResourceHolder.h"

Player::Player()
{
    m_sprite.setSize({ 44, 32 });
    m_sprite.setPosition({ Display::WIDTH / 2, Display::HEIGHT - 40 });
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
    m_sprite.move(m_velocity * dt);
    m_velocity *= 0.95f;
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
