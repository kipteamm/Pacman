//
// Created by toroe on 09/12/2025.
//

#include "../../Random.h"
#include "../../World.h"
#include "GhostModel.h"

#include <iostream>


using namespace logic;


GhostModel::GhostModel(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const float speed,
    const double cooldown
) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, speed), state(GhostState::WAITING), defaultSpeed(speed), startCooldown(cooldown), waitingTime(0) {}


void GhostModel::setState(const GhostState state) {
    this->state = state;
}


void GhostModel::setFrightened(const bool frightened) {
    this->frightened = frightened;

    if (frightened) {
        speed = defaultSpeed * 0.6f;
        return;
    }

    speed = defaultSpeed;
}


void GhostModel::update(const World& world, const double dt) {
    if (state != GhostState::WAITING) return;
    waitingTime += dt;

    if (waitingTime > startCooldown) {
        state = GhostState::EXITING;
        direction = getPossibleMoves(world)[0];
    }
}


void GhostModel::move(const World& world, const float dt) {
    if (state == GhostState::WAITING) return;

    constexpr float epsilon = 0.01f;

    // Target reached
    if (std::abs(x - targetX) < epsilon && std::abs(y - targetY) < epsilon) {
        x = targetX;
        y = targetY;

        switch(direction) {
            case Moves::LEFT:  gridX--; break;
            case Moves::RIGHT: gridX++; break;
            case Moves::UP:    gridY--; break;
            case Moves::DOWN:  gridY++; break;
        }

        int nextGridX = gridX;
        int nextGridY = gridY;

        switch(direction) {
            case Moves::LEFT:  nextGridX--; break;
            case Moves::RIGHT: nextGridX++; break;
            case Moves::UP:    nextGridY--; break;
            case Moves::DOWN:  nextGridY++; break;
        }

        if (state == GhostState::EXITING && gridX == world.getGhostExitX() && gridY == world.getGhostExitY()) {
            state = GhostState::CHASING;
        }

        const bool wall = world.collidesWithWall(world.normalizeX(nextGridX), world.normalizeY(nextGridY), state == GhostState::EXITING);
        if (isAtIntersection(world) || wall) {
            if (state == GhostState::EXITING) direction = minimizeDistance(world, world.getGhostExitX(), world.getGhostExitY());
            else if (frightened) direction = maximizeDistance(world, *world.getPacman());
            else direction = decideNextMove(world, *world.getPacman());

            notify(DIRECTION_CHANGED);
        }

        updateTarget();
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

    if (std::abs(x - targetX) < epsilon) x = targetX;
    if (std::abs(y - targetY) < epsilon) y = targetY;
}

void GhostModel::respawn() {
    state = GhostState::WAITING;
    waitingTime = 0;

    x = spawnX;
    y = spawnY;

    gridX = static_cast<int>((x + 1.0f) * mapWidth / 2.0f);
    gridY = static_cast<int>((y + 1.0f) * mapHeight / 2.0f);

    targetX = x;
    targetY = y;

    notify(Events::RESPAWN);
}


std::vector<Moves> GhostModel::getPossibleMoves(const World &world) const {
    std::vector<Moves> moves;

    for (int i = Moves::UP; i <= Moves::DOWN; i++) {
        const Moves move = static_cast<Moves>(i);

        int moveX = gridX;
        int moveY = gridY;

        switch (move) {
            case Moves::LEFT:
                moveX--; break;
            case Moves::RIGHT:
                moveX++; break;
            case Moves::UP:
                moveY--; break;
            case Moves::DOWN:
                moveY++; break;
        }

        if (world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY), state == GhostState::EXITING)) continue;
        moves.push_back(move);
    }

    return moves;
}


Moves GhostModel::maximizeDistance(const World &world, const PacmanModel &pacman) const {
    const std::vector<Moves> options = getPossibleMoves(world);

    std::vector<Moves> bestCandidates;
    int longestDistance = 0;

    for (const Moves move : options) {
        int nextX = gridX;
        int nextY = gridY;

        // Simulate a move
        if (move == Moves::UP) nextY--;
        else if (move == Moves::DOWN) nextY++;
        else if (move == Moves::LEFT) nextX--;
        else if (move == Moves::RIGHT) nextX++;

        int dist = std::abs(nextX - pacman.getGridX()) + std::abs(nextY - pacman.getGridY());

        if (dist > longestDistance) {
            longestDistance = dist;
            bestCandidates.clear();
            bestCandidates.push_back(move);
        }
        else if (std::abs(dist - longestDistance) == 0) {
            bestCandidates.push_back(move);
        }
    }

    return bestCandidates[Random::getInstance().getInt(0, bestCandidates.size() - 1)];
}


Moves GhostModel::minimizeDistance(const World &world, const int targetX, const int targetY) const {
    const std::vector<Moves> options = getPossibleMoves(world);

    std::vector<Moves> bestCandidates;
    int shortestDistance = 99999;

    for (const Moves move : options) {
        int nextX = gridX;
        int nextY = gridY;

        // Simulate a move
        if (move == Moves::UP) nextY--;
        else if (move == Moves::DOWN) nextY++;
        else if (move == Moves::LEFT) nextX--;
        else if (move == Moves::RIGHT) nextX++;

        int dist = std::abs(nextX - targetX) + std::abs(nextY - targetY);

        if (dist < shortestDistance) {
            shortestDistance = dist;
            bestCandidates.clear();
            bestCandidates.push_back(move);
        }
        else if (std::abs(dist - shortestDistance) == 0) {
            bestCandidates.push_back(move);
        }
    }

    return bestCandidates[Random::getInstance().getInt(0, bestCandidates.size() - 1)];
}


bool GhostModel::sameDirection(const Moves a, const Moves b) const {
    if (a == Moves::UP || a == Moves::DOWN) return (b == Moves::UP || b == Moves::DOWN);
    return (b == Moves::LEFT || b == Moves::RIGHT);
}


bool GhostModel::isAtIntersection(const World &world) const {
    for (int i = Moves::UP; i <= Moves::DOWN; i++) {
        const Moves move = static_cast<Moves>(i);
        if (sameDirection(move, direction)) continue;

        int moveX = gridX;
        int moveY = gridY;

        switch (move) {
            case Moves::LEFT:
                moveX--; break;
            case Moves::RIGHT:
                moveX++; break;
            case Moves::UP:
                moveY--; break;
            case Moves::DOWN:
                moveY++; break;
        }

        if (!world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY), state == GhostState::EXITING)) return true;
    }

    return false;
}
