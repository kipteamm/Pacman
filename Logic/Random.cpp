#include "Random.h"

using namespace logic;


Random::Random() {
    std::random_device rd;
    generator = std::mt19937(rd());
}


Random &Random::getInstance() {
    static Random instance;
    return instance;
}


int Random::getInt(const int min, const int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

float Random::getFloat() {
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(generator);
}