#include <SFML/Window/Event.hpp>

#include "../Logic/Stopwatch.h"
#include "States/MenuState.h"
#include "Camera.h"
#include "Window.h"
#include "Game.h"


Game::Game() {
    context = std::make_unique<StateManager>();
    context->push(std::make_shared<MenuState>(*context));

    scoreSystem = context->getGameContext().scoreSystem;

    // Window::getInstance().setFramerateLimit(60);
    while (Window::getInstance().isOpen()) {
        this->loop();
    }
}


void Game::loop() const {
    Window& window = Window::getInstance();

    // Firstly, handle SFML events.
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            // Using KeyPressed event to be more responsive to player input
            // case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                context->top().handleInput(event.key);
                break;

            case sf::Event::Closed:
                scoreSystem->write();
                window.close();
                return;

            case sf::Event::Resized: {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                Camera::getInstance().resized();
                context->top().resized();
                break;
            }

            default: break;
        }
    }

    context->executeCommand();

    // Secondly update the Stopwatch and the current State with delta time
    logic::Stopwatch::getInstance().tick();
    const double dt = logic::Stopwatch::getInstance().getDeltaTime();

    context->top().update(dt);
    context->executeCommand();

    // Lastly clear the window and render the current State, display after
    window.clear();
    context->top().render();
    window.display();
}


