#include "../AssetManager.h"
#include "GameOverState.h"
#include "MenuState.h"
#include "../Window.h"


GameOverState::GameOverState(StateManager& context) : State(context), elapsedTime(0) {
    title = sf::Text{"Game Over", AssetManager::getInstance().getFont()};
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);

    const logic::ScoreEntry& userScore = context.getGameContext().scoreSystem->getLastScore();

    score = sf::Text{
        "Well done "
            + userScore.username
            + ", you got: "
            + std::to_string(userScore.score),
        AssetManager::getInstance().getFont()
    };
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::White);

    cta = sf::Text{"Press 'esc' to return", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);

    this->resized();
}


void GameOverState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            this->context.swap(std::make_shared<MenuState>(this->context));
            return;

        default: break;
    }
}


void GameOverState::resized() {
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        200
    );

    score.setPosition(
        Window::getInstance().getWidth() / 2 - score.getGlobalBounds().width / 2,
        270
    );

    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        850
    );
}



void GameOverState::update(const double dt) {
    elapsedTime += dt;

    // 0.6s on screen, 0.2s off-screen
    const double SWITCH = renderCta ? 0.6 : 0.2;

    if (elapsedTime < SWITCH) return;
    elapsedTime = 0;
    renderCta = !renderCta;
}


void GameOverState::render() {
    Window::getInstance().draw(title);
    Window::getInstance().draw(score);

    if (!renderCta) return;
    Window::getInstance().draw(cta);
}
