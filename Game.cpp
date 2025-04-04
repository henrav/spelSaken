//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Game.h"
#include "thread"


Game::Game()

{
    window.create(sf::VideoMode(1920, 1080), "SFML Window");
    view = sf::View(sf::FloatRect(0, 0, 1920.f, 1080.f));
    window.setView(view);
    tickRate.restart();


}


void Game::run() {
    sf::Vector2f vector(1000, 1000);
    //sf::Thread thread(&Game::render, this);
    generateWalls();
    player.setPos( mappen.getRow() * 100,  mappen.getCol() * 100 );
    view.zoom(2.f);
    window.setView(view);
    auto *enemy = new BasicEnemy();
    enemy->setPosition(player.getPos().x, player.getPos().y);
    enemies.push_back(enemy);
    std::thread drawThread(&Game::render, this);
    while (window.isOpen()) {
        if (tickRate.getElapsedTime().asMilliseconds() > 1000 / 60) {
            keyProcessing();
            handleCollisions();
            update();
            tickRate.restart();
        }
    }
    drawThread.join();

}

void Game::keyProcessing() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
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
    for ( auto &bullet: player.getGun()->getBullets()){
        bullet->update();
    }
    float playerx = player.getPos().x;
    float playery = player.getPos().y;
    for (auto &enemy : enemies){
        std::cout << "Enemy position: " << enemy->getPosition().x << ", " << enemy->getPosition().y << std::endl;
    }
    view.setCenter(player.getPos());

    window.setView(view);

}

void Game::render() {

    window.setActive(true);
    while (window.isOpen())
    {
        window.clear();
        window.draw(player.getRectangle());
        for (auto &bullet : player.getGun()->getBullets()){
            window.draw(bullet->getBulletShape());
        }
        for (auto &enemy : enemies){
            window.draw(enemy->getEnemyShape());
        }
        drawWalls();
        window.display();
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
        for (int j = 0; j < enemies.size(); j++) {
            if (bullets[i]->getBulletShape().getGlobalBounds().intersects(enemies[j]->getEnemyShape().getGlobalBounds())) {
                enemies[j]->takeDamage(bullets[i]->getDMG());
                player.getGun()->getBullets().erase(player.getGun()->getBullets().begin() + i);
                if (enemies[j]->isDead()) {
                    enemies.erase(enemies.begin() + j);
                    delete enemies[j];
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
    for (auto &wall: walls) {
        if (checkWallDistance(wall)) {
            sf::FloatRect playerBounds = player.getRectangle().getGlobalBounds();  // Assuming a rectangular bound, even if the name suggests a circle
            sf::FloatRect wallBounds = wall.getGlobalBounds();

            // Check if the player's bounding box intersects the wall's bounding box
            sf::FloatRect intersection;
            if (playerBounds.intersects(wallBounds, intersection)) {
                // Determine whether to resolve on the x-axis or y-axis
                if (intersection.width < intersection.height) {
                    // Resolve collision on the x-axis
                    if (playerBounds.left < wallBounds.left) {
                        // Collision from the left side: push the player to the left
                        player.setPos(wallBounds.left - playerBounds.width, player.getPos().y);
                    } else {
                        // Collision from the right side: push the player to the right
                        player.setPos(wallBounds.left + wallBounds.width , player.getPos().y);
                    }
                } else {
                    // Resolve collision on the y-axis
                    if (playerBounds.top < wallBounds.top) {
                        // Collision from the top: push the player upward
                        player.setPos(player.getPos().x, wallBounds.top - playerBounds.height);
                    } else {
                        // Collision from the bottom: push the player downward
                        player.setPos(player.getPos().x, wallBounds.top + wallBounds.height );
                    }
                }
            }
        }
    }
}

void Game::checkBulletWallCollision(){
    auto bullets = player.getGun()->getBullets();
    for (int i = player.getGun()->getBullets().size() - 1; i >= 0; i--) {
        for (auto &wall: walls) {
            if (checkWallDistance(wall, player.getGun()->getBullets()[i]->getBulletShape())) {
                sf::FloatRect bulletBounds = player.getGun()->getBullets()[i]->getBulletShape().getGlobalBounds();
                sf::FloatRect wallBounds = wall.getGlobalBounds();

                sf::FloatRect intersection;
                if (bulletBounds.intersects(wallBounds, intersection)) {
                    player.getGun()->getBullets().erase(player.getGun()->getBullets().begin() + i);
                    break;
                }
            }
        }
    }

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

        if (wallpos < playerpos - 1920 || wallpos > playerpos + 1920 || wallposy < playerposy - 1080 || wallposy > playerposy + 1080){
            return false;
        }
        return true;
}

void Game::drawWalls() {
    for (auto &wall : walls) {

        float xpos = player.getPos().x;
        float ypos = player.getPos().y;
        float wallpos =wall.getPosition().x;
        float wallposy = wall.getPosition().y;
        if (wallpos < xpos - 2100 || wallpos > xpos + 2100 || wallposy < ypos - 1300 || wallposy > ypos + 1300){
            continue;
        }
        window.draw(wall);

    }
}

void Game::generateWalls() {

    for (int row = 0; row < mappen.getHeight(); row++){
        for (int col = 0; col < mappen.getWidth(); col++){
            if (mappen.isWall(row, col)){
                if (!checkAdjecentWalls(row, col)){
                    sf::RectangleShape wall;
                    wall.setSize(sf::Vector2f(100, 100));
                    wall.setPosition(row * 100, col * 100);
                    walls.push_back(wall);
                }
            }
        }
    }
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




struct walls{
    sf::RectangleShape wall;
    walls(float x, float y, float width, float height){
        wall.setSize(sf::Vector2f(width, height));
        wall.setPosition(x, y);
        wall.setFillColor(sf::Color::Green);
    }
};

