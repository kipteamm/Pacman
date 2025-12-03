//
// Created by PPetre on 26/11/2025.
//

#include "EntityModel.h"

#include <iostream>

using namespace logic;


EntityModel::EntityModel(const float normalizedX, const float normalizedY) : x(normalizedX), y(normalizedY) {}


bool EntityModel::checkCollision(const float otherX, const float otherY, const float width, const float height) const {
    // TODO: not the solution, things get stuck
    constexpr float epsilon = 0.005f;

    const float diffWidth = std::abs(x - otherX) + epsilon;
    const float diffHeight = std::abs(y - otherY) + epsilon;

    return diffWidth < width && diffHeight < height;
}

float EntityModel::getX() const {
    return x;
}

float EntityModel::getY() const {
    return y;
}


MovingEntityModel::MovingEntityModel(const float x, const float y, const float mapWidth, const float mapHeight, const float speed) : EntityModel(x, y), mapWidth(mapWidth), mapHeight(mapHeight), speed(speed), direction(Moves::RIGHT) {}


Moves MovingEntityModel::getDirection() const {
    return direction;
}

float MovingEntityModel::getSpeed() const {
    return speed;
}
