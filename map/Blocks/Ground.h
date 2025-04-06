//
// Created by Henrik Ravnborg on 2025-04-05.
//

#ifndef SPEL__GROUND_H
#define SPEL__GROUND_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Ground {
protected:
    sf::RectangleShape m_shape;
    sf::Texture m_texture;
    std::string m_texturePath;
    sf::Sprite m_sprite;
public:
    virtual ~Ground() = default;
    virtual sf::RectangleShape &getShape() = 0;
    Ground() = default;

    void setSprite(const sf::Sprite &sprite) {
        m_sprite = sprite;
    }
    sf::Sprite &getSprite() {
        return m_sprite;
    }


    void setTexture(const std::string &texturePath) {
        if (!m_texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture");
        }
        m_shape.setTexture(&m_texture);
    }

    void setSize(float width, float height) {
        m_shape.setSize(sf::Vector2f(width, height));
        m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    }


    sf::Texture &getTexture() {
        return m_texture;
    }

    std::string getTexturePath() const {
        return m_texturePath;
    }

    void setTexturePath(const std::string &texturePath) {
        m_texturePath = texturePath;
    }

    void setPosition(float x, float y) {
        m_shape.setPosition(x, y);
        m_sprite.setPosition(x, y);
    }




};


#endif //SPEL__GROUND_H
