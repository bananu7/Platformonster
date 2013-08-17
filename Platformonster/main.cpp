#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <string>

#include "Config.hpp"
#include "Level.hpp"
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
    globalConfig.set("bg_color", sf::Color::Black);

    // Game objects
    Level level(globalConfig, win);
    Player player(globalConfig, win, level);
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
                player.move(Direction::Up);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player.move(Direction::Left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.move(Direction::Right);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player.move(Direction::Down);


            level.draw(0.f);
            player.draw();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            win.display();
            win.clear();
        }
    }

}