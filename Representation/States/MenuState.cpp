//
// Created by PPetre on 26/11/2025.
//

#include "../AssetManager.h"
#include "../Window.h"
#include "LevelState.h"
#include "MenuState.h"

#include <iostream>


MenuState::MenuState(StateManager& context) : State(context) {
    this->scoreSystem = context.getGameContext().scoreSystem;
    this->pacmanLogo.setTexture(AssetManager::getInstance().getPacmanLogo(), true);

    const float x = Window::getInstance().getWidth() / 2 - this->pacmanLogo.getGlobalBounds().width / 2;
    this->pacmanLogo.setPosition(x, 100);
}


void MenuState::handleInput(const sf::Event::KeyEvent& keyPressed) {
    // Handle Start Game
    if (keyPressed.code == sf::Keyboard::Space || keyPressed.code == sf::Keyboard::Enter) {
        if (username.empty()) return;

        scoreSystem->setUser(username);
        this->context.swap(std::make_unique<LevelState>(this->context));
        return;
    }

    // Usernames
    // Handle Backspace (Delete char)
    if (keyPressed.code == sf::Keyboard::Backspace) {
        if (username.empty()) return;

        username.pop_back();
        return;
    }

    if (username.size() >= 16) return;

    // Username changing
    char charToAdd = 0;
    if (keyPressed.code >= sf::Keyboard::A && keyPressed.code <= sf::Keyboard::Z) {
        const char base = keyPressed.shift ? 'A' : 'a';
        charToAdd = base + (keyPressed.code - sf::Keyboard::A);
    } else if (keyPressed.code >= sf::Keyboard::Num0 && keyPressed.code <= sf::Keyboard::Num9) {
        charToAdd = '0' + (keyPressed.code - sf::Keyboard::Num0);
    } else if (keyPressed.code >= sf::Keyboard::Numpad0 && keyPressed.code <= sf::Keyboard::Numpad9) {
        charToAdd = '0' + (keyPressed.code - sf::Keyboard::Numpad0);
    } else if (keyPressed.code == sf::Keyboard::Hyphen) {
        charToAdd = keyPressed.shift ? '_' : '-';
    }

    if (charToAdd != 0) username += charToAdd;
}


void MenuState::update(const double dt) {
    elapsedTime += dt;

    // 0.4s on screen, 0.2s off-screen
    const double SWITCH = renderCta ? 0.6 : 0.2;

    if (elapsedTime < SWITCH) return;
    elapsedTime = 0;
    renderCta = !renderCta;
}


void MenuState::render() {
    Window::getInstance().draw(this->pacmanLogo);

    sf::Text name{
        "Playing as: " + username,
        AssetManager::getInstance().getFont()
    };
    name.setCharacterSize(20);
    name.setFillColor(sf::Color::Yellow);
    name.setPosition(Window::getInstance().getWidth() / 2 - name.getGlobalBounds().width / 2, 400);
    name.setString("Playing as: " + username + (username.size() < 16 && renderCta? "_": " "));

    Window::getInstance().draw(name);

    sf::Text title{"Highscores", AssetManager::getInstance().getFont()};
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(
        Window::getInstance().getWidth() / 2 - title.getGlobalBounds().width / 2,
        500
    );

    Window::getInstance().draw(title);

    const auto highscores = this->scoreSystem->getHighscores();
    int y = 500;

    for (int i = 0; i < std::min(5, static_cast<int>(highscores->size())); i++) {
        sf::Text score{
            highscores->at(i)->username + ": " + std::to_string(highscores->at(i)->score),
            AssetManager::getInstance().getFont()
        };
        score.setCharacterSize(20);
        score.setFillColor(sf::Color::White);

        const float x = Window::getInstance().getWidth() / 2 - score.getGlobalBounds().width / 2;
        y += 50;
        score.setPosition(x, y);

        Window::getInstance().draw(score);
    };

    if (!renderCta) return;
    sf::Text cta{"Press 'space' to start", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        950
    );

    Window::getInstance().draw(cta);
}
