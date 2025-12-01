//
// Created by PPetre on 26/11/2025.
//

#include "EntityModel.h"

using namespace logic;


EntityModel::EntityModel(const float normalizedX, const float normalizedY) : x(normalizedX), y(normalizedY) {}


bool EntityModel::checkCollision(const float otherX, const float otherY, const float width, const float height) const {
    // TODO: not the solution, things get stuck
    constexpr float epsilon = 0.00001f;

    return  x < otherX + width - epsilon &&
            x + width - epsilon > otherX &&
            y < otherY + height - epsilon &&
            y + height - epsilon > otherY;
}

float EntityModel::getX() const {
    return x;
}

float EntityModel::getY() const {
    return y;
}


MovingEntityModel::MovingEntityModel(const float x, const float y, const float speed) : EntityModel(x, y), speed(speed), direction(Moves::RIGHT) {}


Moves MovingEntityModel::getDirection() const {
    return direction;
}

float MovingEntityModel::getSpeed() const {
    return speed;
}
