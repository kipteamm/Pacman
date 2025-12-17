//
// Created by PPetre on 11/12/2025.
//

#include "../../Random.h"
#include "RandomGhost.h"

#include <algorithm>


using namespace logic;


RandomGhost::RandomGhost(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : GhostModel(normalizedX, normalizedY, mapWidth, mapHeight, cooldown) {}


Moves RandomGhost::decideNextMove(const World &world, const PacmanModel &pacman) {
    const std::vector<Moves> moves = getPossibleMoves(world);

    // With probability p=0.5 it will remain locked to the same direction (as long as it viable)
    if (Random::getInstance().getFloat() >= 0.5f) {
        if (std::find(moves.begin(), moves.end(), direction) != moves.end()) return direction;
    }

    const int randIndex = Random::getInstance().getInt(0, moves.size() - 1);
    return moves[randIndex];
}