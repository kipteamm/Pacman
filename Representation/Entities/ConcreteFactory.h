#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include <unordered_map>

#include "../../Logic/Entities/AbstractFactory.h"
#include "EntityView.h"


enum Layer { PACMAN, FOREGROUND, BACKGROUND };


class ConcreteFactory final : public logic::AbstractFactory {
public:
    explicit ConcreteFactory(std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>& views);

    std::shared_ptr<logic::PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::ChasingGhost> createBlinky(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::AmbushGhost> createPinky(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::AmbushGhost> createInky(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::RandomGhost> createClyde(float x, float y, float mapWidth, float mapHeight) override;
    std::shared_ptr<logic::WallModel> createWall(float x, float y, char type) override;
    std::shared_ptr<logic::CoinModel> createCoin(float x, float y) override;
    std::shared_ptr<logic::FruitModel> createFruit(float x, float y) override;

private:
    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>& entityViews;
    std::vector<std::shared_ptr<EntityView>> garbageBin;
};




#endif //CONCRETEFACTORY_H
