//
// Created by Henrik Ravnborg on 2025-04-01.
//

#include "Window.h"

Window::Window(int width, int height, const std::string &title) {
    m_window.create(sf::VideoMode(width, height), title);
}

bool Window::pollEvent(sf::Event &event) {
    return m_window.pollEvent(event);
}

void Window::clear() {
    m_window.clear();
}

void Window::display() {
    m_window.display();
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

void Window::close() {
    m_window.close();
}

void Window::draw(const sf::Drawable &drawable) {
    m_window.draw(drawable);
}

sf::RenderWindow& Window::getSFMLWindow() {
    return m_window;
}

