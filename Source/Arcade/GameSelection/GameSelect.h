#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../../Framework/States/StateBase.h"

class GameSelect
{
    public:
        constexpr static float WIDTH = 512;
        constexpr static float HEIGHT = 256;

        GameSelect(const std::string& name);
        bool isClicked(const sf::Vector2i& mousePositon);

        void setPosition(const sf::Vector2f position);
        void draw(sf::RenderTarget& renderer);

        virtual std::unique_ptr<StateBase> getInitState(Game& game) = 0;

    private:
        sf::RectangleShape m_container;
        sf::RectangleShape m_thumbnail;
};

struct SpaceInvadersSelect : public GameSelect
{
    SpaceInvadersSelect(const std::string& name);
    std::unique_ptr<StateBase> getInitState(Game& game) override;
};