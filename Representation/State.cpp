//
// Created by toroe on 25/11/2025.
//

#include "Window.h"
#include "State.h"


MenuState::MenuState() {
    pacmanLogoTexture.loadFromFile("../Representation/assets/pacman_logo.png");

    this->pacmanLogo.setTexture(pacmanLogoTexture, true);
    this->pacmanLogo.setPosition(100, 100);
}


void MenuState::render() {
    Window::getInstance()->draw(this->pacmanLogo);
}
