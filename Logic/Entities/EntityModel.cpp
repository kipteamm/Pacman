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


MovingEntityModel::MovingEntityModel(const float x, const float y, const float mapWidth, const float mapHeight, const float speed) : EntityModel(x, y), mapWidth(mapWidth), mapHeight(mapHeight), spawnX(x), spawnY(y), speed(speed) {
    gridX = static_cast<int>((x + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((y + 1.0f) * mapHeight / 2.0f);

    targetX = x;
    targetY = y;
}


Moves MovingEntityModel::getDirection() const {
    return direction;
}

float MovingEntityModel::getSpeed() const {
    return speed;
}


void MovingEntityModel::gridTargetReached(const World& world) {
    // These are teleport checks. Only relevant on maps that allow ghosts to
    // "exit" the map. For instance the typical Pacman map.
    if (gridX == 0) {
        gridX = static_cast<int>(mapWidth) - 1;
        x = world.normalizeX(gridX);

        return;
    }

    if (gridX == static_cast<int>(mapWidth)) {
        gridX = 1;
        x = world.normalizeX(gridX);

        return;
    }

    // If not teleporting, update position as would be normal.
    x = targetX;
    y = targetY;

    switch(direction) {
    case Moves::LEFT:  gridX--; break;
    case Moves::RIGHT: gridX++; break;
    case Moves::UP:    gridY--; break;
    case Moves::DOWN:  gridY++; break;
    }
}


void MovingEntityModel::updateGridTarget() {
    targetX = (static_cast<float>(gridX) + 0.5f) / mapWidth * 2.0f - 1.0f;
    targetY = (static_cast<float>(gridY) + 0.5f) / mapHeight * 2.0f - 1.0f;
}
