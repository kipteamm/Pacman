//
// Created by PPetre on 26/11/2025.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include <list>


/**
 * Using templates and inheritance for the Observer pattern
 * to assure the presence of specific functions when later
 * applying the pattern. The templates allow the inheriting
 * children to still vary to some extend.
 *
 * Based on https://refactoring.guru/design-patterns/observer/cpp/example
 */


template<typename T>
class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(const T& subject) = 0;
};


template<typename T>
class Subject {
public:
    virtual ~Subject() = default;

    // TODO: FIX POINTER
    void attach(Observer<T>* observer);
    void detach(Observer<T>* observer);

    void notify(const T& subject);

protected:
    std::list<Observer<T>*> observers;
};


#endif //OBSERVER_H
