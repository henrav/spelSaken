//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__PLAYER_H
#define SPEL__PLAYER_H


#include <SFML/Graphics.hpp>


#include "Guns/LvlOneGun.h"

class Player {
private:
    sf::RectangleShape playerShape;
    sf::Vector2f velocity;
    float speed = 15;
    Gun* gun;


public:
    Player();
    void update();
    void move(float x, float y);
    void setPos(float x, float y);
    sf::RectangleShape &getRectangle();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void fire();
    void setGun(Gun* gun);
    Gun* getGun();
    sf::Vector2f getPos();


    void setVelocity(int i, int i1);

    int lastMove;

    void resetVelocity();
};


#endif //SPEL__PLAYER_H
