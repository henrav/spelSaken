//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "BasicBullet.h"

BasicBullet::BasicBullet() {
    bulletShape.setRadius(2);
    velocity.x = 1;
    velocity.y = 1;
    bulletShape.setPosition(0, 0);
}

sf::CircleShape BasicBullet::getBulletShape() {
    return bulletShape;
}


void BasicBullet::update() {
    bulletShape.move(velocity);
}

BasicBullet::~BasicBullet() {

}

void BasicBullet::setPosition(sf::Vector2f pos) {
    bulletShape.setPosition(pos);
}

void BasicBullet::setPosition(float x, float y) {
    bulletShape.setPosition(x, y);
}

sf::Vector2f BasicBullet::getPosition() {
    return sf::Vector2f();
}
