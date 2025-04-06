//
// Created by Henrik Ravnborg on 2025-04-05.
//

#ifndef SPEL__TEXTUREMANAGER_H
#define SPEL__TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

class TextureManager {
public:
    static sf::Texture& getTexture(const std::string& filePath) {
        static std::map<std::string, sf::Texture> textures;
        auto it = textures.find(filePath);
        if (it == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(filePath)) {
                throw std::runtime_error("Failed to load texture: " + filePath);
            }
            // Insert and then get a reference to the texture stored in the map.
            it = textures.insert({filePath, std::move(texture)}).first;
        }
        return it->second;
    }
};



#endif //SPEL__TEXTUREMANAGER_H
