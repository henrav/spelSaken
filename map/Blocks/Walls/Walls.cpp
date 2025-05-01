//
// Created by Henrik Ravnborg on 2025-04-05.
//

#include "Walls.h"
#include "../../../misc/TextureManager.h"

Walls::Walls() {
   m_texturePath = "../textures/Walls/basicWall.png";

    sf::Texture& sharedTexture = TextureManager::getTexture(m_texturePath);
    sharedTexture.setRepeated(true);
    m_sprite.setTexture(sharedTexture);
    m_shape.setSize(sf::Vector2f(0, 0));
    m_shape.setPosition(0, 0);


}

Walls::Walls(float width, sf::Vector2f pos) {
    //m_texturePath = "../textures/Walls/basicWall.png";
    //sf::Texture& sharedTexture = TextureManager::getTexture(m_texturePath);
    //m_sprite.setTexture(sharedTexture);
    m_shape.setSize(sf::Vector2f(width, 100));
    //m_sprite.setTextureRect(sf::IntRect(0, 0, width, 100));
    m_shape.setPosition(pos);
    int randomX = rand() % 100;

    switch (randomX) {
        case 0:
            m_shape.setFillColor(sf::Color::Red);
            break;
        case 1:
            m_shape.setFillColor(sf::Color::Green);
            break;
        case 2:
            m_shape.setFillColor(sf::Color::Blue);
            break;
        case 3:
            m_shape.setFillColor(sf::Color::Yellow);
            break;
        case 4:
            m_shape.setFillColor(sf::Color::Magenta);
            break;
        case 5:
            m_shape.setFillColor(sf::Color::Cyan);
            break;
        case 6:
            m_shape.setFillColor(sf::Color::White);
            break;
        case 7:
            m_shape.setFillColor(sf::Color::Black);
            break;

    }
}

Walls::Walls(float width, float height) {
    m_texturePath = "../textures/Walls/basicWall.png";
    sf::Texture& sharedTexture = TextureManager::getTexture(m_texturePath);
    int randomX = rand() % 100;

    switch (randomX) {
        case 0:
            m_shape.setFillColor(sf::Color::Red);
            break;
        case 1:
            m_shape.setFillColor(sf::Color::Green);
            break;
        case 2:
            m_shape.setFillColor(sf::Color::Blue);
            break;
        case 3:
            m_shape.setFillColor(sf::Color::Yellow);
            break;
        case 4:
            m_shape.setFillColor(sf::Color::Magenta);
            break;
        case 5:
            m_shape.setFillColor(sf::Color::Cyan);
            break;
        case 6:
            m_shape.setFillColor(sf::Color::White);
            break;
        case 7:
            m_shape.setFillColor(sf::Color::Black);
            break;

    }
    m_sprite.setTexture(sharedTexture);
    m_shape.setSize(sf::Vector2f(100, height));
    m_sprite.setTextureRect(sf::IntRect(0, 0, 100, height));
}
