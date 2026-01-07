#include <cmath>

#include "../Difficulty.h"
#include "PacmanModel.h"
#include "../World.h"

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
    Difficulty::getInstance().getPacmanSpeed()
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


bool PacmanModel::gridTargetReached(const World& world) {
    // If there is a buffered direction that is different from the current
    // direction and Pacman can move in this direction, we update the
    // current direction to be the buffered direction.
    if (nextDirection != direction && canMoveInDirection(world, nextDirection)) {
        direction = nextDirection;
        this->notify(Events::DIRECTION_CHANGED);
    }

    // These are teleport checks. Only relevant on maps that allow ghosts to
    // "exit" the map. For instance the typical Pacman map with tunnels.
    if (gridX == 0) {
        gridX = static_cast<int>(mapWidth) - 1;
        x = world.normalizeX(gridX);

        normalizeTarget();
        return false;
    }

    if (gridX == static_cast<int>(mapWidth)) {
        gridX = 1;
        x = world.normalizeX(gridX);

        normalizeTarget();
        return false;
    }

    if (!canMoveInDirection(world, direction)) {
        x = targetX;
        y = targetY;

        if (!moving) return false;
        moving = false;
        notify(Events::ISMOVING_CHANGED);

        return false;
    }

    switch(direction) {
        case Moves::LEFT:  gridX--; break;
        case Moves::RIGHT: gridX++; break;
        case Moves::UP:    gridY--; break;
        case Moves::DOWN:  gridY++; break;
    }

    normalizeTarget();
    return true;
}



void PacmanModel::move(const World& world, const float dt) {
    // Target reached
    if (std::abs(x - targetX) < TARGET_EPSILON && std::abs(y - targetY) < TARGET_EPSILON) {
        // If the Pacman does not continue down its current direction, I return
        // as moving does not make sense.
        if (!gridTargetReached(world)) return;
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

    // Snap to the grid position if we are within TARGET_EPSILON distance.
    if (std::abs(x - targetX) < TARGET_EPSILON) x = targetX;
    if (std::abs(y - targetY) < TARGET_EPSILON) y = targetY;
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


bool PacmanModel::canMoveInDirection(const World& world, const Moves direction) const {
    int newGridX = gridX;
    int newGridY = gridY;

    switch(direction) {
        case Moves::LEFT:  newGridX--; break;
        case Moves::RIGHT: newGridX++; break;
        case Moves::UP:    newGridY--; break;
        case Moves::DOWN:  newGridY++; break;
    }

    return !world.collidesWithWall(
        world.normalizeX(newGridX),
        world.normalizeY(newGridY),
        false
    );
}
