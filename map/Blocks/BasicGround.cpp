//
// Created by Henrik Ravnborg on 2025-04-05.
//

#include "BasicGround.h"
#include "../../misc/TextureManager.h"

BasicGround::BasicGround() : Ground() {
    m_texturePath = "../textures/ground/basicGround.png";
    sf::Texture& sharedTexture = TextureManager::getTexture(m_texturePath);
    m_sprite.setTexture(sharedTexture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));




}
