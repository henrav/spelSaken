//
// Created by Henrik Ravnborg on 2025-04-03.
//

#include "Map.h"
#include "stack"
Map::Map() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Initialize the 2D array to true (all walls)
    walls.resize(minHeight, std::vector<bool>(minWidth, true));
    map(20000);
}

void Map::map(int steg) {

    for (int a = 0; a < minHeight; ++a) {
        for (int b = 0; b < minWidth; ++b) {
            walls[a][b] = true;
        }
    }
    col =  20;
    row = 20;
    int nrOfCells = minWidth * minHeight;
    float coverage = 1 / nrOfCells;

    walls[row][col] = false; // carve out the starting cell

    for (int i = 0; i < 100; i++) {
        // Randomly choose a direction: 0 = right, 1 = left, 2 = down, 3 = up
        int direction = std::rand() % 4;
        // Random corridor length between 1 and 5
        int length = 1 + std::rand() % 20;
        if (direction == 0 && lastDirection == 1) {
            int random = std::rand() % 2;
            if (random == 0) {
                direction = 2;
            } else {
                direction = 3;
            }
        } else if (direction == 1 && lastDirection == 0) {
            int random = std::rand() % 2;
            if (random == 0) {
                direction = 2;
            } else {
                direction = 3;
            }
        } else if (direction == 2 && lastDirection == 3) {
            int random = std::rand() % 2;
            if (random == 0) {
                direction = 0;
            } else {
                direction = 1;
            }
        } else if (direction == 3 && lastDirection == 2) {
            int random = std::rand() % 2;
            if (random == 0) {
                direction = 0;
            } else {
                direction = 1;
            }

        }


            switch (direction) {
                case 0: // right

                    digTunnel2(14, 4, 0);
                    lastDirection = 0;
                    break;
                case 1: // left
                    digTunnel2(14, 4, 1);
                    lastDirection = 1;
                    break;
                case 2: // down
                    digTunnel2(14, 4, 2);
                    lastDirection = 2;
                    break;
                case 3: // up
                    digTunnel2(14, 4, 3);
                    lastDirection = 3;

                    // Carve out the cell (set to false)

            }

    }



/*
    std::srand((unsigned)std::time(nullptr));
    while (steg2 < steg){
        //tunnelLeft(5);
        int random = std::rand() % 4;
        int random2 = std::rand() % 10 + 40;
        if (random == 0){
            if (lastDirection == 1){
                random = 2;
            }
        }else if (random == 1){
            if (lastDirection == 0){
                random = 3;
            }
        }
        else if (random == 2){
            if (lastDirection == 3){
                random = 0;
            }
        }else if (random == 3){
            if (lastDirection == 2){
                random = 1;
            }
        }

        switch (random) {
            case 0:
                digTunnel(1, 5, 0);
                lastDirection = 0;
                break;
                /*
            case 1:
                tunnelLeft(random2);
                lastDirection = 1;
                break;
            case 2:
                tunnelUp(random2);
                lastDirection = 2;
                break;
            case 3:
                tunnelDown(random2);
                lastDirection = 3;
                break;
                 */
        }
        /*
        std::cout<<"steg2: " << steg2 << std::endl;
        steg2++;


    }
         /*

}

int Map::getLastDirection() {
    int lastx = stack.top().first;
    int lasty = stack.top().second;

    stack.pop();

    int secondx = stack.top().first;
    int secondy = stack.top().second;

    stack.emplace(lastx, lasty);

    if (lastx == secondx) {
        if (lasty > secondy) {
            return 1; // left
        } else {
            return 2; // right
        }
    } else {
        if (lastx > secondx) {
            return 3; // up
        } else {
            return 4; // down
        }
    }
}


/*
 *  if (col + 2 < minWidth && walls[row][col + 1]) {
                    walls[row][col + 1] = false;
                    stack.emplace(row, col + 1);
                    col++;
                    steg2++;
                }else{
                    if (stack.empty()) {

                        std::pair par = findNearestNeighbour(col, row);
                        walls[par.first][par.second] = false;
                        stack.emplace(par.first, par.second);
                        col = par.first;
                        row = par.second;

                        break;
                    }
                    auto [prevRow, prevCol] = stack.top();
                    stack.pop();
                    row = prevRow;
                    col = prevCol;
                }

                if (row - 2 >= 0 && walls[row - 1][col]) {
                    walls[row - 1][col] = false;
                    stack.emplace(row - 1, col);
                    row--;
                    steg2++;
                }else{
                    if (stack.empty()) {

                        std::pair par = findNearestNeighbour(col, row);
                        walls[par.first][par.second] = false;
                        stack.emplace(par.first, par.second);
                        col = par.first;
                        row = par.second;

                        break;
                    }
                    auto [prevRow, prevCol] = stack.top();
                    stack.pop();
                    row = prevRow;
                    col = prevCol;
                }

                 if (row + 2 < minHeight && walls[row + 1][col]) {
                    walls[row + 1][col] = false;
                    stack.emplace(row + 1, col);
                    row++;
                    steg2++;
                }else{
                    if (stack.empty()) {

                        std::pair par = findNearestNeighbour(col, row);
                        walls[par.first][par.second] = false;
                        stack.emplace(par.first, par.second);
                        col = par.first;
                        row = par.second;

                        break;
                    }
                    auto [prevRow, prevCol] = stack.top();
                    stack.pop();
                    row = prevRow;
                    col = prevCol;
                }
 */

void Map::carveBlock(int centerRow, int centerCol, int halfHeight, int halfWidth) {
    for (int r = centerRow - halfHeight; r <= centerRow + halfHeight; r++) {
        for (int c = centerCol - halfWidth; c <= centerCol + halfWidth; c++) {
            if (r >= 0 && r < minHeight && c >= 0 && c < minWidth) {
                walls[r][c] = false;
            }
        }
    }
}
void Map::setFalse(int row, int col) {
    walls[row][col] = false;
    stack.emplace(row, col);
}

void Map::digTunnel2(int length, int width, int direction){
    switch (direction) {
        case 0:
            if ((row + length) < minWidth - width + 20) {
                for (int i = 0; i < length; i++) {
                    setFalse(row + 1, col);
                    row++;
                    for (int j = 0; j < width; j++) {
                        setFalse(row, col + j);
                        if (col + j + 1 < minHeight) {
                            setFalse(row, col + j + 1);
                        }
                        if (col - j >= 0) {
                            setFalse(row, col - j);
                        }
                    }
                }
            }
            break;
        case 1:
            if ((row - length) > 20 + width) {
                for (int i = 0; i < length; i++) {
                    setFalse(row - 1, col);
                    row--;
                    for (int j = 0; j < width; j++) {
                        setFalse(row, col + j);
                        if (col + j + 1 < minHeight) {
                            setFalse(row, col + j + 1);
                        }
                        if (col - j >= 0) {
                            setFalse(row, col - j);
                        }
                    }
                }
            }
            break;
        case 2:
            if ((col + length) < minHeight - width - 20) {
                for (int i = 0; i < length; i++) {
                    setFalse(row, col + 1);
                    col++;
                    for (int j = 0; j < width; j++) {
                        setFalse(row + j, col);
                        if (row + j + 1 < minWidth) {
                            setFalse(row + j + 1, col);
                        }
                        if (row - j >= 0) {
                            setFalse(row - j, col);
                        }
                    }
                }
            }
            break;
        case 3:
            if ((col - length +5) > width) {
                for (int i = 0; i < length; i++) {
                    setFalse(row, col - 1);
                    col--;
                    for (int j = 0; j < width; j++) {
                        setFalse(row + j, col);
                        if (row + j + 1 < minWidth) {
                            setFalse(row + j + 1, col);
                        }
                        if (row - j >= 0) {
                            setFalse(row - j, col);
                        }
                    }
                }
            }
            break;


    }

}

void Map::digTunnel(int length, int width, int direction){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (r < 0.6){
        r = 0.6;
    }
    int widthen = width * r;
    switch (direction) {
        case 0: // right
            if ((row + length) < minWidth - widthen + 5) {
                for (int i = 0; i < length; i++) {
                    int random = std::rand() % 50;
                    setFalse(row + 1, col);
                    for (int j = 0; j < widthen; j++) {
                        int random = std::rand() % 50;
                        if (col + j < minHeight) {
                            setFalse(row, col + j);
                            stack.emplace(row, col + j);
                            if (random < 20){
                                if (col + j + 1 < minHeight) {
                                    setFalse(row, col + j + 1);
                                    stack.emplace(row, col + j + 1);
                                }
                                if (random < 5){
                                    if (col + j + 2 < minHeight) {
                                        setFalse(row, col + j + 2);
                                        stack.emplace(row, col + j + 2);
                                    }
                                }
                            }
                        }
                        if (col - j >= 0) {
                            setFalse(row, col - j);
                            stack.emplace(row, col - j);
                            if (random > 20 && random < 40){
                                if (col - j - 1 >= 0) {
                                    setFalse(row, col - j - 1);
                                    stack.emplace(row, col - j - 1);
                                }
                                if (random > 35){
                                    if (col - j - 2 >= 0) {
                                        setFalse(row, col - j - 2);
                                        stack.emplace(row, col - j - 2);
                                    }
                                }
                            }
                        }

                    }
                    row++;
                }


            }
            break;
        case 1:
            if ((row - length) > 5 + width) {
                for (int i = 0; i < length; i++) {
                    int random = std::rand() % 50;
                    setFalse(row - 1, col);
                    for (int j = 0; j < widthen; j++) {
                        int random = std::rand() % 50;
                        if (col + j < minHeight) {
                            setFalse(row, col + j);
                            stack.emplace(row, col + j);
                            if (random < 20) {
                                if (col + j + 1 < minHeight) {
                                    setFalse(row, col + j + 1);
                                    stack.emplace(row, col + j + 1);
                                }
                                if (random < 5) {
                                    if (col + j + 2 < minHeight) {
                                        setFalse(row, col + j + 2);
                                        stack.emplace(row, col + j + 2);
                                    }
                                }
                            }
                        }
                        if (col - j >= 5) {
                            setFalse(row, col - j);
                            stack.emplace(row, col - j);
                            if (random > 20 && random < 40) {
                                if (col - j - 1 >= 0) {
                                    setFalse(row, col - j - 1);
                                    stack.emplace(row, col - j - 1);
                                }
                                if (random > 35) {
                                    if (col - j - 2 >= 0) {
                                        setFalse(row, col - j - 2);
                                        stack.emplace(row, col - j - 2);
                                    }
                                }
                            }
                        }

                    }
                    row--;
                }
                break;
                case 2:
                    if ((col + length) < minHeight - width) {
                        for (int i = 0; i < length; i++) {
                            int random = std::rand() % 50;
                            setFalse(row, col + 1);
                            for (int j = 0; j < widthen; j++) {
                                int random = std::rand() % 50;
                                if (row + j < minWidth) {
                                    setFalse(row + j, col);
                                    stack.emplace(row + j, col);
                                    if (random < 20) {
                                        if (row + j + 1 < minWidth) {
                                            setFalse(row + j + 1, col);
                                            stack.emplace(row + j + 1, col);
                                        }
                                        if (random < 5) {
                                            if (row + j + 2 < minWidth) {
                                                setFalse(row + j + 2, col);
                                                stack.emplace(row + j + 2, col);
                                            }
                                        }
                                    }
                                }
                                if (row - j >= 0) {
                                    setFalse(row - j, col);
                                    stack.emplace(row - j, col);
                                    if (random > 20 && random < 40) {
                                        if (row - j - 1 >= 0) {
                                            setFalse(row - j - 1, col);
                                            stack.emplace(row - j - 1, col);
                                        }
                                        if (random > 35) {
                                            if (row - j - 2 >= 0) {
                                                setFalse(row - j - 2, col);
                                                stack.emplace(row - j - 2, col);
                                            }
                                        }
                                    }
                                }

                            }
                            col++;
                        }
                        break;
                        case 3:
                            if ((col - length) > width) {
                                for (int i = 0; i < length; i++) {
                                    int random = std::rand() % 50;
                                    setFalse(row, col - 1);
                                    for (int j = 0; j < widthen; j++) {
                                        int random = std::rand() % 50;
                                        if (row + j < minWidth) {
                                            setFalse(row + j, col);
                                            stack.emplace(row + j, col);
                                            if (random < 20) {
                                                if (row + j + 1 < minWidth) {
                                                    setFalse(row + j + 1, col);
                                                    stack.emplace(row + j + 1, col);
                                                }
                                                if (random < 5) {
                                                    if (row + j + 2 < minWidth) {
                                                        setFalse(row + j + 2, col);
                                                        stack.emplace(row + j + 2, col);
                                                    }
                                                }
                                            }
                                        }
                                        if (row - j >= 0) {
                                            setFalse(row - j, col);
                                            stack.emplace(row - j, col);
                                            if (random > 20 && random < 40) {
                                                if (row - j - 1 >= 0) {
                                                    setFalse(row - j - 1, col);
                                                    stack.emplace(row - j - 1, col);
                                                }
                                                if (random > 35) {
                                                    if (row - j - 2 >= 0) {
                                                        setFalse(row - j - 2, col);
                                                        stack.emplace(row - j - 2, col);
                                                    }
                                                }
                                            }
                                        }

                                    }
                                    col--;
                                }
                            }
                        break;
                    }
            }


    }


}

void Map::tunnelRight(int steps, int width, int length) {
    for (int i = 0; i < steps; i++){
        if (row + 5 < minWidth) {
            digTunnel(10, 5, 0);
        }


/*
        if (row + 2 < minWidth) {
            walls[row + 1 ][col] = false;
            stack.emplace(row + 1, col);
            row++;
            steg2++;
        }
        */
    }

}

int Map::tunnelLeft(int steps) {

    for (int i = 0; i < steps; i++){
        if (row - 4 > 0){
            walls[row - 1][col] = false;
            stack.emplace(row - i, col);
            if (col + 3 < minHeight) {
                walls[row][col + 1] = false;
                stack.emplace(row, col + 1);
            }
            if (col - 3 >= 0) {
                walls[row][col - 1] = false;
                stack.emplace(row, col - 1);
            }
            int random = std::rand() % 50;
            if (random < 20){
                if (col - 3 >= 0) {
                    walls[row][col - 2] = false;
                    stack.emplace(row, col - 2);
                }

            }
            if (random > 20 && random < 40){
                if (col + 3 < minHeight) {
                    walls[row][col + 2] = false;
                    stack.emplace(row, col + 2);
                }
            }
            row--;
            steg2++;
        }
    }



    /*
    if (row - 2 >= 0) {
        walls[row - 1][col] = false;
        stack.emplace(row - 1, col);
        row--;
        steg2++;
    }
     */

}

int Map::tunnelDown(int steps) {

    for (int i = 0; i < steps; i++){
        if (col + 3 < minHeight){
            walls[row][col + 1] = false;
            stack.emplace(row, col + 1);
            if (row + 2 < minWidth) {
                walls[row + 1][col] = false;
                stack.emplace(row + 1, col);
                int extraWidth = std::rand() % 2 + 3;
            }
            if (row - 2 >= 0) {
                walls[row - 1][col] = false;
                stack.emplace(row - 1, col);
            }
            int random = std::rand() % 50;
            if (random < 20){
                if (row - 3 >= 0) {
                    walls[row - 2][col] = false;
                    stack.emplace(row - 2, col);
                }

            }
            if (random > 20 && random < 40){
                if (row + 3 < minWidth) {
                    walls[row + 2][col] = false;
                    stack.emplace(row + 2, col);
                }
            }
            col++;
            steg2++;
        }else{
            break;
        }

    }

    /*
    if (col + 2 < minHeight) {
        walls[row][col + 1] = false;
        stack.emplace(row, col + 1);
        col++;
        steg2++;
    }
     */

}

int Map::tunnelUp(int steps) {

    for (int i = 0; i < steps; i++){
        if (col - 3 > 0){
            walls[row][col - 1] = false;
            stack.emplace(row, col - 1);
            if (row + 2 < minWidth) {
                walls[row + 1][col] = false;
                stack.emplace(row + 1, col);
                int extraWidth = std::rand() % 2 + 3;
            }
            if (row - 2 >= 0) {
                walls[row - 1][col] = false;
                stack.emplace(row - 1, col);
            }
            int random = std::rand() % 50;
            if (random < 20){
                if (row - 3 >= 0) {
                    walls[row - 2][col] = false;
                    stack.emplace(row - 2, col);
                }

            }
            if (random > 20 && random < 40){
                if (row + 3 < minWidth) {
                    walls[row + 2][col] = false;
                    stack.emplace(row + 2, col);
                }
            }
            col--;
            steg2++;
        }else{
            break;
        }
    }

    /*
    if (col - 2 >= 0) {
        walls[row][col - 1] = false;
        stack.emplace(row, col - 1);
        col--;
        steg2++;
    }
     */

}



/**
 *
 * @param x;  x positionen jag vill kolla
 * @param y;  y positionen jag vill kolla
 * @return
 */
int Map::lonleyIsland(int row, int col) {
    int neighbours = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0)
                continue;
            int nRow = row + dr;
            int nCol = col + dc;
            if (walls[nRow][nCol]) {
                neighbours++;
            }
        }
    }
    return neighbours;
}

bool Map::inXBounds(int x) {
    return x >= 0 && x < minHeight;
}

bool Map::inYBounds(int y) {
    return y >= 0 && y < minWidth;
}

bool Map::isWall(int x, int y) { // returnerar true om en wall
    return walls[x][y];
}

bool Map::isEdge(int x, int y) {
    if (x -1  < 0 || x + 1 >= minHeight || y -1  < 0 || y +1 >= minWidth) {
        return false; // Out of bounds
    }
    return walls[x][y];
}

std::pair<int, int> Map::findNearestNeighbour(int x, int y) {
    std::pair<int, int> nearestNeighbour = {0, 0};
    int minDistance = std::numeric_limits<int>::max();

    for (int i = 0; i < minHeight; ++i) {
        for (int j = 0; j < minWidth; ++j) {
            if (walls[i][j]) {
                int distance = std::abs(i - x) + std::abs(j - y);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbour = {i, j};
                }
            }
        }
    }

    return nearestNeighbour;
}

void Map::generateRooms(){
    int nrofRoooms = 10;
    int rand = std::rand() % nrofRoooms;

}





int Map::getHeight() {
    return minHeight;
}

int Map::getWidth() {
    return minWidth;
}

std::vector<std::vector<bool>> Map::getWalls() {
    return walls;
}
