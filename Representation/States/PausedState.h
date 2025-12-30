#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "StateManager.h"


class PausedState final : public State {
public:
    /**
     * @brief This State determines the Paused menu when pausing the actual
     * Pacman game.
     * @param context StateManager
     */
    explicit PausedState(StateManager& context);

    /**
     * @brief Goes back to the LevelState when specific keys are pressed.
     * @param keyPressed KeyPressed event
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Will resize the contents of the Paused state.
     */
    void resized() override;

    /**
     * @brief This is used for UI animations.
     * @param dt Deltatime
     */
    void update(double dt) override;

    /**
     * @brief Renders the PausedState
     */
    void render() override;

private:
    sf::Text title;
    sf::Text info;
    sf::Text cta;

    bool animationRender = true;
    double elapsedTime;

};



#endif //PAUSEDSTATE_H
