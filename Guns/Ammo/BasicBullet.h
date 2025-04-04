//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__BASICBULLET_H
#define SPEL__BASICBULLET_H
#include "Bullet.h"

class BasicBullet : public Bullet{

public:
    BasicBullet();

    sf::RectangleShape getBulletShape() override;

    void update() override;

    ~BasicBullet() override;

    void setPosition(sf::Vector2f pos) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    void killBullet() override;


    void addVelocity(float d, float d1);


};


#endif //SPEL__BASICBULLET_H
