//
// Created by Henrik Ravnborg on 2025-04-04.
//

#include "Enemy.h"

void Enemy::moveTowardsMoveTo() {

        int xPos = static_cast<int>(enemyShape.getPosition().x / 100);
        int yPos = static_cast<int>(enemyShape.getPosition().y / 100);
        if (xPos == moveToPoint.x && yPos == moveToPoint.y){
            NewPath = true;
        }else{
            int dx = moveToPoint.x - static_cast<int>(enemyShape.getPosition().x / 100);
            int dy = moveToPoint.y - static_cast<int>(enemyShape.getPosition().y / 100);

            double length = std::sqrt(dx * dx + dy * dy);
            if (length > 0){
                float dirX = dx / length;
                float dirY = dy / length;
                move(dirX * speed, dirY * speed);
            }
        }




}
