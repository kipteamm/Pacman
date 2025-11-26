//
// Created by PPetre on 26/11/2025.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../../Logic/Score.h"
#include "StateManager.h"

#include <memory>


class MenuState final : public State {
public:
    explicit MenuState(const std::shared_ptr<logic::Score>& scoreSystem, StateManager* context);

    void update() override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;

    sf::Sprite pacmanLogo;
};


#endif //MENUSTATE_H
