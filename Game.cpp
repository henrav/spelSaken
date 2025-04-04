//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Game.h"
#include "thread"
Game::Game()

{
    window.create(sf::VideoMode(1920, 1080), "SFML Window");
    view = sf::View(sf::FloatRect(0, 0, 10000.f, 10000.f));
    window.setView(view);
    tickRate.restart();
    stone.setSize(sf::Vector2f(100, 100));
    stone.setFillColor(sf::Color::Red);
    stone.setPosition(100, 100);

}


void Game::run() {
    sf::Vector2f vector(1000, 1000);
    //sf::Thread thread(&Game::render, this);
    generateWalls();
    player.setPos( mappen.getWidth() ,  mappen.getHeight()  );
    std::thread drawThread(&Game::render, this);
    while (window.isOpen()) {
        if (tickRate.getElapsedTime().asMilliseconds() > 1000 / 60) {
            keyProcessing();
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.moveDown();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        player.fire();
    }
}


void Game::update() {
    for ( auto &bullet: player.getGun()->getBullets()){
        bullet->update();
    }
    float playerx = player.getPos().x;
    float playery = player.getPos().y;

    view.setCenter(player.getPos());
    window.setView(view);

}

void Game::render() {

    window.setActive(true);
    while (window.isOpen())
    {
        window.clear();
        window.draw(player.getCircle());
        for (auto &bullet : player.getGun()->getBullets()){
            window.draw(bullet->getBulletShape());
        }
        window.draw(stone);
        drawWalls();
        window.display();
    }
}

void Game::drawWalls() {
    for (auto &wall : walls) {
        /*
        float xpos = player.getPos().x;
        float ypos = player.getPos().y;
        float wallpos =wall.getPosition().x;
        float wallposy = wall.getPosition().y;
        if (wallpos < xpos - 1920 || wallpos > xpos + 1920 || wallposy < ypos - 1080 || wallposy > ypos + 1080){
            continue;
        }
         */
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