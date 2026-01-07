#ifndef AMBUSHGHOST_H
#define AMBUSHGHOST_H

#include "GhostModel.h"


namespace logic {

    class AmbushGhost final : public GhostModel {
    public:
        /**
         * @brief Initializes base class GhostModel. AmbushGhost has specific
         * chasing behaviour.
         * @param normalizedX Normalized x spawn coordinate
         * @param normalizedY Normalized y spawn coordinate
         * @param mapWidth Map width (in tiles)
         * @param mapHeight Map height (in tiles)
         * @param cooldown Spawn cooldown before leaving enclosure
         */
        explicit AmbushGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);

    private:
        /**
         * @brief Will return the best Move for the ambush ghost.
         *
         * The Ambush Ghost will target 2 tiles ahead of Pacman. It uses the
         * Manhattan distance for its estimations.
         *
         * @param world World
         * @return Best Move
         */
        Moves decideNextMove(const World &world) override;
    };
}


#endif //AMBUSHGHOST_H
