//
// Created by PPetre on 27/11/2025.
//

#include "PacmanModel.h"

#include <iostream>

#include "../World.h"

using namespace logic;


PacmanModel::PacmanModel(const float normalizedX, const float normalizedY, const float mapWidth, const float mapHeight, const float speed): MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, speed), nextDirection(Moves::RIGHT) {}


Moves PacmanModel::getNextDirection() const {
    return nextDirection;
}


void PacmanModel::setNextDirection(const Moves& move) {
    // if (this->direction == Moves::NONE) this->direction = move;
    this->nextDirection = move;
}


void PacmanModel::move(const World &world, const float dt) {
    float nextDistance = speed * dt;
    float distance = speed * dt;

    if (this->direction != this->nextDirection) {
        float x = this->x;
        float y = this->y;

        if (nextDirection == Moves::RIGHT || nextDirection == Moves::LEFT) nextDistance /= mapWidth;
        else nextDistance /= mapHeight;

        if (!world.collides(this->nextDirection, nextDistance, x, y)) {
            this->direction = this->nextDirection;
        }
    }

    float x = this->x;
    float y = this->y;

    if (direction == Moves::RIGHT || direction == Moves::LEFT) distance /= mapWidth;
    else distance /= mapHeight;

    if (world.collides(this->direction, distance, x, y)) return;

    this->x = x;
    this->y = y;
}


void PacmanModel::update(double dt) {

}
