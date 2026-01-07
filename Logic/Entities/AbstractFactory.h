#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "Ghosts/ChasingGhost.h"
#include "Ghosts/RandomGhost.h"
#include "Ghosts/AmbushGhost.h"
#include "PacmanModel.h"
#include "FruitModel.h"
#include "WallModel.h"
#include "CoinModel.h"


namespace logic {

    /**
     * @brief Interface for creating game entities.
     *
     * Defines the contract that allows the World to create entities without
     * depending on graphical implementations.
     */
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;

        /**
         * @brief Creates a Pacman entity.
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param mapWidth Amount of horizontal tiles
         * @param mapHeight Amount of vertical tiles
         * @return A shared pointer to the PacmanModel.
         */
        virtual std::shared_ptr<PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) = 0;

        /**
         * @brief Creates a ChasingGhost entity (Blinky's chasing personality).
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param mapWidth Amount of horizontal tiles
         * @param mapHeight Amount of vertical tiles
         * @return A shared pointer to the ChasingGhost.
         */
        virtual std::shared_ptr<ChasingGhost> createBlinky(float x, float y, float mapWidth, float mapHeight) = 0;

        /**
         * @brief Creates a AmbushGhost entity (Pinky's chasing personality).
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param mapWidth Amount of horizontal tiles
         * @param mapHeight Amount of vertical tiles
         * @return A shared pointer to the AmbushGhost.
         */
        virtual std::shared_ptr<AmbushGhost> createPinky(float x, float y, float mapWidth, float mapHeight) = 0;

        /**
         * @brief Creates a AmbushGhost entity (Inky's chasing personality).
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param mapWidth Amount of horizontal tiles
         * @param mapHeight Amount of vertical tiles
         * @return A shared pointer to the AmbushGhost.
         */
        virtual std::shared_ptr<AmbushGhost> createInky(float x, float y, float mapWidth, float mapHeight) = 0;

        /**
         * @brief Creates a RandomGhost entity (Clyde's chasing personality).
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param mapWidth Amount of horizontal tiles
         * @param mapHeight Amount of vertical tiles
         * @return A shared pointer to the RandomGhost.
         */
        virtual std::shared_ptr<RandomGhost> createClyde(float x, float y, float mapWidth, float mapHeight) = 0;

        /**
         * @brief Creates a Wall entity.
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @param type Used by to determine the sprite of the view and whether the
         * model is a door
         * @return A shared pointer to the Wall.
         */
        virtual std::shared_ptr<WallModel> createWall(float x, float y, char type) = 0;

        /**
         * @brief Creates a Coin entity.
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @return A shared pointer to the Coin.
         */
        virtual std::shared_ptr<CoinModel> createCoin(float x, float y) = 0;

        /**
         * @brief Creates a Fruit entity.
         * @param x Normalized initial x position
         * @param y Normalized initial y position
         * @return A shared pointer to the Fruit.
         */
        virtual std::shared_ptr<FruitModel> createFruit(float x, float y) = 0;
    };
}


#endif //ABSTRACTFACTORY_H
