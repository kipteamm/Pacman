//
// Created by toroe on 25/11/2025.
//

#include "AssetManager.h"
#include "Window.h"
#include "State.h"


MenuState::MenuState(const std::shared_ptr<logic::Score>& scoreSystem) : scoreSystem(scoreSystem) {
    this->pacmanLogo.setTexture(AssetManager::getInstance().getPacmanLogo(), true);

    const float x = Window::getInstance()->getWidth() / 2 - this->pacmanLogo.getGlobalBounds().width / 2;
    this->pacmanLogo.setPosition(x, 100);
}


void MenuState::render() {
    Window::getInstance()->draw(this->pacmanLogo);

    const std::vector<int> highscores = this->scoreSystem->getHighscores();
    for (int i = 0; i < std::min(5, static_cast<int>(highscores.size())); i++) {
        sf::Text score{std::to_string(highscores[i]), AssetManager::getInstance().getFont()};
        score.setCharacterSize(20);
        score.setFillColor(sf::Color::White);

        Window::getInstance()->draw(score);
    };
}
