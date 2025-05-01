#include <iostream>
#include <thread>

#include "Game.h"

int main() {
    Game game;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window");
    game.setSFRenderWindow(&window);
    game.run();

    return 0;
}
