//
// Created by Henrik Ravnborg on 2025-05-01.
//

#include "EnemySpawner.h"

std::vector<std::pair<int, int>> EnemySpawner::generateEnemyPos(std::vector<Ground*>& list, float playerx, float playery) {
    float x = playerx;
    float y = playery;
    float minxDistance = 1500;
    float minyDistance = 2000;
    float maxxDistance = 3000;
    float maxyDistance = 3500;
    std::vector<std::pair<int,int>> positions;
    positions.reserve(list.size());

    for (int i = 0; i < list.size(); i++){

        auto pos = list[i]->getSprite().getPosition();

        if (pos.x < x + minxDistance &&
            pos.x > x - minxDistance &&
            pos.y < y + minyDistance &&
            pos.y > y - minyDistance
        ) {
            continue;
        }
        std::cout << "generateEnemyPos " << std::endl;
        if (pos.y > y + maxyDistance ||
            pos.y < y - maxyDistance ||
            pos.x > x + maxxDistance ||
            pos.x < x - maxxDistance
        ){
            continue;
        }

        positions.emplace_back(
                static_cast<int>(pos.x),
                static_cast<int>(pos.y)
        );
    }

    return positions;

}
