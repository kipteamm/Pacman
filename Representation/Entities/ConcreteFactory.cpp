//
// Created by PPetre on 26/11/2025.
//

#include "ConcreteFactory.h"
#include "PacmanView.h"
#include "GhostView.h"
#include "WallView.h"
#include "CoinView.h"


ConcreteFactory::ConcreteFactory(const std::shared_ptr<Camera>& camera) : camera(camera), entityViews(nullptr) {}



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

std::shared_ptr<logic::ChasingGhost> ConcreteFactory::createBlinky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::ChasingGhost>(x, y, mapWidth, mapHeight, 3, 0);
    const auto view = std::make_shared<GhostView>(model, camera, 32);

    model->attach(view);
    entityViews->at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::AmbushGhost> ConcreteFactory::createPinky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::AmbushGhost>(x, y, mapWidth, mapHeight, 3, 0);
    const auto view = std::make_shared<GhostView>(model, camera, 48);

    model->attach(view);
    entityViews->at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::AmbushGhost> ConcreteFactory::createInky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::AmbushGhost>(x, y, mapWidth, mapHeight, 3, 500);
    const auto view = std::make_shared<GhostView>(model, camera, 64);

    model->attach(view);
    entityViews->at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::RandomGhost> ConcreteFactory::createClyde(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::RandomGhost>(x, y, mapWidth, mapHeight, 3, 1000);
    const auto view = std::make_shared<GhostView>(model, camera, 80);

    model->attach(view);
    entityViews->at(Layer::FOREGROUND).push_back(view);

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


