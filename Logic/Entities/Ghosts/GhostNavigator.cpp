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


template <typename Scorer>
Moves GhostNavigator::selectBestMove(const World& world, const GhostModel& ghost, const int targetX, const int targetY, Scorer scoreFunc) {
    const std::vector<Moves> options = getPossibleMoves(world, ghost);
    if (options.empty()) return ghost.getDirection();

    std::vector<Moves> bestCandidates;
    // We use a double or float to be flexible with scoring math
    double bestScore = -1.0;

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


std::list<Moves> GhostNavigator::findPathToSpawn(const World& world, const GhostModel& ghost) {
    const int width = static_cast<int>(world.getWidth());
    const int height = static_cast<int>(world.getHeight());

    std::vector<std::vector<logic::Moves>> comeFromMap(width, std::vector<logic::Moves>(height, static_cast<Moves>(-1)));
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

    std::queue<std::pair<int, int>> q;
    q.emplace(ghost.getGridX(), ghost.getGridY());
    visited[ghost.getGridX()][ghost.getGridY()] = true;

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