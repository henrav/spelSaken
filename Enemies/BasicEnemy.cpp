//
// Created by Henrik Ravnborg on 2025-04-04.
//

#include "BasicEnemy.h"

BasicEnemy::BasicEnemy() {
    // enkelt inte farlig gubbe
    /*
     *    sf::RectangleShape enemyShape;
    sf::Vector2f velocity;
    float dmg;
    int speed;
    float health;
    int width;
    int height;

     */

    enemyShape.setSize(sf::Vector2f(50, 50));
    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setPosition(0, 0);
    velocity.x = 0;
    velocity.y = 0;
    dmg = 10;
    speed = 0.5;
    health = 100;
    aggroRange = 4000;
    maxChaseDistance = 10000;



}

sf::RectangleShape BasicEnemy::getEnemyShape() {
    return enemyShape;
}

void BasicEnemy::update() {
    enemyShape.move(velocity.x * speed, velocity.y * speed);
}

void BasicEnemy::killEnemy() {
    enemyShape.setPosition(-100, -100);
    velocity.x = 0;
    velocity.y = 0;
    health = 0;
    speed = 0;
    dmg = 0;
    width = 0;
    height = 0;

}



BasicEnemy::~BasicEnemy() {

}
