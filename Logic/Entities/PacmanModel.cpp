#include "PacmanModel.h"
#include "../World.h"
#include <cmath>
#include <iostream>

#include "../Difficulty.h"


using namespace logic;


PacmanModel::PacmanModel(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight
) : MovingEntityModel(
    normalizedX,
    normalizedY,
    mapWidth,
    mapHeight,
    Difficulty::getInstance().getDifficulty()->pacmanSpeed
), nextDirection(Moves::RIGHT), moving(true) {}


Moves PacmanModel::getNextDirection() const {
    return nextDirection;
}

bool PacmanModel::isMoving() const {
    return moving;
}


void PacmanModel::setNextDirection(const Moves& move) {
    nextDirection = move;
    this->notify(Events::DIRECTION_CHANGED);
}

bool PacmanModel::canMoveInDirection(const World& world, const Moves dir) const {
    int newGridX = gridX;
    int newGridY = gridY;
    
    switch(dir) {
        case Moves::LEFT:  newGridX--; break;
        case Moves::RIGHT: newGridX++; break;
        case Moves::UP:    newGridY--; break;
        case Moves::DOWN:  newGridY++; break;
    }
    
    const float normalizedX = (static_cast<float>(newGridX) + 0.5f) / mapWidth * 2.0f - 1.0f;
    const float normalizedY = (static_cast<float>(newGridY) + 0.5f) / mapHeight * 2.0f - 1.0f;

    return !world.collidesWithWall(normalizedX, normalizedY, false);
}

void PacmanModel::move(const World& world, const float dt) {
    constexpr float epsilon = 0.001f;

    if (std::abs(x - targetX) < epsilon && std::abs(y - targetY) < epsilon) {
        if (nextDirection != direction && canMoveInDirection(world, nextDirection)) {
            direction = nextDirection;
            this->notify(Events::DIRECTION_CHANGED);
        }

        if (!canMoveInDirection(world, direction)) {
            x = targetX;
            y = targetY;

            if (!moving) return;
            moving = false;
            notify(Events::ISMOVING_CHANGED);

            return;
        }

        switch(direction) {
            case Moves::LEFT:  gridX--; break;
            case Moves::RIGHT: gridX++; break;
            case Moves::UP:    gridY--; break;
            case Moves::DOWN:  gridY++; break;
        }

        updateTarget();
    }

    const float moveDistance = speed * dt;
    const float normalizedWidthPerCell = 2.0f / mapWidth;
    const float normalizedHeightPerCell = 2.0f / mapHeight;

    const float dx = targetX - x;
    const float dy = targetY - y;

    if (direction == Moves::LEFT || direction == Moves::RIGHT) {
        const float sign = (dx > 0) ? 1.0f : -1.0f;
        x += sign * std::min(moveDistance * normalizedWidthPerCell, std::abs(dx));
    } else {
        const float sign = (dy > 0) ? 1.0f : -1.0f;
        y += sign * std::min(moveDistance * normalizedHeightPerCell, std::abs(dy));
    }
    
    if (std::abs(x - targetX) < epsilon) x = targetX;
    if (std::abs(y - targetY) < epsilon) y = targetY;
    if (moving) return;

    moving = true;
    notify(Events::ISMOVING_CHANGED);
}


void PacmanModel::respawn() {
    x = spawnX;
    y = spawnY;
    direction = Moves::RIGHT;
    nextDirection = Moves::RIGHT;

    gridX = static_cast<int>((x + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((y + 1.0f) * mapHeight / 2.0f);

    targetX = x;
    targetY = y;

    moving = true;
    notify(Events::RESPAWN);
}
