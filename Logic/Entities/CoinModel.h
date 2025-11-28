//
// Created by toroe on 28/11/2025.
//

#ifndef PACMAN_COINMODEL_H
#define PACMAN_COINMODEL_H
#include "EntityModel.h"


namespace logic {

    class CoinModel final : public EntityModel {
    public:
        explicit CoinModel(float normalizedX, float normalizedY);

        void update(double dt) override {};
    };
}


#endif //PACMAN_COINMODEL_H