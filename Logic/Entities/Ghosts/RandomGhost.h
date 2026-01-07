#ifndef RANDOMGHOST_H
#define RANDOMGHOST_H

#include "GhostModel.h"


namespace logic {

    class RandomGhost final : public GhostModel {
    public:
        /**
         * @brief Initializes base class GhostModel. RandomGhost has specific
         * chasing behaviour.
         * @param normalizedX Normalized x spawn coordinate
         * @param normalizedY Normalized y spawn coordinate
         * @param mapWidth Map width (in tiles)
         * @param mapHeight Map height (in tiles)
         * @param cooldown Spawn cooldown before leaving enclosure
         */
        explicit RandomGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);

    private:
        /**
         * @brief Will return the best Move for the Random ghost.
         *
         * This Ghost picks a random direction to move. 50% chance it continues
         * in the same direction, otherwise it will pick a random direction.
         *
         * @param world World
         * @return Best Move
         */
        Moves decideNextMove(const World &world) override;
    };
}


#endif //RANDOMGHOST_H
