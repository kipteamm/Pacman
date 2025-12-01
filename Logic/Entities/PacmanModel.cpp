//
// Created by PPetre on 27/11/2025.
//

#include "PacmanModel.h"

using namespace logic;


PacmanModel::PacmanModel(const float normalizedX, const float normalizedY, const float speed): MovingEntityModel(normalizedX, normalizedY, speed), nextDirection(Moves::RIGHT) {}


Moves PacmanModel::getNextDirection() const {
    return nextDirection;
}


void PacmanModel::setNextDirection(const Moves& move) {
    if (this->direction == Moves::NONE) this->direction = move;
    this->nextDirection = move;
}


void PacmanModel::move(const bool colliding, const float x, const float y) {
    if (colliding) {
        this->direction = this->nextDirection;
        return;
    }

    this->x = x;
    this->y = y;
}

void PacmanModel::update(double dt) {

}
