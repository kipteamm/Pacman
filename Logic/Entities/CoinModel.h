//
// Created by toroe on 28/11/2025.
//

#ifndef PACMAN_COINMODEL_H
#define PACMAN_COINMODEL_H
#include "EntityModel.h"


namespace logic {

    class CoinModel final : public CollectibleEntityModel {
    public:
        explicit CoinModel(float normalizedX, float normalizedY);

        [[nodiscard]] Events collect() override;
    };
}


#endif //PACMAN_COINMODEL_H