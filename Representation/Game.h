//
// Created by PPetre on 24/11/2025.
//

#ifndef GAME_H
#define GAME_H

#include <memory>

#include "State.h"
#include <stack>


class Game {
public:
    Game();

private:
    void loop();

    std::stack<std::unique_ptr<State>> context;
};



#endif //GAME_H
