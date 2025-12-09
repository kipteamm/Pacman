//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H
#include "EntityModel.h"


namespace logic {

    enum GhostType {
        DIRECTION_LOCKED,
        PACMAN_LOCKED,
        PACMAN_FOCUSSED,
    };

    class GhostModel final : public MovingEntityModel {
    public:
        explicit GhostModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed);
        ~GhostModel() override = default;

        void move(const World& world, float dt) override {};
        void update(double dt) override {};

    private:
        GhostType type;
    };

}


#endif //PACMAN_GHOSTMODEL_H