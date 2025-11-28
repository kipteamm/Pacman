//
// Created by PPetre on 26/11/2025.
//

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "../../Logic/Entities/AbstractFactory.h"
#include "EntityView.h"

#include <vector>


class ConcreteFactory final : public logic::AbstractFactory {
public:
    explicit ConcreteFactory(const std::shared_ptr<Camera>& camera);

    void setViews(std::vector<std::shared_ptr<EntityView>>* views);

    std::shared_ptr<logic::PacManModel> createPacMan(float x, float y) override;
    std::shared_ptr<logic::WallModel> createWall(float x, float y, char type) override;
    std::shared_ptr<logic::CoinModel> createCoin(float x, float y) override;

private:
    std::vector<std::shared_ptr<EntityView>>* entityViews = nullptr;
    std::shared_ptr<Camera> camera;
};




#endif //CONCRETEFACTORY_H
