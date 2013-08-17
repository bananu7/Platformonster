#pragma once
#include "Actor.hpp"
#include "Physics.hpp"
#include "Level.hpp"
#include <SFML/Graphics.hpp>

class Player
    : public Drawable
{
    Entity e;    
    Level& level;
public:
    Player(Config& config, sf::RenderWindow& window, Level& level) 
        : Drawable(config, window), level(level)
    {
        e.size = Point(0.8f, 0.8f);
        e.k.position = Point(1.f, 1.f);
    }

    void move(Direction dir) {
        switch (dir) {
        /*case Direction::Down: e.k.rawMove(sf::Vector2f(0, 5.f)); break;
        case Direction::Up: e.k.rawMove(sf::Vector2f(0, -5.f)); break;
        case Direction::Left: e.k.rawMove(sf::Vector2f(-5.f, 0.f)); break;
        case Direction::Right: e.k.rawMove(sf::Vector2f(5.f, 0.f)); break;*/
        case Direction::Down: e.k.velocity = sf::Vector2f(0, 5.f); break;
        case Direction::Up: e.k.velocity = sf::Vector2f(0, -5.f); break;
        case Direction::Left: e.k.velocity = sf::Vector2f(-5.f, 0.f); break;
        case Direction::Right: e.k.velocity = sf::Vector2f(5.f, 0.f); break;
        }
        e = solve(e, level, 0.01f);
    }

    void draw() {
        sf::RectangleShape rectShape;
        Point displaySize = level.toPixelCoordFromTileCoord(e.size);
        rectShape.setSize(displaySize);
        rectShape.setFillColor(sf::Color::Blue);

        Point displayPosition = level.toPixelCoordFromTileCoord(e.k.position);
        rectShape.setPosition(displayPosition);
        window.draw(rectShape);
    }
};
 
