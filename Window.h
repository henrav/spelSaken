//
// Created by Henrik Ravnborg on 2025-04-01.
//

#ifndef SPEL__WINDOW_H
#define SPEL__WINDOW_H
#include <SFML/Graphics/RenderWindow.hpp>


class Window {
public:
    Window(int width, int height, const std::string &title);

    bool pollEvent(sf::Event &event);

    void clear();

    void display();

    bool isOpen() const;

    void close();

    void draw(const sf::Drawable &drawable);

    sf::RenderWindow& getSFMLWindow();

    void setView(const sf::View &view) {

        m_window.setView(view);
    }




private:
    sf::RenderWindow m_window;

};


#endif //SPEL__WINDOW_H
