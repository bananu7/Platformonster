#pragma once
#include "Util.hpp"
#include "Config.hpp"

#include <SFML/System/Vector2.hpp>
typedef sf::Vector2f Point;

class Configurable {
protected:
    Config& config;
    Configurable(Config& config) : config(config) { }
};

namespace sf { class RenderWindow; }

class Drawable : public Configurable {
protected:
    sf::RenderWindow& window;
public:
    virtual void draw() = 0;

    Drawable(Config& config, sf::RenderWindow& window) :
        Configurable(config), window(window)
    {

    }
};

struct Updateable {
    virtual void update(float dt) = 0;
};

class Kinetic 
    : public Updateable
{
protected:
    Point position;
    Point velocity;
    Point acceleration;

public:
    void update(float delta_time) override {
        // Proper way of integrating
        // "stolen" from http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
        velocity += acceleration*delta_time / 2.f;
        position += velocity*delta_time;
        velocity += acceleration*delta_time / 2.f;
    }

    void rawMove(Point delta) {
        position += delta;
    }
};

