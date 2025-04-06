//
// Created by Henrik Ravnborg on 2025-04-05.
//

#ifndef SPEL__WALLS_H
#define SPEL__WALLS_H


#include "../Ground.h"

class Walls : public Ground{

public:
    Walls();
    Walls(float width);
    Walls(float width, float height);

    Walls(float width, sf::Vector2f pos);

    ~Walls() override {
        // Destructor implementation
    }
    sf::RectangleShape& getShape() override {
        return m_shape;
    }


};


#endif //SPEL__WALLS_H
