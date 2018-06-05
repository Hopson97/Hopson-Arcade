#include "GameSelect.h"

#include "../../Framework/ResourceManager/ResourceHolder.h"
#include "../../SpaceInvaders/States/StateMainMenu.h"

GameSelect::GameSelect(const std::string& name)
{
    m_container.setSize({ WIDTH, HEIGHT });
    m_thumbnail.setSize({ HEIGHT, HEIGHT });

    m_container.setOutlineThickness(2);
    m_container.setOutlineColor({ 100, 100, 100 });
    m_container.setFillColor({ 200, 200, 200 });

    m_thumbnail.setOutlineThickness(1);
    m_thumbnail.setOutlineColor({ 100, 100, 100 });
    m_thumbnail.setTexture(&ResourceHolder::get().textures.get("thumbnails/" + name));
}

bool GameSelect::isClicked(const sf::Vector2i& mousePositon)
{
    return m_container
        .getGlobalBounds()
        .contains((float)mousePositon.x, (float)mousePositon.y);
}

void GameSelect::setPosition(const sf::Vector2f position)
{
    m_container.setPosition(position);
    m_thumbnail.setPosition(position);
}

void GameSelect::draw(sf::RenderTarget& renderer)
{
    renderer.draw(m_container);
    renderer.draw(m_thumbnail);
}

SpaceInvadersSelect::SpaceInvadersSelect(const std::string & name)
:   GameSelect(name) { }

std::unique_ptr<StateBase> SpaceInvadersSelect::getInitState(Game& game)
{
    return std::make_unique<SpaceInvaders::StateMainMenu>(game);
}
