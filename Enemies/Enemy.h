//
// Created by Henrik Ravnborg on 2025-04-04.
//

#ifndef SPEL__ENEMY_H
#define SPEL__ENEMY_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Enemy {
protected:
    sf::RectangleShape enemyShape;
    sf::Vector2f velocity;
    float dmg;
    int speed;
    float health;
    int width;
    int height;
    bool dead = false;

public:

    virtual void update() = 0;

    virtual ~Enemy() = default;

    virtual void killEnemy() = 0;

    virtual sf::RectangleShape getEnemyShape() = 0;



    void takeDamage(float damage){
        health -= damage;
        if (health <= 0) {
            killEnemy();
            dead = true;
        }
    }

    void setVelocity(sf::Vector2f pos) { velocity = pos; }
    void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }
    sf::Vector2f getVelocity() { return velocity; }

    void setSpeed(int speed) { this->speed = speed; }
    int getSpeed() { return speed; }

    void setDMG(float dmg) { this->dmg = dmg; }
    float getDMG() { return dmg; }

    void setHealth(float health) { this->health = health; }
    float getHealth() { return health; }

    void setDead(bool dead) { this->dead = dead; }
    bool isDead() { return dead; }

    void setWidth(int width) { this->width = width; }
    int getWidth() { return width; }

    void setPosition(float x, float y) { enemyShape.setPosition(x, y); }
    void setPosition(sf::Vector2f pos) { enemyShape.setPosition(pos); }
    sf::Vector2f getPosition() { return enemyShape.getPosition(); }

    void moveLeft(float x) { enemyShape.move(-x, 0); velocity.x = -x; }
    void moveRight(float x) { enemyShape.move(x, 0); velocity.x = x; }
    void moveUp(float y) { enemyShape.move(0, -y); velocity.y = -y; }
    void moveDown(float y) { enemyShape.move(0, y); velocity.y = y; }
    void move(float x, float y){enemyShape.move(x, y);}



};


#endif //SPEL__ENEMY_H
