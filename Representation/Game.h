//
// Created by PPetre on 24/11/2025.
//

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>

#include "../Logic/Score.h"
#include "State.h"


class Game {
public:
    Game();

private:
    void loop();

    std::shared_ptr<logic::Score> scoreSystem;
    std::stack<std::unique_ptr<State>> context;
};



#endif //GAME_H
