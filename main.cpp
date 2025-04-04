#include <iostream>
#include <thread>

#include "Game.h"

int main() {
    Game game;
    game.run();
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    return 0;
}
