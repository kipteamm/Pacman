#include <queue>

#include "GhostNavigator.h"
#include "../../Random.h"

using namespace logic;


bool GhostNavigator::sameDirection(const Moves a, const Moves b) {
    if (a == Moves::UP || a == Moves::DOWN) return (b == Moves::UP || b == Moves::DOWN);
    return (b == Moves::LEFT || b == Moves::RIGHT);
}


bool GhostNavigator::isAtIntersection(const World &world, const GhostModel& ghost) {
    for (int i = Moves::UP; i <= Moves::DOWN; i++) {
        const Moves move = static_cast<Moves>(i);

        // A Ghost is at an intersection when there are more directions than
        // just ahead and where it came from. To determine these we use
        // collission detection.
        if (sameDirection(move, ghost.getDirection())) continue;

        int moveX = ghost.getGridX();
        int moveY = ghost.getGridY();

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

        // Check whether the simulated move collides with a wall. If at least
        // one other direction is found, this function can return True and
        // there is no need for checking the remaining direction.
        if (!world.collidesWithWall(
            world.normalizeX(moveX),
            world.normalizeY(moveY),
            ghost.getState() == GhostState::EXITING || ghost.getState() == GhostState::DEAD)
        ) return true;
    }

    return false;
}


std::vector<Moves> GhostNavigator::getPossibleMoves(const World &world, const GhostModel& ghost) {
    std::vector<Moves> moves;

    for (int i = Moves::UP; i <= Moves::DOWN; i++) {
        const Moves move = static_cast<Moves>(i);

        // Uses grid coordinates to determine possible moves. These are nice
        // to use for intersection detection as they are always the exact
        // center of a tile.
        int moveX = ghost.getGridX();
        int moveY = ghost.getGridY();

        // Simulating a move
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

        if (world.collidesWithWall(
            world.normalizeX(moveX),
            world.normalizeY(moveY),
            ghost.getState() == GhostState::EXITING || ghost.getState() == GhostState::DEAD
        )) continue;
        moves.push_back(move);
    }

    return moves;
}


/**
 * A breadth-first search is started from the ghost's current grid position and
 * expands outward until the spawn position is reached. During the search,
 * the direction taken to enter each cell is recorded.
 *
 * Once the spawn tile is found, the path is reconstructed by walking backwards
 * from the spawn to the start using the recorded directions, producing a
 * sequence of concrete Moves (LEFT, RIGHT, UP, DOWN).
 *
 * The returned list represents the shortest possible path in grid steps.
 * If multiple shortest paths exist, the chosen one depends on exploration order.
 */
std::list<Moves> GhostNavigator::findPathToSpawn(const World& world, const GhostModel& ghost) {
    const int width = static_cast<int>(world.getWidth());
    const int height = static_cast<int>(world.getHeight());

    std::vector<std::vector<logic::Moves>> comeFromMap(width, std::vector<logic::Moves>(height, static_cast<Moves>(-1)));
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

    std::queue<std::pair<int, int>> q;
    q.emplace(ghost.getGridX(), ghost.getGridY());
    visited[ghost.getGridX()][ghost.getGridY()] = true;

    // Standard BFS expansion:
    // Explore all reachable tiles layer by layer, recording for each tile
    // which move was used to reach it. This guarantees the first time we
    // encounter the spawn tile is via the shortest path.
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        if (cx == ghost.getGridSpawnX() && cy == ghost.getGridSpawnY()) break;

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

    int currentX = ghost.getGridSpawnX();
    int currentY = ghost.getGridSpawnY();
    std::list<Moves> cachedPath;

    // Generate a list of concrete moves from the end moving back towards the
    // starting position.
    while (currentX != ghost.getGridX() || currentY != ghost.getGridY()) {
        Moves move = comeFromMap[currentX][currentY];
        cachedPath.push_front(move);

        switch (move) {
        case Moves::LEFT:  currentX++; break;
        case Moves::RIGHT: currentX--; break;
        case Moves::UP:    currentY++; break;
        case Moves::DOWN:  currentY--; break;
        }
    }

    return cachedPath;
}


Moves GhostNavigator::maximizeDistance(const World& world, const GhostModel& ghost) {
    return selectBestMove(
        world,
        ghost,
        world.getPacman()->getGridX(),
        world.getPacman()->getGridY(),
        [](const int d) { return static_cast<double>(d); }
    );
}

Moves GhostNavigator::minimizeDistance(const World& world, const GhostModel& ghost, const int targetX, const int targetY) {
    return selectBestMove(
        world,
        ghost,
        targetX,
        targetY,
        [](const int d) { return -1.0 * d; }
    );
}

template <typename Scorer>
Moves GhostNavigator::selectBestMove(const World& world, const GhostModel& ghost, const int targetX, const int targetY, Scorer scoreFunc) {
    const std::vector<Moves> options = getPossibleMoves(world, ghost);
    if (options.empty()) return ghost.getDirection();

    std::vector<Moves> bestCandidates;
    double bestScore = -1.0;

    // Simulate all possible moves and calculate their respective Manhattan
    // distances. Generate a list of all best Moves (multiple in case of ties)
    // based on the provided scoreFunc.
    for (const Moves move : options) {
        int nextX = ghost.getGridX();
        int nextY = ghost.getGridY();

        if (move == Moves::UP) nextY--;
        else if (move == Moves::DOWN) nextY++;
        else if (move == Moves::LEFT) nextX--;
        else if (move == Moves::RIGHT) nextX++;

        int dist = std::abs(nextX - targetX) + std::abs(nextY - targetY);
        const double currentScore = scoreFunc(dist);

        if (bestCandidates.empty() || currentScore > bestScore) {
            bestScore = currentScore;
            bestCandidates.clear();
            bestCandidates.push_back(move);
        } else if (std::abs(currentScore - bestScore) < 0.001) {
            bestCandidates.push_back(move);
        }
    }

    return bestCandidates[Random::getInstance().getInt(0, bestCandidates.size() - 1)];
}
