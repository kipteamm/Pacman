#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include "StateManager.h"


class VictoryState final : public State {
public:
    explicit VictoryState(StateManager& context);

    // Not in use
    void update(double dt) override {};

    /**
     * @brief Will load the next level regardless of what key was pressed.
     *
     * @param keyPressed KeyPressed event
     */
    void handleInput(const sf::Event::KeyEvent& keyPressed) override;

    /**
     * @brief Renders the Victory State.
     */
    void render() override;
};


#endif //PACMAN_VICTORYSTATE_H