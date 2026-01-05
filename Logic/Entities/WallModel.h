#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H

#include "EntityModel.h"


namespace logic {
    class WallModel final : public EntityModel {
    public:
        /**
         * @brief Constructs a WallModel instance.
         *
         * Walls are static entities and outside of being used for collission
         * detetcion don't really do anything.
         *
         * @param normalizedX Normalized x coordinate
         * @param normalizedY Normalized y coordinate
         * @param isDoor Whether this Wall may be considered a door under
         * specific conditions.
         */
        explicit WallModel(float normalizedX, float normalizedY, bool isDoor);


        /**
         * @brief Returns whether this wall piece is a door. Doors are walls
         * that can be passed through by ghosts under certain conditions.
         *
         * Doors act like a wall for Pacman and generally aswell for Ghosts.
         * I added them for the functionality of the Ghost box. Ghosts spawn in
         * this box and must leave it before they can target Pacman. While
         * Ghosts are in this "leaving" state they may consider walls that are
         * doors as non-existant/regular passage ways. Once they are outside
         * the Ghost box they will start chasing Pacman, meaning they no longer
         * consider door wall pieces as passthrough. Pacman never considers
         * them as passthrough.
         *
         * @return Whether this wall is a door
         */
        [[nodiscard]] bool isDoor() const { return door; };

    private:
        bool door;
    };
}



#endif //PACMAN_WALLMODEL_H