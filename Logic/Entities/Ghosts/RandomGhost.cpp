#include <algorithm>

#include "GhostNavigator.h"
#include "../../Random.h"
#include "RandomGhost.h"

using namespace logic;


RandomGhost::RandomGhost(
    const float normalizedX,
    const float normalizedY,
    const float mapWidth,
    const float mapHeight,
    const double cooldown
) : GhostModel(normalizedX, normalizedY, mapWidth, mapHeight, cooldown) {}


Moves RandomGhost::decideNextMove(const World &world) {
    const std::vector<Moves> moves = GhostNavigator::getPossibleMoves(world, *this);

    // With probability p=0.5 it will remain locked to the same direction (as long as it viable)
    if (Random::getInstance().getFloat() >= 0.5f) {
        if (std::find(moves.begin(), moves.end(), direction) != moves.end()) return direction;
    }

    const int randIndex = Random::getInstance().getInt(0, moves.size() - 1);
    return moves[randIndex];
}