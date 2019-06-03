#pragma once

#include "../../Framework/Util/Animation.h"
#include "../../Framework/Util/Random.h"
#include "../Collidable.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace SpaceInvaders {
class UFO : public Collidable {
public:
    enum class State { Waiting, Flying, Destroyed };

    UFO(Random<> &rand);

    State getState() const;

    void update(float dt);

    void draw(sf::RenderTarget &window);

    const sf::Vector2f &getPosition() const;
    void onCollide(Collidable &other);

private:
    Random<> &m_rng;

    sf::RectangleShape m_sprite;
    float m_vx;
    State m_state;
    Animation m_animation;

    sf::Sound m_flyingSound;
};
} // namespace SpaceInvaders