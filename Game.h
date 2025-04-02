//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__GAME_H
#define SPEL__GAME_H


#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
public:
    Game();
    void run();
    sf::Clock tickRate;

private:
    Player player;
    void keyProcessing();
    void update();
    void render();
    Window m_window;


};


#endif //SPEL__GAME_H
