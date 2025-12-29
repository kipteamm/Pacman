#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "StateManager.h"


class GameOverState final : public State {
public:
    /**
     * @brief This State determines the GameOver menu when the Player has lost
     * all their lives.
     * @param context StateManager
     */
    explicit GameOverState(StateManager& context);

    /**
     * @brief Will return to the Menu when a specific key is pressed.
     * @param keyPressed KeyPressed event
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Update the GameOverState, is used for UI animations.
     * @param dt Deltatime
     */
    void update(double dt) override;

    /**
     * @brief Renders the GameOver State.
     */
    void render() override;

private:
    sf::Text title;
    sf::Text score;

    sf::Text cta;
    bool renderCta = true;
    double elapsedTime;
};



#endif //GAMEOVERSTATE_H
