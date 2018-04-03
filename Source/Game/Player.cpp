#include "Player.h"
#include "../DisplayInfo.h"

Player::Player()
{
    m_sprite.setSize({ 44, 32 });
    m_sprite.setPosition({ Display::WIDTH / 2, Display::HEIGHT - 40 });
}

void Player::input()
{
    using Key = sf::Keyboard::Key;
    auto keyDown = [](sf::Keyboard::Key k) {
        return sf::Keyboard::isKeyPressed(k);
    };

    float speed = 5;
    if (keyDown(Key::A)) {

    }
    else if (keyDown(Key::D)) {

    }

    if (keyDown(Key::Space)) {

    }
}

void Player::update(float dt)
{
    m_sprite.move(m_velocity);
    m_velocity *= 0.95f;
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(m_sprite);
}
