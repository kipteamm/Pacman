#include "../../Difficulty.h"
#include "GhostNavigator.h"
#include "../../Random.h"
#include "../../World.h"
#include "GhostModel.h"

#include <queue>

using namespace logic;


GhostModel::GhostModel(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, Difficulty::getInstance().getGhostSpeed()), state(GhostState::WAITING), defaultSpeed(speed), startCooldown(cooldown), waitingTime(0) {
    gridSpawnX = static_cast<int>((normalizedX + 1.0f) * mapWidth / 2.0f);
    gridSpawnY = static_cast<int>((normalizedY + 1.0f) * mapHeight / 2.0f);
}


GhostState GhostModel::getState() const {
    return this->state;
}

bool GhostModel::isFrightened() const {
    return this->frightened;
}

int GhostModel::getGridSpawnX() const {
    return this->gridSpawnX;
}

int GhostModel::getGridSpawnY() const {
    return this->gridSpawnY;
}


void GhostModel::setFrightened(const bool frightened, const World& world) {
    // Dead ghosts will remain frightened untill they respawn.
    if (state == GhostState::DEAD) return;
    this->frightened = frightened;

    if (frightened) {
        // Update direction to maximizeDistance to Pacman as the Ghost is now
        // frightened.
        direction = GhostNavigator::maximizeDistance(world, *this);
        notify(Events::DIRECTION_CHANGED);

        speed = defaultSpeed * Difficulty::getInstance().getFrighenedGhostSpeed();
        notify(Events::GHOST_FRIGHTENED);
        return;
    }

    direction = decideNextMove(world);
    notify(Events::DIRECTION_CHANGED);

    speed = defaultSpeed;
    notify(Events::GHOST_NORMAL);
}


void GhostModel::pacmanCollides(World& world) {
    // If we are dead (= pathfinding our way back to the Ghost enclosure)
    // ghosts will still collide with Pacman, but nothing should come of it.
    if (state == GhostState::DEAD) return;

    // Upon colliding with Pacman there are two possible outcomes:
    // 1. Pacman dies
    if (!frightened) return world.killPacman();

    // 2. Ghost is frightened and therefore pacman 'eats' the Ghost
    state = GhostState::DEAD;
    speed = defaultSpeed * 2.5f;

    notify(Events::GHOST_EATEN);
    world.notify(Events::GHOST_EATEN);
}


void GhostModel::move(const World& world, const float dt) {
    switch (state) {
        // Returns because this is the only state in which a Ghost is not
        // moving.
    case GhostState::WAITING:
        updateWaiting(world, dt); return;
    case GhostState::EXITING:
        updateExiting(world); break;
    case GhostState::CHASING:
        updateChasing(world); break;
    case GhostState::DEAD:
        updateDead(world); break;
    }

    const float moveDistance = speed * dt;
    const float normalizedWidthPerCell = 2.0f / mapWidth;
    const float normalizedHeightPerCell = 2.0f / mapHeight;

    const float dx = targetX - x;
    const float dy = targetY - y;

    if (dx != 0) {
        const float sign = (dx > 0) ? 1.0f : -1.0f;
        x += sign * std::min(std::abs(dx), moveDistance * normalizedWidthPerCell);
    }
    else if (dy != 0) {
        const float sign = (dy > 0) ? 1.0f : -1.0f;
        y += sign * std::min(std::abs(dy), moveDistance * normalizedHeightPerCell);
    }

    // Snap to the grid position if we are within TARGET_EPSILON distance.
    if (std::abs(x - targetX) < TARGET_EPSILON) x = targetX;
    if (std::abs(y - targetY) < TARGET_EPSILON) y = targetY;
}


void GhostModel::respawn() {
    state = GhostState::WAITING;
    // Frightened Ghosts when respawning instantly leave their enclosure. Only
    // when the game starts or Pacman dies, the Ghosts should wait again.
    if (!frightened) waitingTime = 0;

    frightened = false;
    speed = defaultSpeed;

    x = spawnX;
    y = spawnY;

    gridX = static_cast<int>((x + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((y + 1.0f) * mapHeight / 2.0f);

    targetX = x;
    targetY = y;

    notify(Events::RESPAWN);
}


void GhostModel::updateWaiting(const World& world, const double dt) {
    // Track how long we have been waiting. If this surpasses the cooldown, the
    // Ghost state changes to EXITING, allowing the Ghost to start moving and
    // eventually chase Pacman.
    waitingTime += dt;

    if (waitingTime < startCooldown) return;
    state = GhostState::EXITING;
    direction = GhostNavigator::getPossibleMoves(world, *this)[0];
}


void GhostModel::updateExiting(const World& world) {
    // Early return if we have not yet reached the target.
    if (std::abs(x - targetX) >= TARGET_EPSILON || std::abs(y - targetY) >= TARGET_EPSILON) return;
    gridTargetReached(world);
    updateGridTarget();

    if (gridX == world.getGhostExitX() && gridY == world.getGhostExitY()) {
        state = GhostState::CHASING;
    }

    // When a Ghost is exiting, it will think about its next direction whenever
    // at an intersection. The direction of an exiting ghost is whatever gets
    // it closest to the exit coordinates based on the Manhatten distance
    if (!GhostNavigator::isAtIntersection(world, *this)) return;

    direction = GhostNavigator::minimizeDistance(world, *this, world.getGhostExitX(), world.getGhostExitY());
    notify(Events::DIRECTION_CHANGED);
}


void GhostModel::updateChasing(const World& world) {
    if (std::abs(x - targetX) >= TARGET_EPSILON || std::abs(y - targetY) >= TARGET_EPSILON) return;
    gridTargetReached(world);
    updateGridTarget();

    if (!GhostNavigator::isAtIntersection(world, *this)) return;

    // When chasing a Ghost is either frightened or not, and will base its
    // next direction on this.
    // If frightened it will maximize the Manhattan distance to Pacman
    // Otherwise it will determine the next move as per its behaviour
    if (frightened) {
        direction = GhostNavigator::maximizeDistance(world, *this);
    } else {
        direction = decideNextMove(world);
    }

    notify(Events::DIRECTION_CHANGED);
}


void GhostModel::updateDead(const World& world) {
    // Early return if we have not yet reached the target.
    if (std::abs(x - targetX) >= TARGET_EPSILON || std::abs(y - targetY) >= TARGET_EPSILON) return;
    gridTargetReached(world);
    updateGridTarget();

    if (gridX == gridSpawnX && gridY == gridSpawnY) return respawn();

    // Gets the next position based on the BFS fastest path to its spawnpoint.
    // I use BSF here because Manhattan doesn't work. Ghosts would not
    // correctly navigate to their original spawn points because whether they
    // are in the passageway below or above it, the Manhattan distance would be
    // the same.
    if (cachedPath.empty()) cachedPath = GhostNavigator::findPathToSpawn(world, *this);
    const bool notify = direction != cachedPath.front();

    direction = cachedPath.front();
    cachedPath.pop_front();

    if (!notify) return;
    this->notify(Events::DIRECTION_CHANGED);
}
