//
// Created by PPetre on 26/11/2025.
//

#include "EntityModel.h"

using namespace logic;


EntityModel::EntityModel(const float normalizedX, const float normalizedY) : x(normalizedX), y(normalizedY) {}


float EntityModel::getX() const {
    return x;
}

float EntityModel::getY() const {
    return y;
}
