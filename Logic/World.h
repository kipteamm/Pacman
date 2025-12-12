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

    enum WorldState { RESTARTING, FRIGHTENED, PLAYING };


    class World final : public Subject {
    public:
        explicit World(const std::shared_ptr<AbstractFactory> &factory);

        [[nodiscard]] float normalizeX(int value) const;
        [[nodiscard]] float normalizeY(int value) const;

        [[nodiscard]] float getWidth() const;
        [[nodiscard]] float getHeight() const;

        [[nodiscard]] int getGhostExitX() const;
        [[nodiscard]] int getGhostExitY() const;

        [[nodiscard]] std::shared_ptr<PacmanModel> getPacman() const;
        [[nodiscard]] unsigned int getLives() const;

        [[nodiscard]] bool collidesWithWall(float x, float y, bool passDoor) const;

        void loadLevel(const std::string& filename);
        void resetLevel();
        void resetFright();

        [[nodiscard]] Events update(double dt);

        void handleMove(const Moves& move) const;

    private:
        float mapHeight = 20;
        float mapWidth = 20;

        float tileWidth = 16;
        float tileHeight = 16;

        int ghostExitX;
        int ghostExitY;

        float DEATH_DURATION = 1;
        float FEAR_DURATION = 6;

        WorldState state;
        float timer = 0;

        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<CollectibleEntityModel>> collectibles;
        std::vector<std::shared_ptr<GhostModel>> ghosts;
        std::vector<std::shared_ptr<WallModel>> walls;

        std::shared_ptr<PacmanModel> pacman;
        unsigned int lives;
    };
}



#endif //WORLD_H
