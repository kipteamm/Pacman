//
// Created by PPetre on 26/11/2025.
//

#include "ConcreteFactory.h"
#include "PacmanView.h"
#include "WallView.h"
#include "CoinView.h"


ConcreteFactory::ConcreteFactory(const std::shared_ptr<Camera>& camera) : camera(camera) {}



void ConcreteFactory::setViews(std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>* views) {
    this->entityViews = views;
}


std::shared_ptr<logic::PacmanModel> ConcreteFactory::createPacMan(float x, float y, float mapWidth, float mapHeight) {
    const auto model = std::make_shared<logic::PacmanModel>(x, y, mapWidth, mapHeight, 4);
    const auto view = std::make_shared<PacmanView>(model, camera);

    model->attach(view);
    entityViews->at(Layer::PACMAN).push_back(view);

    return model;
}


std::shared_ptr<logic::WallModel> ConcreteFactory::createWall(float x, float y, char type) {
    const auto model = std::make_shared<logic::WallModel>(x, y);
    const auto view = std::make_shared<WallView>(model, camera, type);

    model->attach(view);
    entityViews->at(Layer::BACKGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::CoinModel> ConcreteFactory::createCoin(float x, float y) {
    const auto model = std::make_shared<logic::CoinModel>(x, y);
    const auto view = std::make_shared<CoinView>(model, camera);

    model->attach(view);
    entityViews->at(Layer::BACKGROUND).push_back(view);

    return model;
}


