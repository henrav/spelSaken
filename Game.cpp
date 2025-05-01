//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Game.h"
#include "thread"
#include "map/Blocks/BasicGround.h"
#include "map/Blocks/Walls/Walls.h"
#include <mutex>
#include <iostream>
using namespace std;



Game::Game()

{
    sf::ContextSettings settings;
    tickRate.restart();


}


void Game::run() {
    sf::Vector2f vector(1000, 1000);
    //sf::Thread thread(&Game::render, this);
    generateWalls();
    view = sf::View(sf::FloatRect(0, 0, 1920.f, 1080.f));
    window->setView(view);
    player.setPos( mappen.getRow() * 100,  mappen.getCol() * 100 );
    window->setVerticalSyncEnabled(true);
    view.zoom(2.f);
    window->setView(view);

    auto *enemy = new BasicEnemy();
    enemy->setPosition(player.getPos().x, player.getPos().y);

        enemies.push_back(enemy);

    window->setActive(false);
    std::thread drawThread(&Game::render, this);
    while (window->isOpen()) {
        if (tickRate.getElapsedTime().asMilliseconds() > 1000/60) {
            keyProcessing();
            handleCollisions();
            tickRate.restart();
            if (nrOfEnemies < 15){
                generateEnemies();
            }
            if (enemiesGenerated){
                mergeNewEnemies();
            }


        }

        this_thread::sleep_for(chrono::milliseconds(1));
    }
    drawThread.join();
}


void Game::keyProcessing() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player.moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.moveDown();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        player.fire();
    }

    player.resetVelocity();

}


void Game::update() {
    auto &bullets = player.getGun()->getBullets();
    for (int i = bullets.size() - 1; i >= 0; i--) {
        bullets[i]->update();
    }



}





void Game::render() {
    window->setActive(true);

    while (window->isOpen())
    {

        fps++;
        window->clear();

        drawGrounds();
        drawWalls();

        window->draw(player.getRectangle());
        for (auto bullet : player.getGun()->getBullets()){
            window->draw(bullet->getBulletShape());
        }
        {

            std::lock_guard<std::mutex> lk(enemiesMtx);
            for (int i = 0; i < enemies.size(); i++){
                window->draw(enemies[i]->getEnemyShape());
            }


        }


        if (clock2.getElapsedTime().asMilliseconds() > 1000) {
            cout << "fps: " << fps << endl;
            cout << "amount of enemies: " << enemies.size() << endl;

            fps = 0;
            clock2.restart();
        }
        view.setCenter(player.getPos());
        window->setView(view);
        window->display();
        if (window->hasFocus()) {
            window->setActive(true);
        } else {
            window->setActive(false);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));


    }


}



void Game::handleCollisions() {
    checkWallCollision();
    checkBulletWallCollision();
    checkBulletEnemyCollision();
}

void Game::checkBulletEnemyCollision() {
    auto bullets = player.getGun()->getBullets();

    for (int i = bullets.size() - 1; i >= 0; i--) {
        bullets[i]->update();
        std::lock_guard<std::mutex> lk(enemiesMtx);

        for (int j = 0; j < enemies.size(); j++) {
            if (bullets[i]->getBulletShape().getGlobalBounds().intersects(enemies[j]->getEnemyShape().getGlobalBounds())) {
                enemies[j]->takeDamage(bullets[i]->getDMG());
                player.getGun()->getBullets().erase(player.getGun()->getBullets().begin() + i);
                if (enemies[j]->isDead()) {
                    deadEnemies.push_back(j);
                    nrOfEnemies--;
                    std::cout << "Enemy killed!" << std::endl;
                } else {
                    std::cout << "Enemy took damage!" << std::endl;
                }
                break;
            }
        }
    }
}

void Game::checkWallCollision() {
    for (auto &wall: wallsGrounds) {
            sf::FloatRect playerBounds = player.getRectangle().getGlobalBounds();
            sf::FloatRect wallBounds = wall->getSprite().getGlobalBounds();

            sf::FloatRect intersection;
            if (playerBounds.intersects(wallBounds, intersection)) {
                if (intersection.width < intersection.height) {
                    if (playerBounds.left < wallBounds.left) {
                        player.setPos(wallBounds.left - playerBounds.width, player.getPos().y);
                    } else {
                        player.setPos(wallBounds.left + wallBounds.width , player.getPos().y);
                    }
                } else {
                    if (playerBounds.top < wallBounds.top) {
                        player.setPos(player.getPos().x, wallBounds.top - playerBounds.height);
                    } else {
                        player.setPos(player.getPos().x, wallBounds.top + wallBounds.height );
                    }
                }
            }
    }
}

void Game::checkBulletWallCollision(){
    auto bullets = player.getGun()->getBullets();
    for (int i = bullets.size() - 1; i >= 0; i--) {
        for (auto &wall: wallsGrounds) {
                if (checkDistanceToWall(wall, bullets[i]->getPosition() )){
                    sf::FloatRect bulletBounds = bullets[i]->getBulletShape().getGlobalBounds();
                    sf::FloatRect wallBounds = wall->getShape().getGlobalBounds();

                    sf::FloatRect intersection;
                    if (bulletBounds.intersects(wallBounds, intersection)) {
                        player.getGun()->getBullets().erase(player.getGun()->getBullets().begin() + i);
                        break;
                }

            }
        }
    }

}

bool Game::checkDistanceToWall(Ground *wall, sf::Vector2f pos){
    float posx = pos.x;
    float posy = pos.y;
    float wallx = wall->getShape().getPosition().x;
    float wally = wall->getShape().getPosition().y;
    if (wallx < posx - 10000 || posx > wallx + 10000 || wally < posy - 10000 || wally > posy + 10000){
        return false;
    }
    return true;
}


bool Game::checkWallDistance(sf::RectangleShape &wall, sf::RectangleShape shape) {
    float wallpos = wall.getPosition().x;
    float wallposy = wall.getPosition().y;
    float shapepos = shape.getPosition().x;
    float shapeposy = shape.getPosition().y;
    if (wallpos < shapepos - 1920 || wallpos > shapepos + 1920 || wallposy < shapeposy - 1080 || wallposy > shapeposy + 1080){
        return false;
    }
    return true;

}

bool Game::checkWallDistance(sf::RectangleShape &wall) {
        float wallpos = wall.getPosition().x;
        float wallposy = wall.getPosition().y;
        float playerpos = player.getPos().x;
        float playerposy = player.getPos().y;

        if (wallpos < playerpos - 5000 || wallpos > playerpos + 5000 || wallposy < playerposy - 4000 || wallposy > playerposy + 4000){
            return false;
        }
        return true;
}

void Game::drawWalls() {


     for (auto &wall : wallsGrounds) {

        float xpos = player.getPos().x;
        float ypos = player.getPos().y;
        float wallpos =wall->getShape().getPosition().x;
        float wallposy = wall->getShape().getPosition().y;
        if (wallpos < xpos - 2100 || wallpos > xpos + 2100 || wallposy < ypos - 1300 || wallposy > ypos + 1300){
            continue;
        }
        window->draw(wall->getSprite());

    }

    sf::View currentView = window->getView();
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCenter = currentView.getCenter();
    sf::FloatRect viewRect(viewCenter - viewSize / 2.f, viewSize);

    for (auto &ground : wallsGrounds) {
        if (ground->getSprite().getGlobalBounds().intersects(viewRect)) {
            window->draw(ground->getSprite());
        }
    }

}

void Game::drawGrounds() {

    /*
     *  for (auto &ground : grounds) {
        float xpos = player.getPos().x;
        float ypos = player.getPos().y;
        float groundpos =ground->getSprite().getPosition().x;
        float groundposy = ground->getSprite().getPosition().y;
        if (groundpos < xpos - 2100 || groundpos > xpos + 2100 || groundposy < ypos - 1300 || groundposy > ypos + 1300){
            continue;
        }
        window->draw(ground->getSprite());
    }
     */
    sf::View currentView = window->getView();
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCenter = currentView.getCenter();
    sf::FloatRect viewRect(viewCenter - viewSize / 2.f, viewSize);

    for (auto &ground : grounds) {
        if (ground->getSprite().getGlobalBounds().intersects(viewRect)) {
            window->draw(ground->getSprite());
        }
    }
}

void Game::generateWalls() {
    int columns = mappen.getWidth();
    int rows = mappen.getHeight();
    int cellsize = 100;

    std::vector<std::vector<bool>> redanKombinerad(columns, std::vector<bool>(rows, false));

    for (int row = 0; row < rows; row++){
        for (int col = 0; col < columns; col++){
            if (mappen.isWall(col, row)){
                if (!checkAdjecentWalls(col, row)){
                }else{}
            }else{
                auto *Ground = new BasicGround();
                Ground->getSprite().setPosition(col * 100, row * 100);
                grounds.push_back(Ground);
            }
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (mappen.isWall(row, col) && !redanKombinerad[row][col] && !checkAdjecentWalls(row, col)) {
                int startCol = col;
                int endCol = col;
                while (endCol < columns && mappen.isWall(row, endCol) &&
                       !redanKombinerad[row][endCol] && !checkAdjecentWalls(row, endCol)) {
                    redanKombinerad[row][endCol] = true;
                    endCol++;
                }

                int startRow = row;
                int endRow = row + 1;
                while (endRow < rows) {
                    bool canMergeRow = true;
                    for (int j = startCol; j < endCol; j++) {
                        if (!mappen.isWall(endRow, j) || checkAdjecentWalls(endRow, j) || redanKombinerad[endRow][j]) {
                            canMergeRow = false;
                            break;
                        }
                    }
                    if (!canMergeRow)
                        break;
                    for (int j = startCol; j < endCol; j++) {
                        redanKombinerad[endRow][j] = true;
                    }
                    endRow++;
                }
                int height = (endRow - startRow) * cellsize;
                int width = (endCol - startCol) * cellsize;
                auto* wallObj = new Walls();
                wallObj->setPosition(startRow * cellsize,startCol * cellsize  );
                wallObj->setSize(height, width);
                wallsGrounds.push_back(wallObj);
            }
        }
    }



    /*

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (mappen.isWall(row, col) && !redanKombinerad[row][col] && !checkAdjecentWalls(row, col)) {
                int startCol = col;
                int endCol = col;
                while (endCol < columns && mappen.isWall(row, endCol) &&
                       !redanKombinerad[row][endCol] && !checkAdjecentWalls(row, endCol)) {
                    redanKombinerad[row][endCol] = true;
                    endCol++;
                }

                int startRow = row;
                int endRow = row + 1;
                while (endRow < rows) {
                    bool canMergeRow = true;
                    for (int j = startCol; j < endCol; j++) {
                        if (!mappen.isWall(endRow, j) || checkAdjecentWalls(endRow, j) || redanKombinerad[endRow][j]) {
                            canMergeRow = false;
                            break;
                        }
                    }
                    if (!canMergeRow)
                        break;
                    for (int j = startCol; j < endCol; j++) {
                        redanKombinerad[endRow][j] = true;
                    }
                    endRow++;
                }
                int height = (endRow - startRow) * cellsize;
                int width = (endCol - startCol) * cellsize;
                auto* wallObj = new Walls();
                wallObj->setPosition(startRow * cellsize,startCol * cellsize  );
                wallObj->setSize(height, width);
                wallsGrounds.push_back(wallObj);
            }
        }
    }
     */







    cout << "Walls generated: " << wallsGrounds.size() << endl;










/*
    for (int row = 0; row < mappen.getHeight(); row++){
        for (int col = 0; col < mappen.getWidth(); col++){
            if (mappen.isWall(row, col)){
                if (!checkAdjecentWalls(row, col)){
                    auto *Ground = new Walls();
                    Ground->setPosition(row * 100, col * 100);

                    wallsGrounds.push_back(Ground);
                }
            }else{
                auto *Ground = new BasicGround();
                Ground->getSprite().setPosition(row * 100, col * 100);
                grounds.push_back(Ground);
            }
        }
    }

*/

}
bool Game::checkAdjecentWalls(int row, int col) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {

            if (dr == 0 && dc == 0)
                continue;
            int r = row + dr;
            int c = col + dc;

            if (r < 0 || r >= mappen.getHeight() || c < 0 || c >= mappen.getWidth())
                continue;
            if (!mappen.isWall(r, c))
                return false;
        }
    }
    return true;
}

void Game::generateEnemies() {
    vector<Ground*> nylista = grounds;

    vector<pair<int, int>> positioner = EnemySpawner::generateEnemyPos(nylista, player.getPos().x, player.getPos().y);
    int i = 0;

    int rand = random() % static_cast<int>(positioner.size());
    auto *enemy = new BasicEnemy();
    enemy->setPosition(positioner[rand].first, positioner[rand].second);
    tempEnemies.push_back(enemy);
    enemiesGenerated = true;
    nrOfEnemies++;
    cout << "enemy spawned at: " << enemy->getPosition().x << enemy->getPosition().y << endl;
    i++;
}

void Game::mergeNewEnemies() {
    std::lock_guard<std::mutex> lk(enemiesMtx);
    for (int i = int(deadEnemies.size()) - 1; i >= 0; --i) {
        int pos = deadEnemies[i];
        delete enemies[pos];
        enemies.erase(enemies.begin() + pos);
    }
    deadEnemies.clear();
    enemies.resize(enemies.size());
    enemies.insert(enemies.end(), tempEnemies.begin(), tempEnemies.end());
    tempEnemies.clear();
    enemiesGenerated = false;
    nrOfEnemies = enemies.size();
}


struct walls{
    sf::RectangleShape wall;
    walls(float x, float y, float width, float height){
        wall.setSize(sf::Vector2f(width, height));
        wall.setPosition(x, y);
        wall.setFillColor(sf::Color::Green);
    }
};


