//
// Created by PPetre on 26/11/2025.
//

#include "EntityModel.h"

using namespace logic;


EntityModel::EntityModel(const float normalizedX, const float normalizedY) : x(normalizedX), y(normalizedY) {}


bool EntityModel::checkCollision(const float otherX, const float otherY, const float width, const float height) const {
    return  x < otherX + width &&
            x + width > otherX &&
            y < otherY + height &&
            y + height > otherY;
}

float EntityModel::getX() const {
    return x;
}

float EntityModel::getY() const {
    return y;
}


MovingEntityModel::MovingEntityModel(const float x, const float y, const float speed) : EntityModel(x, y), speed(speed) {}


Moves MovingEntityModel::getDirection() const {
    return direction;
}

float MovingEntityModel::getSpeed() const {
    return speed;
}
