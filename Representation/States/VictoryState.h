//
// Created by toroe on 17/12/2025.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"
#include "StateManager.h"


class VictoryState final : public State {
public:
    explicit VictoryState(StateManager* context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<logic::Score>& scoreSystem);

    void update(double dt) override {};
    void handleInput(const sf::Event::KeyEvent& keyPressed) override;
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<logic::Score> scoreSystem;
};


#endif //PACMAN_VICTORYSTATE_H