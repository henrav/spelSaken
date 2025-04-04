//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "LvlOneGun.h"
#include "iostream"




void LvlOneGun::fire(sf::Vector2f position) {
    if (fireRateClock.getElapsedTime().asSeconds() > fireRate) {
        if (ammo > 0) {
            auto *bullet = new BasicBullet();
            bullet->setPosition(position);
            bullet->setVelocity(1, 1);
            bullets.emplace_back(bullet);
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

std::vector<Bullet*>& LvlOneGun::getBullets() {
    return bullets;
}

LvlOneGun::~LvlOneGun() {


}

void LvlOneGun::fire(sf::Vector2f position, sf::Vector2f velocity) {
    if (fireRateClock.getElapsedTime().asSeconds() > fireRate) {
        if (ammo > 0) {
            auto *bullet = new BasicBullet();
            bullet->setPosition(position);
            bullet->setVelocity(velocity.x, velocity.y);
            bullet->addDMG(extraDamage);
            std::cout << "Firing bullet with velocity: " << velocity.x << ", " << velocity.y << std::endl;
            bullets.push_back(bullet);
            ammo--;
            fireRateClock.restart();
        }
    }

}
