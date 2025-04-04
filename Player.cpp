//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Player.h"

Player::Player() {
    playerShape.setSize(sf::Vector2f(50, 50));
    playerShape.setFillColor(sf::Color::Red);
    velocity.x = 1;
    velocity.y = 0;
    gun = new LvlOneGun();
}

void Player::move(float x, float y) {
    playerShape.move(x, y);
}

void Player::setPos(float x, float y) {
    playerShape.setPosition(x, y);
}

sf::RectangleShape &Player::getRectangle() {
    return playerShape;
}

void Player::moveLeft() {
    playerShape.move(-speed, 0);
    velocity.x = -1;
    lastMove = 1;
}

void Player::moveRight() {
    playerShape.move(speed, 0);
    velocity.x = 1;
    lastMove = 2;
}

void Player::moveUp() {
    playerShape.move(0, -speed);
    velocity.y = -1;
    lastMove = 3;
}

void Player::moveDown() {
    playerShape.move(0, speed);
    velocity.y = 1;
    lastMove = 4;
}

void Player::fire() {
    sf::Vector2f spawnPos = playerShape.getPosition();

    sf::Vector2f bulletVelocity = velocity;

    gun->fire(spawnPos, bulletVelocity);
}

Gun* Player::getGun() {
    return gun;
}

void Player::setGun(Gun *newGun) {
    if (gun){
        delete gun;
    }
    gun = newGun;
}

sf::Vector2f Player::getPos() {
    return playerShape.getPosition();
}

void Player::setVelocity(int i, int i1) {
    velocity.x = i;
    velocity.y = i1;
}

void Player::resetVelocity() {
    switch (lastMove) {
        case 1: // left
            velocity.x = -1;
            velocity.y = 0;
            break;

        case 2: // right
            velocity.x = 1;
            velocity.y = 0;
            break;

        case 3: // up
            velocity.x = 0;
            velocity.y = -1;
            break;

        case 4: // down
            velocity.x = 0;
            velocity.y = 1;
            break;


    }
}
