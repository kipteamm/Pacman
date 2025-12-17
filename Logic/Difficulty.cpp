//
// Created by toroe on 16/12/2025.
//

#include "Difficulty.h"

#include <iostream>
#include <ostream>

using namespace logic;


Difficulty::Difficulty() = default;


Difficulty& Difficulty::getInstance() {
    static Difficulty instance;
    return instance;
}


void Difficulty::increaseDifficulty() {
    if (difficulty + 1 == difficultyMap.size()) return;
    difficulty++;
}


DifficultySpecs* Difficulty::getDifficulty() {
    return &difficultyMap[difficulty];
}


