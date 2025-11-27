//
// Created by PPetre on 26/11/2025.
//

#include "../AssetManager.h"
#include "../Window.h"
#include "LevelState.h"
#include "MenuState.h"

#include <iostream>


MenuState::MenuState(const std::shared_ptr<logic::Score>& scoreSystem, StateManager* context) : State(std::move(context)), scoreSystem(scoreSystem) {
    this->pacmanLogo.setTexture(AssetManager::getInstance().getPacmanLogo(), true);

    const float x = Window::getInstance().getWidth() / 2 - this->pacmanLogo.getGlobalBounds().width / 2;
    this->pacmanLogo.setPosition(x, 100);
}


void MenuState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Space:
            this->context->swap(std::make_unique<LevelState>(this->context));
            break;

        default: break;
    }
}

void MenuState::render() {
    Window::getInstance().draw(this->pacmanLogo);

    sf::Text title{"Highscores", AssetManager::getInstance().getFont()};
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        400
    );

    Window::getInstance().draw(title);

    const std::vector<int> highscores = this->scoreSystem->getHighscores();
    int y = 400;

    for (int i = 0; i < std::min(5, static_cast<int>(highscores.size())); i++) {
        sf::Text score{std::to_string(highscores[i]), AssetManager::getInstance().getFont()};
        score.setCharacterSize(20);
        score.setFillColor(sf::Color::White);

        const float x = Window::getInstance().getWidth() / 2 - score.getGlobalBounds().width / 2;
        y += 50;
        score.setPosition(x, y);

        Window::getInstance().draw(score);
    };

    // TODO: animate this when dt is added
    sf::Text cta{"Press 'space' to start", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        850
    );

    Window::getInstance().draw(cta);
}
