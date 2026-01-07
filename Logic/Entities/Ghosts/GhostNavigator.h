#ifndef PACMAN_GHOSTNAVIGATOR_H
#define PACMAN_GHOSTNAVIGATOR_H

#include "../../World.h"


namespace logic {
    class GhostNavigator {
    public:
        /**
         * @brief Compares Move a and b and returns whether they are in the
         * same direction.
         * @param a Move
         * @param b Move
         * @return Whether they are the same direction
         */
        [[nodiscard]] static bool sameDirection(Moves a, Moves b);

        /**
         * @brief Checks whether the provided Ghost currently is at an
         * intersection.
         * @param world World
         * @param ghost Ghost to be checked
         * @return Whether ghost is at intersection
         */
        [[nodiscard]] static bool isAtIntersection(const World &world, const GhostModel& ghost);


        /**
         * @brief Checks all possible directions the Ghost can go at its
         * current position and returns them.
         * @param world World
         * @param ghost Ghost to be checked
         * @return A vector of moves
         */
        [[nodiscard]] static std::vector<Moves> getPossibleMoves(const World& world, const GhostModel& ghost);


        /**
         * @brief Determines the fastest path back to the Ghost enclosure
         * starting from the Ghost position using BFS pathfinding.
         * @param world World
         * @param ghost Ghost in need of a path
         * @return An ordered list of moves to be strictly followed
         */
        [[nodiscard]] static std::list<Moves> findPathToSpawn(const World& world, const GhostModel& ghost);


        /**
         * @brief Will return the best Move from all possible moves to maximize
         * the Manhattan distance between the Ghost and Pacman.
         * @param world World
         * @param ghost Ghosts to be checked
         * @return Best move
         */
        [[nodiscard]] static Moves maximizeDistance(const World &world, const GhostModel &ghost);

        /**
         * @brief Will return the best Move from all possible moves to minimize
         * the Manhattan distance between the Ghost and the provided target.
         * @param world World
         * @param ghost Ghosts to be checked
         * @param targetX X grid target coordinate
         * @param targetY Y grid target coordinate
         * @return Best move
         */
        [[nodiscard]] static Moves minimizeDistance(const World &world, const GhostModel &ghost, int targetX, int targetY);

    private:
        /**
         * @brief Helper function that abstracts all code out of
         * GhostNavigator::maximizeDistance and GhostNavigator::minimizeDistanc
         *
         * Requires a Scorer function to determine whether it should prioritize
         * minimal distance or maximal distance. Technically speaking you could
         * implement any Scorer function that takes an int and returns a
         * double.
         *
         * @tparam Scorer Score function
         * @param world
         * @param ghost
         * @param targetX
         * @param targetY
         * @param scoreFunc
         * @return
         */
        template<typename Scorer>
        [[nodiscard]] static Moves selectBestMove(const World& world, const GhostModel& ghost, int targetX, int targetY, Scorer scoreFunc);
    };
}


#endif //PACMAN_GHOSTNAVIGATOR_H