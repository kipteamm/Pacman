//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H

#include "../EntityModel.h"
#include "../PacmanModel.h"

#include <vector>


namespace logic {
    enum class GhostState { WAITING, EXITING, CHASING, FRIGHTENED };

    class GhostModel : public MovingEntityModel {
    public:
        explicit GhostModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed, double cooldown);
        ~GhostModel() override = default;

        void setState(GhostState state);
        [[nodiscard]] GhostState getState() const { return this->state; };

        void update(const World& world, double dt) override;
        void move(const World& world, float dt) override;

    protected:
        GhostState state;
        float defaultSpeed;

        [[nodiscard]] std::vector<Moves> getPossibleMoves(const World& world) const;
        [[nodiscard]] Moves maximizeDistance(const World& world, const PacmanModel& pacman);
        [[nodiscard]] Moves minimizeDistance(const World& world, int targetX, int targetY) const;

        virtual Moves decideNextMove(const World& world, const PacmanModel& pacman) = 0;

    private:
        double startCooldown;
        double waitingTime;

        [[nodiscard]] bool sameDirection(Moves a, Moves b) const;
        [[nodiscard]] bool isAtIntersection(const World &world) const;
    };

}


#endif //PACMAN_GHOSTMODEL_H