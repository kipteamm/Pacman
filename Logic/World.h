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

        [[nodiscard]] int getGhostExitX() const;
        [[nodiscard]] int getGhostExitY() const;

        [[nodiscard]] std::shared_ptr<PacmanModel> getPacman() const;

        [[nodiscard]] bool collidesWithWall(float x, float y, bool passDoor) const;

        void loadLevel(const std::string& filename);
        void resetLevel();
        void update(double dt);
        void handleMove(const Moves& move) const;

    private:
        float mapHeight = 20;
        float mapWidth = 20;

        float tileWidth = 16;
        float tileHeight = 16;

        int ghostExitX;
        int ghostExitY;

        float DEATH_DURATION = 1;
        bool restarting = false;
        float restartTime = 0;

        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<EntityModel>> collectibles;
        std::vector<std::shared_ptr<GhostModel>> ghosts;
        std::vector<std::shared_ptr<WallModel>> walls;

        std::shared_ptr<PacmanModel> pacman;
        int lives = 3;
    };
}



#endif //WORLD_H
