//
// Created by Henrik Ravnborg on 2025-05-01.
//

#ifndef SPEL__ENEMYHANDLER_H
#define SPEL__ENEMYHANDLER_H
#include <utility>
#include <iostream>
#include "../map/Blocks/Ground.h"
#include "Enemy.h"
#include "../Player.h"

class EnemyHandler {
public:

    static std::vector<std::pair<int, int>> generateEnemyPos (std::vector<Ground*>& list, float playerx, float playery);

    static void moveEnemies (std::vector<Enemy*>& enemies, Player player, std::vector<Ground*>& ground);

    static std::pair<int, int> moveEnemyCloser (std::vector<Ground*> ground, Player player);

};


#endif //SPEL__ENEMYHANDLER_H
