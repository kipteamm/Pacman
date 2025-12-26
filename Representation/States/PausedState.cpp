#include "../AssetManager.h"
#include "PausedState.h"
#include "../Window.h"


PausedState::PausedState(StateManager& context) : State(context) {}


void PausedState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Space:
            this->context.pop();
            break;

        default: break;
    }
}

void PausedState::render() {
    sf::Text title{"Paused", AssetManager::getInstance().getFont()};
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    Window::getInstance().draw(title);
}

