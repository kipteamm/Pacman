#include "Observer.h"

using namespace logic;


void Subject::attach(const std::shared_ptr<Observer> &observer) {
    // Converts explicit shared_ptr to a weak_ptr to the same object.
    observers.push_back(observer);
}


void Subject::notify(const Events event) {
    auto it = observers.begin();

    while (it != observers.end()) {
        // Checks whether the observing entity still exists and notifies it of
        // any updates if that is the case. Otherwise, it will remove the
        // observer from the subject.
        if (const auto observer = it->lock()) {
            observer->update(event);
            ++it;
        } else {
            it = observers.erase(it);
        }
    }
}
