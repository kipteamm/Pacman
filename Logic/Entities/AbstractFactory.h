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

        virtual std::shared_ptr<EntityModel> createPacMan(float x, float y) = 0;
        virtual std::shared_ptr<EntityModel> createWall(float x, float y, char type) = 0;
    };
}


#endif //ABSTRACTFACTORY_H
