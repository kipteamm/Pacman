//
// Created by PPetre on 26/11/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <string>
#include <vector>

#include "Entities/AbstractFactory.h"


namespace logic {

    enum Moves { UP, LEFT, RIGHT, DOWN };


    class World {
    public:
        explicit World(const std::shared_ptr<AbstractFactory> &factory);

        [[nodiscard]] float normalizeX(int value) const;
        [[nodiscard]] float normalizeY(int value) const;

        void loadLevel(const std::string& filename);
        void update(double dt);
        void handleMove(const Moves& move);

    private:
        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<EntityModel>> entities;

        float mapHeight = 20;
        float mapWidth = 20;
    };

}



#endif //WORLD_H
