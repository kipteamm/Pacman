//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H
#include "EntityModel.h"


namespace logic {

    enum GhostType {
        BLINKY,
        PINKY,
        INKY,
        CLYDE
    };

    enum GhostState {
        WAITING,
        CHASING,
    };

    class GhostModel final : public MovingEntityModel {
    public:
        explicit GhostModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed, GhostType type);
        ~GhostModel() override = default;

        void move(const World& world, float dt) override;
        void update(double dt) override {};

    private:
        GhostState state;
        GhostType type;
    };

}


#endif //PACMAN_GHOSTMODEL_H