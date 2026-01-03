#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <list>


/**
 * Based on https://refactoring.guru/design-patterns/observer/cpp/example
 */

namespace logic {

    enum Events { NO_EVENT, GAME_OVER, LEVEL_COMPLETED, DIRECTION_CHANGED, ISMOVING_CHANGED, DEATH, RESPAWN, FRUIT_EATEN, GHOST_EATEN, COIN_EATEN, SCORE_UPDATE, GHOST_FRIGHTENED, GHOST_NORMAL, FRIGHTENED_FLASHING };

    class Observer {
    public:
        virtual ~Observer() = default;

        /**
         * @brief Update method that is called by the observed Subjects.
         *
         * World Events are passed down as such that Observers know what has
         * happened and can act properly.
         *
         * @param event World event
         */
        virtual void update(Events event) = 0;
    };


    class Subject {
    public:
        virtual ~Subject() = default;

        /**
         * @brief Attaches an observer to this Subject.
         * @param observer
         */
        void attach(const std::shared_ptr<Observer> &observer);

        /**
         * @brief Call the Observer update function with the provided event.
         * @param event World Event
         */
        void notify(Events event);

    protected:
        std::list<std::weak_ptr<Observer>> observers;
    };
}



#endif //OBSERVER_H
