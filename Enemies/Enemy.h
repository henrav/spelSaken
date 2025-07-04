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
    float speed;
    float health;
    int width;
    int height;
    bool dead = false;
    bool aggrod = false;
    int aggroRange = 1500;
    int maxChaseDistance = 4000;
    sf::Vector2i moveToPoint = sf::Vector2i (-1, -1);
    sf::Vector2i lastPosBeforeMoveTo = sf::Vector2i (-1000, -1000);
    bool NewPath = true;
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

    void setAggrod (bool value){aggrod = value;}
    bool getAggrod (){return aggrod;}
    int getAggroRange(){return aggroRange;}

    void setChaseDistance(int value){maxChaseDistance = value;}
    int getChaseDistance(){return maxChaseDistance;}

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

    void setMoveTo (int x, int y){moveToPoint.x = x; moveToPoint.y = y;}
    std::pair<int, int> getMoveToPoint (){return {moveToPoint.x, moveToPoint.y};}
    void moveTowardsMoveTo();

    void setLastPos(int x, int y){lastPosBeforeMoveTo.x = x; lastPosBeforeMoveTo.y = y;}
    std::pair<int, int> getLastPosBefore(){return {moveToPoint.x, moveToPoint.y};}

    bool needNewPath(){return NewPath;}
    void setNewPath(bool value){NewPath = value;}

};


#endif //SPEL__ENEMY_H
