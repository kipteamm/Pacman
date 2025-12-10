#include "PacmanModel.h"
#include "../World.h"
#include <cmath>
#include <iostream>


using namespace logic;


PacmanModel::PacmanModel(const float normalizedX, const float normalizedY, const float mapWidth, const float mapHeight, const float speed) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, speed), nextDirection(Moves::RIGHT), moving(true) {
    gridX = static_cast<int>((normalizedX + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((normalizedY + 1.0f) * mapHeight / 2.0f);
    
    targetX = x;
    targetY = y;
}


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
    
    float checkX = normalizedX;
    float checkY = normalizedY;
    
    return !world.collides(dir, 0.0f, checkX, checkY);
}

void PacmanModel::updateTarget() {
    targetX = (static_cast<float>(gridX) + 0.5f) / mapWidth * 2.0f - 1.0f;
    targetY = (static_cast<float>(gridY) + 0.5f) / mapHeight * 2.0f - 1.0f;
}

void PacmanModel::move(const World& world, const float dt) {
    const float distancePerSecond = speed;
    const float moveDistance = distancePerSecond * dt;
    
    const float normalizedWidthPerCell = 2.0f / mapWidth;
    const float normalizedHeightPerCell = 2.0f / mapHeight;

    constexpr float epsilon = 0.001f;
    const float distToTargetX = std::abs(x - targetX);
    const float distToTargetY = std::abs(y - targetY);

    if (distToTargetX < epsilon && distToTargetY < epsilon) {
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

    const float dx = targetX - x;
    const float dy = targetY - y;
    
    float moveX = 0.0f;
    float moveY = 0.0f;
    
    if (direction == Moves::LEFT || direction == Moves::RIGHT) {
        const float sign = (dx > 0) ? 1.0f : -1.0f;
        moveX = sign * std::min(moveDistance * normalizedWidthPerCell, std::abs(dx));
    } else {
        const float sign = (dy > 0) ? 1.0f : -1.0f;
        moveY = sign * std::min(moveDistance * normalizedHeightPerCell, std::abs(dy));
    }
    
    x += moveX;
    y += moveY;
    
    if (std::abs(x - targetX) < epsilon) x = targetX;
    if (std::abs(y - targetY) < epsilon) y = targetY;
    if (moving) return;

    moving = true;
    notify(Events::ISMOVING_CHANGED);
}

void PacmanModel::update(double dt) {
    // Called by observer pattern if needed
}