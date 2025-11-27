//
// Created by PPetre on 24/11/2025.
//

#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Entities/ConcreteFactory.h"
#include "States/StateManager.h"
#include "../Logic/Score.h"
#include "Camera.h"


class Game {
public:
    Game();

private:
    void loop() const;

    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<logic::Score> scoreSystem;
    std::unique_ptr<StateManager> context{};
};



#endif //GAME_H
