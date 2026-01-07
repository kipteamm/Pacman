#ifndef CHASINGGHOST_H
#define CHASINGGHOST_H

#include "GhostModel.h"


namespace logic {

    class ChasingGhost final : public GhostModel {
    public:
        /**
         * @brief Initializes base class GhostModel. ChasingGhost has specific
         * chasing behaviour.
         * @param normalizedX Normalized x spawn coordinate
         * @param normalizedY Normalized y spawn coordinate
         * @param mapWidth Map width (in tiles)
         * @param mapHeight Map height (in tiles)
         * @param cooldown Spawn cooldown before leaving enclosure
         */
        explicit ChasingGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);

    private:
        /**
         * @brief Will return the best Move for the Chasing ghost.
         *
         * The Chasing Ghost will chase Pacman directly. It uses the Manhattan
         * distance for its estimations.
         *
         * @param world World
         * @return Best Move
         */
        Moves decideNextMove(const World &world) override;
    };
}



#endif //CHASINGGHOST_H
