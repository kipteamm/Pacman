#include "Difficulty.h"

#include <iostream>
#include <ostream>

using namespace logic;


/**
 * The difficulty mapping for difficulties 0 up to 10, after difficulty level
 * 10, the 11th difficulty, it will stay in the 11th difficulty (index 10).
 */
Difficulty::Difficulty() :
    difficultyMap({
        {0, DifficultySpecs{0, 100, 4, 2.3, 0.5, 6, 5}},
        {1, DifficultySpecs{1, 300, 4.4, 2.5, 0.6, 5, 5}},
        {2, DifficultySpecs{2, 500, 4.4, 2.5, 0.6, 4, 5}},
        {3, DifficultySpecs{2, 500, 4.4, 2.5, 0.6, 3, 5}},
        {4, DifficultySpecs{3, 700, 4.5, 2.7, 0.7, 2, 5}},
        {5, DifficultySpecs{3, 700, 4.5, 2.7, 0.7, 5, 5}},
        {6, DifficultySpecs{4, 1000, 4.5, 2.7, 0.7, 2, 5}},
        {7, DifficultySpecs{5, 2000, 4.5, 2.7, 0.7, 2, 5}},
        {8, DifficultySpecs{5, 2000, 4.5, 2.8, 0.7, 1, 2}},
        {9, DifficultySpecs{6, 3000, 4.5, 2.8, 0.7, 2, 4}},
        {10, DifficultySpecs{7, 5000, 4.5, 2.8, 0.8, 1, 2}},
    }), currentDifficulty(difficultyMap[difficulty])
{}


Difficulty& Difficulty::getInstance() {
    static Difficulty instance;
    return instance;
}


void Difficulty::increaseDifficulty() {
    if (difficulty + 1 == difficultyMap.size()) return;
    difficulty++;
    currentDifficulty = difficultyMap[difficulty];
}

void Difficulty::reset() {
    difficulty = 0;
}


int Difficulty::getFruitSpriteOffset() const {
    return currentDifficulty.fruitSpriteOffset;
}

int Difficulty::getFruitPoints() const {
    return currentDifficulty.fruitPoints;
}

float Difficulty::getPacmanSpeed() const {
    return currentDifficulty.pacmanSpeed;
}

float Difficulty::getGhostSpeed() const {
    return currentDifficulty.ghostSpeed;
}

float Difficulty::getFrighenedGhostSpeed() const {
    return currentDifficulty.frighenedGhostSpeed;
}

float Difficulty::getFrightenedTime() const {
    return currentDifficulty.frightenedTime;
}

int Difficulty::getFlashesh() const {
    return currentDifficulty.flashesh;
}
