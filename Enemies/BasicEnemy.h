//
// Created by Henrik Ravnborg on 2025-04-04.
//

#ifndef SPEL__BASICENEMY_H
#define SPEL__BASICENEMY_H


#include "Enemy.h"

class BasicEnemy : public Enemy {
public:
    /*
    virtual void update() = 0;

    virtual ~Enemy() = default;

    virtual sf::Vector2f getPosition() = 0;
    virtual void killEnemy() = 0;

    virtual sf::RectangleShape getEnemyShape() = 0;
     */

    BasicEnemy();

    sf::RectangleShape getEnemyShape() override;

    void update() override;

    ~BasicEnemy() override;

    void killEnemy() override;

   



};


#endif //SPEL__BASICENEMY_H
