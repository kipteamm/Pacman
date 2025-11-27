//
// Created by PPetre on 26/11/2025.
//

#include "Observer.h"

using namespace logic;


void Subject::attach(const std::shared_ptr<Observer> &observer) {
    observers.push_back(observer);
}

void Subject::detach(const std::shared_ptr<Observer> &observer) {
    observers.remove(observer);
}


void Subject::notify() {
    for (const std::shared_ptr<Observer> observer : observers) {
        observer->update();
    }
}
