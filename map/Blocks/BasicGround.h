//
// Created by Henrik Ravnborg on 2025-04-05.
//

#ifndef SPEL__BASICGROUND_H
#define SPEL__BASICGROUND_H


#include "Ground.h"

class BasicGround : public Ground{

public:
    BasicGround();
    ~BasicGround() override {
        // Destructor implementation
    }

    sf::RectangleShape& getShape() override {
        return m_shape;
    }


};


#endif //SPEL__BASICGROUND_H
