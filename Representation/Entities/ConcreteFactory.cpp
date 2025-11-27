//
// Created by PPetre on 26/11/2025.
//

#include "../../Logic/Entities/PacManModel.h"
#include "ConcreteFactory.h"
#include "PacManView.h"


ConcreteFactory::ConcreteFactory(const std::shared_ptr<Camera>& camera) : camera(camera) {}



void ConcreteFactory::setViews(std::vector<std::shared_ptr<EntityView>>* views) {
    this->entityViews = views;
}


std::shared_ptr<logic::EntityModel> ConcreteFactory::createPacMan(float x, float y) {
    const auto model = std::make_shared<logic::PacManModel>(x, y);
    const auto view = std::make_shared<PacManView>(model, camera);

    model->attach(view);
    entityViews->push_back(view);

    return model;
}

