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
struct Pos {
    int x, y;

};

struct Cell {
    Pos position;
    std::vector<Pos> neighbors;


    void addNeighbor(const Pos& p) {
        neighbors.push_back(p);
    }


    const std::vector<Pos>& getNeighbors() const {
        return neighbors;
    }
};

class EnemyHandler {
public:

    static std::vector<std::pair<int, int>> generateEnemyPos (std::vector<Ground*>& list, float playerx, float playery);

    static void moveEnemies (std::vector<Enemy*>& enemies, Player player, std::vector<Ground*>& ground, std::vector<Ground*>& walls);

    static void testMove(std::vector<Cell> cells, std::pair<int,int> playerPos, std::pair<int, int> startpos);

    //static void tjena (std::pair<int,int> playerPos, std::pair<int, int> enemyPos , );



};


#endif //SPEL__ENEMYHANDLER_H
