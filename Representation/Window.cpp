#include "Window.h"


Window::Window() {
    // sf::Style::Fullscreen
    window.create(sf::VideoMode::getDesktopMode(), "Pacman - Torben Petre", sf::Style::Fullscreen);
}


Window& Window::getInstance() {
    // The instance is created the first time this function is called.
    // It is destroyed automatically when the program exits.
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

void Window::setFramerateLimit(const unsigned int frameRate) {
    window.setFramerateLimit(frameRate);
}

unsigned int Window::getWidth() const {
    return window.getSize().x;
}

unsigned int Window::getHeight() const {
    return window.getSize().y;
}

void Window::setView(const sf::View& view) {
    window.setView(view);
}
