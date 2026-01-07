//
// Created by toroe on 28/11/2025.
//

#ifndef PACMAN_COINMODEL_H
#define PACMAN_COINMODEL_H
#include "EntityModel.h"


namespace logic {

    class CoinModel final : public CollectibleEntityModel {
    public:
        /**
         * @brief Constructs a Coin model. Coins can be picked up by Pacman.
         * @param normalizedX Normalized X spawn coordinate
         * @param normalizedY Normalized Y spawn coordinate
         */
        explicit CoinModel(float normalizedX, float normalizedY);


        /**
         * @brief To be called when Pacman interacts with this Coin. Will
         * notify its observers.
         * @return Event that the World should notify its Observers about.
         */
        [[nodiscard]] Events collect() override;
    };
}


#endif //PACMAN_COINMODEL_H