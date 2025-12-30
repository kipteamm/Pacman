//
// Created by toroe on 09/12/2025.
//

#include "../../Random.h"
#include "../../World.h"
#include "GhostModel.h"

#include <iostream>
#include <queue>

#include "../../Difficulty.h"


using namespace logic;


GhostModel::GhostModel(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, Difficulty::getInstance().getDifficulty()->ghostSpeed), state(GhostState::WAITING), defaultSpeed(speed), startCooldown(cooldown), waitingTime(0) {
    gridSpawnX = static_cast<int>((normalizedX + 1.0f) * mapWidth / 2.0f);
    gridSpawnY = static_cast<int>((normalizedY + 1.0f) * mapHeight / 2.0f);
}


void GhostModel::setState(const GhostState state) {
    this->state = state;
}


void GhostModel::setFrightened(const bool frightened, const World& world) {
    // Dead ghosts will remain frightened untill they respawn.
    if (state == GhostState::DEAD) return;

    this->frightened = frightened;
    updateDirection(world);

    if (frightened) {
        speed = defaultSpeed * Difficulty::getInstance().getDifficulty()->frighenedGhostSpeed;
        return;
    }

    notify(Events::GHOST_NORMAL);
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

        if (state == GhostState::EXITING && gridX == world.getGhostExitX() && gridY == world.getGhostExitY()) {
            state = GhostState::CHASING;
        }
        if (state == GhostState::DEAD && gridX == gridSpawnX && gridY == gridSpawnY) {
            respawn();
        }

        if (state == GhostState::DEAD || isAtIntersection(world)) updateDirection(world);

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

void GhostModel::eat() {
    state = GhostState::DEAD;
    speed = defaultSpeed * 2.5f;

    notify(Events::GHOST_EATEN);
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

        if (world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY), state == GhostState::EXITING || state == GhostState::DEAD)) continue;
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


void GhostModel::updatePathToSpawn(const World& world) {
    cachedPath.clear();

    const int width = static_cast<int>(mapWidth);
    const int height = static_cast<int>(mapHeight);

    std::vector<std::vector<logic::Moves>> comeFromMap(width, std::vector<logic::Moves>(height, static_cast<Moves>(-1)));
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

    std::queue<std::pair<int, int>> q;
    q.emplace(gridX, gridY);
    visited[gridX][gridY] = true;

    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        if (cx == gridSpawnX && cy == gridSpawnY) break;

        struct Dir { int dx, dy; logic::Moves move; };
        Dir dirs[] = { {-1, 0, Moves::LEFT}, {1, 0, Moves::RIGHT}, {0, -1, Moves::UP}, {0, 1, Moves::DOWN} };

        for (const auto& dir : dirs) {
            int nx = cx + dir.dx;
            int ny = cy + dir.dy;

            if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;
            if (visited[nx][ny] || world.collidesWithWall(world.normalizeX(nx), world.normalizeY(ny), true)) continue;

            visited[nx][ny] = true;
            comeFromMap[nx][ny] = dir.move;
            q.emplace(nx, ny);
        }
    }

    int currentX = gridSpawnX;
    int currentY = gridSpawnY;

    while (currentX != gridX || currentY != gridY) {
        Moves move = comeFromMap[currentX][currentY];
        cachedPath.push_front(move);

        switch (move) {
            case Moves::LEFT:  currentX++; break;
            case Moves::RIGHT: currentX--; break;
            case Moves::UP:    currentY++; break;
            case Moves::DOWN:  currentY--; break;
        }
    }
}



bool GhostModel::sameDirection(const Moves a, const Moves b) {
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

        if (!world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY), state == GhostState::EXITING || state == GhostState::DEAD)) return true;
    }

    return false;
}


void GhostModel::updateDirection(const World& world) {
    if (state == GhostState::EXITING) direction = minimizeDistance(world, world.getGhostExitX(), world.getGhostExitY());

    else if (state == GhostState::DEAD) {
        if (cachedPath.empty()) updatePathToSpawn(world);
        direction = cachedPath.front();
        cachedPath.pop_front();
    }

    else if (frightened) direction = maximizeDistance(world, *world.getPacman());

    else direction = decideNextMove(world, *world.getPacman());

    notify(Events::DIRECTION_CHANGED);
}
