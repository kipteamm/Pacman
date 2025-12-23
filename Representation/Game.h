#ifndef GAME_H
#define GAME_H

#include "States/StateManager.h"


class Game {
public:
    Game();

private:
    /**
     * @brief The main game loop.
     *
     * Will update the Stopwatch, World and the current State. After updating,
     * it will call the render function of the current State.
     */
    void loop() const;

    std::shared_ptr<logic::Score> scoreSystem;
    std::unique_ptr<StateManager> context{};
};



#endif //GAME_H
