#include "../AssetManager.h"
#include "VictoryState.h"
#include "LevelState.h"
#include "../Window.h"


VictoryState::VictoryState(StateManager& context) : State(context), elapsedTime(0) {
    title = sf::Text{"Level Cleared", AssetManager::getInstance().getFont()};
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    cta = sf::Text{"Press 'enter' to continue", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        950
    );
}


void VictoryState::handleInput(const sf::Event::KeyEvent& keyPressed) {
    this->context.swap(std::make_unique<LevelState>(context));
}


void VictoryState::update(const double dt) {
    elapsedTime += dt;

    // 0.6s on screen, 0.2s off-screen
    const double SWITCH = renderCta ? 0.6 : 0.2;

    if (elapsedTime < SWITCH) return;
    elapsedTime = 0;
    renderCta = !renderCta;
}


void VictoryState::render() {
    Window::getInstance().draw(title);

    if (!renderCta) return;
    Window::getInstance().draw(cta);
}
