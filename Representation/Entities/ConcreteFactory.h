//
// Created by PPetre on 26/11/2025.
//

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "../../Logic/Entities/AbstractFactory.h"
#include "EntityView.h"

#include <vector>


class ConcreteFactory : public logic::AbstractFactory {
public:
    explicit ConcreteFactory(std::vector<std::shared_ptr<EntityView>>& entityViews);

    std::shared_ptr<logic::EntityModel> createPacMan(double x, double y) override;

private:
    std::vector<std::shared_ptr<EntityView>>& entityViews;
};




#endif //CONCRETEFACTORY_H
