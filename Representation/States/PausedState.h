//
// Created by PPetre on 26/11/2025.
//

#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "StateManager.h"


class PausedState final : public State {
public:
    explicit PausedState(StateManager* context);

    void update(double dt) override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;
};



#endif //PAUSEDSTATE_H
