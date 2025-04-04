//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__GAME_H
#define SPEL__GAME_H


#include "Window.h"
#include "Player.h"
#include "map/Map.h"
#include "Enemies/BasicEnemy.h"
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
    float startX = 0;
    float startY = 0;
    Map mappen;
    std::vector<sf::RectangleShape> walls;
    std::vector<Enemy*> enemies;


    bool checkAdjecentWalls(int x, int y);

    bool checkWallDistance(sf::RectangleShape &wall);

    void checkWallCollision();

    void handleCollisions();

    void checkBulletWallCollision();

    static bool checkWallDistance(sf::RectangleShape &wall, sf::RectangleShape shape);

    void checkBulletEnemyCollision();

    void cleanUp();
};


#endif //SPEL__GAME_H
