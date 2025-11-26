//
// Created by PPetre on 24/11/2025.
//

#include <SFML/Window/Event.hpp>

#include "Window.h"
#include "Game.h"


Game::Game() {
    context.push(std::make_unique<MenuState>());

    const Window& window = *Window::getInstance();

    while (window.isOpen()) {
        this->loop();
    }
}


void Game::loop() {
    Window& window = *Window::getInstance();
    window.clear();

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                context.top()->handleInput(event.key);
                break;

            case sf::Event::Closed:
                window.close();
                break;

            default: break;
        }
    }

    context.top()->update();
    context.top()->render();

    window.display();
}


