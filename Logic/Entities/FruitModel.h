#ifndef FRUITMODEL_H
#define FRUITMODEL_H
#include "EntityModel.h"


namespace logic {

    class FruitModel final : public CollectibleEntityModel {
    public:
        /**
         * @brief Constructs a Fruit model. Fruit can be eaten by Pacman which
         * initiates the Ghosts frightened mode.
         * @param normalizedX Normalized X spawn coordinate
         * @param normalizedY Normalized Y spawn coordinate
         */
        explicit FruitModel(float normalizedX, float normalizedY);

        /**
         * @brief To be called when Pacman interacts with this Fruit. Will
         * notify its observers.
         * @return Event that the World should notify its Observers about.
         */
        [[nodiscard]] Events collect() override;
    };
}




#endif //FRUITMODEL_H
