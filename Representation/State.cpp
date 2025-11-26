//
// Created by toroe on 25/11/2025.
//

#include "Window.h"
#include "State.h"


MenuState::MenuState(const std::shared_ptr<logic::Score>& scoreSystem) : scoreSystem(scoreSystem) {
    pacmanLogoTexture.loadFromFile("../Representation/assets/pacman_logo.png");

    this->pacmanLogo.setTexture(pacmanLogoTexture, true);

    const float x = Window::getInstance()->getWidth() / 2 - this->pacmanLogo.getGlobalBounds().width / 2;
    this->pacmanLogo.setPosition(x, 100);
}


void MenuState::render() {
    Window::getInstance()->draw(this->pacmanLogo);

    // scoreSystem->getHighscores();
}
