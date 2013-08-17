#pragma once
#include "Config.hpp"

class World {
    std::vector<sf::Color> data;
    int sizeX, sizeY;
    int displaySizeX, displaySizeY;
    float tileSizeX, tileSizeY;
    sf::RenderWindow& window;
    Config& config;

    sf::Color& get(int x, int y) { return data[sizeY * x + y]; }

public:
    void drawBlock(float x, float y, sf::Color c){
        sf::RectangleShape rectShape;
        rectShape.setSize(sf::Vector2f(tileSizeX, tileSizeY));
        rectShape.setFillColor(c);

        rectShape.setPosition(sf::Vector2f(x, y));
        window.draw(rectShape);
    }

    void draw(float deltaInWorld) {
        float pixelOffsetX = (deltaInWorld - std::floor(deltaInWorld)) * tileSizeX;
        int tileOffsetX = static_cast<int>(std::floor(deltaInWorld));

        for (int x = 0; x < displaySizeX; ++x){
            for (int y = 0; y < displaySizeY; ++y){
                auto color = get(x + tileOffsetX, y);

                float xPos = (x * tileSizeX) - pixelOffsetX;
                float yPos = (y * tileSizeY);

                drawBlock(xPos, yPos, color);
            }
        }
    }

    World(Config& config, sf::RenderWindow& win) : sizeX(20), sizeY(5), window(win), config(config) {
        int windowSizeX = win.getSize().x, windowSizeY = win.getSize().y;
        tileSizeX = windowSizeX / 10; //fixed 10 tiles in window
        tileSizeY = windowSizeY / sizeY;

        displaySizeX = 10;
        displaySizeY = sizeY;

        auto bgColor = config.get<sf::Color>("bg_color").get_value_or(sf::Color::Black);

        data = std::vector<sf::Color>(sizeX * sizeY, bgColor);
        
        for (int i = 0; i < std::min(sizeX, sizeY); ++i)
            get(i, -i) = sf::Color(20, 120, 20);

        for (int i = 0; i < sizeX; ++i)
            get(i, 0) = sf::Color(20, 120, 20);;
    }
};
