#pragma once
#include "Actor.hpp"
#include <SFML/Graphics.hpp>

class Player
    : public Kinetic
    , public Drawable
{
public:
    Player(Config& config, sf::RenderWindow& window) 
        : Drawable(config, window)
    {
        position = Point(20.f, 20.f);
    }

    void draw() {
        sf::RectangleShape rectShape;
        rectShape.setSize(sf::Vector2f(50, 100));
        rectShape.setFillColor(sf::Color::Blue);

        rectShape.setPosition(position);
        window.draw(rectShape);
    }
};
 
