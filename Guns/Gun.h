//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__GUN_H
#define SPEL__GUN_H


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <ios>
#include <vector>
class Bullet;


class Gun {
public:
    virtual ~Gun() = default;
    virtual void fire(sf::Vector2f position) = 0;
    virtual void update() = 0;
    virtual std::vector<Bullet*> getBullets() = 0;
    virtual void fire(sf::Vector2f position, sf::Vector2f velocity) = 0;

    float getAmmo() const { return ammo; }
    void setAmmo(float ammo) { ammo = ammo; }

    float getFireRate() const { return fireRate; }
    void setFireRate(float rate) { fireRate = rate; }

    sf::Vector2f getSpeed() const {return speed;}
    void setSpeed(sf::Vector2f inSpeed){ speed = inSpeed;};
    void setSpeed(float x, float y){speed.x = x; speed.y = y;}


protected:
    float ammo = 10;
    float fireRate = 1.0f;
    sf::Vector2f speed = {1,1};
    sf::Clock fireRateClock;
    std::vector<Bullet*> bullets;
};


#endif //SPEL__GUN_H
