#include "../AssetManager.h"
#include "PausedState.h"
#include "MenuState.h"
#include "../Window.h"


PausedState::PausedState(StateManager& context) : State(context), elapsedTime(0) {
    title = sf::Text{"Paused", AssetManager::getInstance().getFont()};
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Yellow);

    info = sf::Text{"Press 'ESC' to return to the main menu", AssetManager::getInstance().getFont()};
    info.setCharacterSize(20);
    info.setFillColor(sf::Color::White);

    cta = sf::Text{"Press 'enter' to continue playing", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);

    this->resized();
}


void PausedState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
            this->context.getGameContext().soundManager->start();
            this->context.pop();
            break;

        case sf::Keyboard::Escape:
            this->context.clear(std::make_unique<MenuState>(context));
            break;

        default: break;
    }
}


void PausedState::resized() {
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    info.setPosition(
        Window::getInstance().getWidth() / 2 - info.getGlobalBounds().width / 2,
        900
    );

    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        950
    );
}


void PausedState::update(const double dt) {
    elapsedTime += dt;

    // 0.6s on screen, 0.2s off-screen
    const double SWITCH = animationRender ? 0.6 : 0.2;

    if (elapsedTime < SWITCH) return;
    elapsedTime = 0;
    animationRender = !animationRender;
}

void PausedState::render() {
    Window::getInstance().draw(info);

    if (!animationRender) return;
    Window::getInstance().draw(title);
    Window::getInstance().draw(cta);
}

