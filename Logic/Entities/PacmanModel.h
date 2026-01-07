#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacmanModel final : public MovingEntityModel {
    public:
        /**
         *
         * @param normalizedX Normalized X spawn coordinate
         * @param normalizedY Normalized Y spawn coordinate
         * @param mapWidth Width of map (in tiles)
         * @param mapHeight Width of map (in tiles)
         */
        PacmanModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight);


        /**
         * @brief Pacman works with input buffering, this function returns the
         * buffered direction.
         * @return Buffered direction
         */
        [[nodiscard]] Moves getNextDirection() const;

        /**
         * @return Whether Pacman is moving
         */
        [[nodiscard]] bool isMoving() const;


        /**
         * @brief Update the direction of Pacman. This move is buffed if Pacman
         * can not currently move in this direction. The moment it can, it will
         * @param move Direction
         */
        void setNextDirection(const Moves& move);

        /**
         * @brief This function is to be called inside the World loop. Moves
         * Pacman in its current direction. Will change that direction if
         * possible.
         * @param world World
         * @param dt Deltatime since last call
         */
        void move(const World& world, float dt) override;

        /**
         * @brief Tell Pacman to respawn. It will go back to its spawnpoint and
         * change everything back to their default values.
         */
        void respawn() override;

    private:
        /**
         * @brief This function should be called when the MovingEntity has
         * reached its targetX and targetY values (within a certain Epsilon).
         *
         * It keeps the grid coordinates up to date or detects that Pacman
         * stopped moving. Possibly teleports Pacman when he 'exits' the map
         * via tunnels/portals.
         *
         * @param world World
         * @return Whether Pacman continues down its current direction.
         */
        bool gridTargetReached(const World& world) override;

        /**
         * @brief Will simulate a move and perform a wall collission to
         * determine whether Pacman can move in the direction.
         * @param world World
         * @param direction Direction
         * @return Whether Pacman can move in the direction
         */
        [[nodiscard]] bool canMoveInDirection(const World& world, Moves direction) const;

        Moves nextDirection;
        bool moving;
    };

}

#endif // PACMANMODEL_H