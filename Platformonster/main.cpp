#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <future>

#include "World.hpp"

int main(void)
{
    int winSizeX = 640, winSizeY = 480;
    sf::RenderWindow win;
    win.create(sf::VideoMode(winSizeX, winSizeY), "");

    World world(win);
    //inits random generator
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
                    //case sf::Event::KeyReleased:
                    /* case sf::Event::MouseButtonPressed:
                    case sf::Event::MouseButtonReleased:
                    //case sf::Event::MouseMoved:
                    case sf::Event::MouseWheelMoved:*/
                case sf::Event::Closed:
                    return 0;
                }


            }

            world.draw(delta += 0.01f);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            win.display();
            win.clear();
        }
    }

}