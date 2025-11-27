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
    class Observer {
    public:
        virtual ~Observer() = default;

        virtual void update() = 0;
    };


    class Subject {
    public:
        virtual ~Subject() = default;

        // TODO: FIX POINTER
        void attach(const std::shared_ptr<Observer> &observer);
        void detach(const std::shared_ptr<Observer> &observer);

        void notify();

    protected:
        std::list<std::shared_ptr<Observer>> observers;
    };
}



#endif //OBSERVER_H
