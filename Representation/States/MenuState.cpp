#include "../AssetManager.h"
#include "../Window.h"
#include "LevelState.h"
#include "MenuState.h"

#include <iostream>


MenuState::MenuState(StateManager& context) : State(context), elapsedTime(0) {
    this->scoreSystem = context.getGameContext().scoreSystem;

    this->pacmanLogo.setTexture(AssetManager::getInstance().getPacmanLogo(), true);
    this->pacmanLogo.setPosition(
        Window::getInstance().getWidth() / 2 - this->pacmanLogo.getGlobalBounds().width / 2,
        100
    );

    highscoresTitle = sf::Text{"Highscores", AssetManager::getInstance().getFont()};
    highscoresTitle.setCharacterSize(20);
    highscoresTitle.setFillColor(sf::Color::Yellow);
    highscoresTitle.setPosition(
        Window::getInstance().getWidth() / 2 - highscoresTitle.getGlobalBounds().width / 2,
        500
    );

    const auto _highscores = this->scoreSystem->getHighscores();
    int y = 500;

    for (int i = 0; i < std::min(5, static_cast<int>(_highscores->size())); i++) {
        sf::Text score{
            _highscores->at(i)->username + ": " + std::to_string(_highscores->at(i)->score),
            AssetManager::getInstance().getFont()
        };
        score.setCharacterSize(20);
        score.setFillColor(sf::Color::White);

        const float x = Window::getInstance().getWidth() / 2 - score.getGlobalBounds().width / 2;
        y += 50;
        score.setPosition(x, y);

        highscores.push_back(score);
    };

    username = sf::Text{"Playing as: ", AssetManager::getInstance().getFont()};
    username.setCharacterSize(20);
    username.setPosition(Window::getInstance().getWidth() / 2 - username.getGlobalBounds().width / 2, 400);
    username.setFillColor(sf::Color::Yellow);

    cta = sf::Text{"Start with typing your username", AssetManager::getInstance().getFont()};
    cta.setCharacterSize(20);
    cta.setFillColor(sf::Color::Yellow);
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        950
    );
}


/**
 * @warning Username changing has not been tested with AZERTY keyboard layouts.
 */
void MenuState::handleInput(const sf::Event::KeyEvent& keyPressed) {
    // Handle Start Game
    if (keyPressed.code == sf::Keyboard::Space || keyPressed.code == sf::Keyboard::Enter) {
        if (usernameValue.empty()) return;

        scoreSystem->setUser(usernameValue);
        this->context.swap(std::make_unique<LevelState>(this->context));
        return;
    }


    // Usernames

    // Handle Backspace (delete char)
    if (keyPressed.code == sf::Keyboard::Backspace) {
        if (usernameValue.empty()) return;

        usernameValue.pop_back();
        // Only reposition the username element here because the animated trailing
        // underscore would make change the X position everytime it is appended.
        username.setString("Playing as: " + usernameValue);
        username.setPosition(Window::getInstance().getWidth() / 2 - username.getGlobalBounds().width / 2, 400);

        if (!usernameValue.empty()) return;
        // Change the CTA text & position when no username is selected.
        cta.setString("Start with typing your username");
        cta.setPosition(
            Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
            950
        );

        return;
    }

    if (usernameValue.size() >= 16) return;

    // New characters
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

    if (charToAdd == 0) return;

    usernameValue += charToAdd;
    // Only reposition the username element here because the animated trailing
    // underscore would make change the X position everytime it is appended.
    username.setString("Playing as: " + usernameValue);
    username.setPosition(Window::getInstance().getWidth() / 2 - username.getGlobalBounds().width / 2, 400);

    // Only change the CTA string and position when the username length is one.
    // This way I avoid repositioning it without the position changing.
    if (usernameValue.size() != 1) return;
    cta.setString("Press 'enter' to start");
    cta.setPosition(
        Window::getInstance().getWidth() / 2 - cta.getGlobalBounds().width / 2,
        950
    );
}


void MenuState::update(const double dt) {
    elapsedTime += dt;

    // 0.6s on screen, 0.2s off-screen
    const double SWITCH = renderCta ? 0.6 : 0.2;

    if (elapsedTime < SWITCH) return;
    elapsedTime = 0;
    renderCta = !renderCta;
}


void MenuState::render() {
    Window::getInstance().draw(this->pacmanLogo);

    // Username with trailing underscore to indicate editing. The underscore is
    // animated with the same loop as the call to action. It will not be
    // appended when the username is already of maxlength.
    username.setString("Playing as: " + usernameValue + (usernameValue.size() < 16 && renderCta? "_": ""));
    Window::getInstance().draw(username);

    Window::getInstance().draw(highscoresTitle);
    for (const sf::Text& highscore : highscores) {
        Window::getInstance().draw(highscore);
    }

    // renderCta is a bool managed by the update function which is used to
    // animate the call to action string.
    if (!renderCta) return;
    Window::getInstance().draw(cta);
}
