//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__LVLONEGUN_H
#define SPEL__LVLONEGUN_H


#include <SFML/System/Vector2.hpp>

#include "Gun.h"

#include "Ammo/BasicBullet.h"


class LvlOneGun: public Gun {

public:
    LvlOneGun();
    void update() override;
    void fire(sf::Vector2f position) override;
    void fire(sf::Vector2f position, sf::Vector2f velocity) override;
    std::vector<Bullet*>& getBullets() override;
    ~LvlOneGun() override;






};


#endif //SPEL__LVLONEGUN_H
