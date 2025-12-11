//
// Created by toroe on 09/12/2025.
//

#include "../../World.h"
#include "GhostModel.h"


using namespace logic;


GhostModel::GhostModel(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const float speed,
    const double cooldown
) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, speed), state(GhostState::WAITING), defaultSpeed(speed), startCooldown(cooldown), waitingTime(0) {}


// void GhostModel::updateTarget(const World& world) {
    // if (this->type == GhostType::PINKY || this->type == GhostType::INKY) {
    //     double shortestDistance = std::numeric_limits<double>::max();
    //     const std::shared_ptr<PacmanModel>& pacman = world.getPacman();
    //
    //     int pacmanX = pacman->getGridX();
    //     int pacmanY = pacman->getGridY();
    //
    //     switch (pacman->getDirection()) {
    //         case Moves::LEFT:
    //             pacmanX--; break;
    //         case Moves::RIGHT:
    //             pacmanX++; break;
    //         case Moves::UP:
    //             pacmanY--; break;
    //         case Moves::DOWN:
    //             pacmanY++; break;
    //     }
    //
    //     // ReSharper disable once CppJoinDeclarationAndAssignment
    //     double manhattanDistance;
    //
    //     manhattanDistance = std::abs(pacmanX - (gridX - 1)) + std::abs(pacmanY - gridY);
    //     if (!world.collidesWithWall(gridX - 1, gridY) && manhattanDistance < shortestDistance) {
    //         direction = Moves::LEFT;
    //         shortestDistance = manhattanDistance;
    //     }
    //
    //     manhattanDistance = std::abs(pacmanX - (gridX + 1)) + std::abs(pacmanY - gridY);
    //     if (!world.collidesWithWall(gridX + 1, gridY) && manhattanDistance < shortestDistance) {
    //         direction = Moves::RIGHT;
    //         shortestDistance = manhattanDistance;
    //     }
    //
    //     manhattanDistance = std::abs(pacmanX - gridX) + std::abs(pacmanY - (gridY - 1));
    //     if (!world.collidesWithWall(gridX, gridY - 1) && manhattanDistance < shortestDistance) {
    //         direction = Moves::UP;
    //         shortestDistance = manhattanDistance;
    //     }
    //
    //     manhattanDistance = std::abs(pacmanX - gridX) + std::abs(pacmanY - (gridY + 1));
    //     if (!world.collidesWithWall(gridX, gridY + 1) && manhattanDistance < shortestDistance) {
    //         direction = Moves::DOWN;
    //     }
    //
    //     this->state = GhostState::CHASING;
    //     targetX = (static_cast<float>(gridX) + 0.5f) / mapWidth * 2.0f - 1.0f;
    //     targetY = (static_cast<float>(gridY) + 0.5f) / mapHeight * 2.0f - 1.0f;
    // }
// }


void GhostModel::setState(const GhostState state) {
    this->state = state;
}


void GhostModel::update(const World& world, const double dt) {
    if (this->state != GhostState::WAITING) return;
    waitingTime += dt;

    if (waitingTime > startCooldown) {
        this->state = GhostState::CHASING;
    }
}


void GhostModel::move(const World& world, const float dt) {
    if (state == GhostState::CHASING) speed = defaultSpeed;
    else if (state == GhostState::FRIGHTENED) speed = defaultSpeed * 0.5f;
    else return;

    const float moveDistance = speed * dt;
    const float normalizedWidthPerCell = 2.0f / mapWidth;
    const float normalizedHeightPerCell = 2.0f / mapHeight;

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

    if (!isAtIntersection(world)) return;

    // snap to grid to assure being able to turn...?
    // x = world.normalizeX(gridX);
    // y = world.normalizeY(gridY);

    if (state == GhostState::FRIGHTENED) direction = maximizeDistance(world, *world.getPacman());
    else direction = decideNextMove(world, *world.getPacman());
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

        if (world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY))) continue;
        moves.push_back(move);
    }

    return moves;
}

Moves GhostModel::maximizeDistance(const World &world, const PacmanModel &pacman) {
    return Moves::UP;
}

Moves GhostModel::minimizeDistance(const World &world, const int targetX, const int targetY) const {
    const std::vector<Moves> options = getPossibleMoves(world);

    Moves bestMove = options[0];
    float shortestDistance = 99999.0f;

    for (const Moves move : options) {
        int nextX = gridX;
        int nextY = gridY;

        // Simulate a move
        if (move == Moves::UP) nextY--;
        else if (move == Moves::DOWN) nextY++;
        else if (move == Moves::LEFT) nextX--;
        else if (move == Moves::RIGHT) nextX++;

        float dist = std::abs(nextX - targetX) + std::abs(nextY - targetY);

        // Ties broken at random?
        if (dist > shortestDistance) continue;
        shortestDistance = dist;
        bestMove = move;
    }

    return bestMove;
}


bool GhostModel::isAtIntersection(const World &world) const {
    for (int i = Moves::UP; i <= Moves::DOWN; i++) {
        const Moves move = static_cast<Moves>(i);
        if (move == direction) continue;

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

        if (!world.collidesWithWall(world.normalizeX(moveX), world.normalizeY(moveY))) return true;
    }

    return false;
}

