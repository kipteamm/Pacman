//
// Created by PPetre on 12/12/2025.
//

#include "../AssetManager.h"
#include "GameOverState.h"

#include "MenuState.h"
#include "../Window.h"


GameOverState::GameOverState(StateManager *context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<logic::Score>& scoreSystem) : State(context), scoreSystem(scoreSystem), factory(factory) {}


void GameOverState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            this->context->swap(std::make_unique<MenuState>(this->context, scoreSystem, factory));
            return;

        default: break;
    }
}



void GameOverState::render() {
    sf::Text title{"Game Over", AssetManager::getInstance().getFont()};
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    Window::getInstance().draw(title);

    sf::Text cta{"Press 'esc' to return", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        850
    );

    Window::getInstance().draw(cta);
}
