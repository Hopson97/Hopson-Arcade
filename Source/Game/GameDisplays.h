#pragma once

#include <SFML/Graphics.hpp>

//All defined in States/PlayingState.cpp for now
struct DisplayText
{
    DisplayText();
    sf::Text text;
};

class LifeDisplay
{
public:
    LifeDisplay();

    void draw(sf::RenderTarget& window, int lives);

private:
    DisplayText m_label;
    sf::RectangleShape m_lifeStamp;
};

class ScoreDisplay
{
public:
    ScoreDisplay();

    void update(int newScore);

    void draw(sf::RenderTarget& target);

private:
    DisplayText m_label;

};