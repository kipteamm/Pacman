#include "EntityModel.h"
#include "../World.h"

using namespace logic;


EntityModel::EntityModel(const float normalizedX, const float normalizedY) : x(normalizedX), y(normalizedY) {}


float EntityModel::getX() const {
    return x;
}

float EntityModel::getY() const {
    return y;
}


CollectibleEntityModel::CollectibleEntityModel(const float normalizedX, const float normalizedY) : EntityModel(normalizedX, normalizedY) {}


MovingEntityModel::MovingEntityModel(const float normalizedX, const float normalizedY, const float mapWidth, const float mapHeight, const float speed) : EntityModel(normalizedX, normalizedY), mapWidth(mapWidth), mapHeight(mapHeight), spawnX(x), spawnY(y), speed(speed) {
    gridX = static_cast<int>((x + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((y + 1.0f) * mapHeight / 2.0f);

    targetX = normalizedX;
    targetY = normalizedY;
}


Moves MovingEntityModel::getDirection() const {
    return direction;
}

int MovingEntityModel::getGridX() const {
    return gridX;
}

int MovingEntityModel::getGridY() const {
    return gridY;
}


void MovingEntityModel::normalizeTarget() {
    targetX = (static_cast<float>(gridX) + 0.5f) / mapWidth * 2.0f - 1.0f;
    targetY = (static_cast<float>(gridY) + 0.5f) / mapHeight * 2.0f - 1.0f;
}
