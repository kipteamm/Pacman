#include <SFML/Window/Event.hpp>

#include "../Logic/Stopwatch.h"
#include "States/MenuState.h"
#include "Window.h"
#include "Game.h"


Game::Game() {
    scoreSystem = std::make_shared<logic::Score>();

    context = std::make_unique<StateManager>(scoreSystem);
    context->push(std::make_unique<MenuState>(context.get()));
    // Window::getInstance().setFramerateLimit(60);

    while (Window::getInstance().isOpen()) {
        this->loop();
    }
}


void Game::loop() const {
    Window& window = Window::getInstance();

    // Firstly, handle SFML events.
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            // Using KeyPressed event to be more responsive to player input
            // case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                context->top()->handleInput(event.key);
                break;

            case sf::Event::Closed:
                scoreSystem->write();
                window.close();
                return;

            case sf::Event::Resized:
                Camera::getInstance().resize();
                break;

            default: break;
        }
    }

    // Secondly update the Stopwatch and the current State with delta time
    logic::Stopwatch::getInstance().tick();
    const double dt = logic::Stopwatch::getInstance().getDeltaTime();

    context->top()->update(dt);

    // Lastly clear the window and render the current State, display after
    window.clear();
    context->top()->render();
    window.display();
}


