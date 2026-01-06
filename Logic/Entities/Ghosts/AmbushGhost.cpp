#include "GhostNavigator.h"
#include "AmbushGhost.h"

using namespace logic;


AmbushGhost::AmbushGhost(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : GhostModel(normalizedX, normalizedY, mapWidth, mapHeight, cooldown) {}


Moves AmbushGhost::decideNextMove(const World &world, const PacmanModel &pacman) {
    int targetX = pacman.getGridX();
    int targetY = pacman.getGridY();

    switch(pacman.getDirection()) {
        case Moves::UP:    targetY -= 2; break;
        case Moves::DOWN:  targetY += 2; break;
        case Moves::LEFT:  targetX -= 2; break;
        case Moves::RIGHT: targetX += 2; break;
    }

    return GhostNavigator::minimizeDistance(world, *this, targetX, targetY);
}