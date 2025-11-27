//
// Created by PPetre on 24/11/2025.
//

#include <SFML/Graphics.hpp>
#include "Window.h"


Window::Window() {
    // sf::Style::Fullscreen
    window.create(sf::VideoMode::getDesktopMode(), "Pacman - Torben Petre", sf::Style::Default);
}


Window& Window::getInstance() {
    static Window instance;
    return instance;
}


bool Window::isOpen() const {
    return window.isOpen();
}

bool Window::pollEvent(sf::Event &event) {
    return window.pollEvent(event);
}

void Window::draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

void Window::clear() {
    window.clear();
}

void Window::display() {
    window.display();
}

void Window::close() {
    window.close();
}


unsigned int Window::getWidth() const {
    return window.getSize().x;
}

unsigned int Window::getHeight() const {
    return window.getSize().y;
}
