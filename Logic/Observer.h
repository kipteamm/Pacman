//
// Created by PPetre on 26/11/2025.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <list>


/**
 * Based on https://refactoring.guru/design-patterns/observer/cpp/example
 */


namespace logic {

    enum Events { GAME_OVER, LEVEL_COMPLETED, DIRECTION_CHANGED, ISMOVING_CHANGED, DEATH, RESPAWN, FRUIT_EATEN, GHOST_EATEN, COIN_EATEN, SCORE_UPDATE, GHOST_FRIGHTENED, GHOST_NORMAL, FRIGHTENED_FLASHING };

    class Observer {
    public:
        virtual ~Observer() = default;

        virtual void update(Events event) = 0;
    };


    class Subject {
    public:
        virtual ~Subject() = default;

        void attach(const std::shared_ptr<Observer> &observer);
        void detach(const std::shared_ptr<Observer> &observer);

        void notify(Events event);

    protected:
        std::list<std::shared_ptr<Observer>> observers;
    };
}



#endif //OBSERVER_H
