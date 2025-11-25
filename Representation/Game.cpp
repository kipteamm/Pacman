//
// Created by PPetre on 24/11/2025.
//

#include "Window.h"
#include "Game.h"

#include <iostream>
#include <SFML/Window/Event.hpp>


Game::Game() {
    const MenuState menuState();
    context.push(menuState);

    const Window& window = *Window::getInstance();

    while (window.isOpen()) {
        this->loop();
    }
}


void Game::loop() {
    Window& window = *Window::getInstance();

    // sf::Event event;
    // while (window.pollEvent(event)) {
    //
    // }
}


