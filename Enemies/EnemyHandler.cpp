//
// Created by Henrik Ravnborg on 2025-05-01.
//

#include "EnemyHandler.h"

std::vector<std::pair<int, int>> EnemyHandler::generateEnemyPos(std::vector<Ground*>& list, float playerx, float playery) {
    float x = playerx;
    float y = playery;
    float minxDistance = 5000;
    float minyDistance = 5000;
    float maxxDistance = 15000;
    float maxyDistance = 15000;
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


void EnemyHandler::moveEnemies(std::vector<Enemy*> &enemies, Player player, std::vector<Ground*>& ground,  std::vector<Ground*>& walls) {
    auto playerPos = player.getPos();
    for (auto &enemy : enemies) {
        auto pos = enemy->getPosition();
        auto shape = enemy->getEnemyShape();
        float speed = static_cast<float>(enemy->getSpeed());

        float dx = playerPos.x - pos.x;
        float dy = playerPos.y - pos.y;

        float length = std::sqrt(dx * dx + dy * dy);
        if (length == 0) continue;

        float dirX = dx / length;
        float dirY = dy / length;
        if (length > 10000){
            dirX = dirX * 1000;
            dirY = dirY * 1000;
        }
        enemy->move(dirX * speed, dirY * speed);
    }
}

auto thingy1  (int col, int row){

};

auto heuristic (Pos current, Pos goal){
    int dx = goal.x - current.x;
    int dy = goal.y - current.y;
    return std::sqrt(dx * dx + dy * dy);
};

auto isDestination(Pos current, Pos goal){
    if (current.x == goal.x && current.y == goal.y){
        return true;
    }else{
        return false;
    }
};

void EnemyHandler::testMove(std::vector<Cell> cells, std::pair<int, int> playerPos, std::pair<int, int> startpos) {




}


