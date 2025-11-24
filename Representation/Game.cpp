//
// Created by PPetre on 24/11/2025.
//

#include "Window.h"
#include "Game.h"

#include <iostream>
#include <SFML/Window/Event.hpp>


Game::Game() {
    const Window& window = *Window::getInstance();
    std::cout << "Initiated game" << std::endl;

    while (window.isOpen()) {
        this->loop();
    }
}


void Game::loop() {
    Window& window = *Window::getInstance();

    sf::Event event;
    while (window.pollEvent(event)) {

    }
}


