//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__BULLET_H
#define SPEL__BULLET_H
#include <SFML/Graphics/CircleShape.hpp>
#include "SFML/Graphics/RectangleShape.hpp"

class Bullet {
protected:
    sf::RectangleShape bulletShape;
    sf::Vector2f velocity;
    float dmg;
    int speed;
    int width;
    int height;

public:
    virtual sf::RectangleShape getBulletShape() = 0;
    virtual void update() = 0;
    virtual ~Bullet() = default;
    virtual void setPosition(sf::Vector2f pos) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual void killBullet() = 0;

    void setVelocity(sf::Vector2f pos) { velocity=pos; }
    void setVelocity(float x, float y) { velocity.x =x; velocity.y=y; }
    sf::Vector2f getVelocity() { return velocity; }

    void setSpeed(int speed) { this->speed = speed; }
    int getSpeed() { return speed; }



    void setDMG(float dmg) { this->dmg = dmg; }
    void addDMG(float dmg) { this->dmg += dmg; }
    float getDMG() { return dmg; }

    void setWidth(int width) { this->width = width; }
    int getWidth() { return width; }

    void setHeight(int height) { this->height = height; }
    int getHeight() { return height; }


};


#endif //SPEL__BULLET_H
