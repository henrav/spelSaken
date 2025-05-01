//
// Created by Henrik Ravnborg on 2025-05-01.
//

#ifndef SPEL__ENEMYSPAWNER_H
#define SPEL__ENEMYSPAWNER_H
#include <utility>
#include <iostream>
#include "../map/Blocks/Ground.h"
class EnemySpawner {
public:

    static std::vector<std::pair<int, int>> generateEnemyPos (std::vector<Ground*>& list, float playerx, float playery);

};


#endif //SPEL__ENEMYSPAWNER_H
