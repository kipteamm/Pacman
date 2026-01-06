#ifndef PACMAN_GHOSTNAVIGATOR_H
#define PACMAN_GHOSTNAVIGATOR_H

#include "../../World.h"


namespace logic {
    class GhostNavigator {
    public:
        [[nodiscard]] static bool sameDirection(Moves a, Moves b) ;
        [[nodiscard]] static bool isAtIntersection(const World &world, const GhostModel& ghost);

        [[nodiscard]] static std::vector<Moves> getPossibleMoves(const World& world, const GhostModel& ghost);

        [[nodiscard]] static Moves maximizeDistance(const World &world, const GhostModel &ghost);
        [[nodiscard]] static Moves minimizeDistance(const World &world, const GhostModel &ghost, int targetX, int targetY);

        [[nodiscard]] static std::list<Moves> findPathToSpawn(const World& world, const GhostModel& ghost);

    private:
        template<typename Scorer>
        [[nodiscard]] static Moves selectBestMove(const World& world, const GhostModel& ghost, int targetX, int targetY, Scorer scoreFunc);
    };
}


#endif //PACMAN_GHOSTNAVIGATOR_H