//
// Created by toroe on 17/12/2025.
//

#include "../AssetManager.h"
#include "VictoryState.h"
#include "LevelState.h"
#include "../Window.h"


VictoryState::VictoryState(StateManager *context) : State(context) {}


void VictoryState::handleInput(const sf::Event::KeyEvent& keyPressed) {
    this->context->swap(std::make_unique<LevelState>(context));
}


void VictoryState::render() {
    sf::Text title{"Level Cleared", AssetManager::getInstance().getFont()};
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    Window::getInstance().draw(title);
}


