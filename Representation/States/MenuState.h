#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "StateManager.h"


class MenuState final : public State {
public:
    /**
     * @brief This State determines the main Pacman game menu.
     * @param context StateManager
     */
    explicit MenuState(StateManager& context);

    /**
     * @brief Will start the game when specific keys are a pressed. Also
     * handles usernames.
     *
     * In MenuState you have to set a username. The keys a through z, A through
     * Z, _ and - will result in their respective letters getting appended to
     * your username.
     *
     * @warning Username changing has not been tested with AZERTY
     * @param keyPressed SFML KeyEvent
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Update the MenuState, is used for UI animations.
     * @param dt Deltatime
     */
    void update(double dt) override;

    /**
     * @brief Renders the menu state.
     */
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;

    sf::Sprite pacmanLogo;

    sf::Text highscoresTitle;
    std::vector<sf::Text> highscores;

    sf::Text username;
    std::string usernameValue;

    sf::Text cta;
    bool renderCta = true;
    double elapsedTime;
};


#endif //MENUSTATE_H
