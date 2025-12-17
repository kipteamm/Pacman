//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H

#include "../EntityModel.h"
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

        void setState(GhostState state);
        [[nodiscard]] GhostState getState() const { return this->state; }
        [[nodiscard]] bool isFrightened() const { return this->frightened; }

        void setFrightened(bool frightened, const World& world);

        void update(const World& world, double dt);
        void move(const World& world, float dt) override;

        void respawn() override;
        void eat();

    protected:
        GhostState state;
        float defaultSpeed;

        [[nodiscard]] std::vector<Moves> getPossibleMoves(const World& world) const;
        [[nodiscard]] Moves maximizeDistance(const World& world, const PacmanModel& pacman) const;
        [[nodiscard]] Moves minimizeDistance(const World& world, int targetX, int targetY) const;

        virtual Moves decideNextMove(const World& world, const PacmanModel& pacman) = 0;
        void updateDirection(const World& world);

    private:
        int gridSpawnX;
        int gridSpawnY;

        bool frightened = false;

        double startCooldown;
        double waitingTime;

        std::list<Moves> cachedPath;
        void updatePathToSpawn(const World& world);

        [[nodiscard]] static bool sameDirection(Moves a, Moves b) ;
        [[nodiscard]] bool isAtIntersection(const World &world) const;
    };

}


#endif //PACMAN_GHOSTMODEL_H