//
// Created by PPetre on 26/11/2025.
//

#include "../../Logic/Entities/PacManModel.h"
#include "ConcreteFactory.h"
#include "PacManView.h"


ConcreteFactory::ConcreteFactory(std::vector<std::shared_ptr<EntityView> > &entityViews) : entityViews(entityViews) {}


std::shared_ptr<logic::EntityModel> ConcreteFactory::createPacMan(double x, double y) {
    const auto model = std::make_shared<logic::PacManModel>(x, y);
    const auto view = std::make_shared<PacManView>(model);

    model->attach(view);
    entityViews.push_back(view);

    return model;
}

