//
// Created by toroe on 27/11/2025.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "EntityModel.h"


namespace logic {
    class WallModel final : public EntityModel {
    public:
        explicit WallModel(float normalizedX, float normalizedY, bool isDoor);

        [[nodiscard]] bool isDoor() const { return door; };

    private:
        bool door;
    };
}



#endif //PACMAN_WALLMODEL_H