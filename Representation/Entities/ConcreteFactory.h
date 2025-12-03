//
// Created by PPetre on 26/11/2025.
//

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include <unordered_map>

#include "../../Logic/Entities/AbstractFactory.h"
#include "EntityView.h"

#include <vector>


enum Layer { PACMAN, FOREGROUND, BACKGROUND };


class ConcreteFactory final : public logic::AbstractFactory {
public:
    explicit ConcreteFactory(const std::shared_ptr<Camera>& camera);

    void setViews(std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>* views);

    std::shared_ptr<logic::PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::WallModel> createWall(float x, float y, char type) override;
    std::shared_ptr<logic::CoinModel> createCoin(float x, float y) override;

private:
    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>* entityViews;
    std::shared_ptr<Camera> camera;
};




#endif //CONCRETEFACTORY_H
