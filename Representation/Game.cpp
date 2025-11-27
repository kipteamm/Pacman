//
// Created by PPetre on 24/11/2025.
//

#include <SFML/Window/Event.hpp>

#include "../Logic/Stopwatch.h"
#include "States/MenuState.h"
#include "Window.h"
#include "Game.h"


Game::Game() {
    scoreSystem = std::make_shared<logic::Score>();
    context = std::make_unique<StateManager>();

    // Add game starting state to buffer for the assets loading in
    context->push(std::make_unique<MenuState>(scoreSystem, context.get()));

    while (Window::getInstance().isOpen()) {
        this->loop();
    }
}


void Game::loop() const {
    Window& window = Window::getInstance();

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
            // case sf::Event::KeyPressed:
                context->top()->handleInput(event.key);
                break;

            case sf::Event::Closed:
                scoreSystem->write();
                window.close();
                return;

            default: break;
        }
    }

    logic::Stopwatch::getInstance().tick();
    const double dt = logic::Stopwatch::getInstance().getDeltaTime();
    context->top()->update(dt);

    window.clear();
    context->top()->render();
    window.display();
}


