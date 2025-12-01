//
// Created by PPetre on 26/11/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <string>
#include <vector>

#include "Entities/AbstractFactory.h"
#include "Entities/PacmanModel.h"


namespace logic {
    class World {
    public:
        explicit World(const std::shared_ptr<AbstractFactory> &factory);

        [[nodiscard]] float normalizeX(int value) const;
        [[nodiscard]] float normalizeY(int value) const;

        [[nodiscard]] float getWidth() const;
        [[nodiscard]] float getHeight() const;

        void loadLevel(const std::string& filename);
        void update(double dt);
        void handleMove(const Moves& move);
        void move(const std::shared_ptr<MovingEntityModel>& entity, float dt) const;

    private:
        float mapHeight = 20;
        float mapWidth = 20;

        float tileWidth = 16;
        float tileHeight = 16;

        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<EntityModel>> interactables;
        std::vector<std::shared_ptr<WallModel>> walls;
        std::shared_ptr<PacmanModel> pacman;
    };
}



#endif //WORLD_H
