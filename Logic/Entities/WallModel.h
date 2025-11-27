//
// Created by toroe on 27/11/2025.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "EntityModel.h"


namespace logic {
    class WallModel final : public EntityModel {
    public:
        explicit WallModel(float normalizedX, float normalizedY);

        void update(double dt) override;
    };
}



#endif //PACMAN_WALLMODEL_H