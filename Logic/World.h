#ifndef WORLD_H
#define WORLD_H

#include <string>

#include "Entities/AbstractFactory.h"
#include "Difficulty.h"


namespace logic {
    enum WorldState { AWAITING_MAP, RESTARTING, FRIGHTENED, PLAYING };

    constexpr float COLLISSION_EPSILON = 0.07f;

    class World final : public Subject {
    public:
        /**
         * @brief Creates a World instance. Creating an instance does nothing
         * on its own.
         * @param factory Concere implementation of AbstractFactory.
         * @param lives Amount of lives that Pacman will begin with.
         */
        explicit World(const std::shared_ptr<AbstractFactory> &factory, int lives);

        [[nodiscard]] float getWidth() const;
        [[nodiscard]] float getHeight() const;

        [[nodiscard]] int getGhostExitX() const;
        [[nodiscard]] int getGhostExitY() const;

        [[nodiscard]] std::shared_ptr<PacmanModel> getPacman() const;
        [[nodiscard]] unsigned int getLives() const;

        [[nodiscard]] std::pair<float, float> getCollissionCoordinates() const;

        [[nodiscard]] float normalizeX(int value) const;
        [[nodiscard]] float normalizeY(int value) const;

        [[nodiscard]] bool collidesWithWall(float x, float y, bool passDoor) const;

        void loadMap(const std::string& filename);

        void update(double dt);

        void handleMove(const Moves& move) const;

        void killPacman();

    private:
        static bool isColliding(const EntityModel& a, const EntityModel& b);

        void respawnEntities();
        void startFrightened();
        void endFrightened();

        void updateRestartingState(double dt);
        void updateFrightenedState(double dt);
        void updatePlayingState(double dt);

        void updateGhosts(double dt);
        void updateCollectibles();

        float mapHeight = 20;
        float mapWidth = 20;

        float tileWidth = 16;
        float tileHeight = 16;

        int ghostExitX;
        int ghostExitY;

        float DEATH_DURATION = 2;
        float FEAR_DURATION = Difficulty::getInstance().getFrightenedTime();
        float FLASH_TIMESTAMP = FEAR_DURATION - (0.4f * Difficulty::getInstance().getFlashesh());

        WorldState state;
        double timer = 0;
        bool flashing = false;

        std::pair<float, float> collissionCoordinates;

        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<CollectibleEntityModel>> collectibles;
        std::vector<std::shared_ptr<GhostModel>> ghosts;
        std::vector<std::shared_ptr<WallModel>> walls;

        std::shared_ptr<PacmanModel> pacman;
        unsigned int lives;
    };
}



#endif //WORLD_H
