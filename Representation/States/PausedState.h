//
// Created by PPetre on 26/11/2025.
//

#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "StateManager.h"


class PausedState final : public State {
public:
    explicit PausedState(StateManager& context);

    // Not in use
    void update(double dt) override {};

    /**
     * @brief Goes back to the LevelState when specific keys are pressed.
     *
     * @param keyPressed KeyPressed event
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Renders the PausedState
     */
    void render() override;
};



#endif //PAUSEDSTATE_H
