#ifndef GAME_H
#define GAME_H

#include "States/StateManager.h"


class Game {
public:
    Game();

private:
    void loop() const;

    std::shared_ptr<logic::Score> scoreSystem;
    std::unique_ptr<StateManager> context{};
};



#endif //GAME_H
