//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__GAME_H
#define SPEL__GAME_H


#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "map/Map.h"
class Map;

class Game {
public:
    Game();
    void run();
    sf::Clock tickRate;
    void drawWalls();
    void generateWalls();

private:
    Player player;
    void keyProcessing();
    void update();
    void render();
    sf::RenderWindow window;
    sf::View view;
    sf::RectangleShape stone;
    float startX = 0;
    float startY = 0;
    Map mappen;
    std::vector<sf::RectangleShape> walls;


    bool checkAdjecentWalls(int x, int y);
};


#endif //SPEL__GAME_H
