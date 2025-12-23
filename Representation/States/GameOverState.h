//
// Created by PPetre on 12/12/2025.
//

#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"
#include "StateManager.h"
#include "../Camera.h"


class GameOverState final : public State {
public:
    explicit GameOverState(
        StateManager* context
    );

    void update(double dt) override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;
};



#endif //GAMEOVERSTATE_H
