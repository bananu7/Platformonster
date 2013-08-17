#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <string>

#include "Config.hpp"
#include "World.hpp"
#include "Player.hpp"

int main(void)
{
    // Window
    int winSizeX = 800, winSizeY = 600;
    sf::RenderWindow win;
    win.create(sf::VideoMode(winSizeX, winSizeY), "");

    // Config
    Config globalConfig;
    globalConfig.set("player_hp", 100);
    globalConfig.set("bg_color", sf::Color(sf::Color(20, 100, 20)));

    // Game objects
    World world(globalConfig, win);
    Player player(globalConfig, win);
    sf::Clock timer;

    float delta = 0.f;

    while (true)
    {
        while (true)
        {
            sf::Event event;

            while (win.pollEvent(event))
            {
                switch (event.type)
                {
                    //case sf::Event::KeyPressed:
                    /* case sf::Event::MouseButtonPressed:
                    case sf::Event::MouseButtonReleased:
                    //case sf::Event::MouseMoved:
                    case sf::Event::MouseWheelMoved:*/
                case sf::Event::Closed:
                    return 0;
                }
            }

            // realtime input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player.rawMove(sf::Vector2f(0, -5.f));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player.rawMove(sf::Vector2f(-5.f, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.rawMove(sf::Vector2f(5.f, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player.rawMove(sf::Vector2f(0, 5.f));


            world.draw(0.f);
            player.draw();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            win.display();
            win.clear();
        }
    }

}