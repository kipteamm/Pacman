//
// Created by PPetre on 26/11/2025.
//

#include "Observer.h"


template<typename T>
void Subject<T>::attach(Observer<T> *observer) {
    observers.push_back(observer);
}

template<typename T>
void Subject<T>::detach(Observer<T> *observer) {
    observers.remove(observer);
}


template<typename T>
void Subject<T>::notify(const T& subject) {
    for (Observer<T>* observer : observers) {
        observer->update(subject);
    }
}
