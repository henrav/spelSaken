//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Game.h"

Game::Game()
        : m_window(1920, 1080, "Game") // Constructor initializer list
{
    player.setPos(400.0f, 300.0f);
    tickRate.restart();
}


void Game::run() {
    while (m_window.isOpen()) {
        if (tickRate.getElapsedTime().asMilliseconds() > 1000 / 60) {
            keyProcessing();
            update();
            render();
            tickRate.restart();
        }
    }
}

void Game::keyProcessing() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
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

}

void Game::render() {
    m_window.clear();
    m_window.draw(player.getCircle());
    for (auto &bullet : player.getGun()->getBullets()){
        m_window.draw(bullet->getBulletShape());
    }
    m_window.display();
}