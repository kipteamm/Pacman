//
// Created by PPetre on 11/12/2025.
//

#include "ChasingGhost.h"


using namespace logic;


ChasingGhost::ChasingGhost(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : GhostModel(normalizedX, normalizedY, mapWidth, mapHeight, cooldown) {}


Moves ChasingGhost::decideNextMove(const World &world, const PacmanModel &pacman) {
    const int targetX = pacman.getGridX();
    const int targetY = pacman.getGridY();

    return minimizeDistance(world, targetX, targetY);
}
