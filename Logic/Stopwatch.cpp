#include "Stopwatch.h"

using namespace logic;


Stopwatch::Stopwatch() {
    reset();
}


Stopwatch &Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

double Stopwatch::getDeltaTime() const {
    return deltaTime;
}


void Stopwatch::tick() {
    const auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
    lastTime = currentTime;
}

void Stopwatch::reset() {
    lastTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0.0;
}
