//
// Created by PPetre on 27/11/2025.
//

#include "PacmanModel.h"
#include "../World.h"

using namespace logic;


PacmanModel::PacmanModel(const float normalizedX, const float normalizedY, const float speed): MovingEntityModel(normalizedX, normalizedY, speed), nextDirection(Moves::RIGHT) {}


Moves PacmanModel::getNextDirection() const {
    return nextDirection;
}


void PacmanModel::setNextDirection(const Moves& move) {
    if (this->direction == Moves::NONE) this->direction = move;
    this->nextDirection = move;
}


void PacmanModel::move(const World &world, const float dt) {
    const float distance = speed * dt;

    if (this->direction != this->nextDirection) {
        float x = this->x;
        float y = this->y;
        const bool collides = world.collides(this->nextDirection, distance, x, y);

        if (!collides) {
            this->direction = this->nextDirection;
        }
    }

    float x = this->x;
    float y = this->y;
    if (world.collides(this->direction, distance, x, y)) return;

    this->x = x;
    this->y = y;
}


void PacmanModel::update(double dt) {

}
