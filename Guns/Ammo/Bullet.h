//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__BULLET_H
#define SPEL__BULLET_H
#include <SFML/Graphics/CircleShape.hpp>


class Bullet {
protected:
    sf::CircleShape bulletShape;
    sf::Vector2f velocity;
    float dmg;
public:
    virtual sf::CircleShape getBulletShape() = 0;
    virtual void update() = 0;
    virtual ~Bullet() = default;
    virtual void setPosition(sf::Vector2f pos) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2f getPosition() = 0;

    void setVelocity(sf::Vector2f pos) { velocity=pos; }
    void setVelocity(float x, float y) { velocity.x =x; velocity.y=y; }
    sf::Vector2f getVelocity() { return velocity; }



    void setDMG(float dmg) { this->dmg = dmg; }
    float getDMG() { return dmg; }


};


#endif //SPEL__BULLET_H
