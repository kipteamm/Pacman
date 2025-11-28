//
// Created by PPetre on 27/11/2025.
//

#include "PacManModel.h"

using namespace logic;


PacManModel::PacManModel(const float normalizedX, const float normalizedY, const float speed): MovingEntityModel(normalizedX, normalizedY, speed) {}


Moves PacManModel::getNextDirection() const {
    return nextDirection;
}


void PacManModel::setNextDirection(const Moves& move) {
    if (this->direction == Moves::NONE) this->direction = move;
    this->nextDirection = move;
}


void PacManModel::move(const bool colliding, const float x, const float y) {
    if (colliding) {
        this->direction = this->nextDirection;
        return;
    }

    this->x = x;
    this->y = y;
}

void PacManModel::update(double dt) {

}
