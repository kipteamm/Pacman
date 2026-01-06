#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H

#include "../PacmanModel.h"
#include <vector>


namespace logic {

    enum class GhostState { WAITING, EXITING, CHASING, DEAD };


    struct PathNode {
        int x, y;
        logic::Moves firstMove;
        int parentX, parentY;
    };


    class GhostModel : public MovingEntityModel {
    public:
        explicit GhostModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);
        ~GhostModel() override = default;

        [[nodiscard]] GhostState getState() const;
        [[nodiscard]] bool isFrightened() const;
        [[nodiscard]] int getGridSpawnX() const;
        [[nodiscard]] int getGridSpawnY() const;

        void setState(GhostState state);
        void setFrightened(bool frightened, const World& world);

        [[nodiscard]] Events pacmanCollides(World& world);

        void move(const World& world, float dt) override;
        void respawn() override;

    protected:
        virtual Moves decideNextMove(const World& world, const PacmanModel& pacman) = 0;

        GhostState state;
        float defaultSpeed;

    private:
        void gridTargetReached(const World& world);

        void updateWaiting(const World& world, double dt);
        void updateExiting(const World& world);
        void updateChasing(const World& world);
        void updateDead(const World& world);

        int gridSpawnX;
        int gridSpawnY;

        bool frightened = false;

        double startCooldown;
        double waitingTime;

        std::list<Moves> cachedPath;
    };

}


#endif //PACMAN_GHOSTMODEL_H