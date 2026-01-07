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
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;

        // TODO: how to document abstract factory
        virtual std::shared_ptr<PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<ChasingGhost> createBlinky(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<AmbushGhost> createPinky(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<AmbushGhost> createInky(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<RandomGhost> createClyde(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<WallModel> createWall(float x, float y, char type) = 0;
        virtual std::shared_ptr<CoinModel> createCoin(float x, float y) = 0;
        virtual std::shared_ptr<FruitModel> createFruit(float x, float y) = 0;
    };
}


#endif //ABSTRACTFACTORY_H
