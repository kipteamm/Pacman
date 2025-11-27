//
// Created by PPetre on 26/11/2025.
//

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "EntityModel.h"

#include <memory>


namespace logic {
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;

        virtual std::shared_ptr<EntityModel> createPacMan(double x, double y) = 0;
        // virtual std::shared_ptr<EntityModel> createWall(double x, double y) = 0;
        // virtual std::shared_ptr<EntityModel> createGhost(double x, double y) = 0;
        // virtual std::shared_ptr<EntityModel> createCoin(double x, double y) = 0;
        // virtual std::shared_ptr<EntityModel> createFruit(double x, double y) = 0;
    };
}


#endif //ABSTRACTFACTORY_H
