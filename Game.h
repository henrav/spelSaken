//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__GAME_H
#define SPEL__GAME_H


#include "Window.h"
#include "Player.h"
#include "map/Map.h"
#include "Enemies/BasicEnemy.h"
#include "map/Blocks/Ground.h"
#include "map/Blocks/Walls/Walls.h"

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
    std::vector<Ground*> grounds;
    std::vector<Ground*> wallsGrounds;
    sf::Clock clock2;
    float fps = 0;
    clock_t deltaTime = 0;
    double  frameRate = 30;
    double  averageFrameTimeMilliseconds = 33.333;

    double clockToMilliseconds(clock_t clock) {
        return static_cast<double>(clock) / CLOCKS_PER_SEC * 1000;
    }


    bool checkAdjecentWalls(int x, int y);

    bool checkWallDistance(sf::RectangleShape &wall);

    void checkWallCollision();

    void handleCollisions();

    void checkBulletWallCollision();

    static bool checkWallDistance(sf::RectangleShape &wall, sf::RectangleShape shape);

    void checkBulletEnemyCollision();

    void cleanUp();

    void drawGrounds();

    bool checkDistanceToWall(Ground *wall, sf::Vector2f pos);
};


#endif //SPEL__GAME_H
