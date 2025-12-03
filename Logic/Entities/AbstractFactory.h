//
// Created by PPetre on 26/11/2025.
//

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "PacmanModel.h"
#include "WallModel.h"
#include "CoinModel.h"

#include <memory>


namespace logic {
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;

        virtual std::shared_ptr<PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) = 0;
        virtual std::shared_ptr<WallModel> createWall(float x, float y, char type) = 0;
        virtual std::shared_ptr<CoinModel> createCoin(float x, float y) = 0;
    };
}


#endif //ABSTRACTFACTORY_H
