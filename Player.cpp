//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Player.h"

Player::Player() {
    playerShape.setRadius(10);
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(playerShape.getRadius(), playerShape.getRadius());
    velocity.x = speed;
    velocity.y = speed;
    gun = new LvlOneGun();
}

void Player::move(float x, float y) {
    playerShape.move(x, y);
}

void Player::setPos(float x, float y) {
    playerShape.setPosition(x, y);
}

sf::CircleShape &Player::getCircle() {
    return playerShape;
}

void Player::moveLeft() {
    playerShape.move(-speed, 0);
    velocity.x = -speed;
}

void Player::moveRight() {
    playerShape.move(speed, 0);
    velocity.x = speed;
}

void Player::moveUp() {
    playerShape.move(0, -speed);
    velocity.y = -speed;
}

void Player::moveDown() {
    playerShape.move(0, speed);
    velocity.y = speed;
}

void Player::fire() {
    sf::Vector2f spawnPos = playerShape.getPosition();

    sf::Vector2f bulletVelocity = velocity;

    gun->fire(spawnPos, bulletVelocity);
}

Gun * Player::getGun() {
    return gun;
}

void Player::setGun(Gun *newGun) {
    if (gun){
        delete gun;
    }
    gun = newGun;
}
