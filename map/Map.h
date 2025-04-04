//
// Created by Henrik Ravnborg on 2025-04-03.
//

#ifndef SPEL__MAP_H
#define SPEL__MAP_H


#include "iostream"

class Map {
public:
    Map();
    void map(int steg);
    int getHeight();
    int getWidth();
    std::vector<std::vector<bool>> getWalls();
    bool isWall(int x, int y);
    int steg2;
    int lastDirection = 0;


    int minHeight = 400;
    int minWidth = 400;
    std::vector<std::vector<bool>> walls;
    std::stack<std::pair<int, int>> stack;

    bool isEdge(int x, int y);

    int lonleyIsland(int x, int y);

    std::pair<int, int> findNearestNeighbour(int x, int y);

    void generateRooms();

    void createTunnel(int row, int col);

    bool inXBounds(int x);

    bool inYBounds(int y);

    void createTunnel();

    int col;
    int row;

    void tunnelRight(int steps, int width, int length);

    int tunnelLeft(int steps);

    int tunnelUp(int steps);

    int tunnelDown(int steps);

    int getLastDirection();

    void carveBlock(int centerRow, int centerCol, int halfHeight, int halfWidth);

    void setFalse(int row, int col);



    void digTunnel(int length, int width, int direction);
    void digTunnel2(int length, int width, int direction);


    int getCol(){return col;};
    int getRow(){return row;};
};


#endif //SPEL__MAP_H
