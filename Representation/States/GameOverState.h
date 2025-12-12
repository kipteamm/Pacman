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
        StateManager* context,
        const std::shared_ptr<logic::Score>& scoreSystem,
        const std::shared_ptr<ConcreteFactory>& factory,
        const std::shared_ptr<Camera>& camera
    );

    void update(double dt) override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<Camera> camera;
};



#endif //GAMEOVERSTATE_H
