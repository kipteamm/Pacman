//
// Created by PPetre on 11/12/2025.
//

#include "AmbushGhost.h"


using namespace logic;


AmbushGhost::AmbushGhost(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const float speed,
    const double cooldown
) : GhostModel(normalizedX, normalizedY, mapWidth, mapHeight, speed, cooldown) {}


Moves AmbushGhost::decideNextMove(const World &world, const PacmanModel &pacman) {
    int targetX = pacman.getGridX();
    int targetY = pacman.getGridY();

    switch(pacman.getDirection()) {
        case Moves::UP:    targetY -= 2; break;
        case Moves::DOWN:  targetY += 2; break;
        case Moves::LEFT:  targetX -= 2; break;
        case Moves::RIGHT: targetX += 2; break;
    }

    return minimizeDistance(world, targetX, targetY);
}