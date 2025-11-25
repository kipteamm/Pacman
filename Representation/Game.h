//
// Created by PPetre on 24/11/2025.
//

#ifndef GAME_H
#define GAME_H

#include "State.h"
#include <stack>


class Game {
public:
    Game();

private:
    void loop();

    std::stack<State> context;
};



#endif //GAME_H
