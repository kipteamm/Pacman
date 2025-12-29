//
// Created by PPetre on 26/11/2025.
//

#include "ConcreteFactory.h"
#include "PacmanView.h"
#include "GhostView.h"
#include "FruitView.h"
#include "WallView.h"
#include "CoinView.h"


ConcreteFactory::ConcreteFactory(std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>& views) : entityViews(views) {}


std::shared_ptr<logic::PacmanModel> ConcreteFactory::createPacMan(float x, float y, float mapWidth, float mapHeight) {
    const auto model = std::make_shared<logic::PacmanModel>(x, y, mapWidth, mapHeight);
    const auto view = std::make_shared<PacmanView>(model);

    model->attach(view);
    entityViews.at(Layer::PACMAN).push_back(view);

    return model;
}

std::shared_ptr<logic::ChasingGhost> ConcreteFactory::createBlinky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::ChasingGhost>(x, y, mapWidth, mapHeight, 0);
    const auto view = std::make_shared<GhostView>(model, 32);

    model->attach(view);
    entityViews.at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::AmbushGhost> ConcreteFactory::createPinky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::AmbushGhost>(x, y, mapWidth, mapHeight, 0);
    const auto view = std::make_shared<GhostView>(model, 48);

    model->attach(view);
    entityViews.at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::AmbushGhost> ConcreteFactory::createInky(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::AmbushGhost>(x, y, mapWidth, mapHeight, 5);
    const auto view = std::make_shared<GhostView>(model, 64);

    model->attach(view);
    entityViews.at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::RandomGhost> ConcreteFactory::createClyde(const float x, const float y, const float mapWidth, const float mapHeight) {
    const auto model = std::make_shared<logic::RandomGhost>(x, y, mapWidth, mapHeight, 10);
    const auto view = std::make_shared<GhostView>(model, 80);

    model->attach(view);
    entityViews.at(Layer::FOREGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::WallModel> ConcreteFactory::createWall(float x, float y, char type) {
    const auto model = std::make_shared<logic::WallModel>(x, y, type == 'd');
    const auto view = std::make_shared<WallView>(model, type);

    model->attach(view);
    entityViews.at(Layer::BACKGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::CoinModel> ConcreteFactory::createCoin(float x, float y) {
    const auto model = std::make_shared<logic::CoinModel>(x, y);
    const auto view = std::make_shared<CoinView>(model);

    model->attach(view);
    entityViews.at(Layer::BACKGROUND).push_back(view);

    return model;
}

std::shared_ptr<logic::FruitModel> ConcreteFactory::createFruit(float x, float y) {
    const auto model = std::make_shared<logic::FruitModel>(x, y, 100);
    const auto view = std::make_shared<FruitView>(model);

    model->attach(view);
    entityViews.at(Layer::BACKGROUND).push_back(view);

    return model;
}


