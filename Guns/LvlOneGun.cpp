//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "LvlOneGun.h"

LvlOneGun::LvlOneGun() {
    speed = {1,1};
    ammo = 1000;
    fireRate = 0.2;
}



void LvlOneGun::fire(sf::Vector2f position) {
    if (fireRateClock.getElapsedTime().asSeconds() > fireRate) {
        if (ammo > 0) {
            auto *bullet = new BasicBullet();
            bullet->setPosition(position);
            bullet->setVelocity(1, 1);
            bullets.push_back(bullet);
            ammo--;
            fireRateClock.restart();
        }
    }
}

void LvlOneGun::update() {
    for (auto &bullet: bullets){
        bullet->update();
    }
}

std::vector<Bullet*> LvlOneGun::getBullets() {
    return bullets;
}

LvlOneGun::~LvlOneGun() {


}

void LvlOneGun::fire(sf::Vector2f position, sf::Vector2f velocity) {
    if (fireRateClock.getElapsedTime().asSeconds() > fireRate) {
        if (ammo > 0) {
            auto *bullet = new BasicBullet();
            bullet->setPosition(position);
            bullet->setVelocity(velocity);
            bullets.push_back(bullet);
            ammo--;
            fireRateClock.restart();
        }
    }

}
