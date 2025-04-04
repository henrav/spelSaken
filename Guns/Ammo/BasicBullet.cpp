//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "BasicBullet.h"

BasicBullet::BasicBullet() {
    bulletShape.setSize(sf::Vector2f(9, 9));
    speed = 9;
    bulletShape.setPosition(0, 0);
    velocity.x = 1;
    velocity.y = 1;
    dmg = 1;
}

sf::RectangleShape BasicBullet::getBulletShape() {
    return bulletShape;
}


void BasicBullet::update() {
    bulletShape.move(velocity.x * speed , velocity.y * speed);
}

BasicBullet::~BasicBullet() {
    // Destructor implementation
    // You might want to clean up resources here if needed
    // For example, if you dynamically allocated memory, delete it here
    // But in this case, we are not dynamically allocating anything in BasicBullet
    // So we can leave it empty or add a comment

    // Destructor is empty because we are not dynamically allocating any resources

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

void BasicBullet::killBullet() {


}

void BasicBullet::addVelocity(float d, float d1) {
    velocity.x += d;
    velocity.y += d1;
}
