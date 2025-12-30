#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "StateManager.h"


class VictoryState final : public State {
public:
    /**
     * @brief This State determines the Victory menu at the end of a single
     * Pacman level.
     * @param context StateManager
     */
    explicit VictoryState(StateManager& context);

    /**
     * @brief Will load the next level regardless of what key was pressed.
     * @param keyPressed KeyPressed event
     */
    void handleInput(const sf::Event::KeyEvent& keyPressed) override;

    /**
     * @brief Will resize the contents of the Victory state.
     */
    void resized() override;

    /**
     * @brief This is used for UI animations.
     * @param dt Deltatime
     */
    void update(double dt) override;

    /**
     * @brief Renders the Victory State.
     */
    void render() override;

private:
    sf::Text title;

    sf::Text cta;
    bool renderCta = true;
    double elapsedTime;
};


#endif //PACMAN_VICTORYSTATE_H