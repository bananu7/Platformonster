#pragma once
#include "Util.hpp"
#include "Config.hpp"

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

