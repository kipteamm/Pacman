//
// Created by PPetre on 26/11/2025.
//

#include "Observer.h"

using namespace logic;


void Subject::attach(const std::shared_ptr<Observer> &observer) {
    observers.push_back(observer);
}


void Subject::notify(const Events event) {
    auto it = observers.begin();

    while (it != observers.end()) {
        if (const auto observer = it->lock()) {
            observer->update(event);
            ++it;
        } else {
            it = observers.erase(it);
        }
    }
}
